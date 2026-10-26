#include "ConcurrenciaProfe.h"

#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>

std::mutex mutex_cout;

class Msg {
public:
    int src;
    int dst;
    int value;
    std::string msg;

    Msg(int _src, int _dst, int _value, std::string message)
        : src(_src), dst(_dst), value(_value), msg(std::move(message)) {
    }

    virtual ~Msg() = default;
};

std::ostream& operator<<(std::ostream& os, const Msg& m) {
    os << "Msg from " << m.src << " to " << m.dst
       << " with value " << m.value
       << " and content: " << m.msg << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Msg* m) {
    if (m == nullptr) {
        os << "Msg pointer is nullptr" << std::endl;
    } else {
        os << *m;
    }
    return os;
}

class ThWrapper;

class Params {
public:
    int k;
    bool keepwork;
    bool blocking;
    Msg* m;

    Params(int _k, bool _blocking, Msg* _m)
        : k(_k), keepwork(true), blocking(_blocking), m(_m) {
    }

    virtual ~Params() = default;
};

std::ostream& operator<<(std::ostream& os, const Params& p) {
    if (p.m == nullptr) {
        os << "Params: k = " << p.k << " m = nullptr" << std::endl;
    } else {
        os << "Params: k = " << p.k << " m = " << *p.m << std::endl;
    }
    return os;
}

class MsgQueue {
private:
    std::deque<Msg*>* q;
    std::mutex mtx_q;
    std::condition_variable cond_q_nonempty;

public:
    MsgQueue() {
        q = new std::deque<Msg*>();
    }

    ~MsgQueue() {
        for (auto* m : *q) {
            delete m;
        }
        delete q;
    }

    MsgQueue& operator=(const MsgQueue& other) {
        if (this == &other) {
            return *this;
        }

        q->clear();
        q = new std::deque<Msg*>(*other.q);
        return *this;
    }

    bool push(Msg* m) {
        if (m == nullptr) {
            return false;
        }

        std::unique_lock<std::mutex> unique_q(mtx_q);
        q->push_back(m);
        cond_q_nonempty.notify_all();
        return true;
    }

    Msg* pop() {
        std::unique_lock<std::mutex> unique_q(mtx_q);
        cond_q_nonempty.wait(unique_q, [this] { return !q->empty(); });
        Msg* m = q->front();
        q->pop_front();
        return m;
    }

    Msg* try_pop() {
        std::unique_lock<std::mutex> unique_q(mtx_q);
        if (q->empty()) {
            return nullptr;
        }

        Msg* m = q->front();
        q->pop_front();
        return m;
    }
};

class ThWrapper {
protected:
    std::thread t;
    MsgQueue queue;

    virtual void work(Params* p) {
        while (p->keepwork) {
            if (!p->blocking) {
                p->m = queue.try_pop();
            } else {
                p->m = queue.pop();
            }

            this->criticalSection(p);
        }

        this->wrapUp(p);
        delete p;
    }

    virtual void criticalSection(Params* p) = 0;
    virtual void wrapUp(Params* p) = 0;

public:
    unsigned int id;

    explicit ThWrapper(unsigned int _id) : id(_id) {
    }

    virtual ~ThWrapper() {
        if (t.joinable()) {
            t.join();
        }
    }

    virtual void run(Params* p) = 0;

    void pushMsg(Msg* m) {
        queue.push(m);
    }
};
