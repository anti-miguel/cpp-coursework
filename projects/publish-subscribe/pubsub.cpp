#include <algorithm>
#include <chrono>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "msgsbase.cpp"

class PubSubMsg : public Msg {
public:
    enum class Operation {
        PUBLISH_REQUEST,
        PUBLISH,
        SUBSCRIBE,
        UNSUBSCRIBE,
        SHUTDOWN
    };

    Operation op;
    std::string topic;

    PubSubMsg(
        int _src,
        int _dst,
        int _value,
        const std::string& message,
        Operation _op,
        const std::string& _topic
    ) : Msg(_src, _dst, _value, message), op(_op), topic(_topic) {
    }
};

class Broker : public ThWrapper {
private:
    std::map<std::string, std::list<unsigned int>> suscripciones;
    std::map<unsigned int, ThWrapper*> conexiones;
    int receivedPublications = 0;
    int forwardedMessages = 0;

    void forwardToSubscribers(const PubSubMsg& msg) {
        const auto topicIt = suscripciones.find(msg.topic);
        if (topicIt == suscripciones.end()) {
            return;
        }

        for (unsigned int suscriberId : topicIt->second) {
            const auto connectionIt = conexiones.find(suscriberId);
            if (connectionIt == conexiones.end() || connectionIt->second == nullptr) {
                continue;
            }

            connectionIt->second->pushMsg(
                new PubSubMsg(
                    msg.src,
                    static_cast<int>(suscriberId),
                    msg.value,
                    msg.msg,
                    PubSubMsg::Operation::PUBLISH,
                    msg.topic
                )
            );
            ++forwardedMessages;
        }
    }

protected:
    void criticalSection(Params* p) override {
        if (p == nullptr || p->m == nullptr) {
            return;
        }

        PubSubMsg* msg = static_cast<PubSubMsg*>(p->m);

        switch (msg->op) {
        case PubSubMsg::Operation::SUBSCRIBE:
            addSuscriber(msg->topic, static_cast<unsigned int>(msg->src));
            break;
        case PubSubMsg::Operation::UNSUBSCRIBE:
            removeSuscriber(msg->topic, static_cast<unsigned int>(msg->src));
            break;
        case PubSubMsg::Operation::PUBLISH:
            ++receivedPublications;
            forwardToSubscribers(*msg);
            break;
        case PubSubMsg::Operation::SHUTDOWN:
            p->keepwork = false;
            break;
        case PubSubMsg::Operation::PUBLISH_REQUEST:
            break;
        }

        delete msg;
        p->m = nullptr;
    }

    void wrapUp(Params* p) override {
        (void)p;
        std::lock_guard<std::mutex> lock(mutex_cout);
        std::cout << "[Broker] publications received: " << receivedPublications << std::endl;
        std::cout << "[Broker] messages forwarded: " << forwardedMessages << std::endl;
        for (const auto& entry : suscripciones) {
            std::cout << "[Broker] topic " << entry.first << " -> ";
            for (unsigned int suscriberId : entry.second) {
                std::cout << suscriberId << ' ';
            }
            std::cout << std::endl;
        }
    }

public:
    explicit Broker(unsigned int id) : ThWrapper(id) {
    }

    void addTopic(const std::string& topic) {
        if (suscripciones.find(topic) == suscripciones.end()) {
            suscripciones.emplace(topic, std::list<unsigned int>{});
        }
    }

    void removeTopic(const std::string& topic) {
        suscripciones.erase(topic);
    }

    void addSuscriber(const std::string& topic, unsigned int suscriberId) {
        auto& interested = suscripciones[topic];
        const bool alreadySubscribed =
            std::find(interested.begin(), interested.end(), suscriberId) != interested.end();

        if (!alreadySubscribed) {
            interested.push_back(suscriberId);
        }
    }

    void removeSuscriber(const std::string& topic, unsigned int suscriberId) {
        auto topicIt = suscripciones.find(topic);
        if (topicIt == suscripciones.end()) {
            return;
        }

        topicIt->second.remove(suscriberId);
    }

    void addConnection(unsigned int connectionId, ThWrapper* connection) {
        if (connection != nullptr) {
            conexiones[connectionId] = connection;
        }
    }

    void removeConnection(unsigned int connectionId) {
        conexiones.erase(connectionId);
    }

    void stop() {
        pushMsg(
            new PubSubMsg(
                static_cast<int>(id),
                static_cast<int>(id),
                0,
                "broker shutdown",
                PubSubMsg::Operation::SHUTDOWN,
                ""
            )
        );
    }

    void run(Params* p) override {
        t = std::thread(&Broker::work, this, p);
    }
};

class Publisher : public ThWrapper {
private:
    Broker* broker;
    std::vector<std::string> topics;
    int sentCount = 0;
    std::size_t nextTopicIndex = 0;

    std::string nextTopic() {
        if (topics.empty()) {
            return "";
        }

        const std::string topic = topics[nextTopicIndex % topics.size()];
        ++nextTopicIndex;
        return topic;
    }

protected:
    void criticalSection(Params* p) override {
        if (p == nullptr || p->m == nullptr) {
            return;
        }

        PubSubMsg* msg = static_cast<PubSubMsg*>(p->m);

        switch (msg->op) {
        case PubSubMsg::Operation::PUBLISH_REQUEST:
            for (int i = 0; i < msg->value; ++i) {
                const std::string topic = nextTopic();
                if (topic.empty()) {
                    break;
                }

                broker->pushMsg(
                    new PubSubMsg(
                        static_cast<int>(id),
                        static_cast<int>(broker->id),
                        i + 1,
                        "publisher " + std::to_string(id) + " message " + std::to_string(sentCount + 1),
                        PubSubMsg::Operation::PUBLISH,
                        topic
                    )
                );
                ++sentCount;
            }
            break;
        case PubSubMsg::Operation::SHUTDOWN:
            p->keepwork = false;
            break;
        case PubSubMsg::Operation::PUBLISH:
        case PubSubMsg::Operation::SUBSCRIBE:
        case PubSubMsg::Operation::UNSUBSCRIBE:
            break;
        }

        delete msg;
        p->m = nullptr;
    }

    void wrapUp(Params* p) override {
        (void)p;
        std::lock_guard<std::mutex> lock(mutex_cout);
        std::cout << "[Publisher " << id << "] sent " << sentCount << " messages" << std::endl;
    }

public:
    Publisher(unsigned int id, Broker* _broker, const std::vector<std::string>& _topics)
        : ThWrapper(id), broker(_broker), topics(_topics) {
    }

    void addTopic(const std::string& topic) {
        topics.push_back(topic);
    }

    void publish(int numberOfMessages) {
        pushMsg(
            new PubSubMsg(
                static_cast<int>(id),
                static_cast<int>(id),
                numberOfMessages,
                "publish request",
                PubSubMsg::Operation::PUBLISH_REQUEST,
                ""
            )
        );
    }

    void stop() {
        pushMsg(
            new PubSubMsg(
                static_cast<int>(id),
                static_cast<int>(id),
                0,
                "publisher shutdown",
                PubSubMsg::Operation::SHUTDOWN,
                ""
            )
        );
    }

    void run(Params* p) override {
        t = std::thread(&Publisher::work, this, p);
    }
};

class Suscriber : public ThWrapper {
private:
    Broker* broker;
    int received = 0;

protected:
    void criticalSection(Params* p) override {
        if (p == nullptr || p->m == nullptr) {
            return;
        }

        PubSubMsg* msg = static_cast<PubSubMsg*>(p->m);

        switch (msg->op) {
        case PubSubMsg::Operation::PUBLISH:
            ++received;
            {
                std::lock_guard<std::mutex> lock(mutex_cout);
                std::cout << "[Suscriber " << id << "] topic=" << msg->topic
                          << " content=" << msg->msg << std::endl;
            }
            break;
        case PubSubMsg::Operation::SHUTDOWN:
            p->keepwork = false;
            break;
        case PubSubMsg::Operation::PUBLISH_REQUEST:
        case PubSubMsg::Operation::SUBSCRIBE:
        case PubSubMsg::Operation::UNSUBSCRIBE:
            break;
        }

        delete msg;
        p->m = nullptr;
    }

    void wrapUp(Params* p) override {
        (void)p;
        std::lock_guard<std::mutex> lock(mutex_cout);
        std::cout << "[Suscriber " << id << "] received " << received << " messages" << std::endl;
    }

public:
    Suscriber(unsigned int id, Broker* _broker) : ThWrapper(id), broker(_broker) {
    }

    void suscribe(const std::vector<std::string>& topics) {
        for (const std::string& topic : topics) {
            broker->pushMsg(
                new PubSubMsg(
                    static_cast<int>(id),
                    static_cast<int>(broker->id),
                    0,
                    "subscribe",
                    PubSubMsg::Operation::SUBSCRIBE,
                    topic
                )
            );
        }
    }

    void suscribe(const std::string& topic) {
        broker->pushMsg(
            new PubSubMsg(
                static_cast<int>(id),
                static_cast<int>(broker->id),
                0,
                "subscribe",
                PubSubMsg::Operation::SUBSCRIBE,
                topic
            )
        );
    }

    void unsuscribe(const std::string& topic) {
        broker->pushMsg(
            new PubSubMsg(
                static_cast<int>(id),
                static_cast<int>(broker->id),
                0,
                "unsubscribe",
                PubSubMsg::Operation::UNSUBSCRIBE,
                topic
            )
        );
    }

    void stop() {
        pushMsg(
            new PubSubMsg(
                static_cast<int>(id),
                static_cast<int>(id),
                0,
                "suscriber shutdown",
                PubSubMsg::Operation::SHUTDOWN,
                ""
            )
        );
    }

    void run(Params* p) override {
        t = std::thread(&Suscriber::work, this, p);
    }
};

int main() {
    std::cout << "Publisher Suscriber demo" << std::endl;

    Broker broker(0);
    Publisher publisherNews(1, &broker, {"news", "sports"});
    Publisher publisherTech(2, &broker, {"tech"});
    Suscriber suscriberA(3, &broker);
    Suscriber suscriberB(4, &broker);

    broker.addConnection(publisherNews.id, &publisherNews);
    broker.addConnection(publisherTech.id, &publisherTech);
    broker.addConnection(suscriberA.id, &suscriberA);
    broker.addConnection(suscriberB.id, &suscriberB);

    broker.addTopic("news");
    broker.addTopic("sports");
    broker.addTopic("tech");

    broker.run(new Params(0, true, nullptr));
    publisherNews.run(new Params(0, true, nullptr));
    publisherTech.run(new Params(0, true, nullptr));
    suscriberA.run(new Params(0, true, nullptr));
    suscriberB.run(new Params(0, true, nullptr));

    suscriberA.suscribe(std::vector<std::string>{"news", "tech"});
    suscriberB.suscribe(std::vector<std::string>{"sports", "news"});

    publisherNews.publish(6);
    publisherTech.publish(3);

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    publisherNews.stop();
    publisherTech.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    broker.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    suscriberA.stop();
    suscriberB.stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    return 0;
}
