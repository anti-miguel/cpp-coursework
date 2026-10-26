#pragma once

#include <vector>

namespace AEDnames {

template<typename T>
class NodoTree;

template<typename T>
class Nodo {
private:
    T dato {};
    Nodo<T>* anterior = nullptr;
    Nodo<T>* siguiente = nullptr;

public:
    Nodo() = default;
    Nodo(const T& dato, Nodo<T>* anterior = nullptr, Nodo<T>* siguiente = nullptr)
        : dato(dato), anterior(anterior), siguiente(siguiente) {
    }

    bool operator==(const Nodo<T>& other) const {
        return dato == other.dato && anterior == other.anterior && siguiente == other.siguiente;
    }

    bool operator!=(const Nodo<T>& other) const {
        return !(*this == other);
    }

    T getDato() const;
    bool setDato(const T& nuevoDato);
    void setAnterior(Nodo<T>* nuevoAnterior);
    Nodo<T>* getAnterior() const;
    void setSiguiente(Nodo<T>* nuevoSiguiente);
    Nodo<T>* getSiguiente() const;
};

template<typename T>
class NodoTree {
public:
    T dato {};
    NodoTree<T>* left = nullptr;
    NodoTree<T>* right = nullptr;
    NodoTree<T>* parent = nullptr;

    NodoTree() = default;
    explicit NodoTree(
        const T& dato,
        NodoTree<T>* leftChild = nullptr,
        NodoTree<T>* rightChild = nullptr,
        NodoTree<T>* parentNode = nullptr
    );
    NodoTree(const NodoTree<T>& other) = delete;
    NodoTree<T>& operator=(const NodoTree<T>& other) = delete;
    ~NodoTree();

    bool isRoot() const;
    bool isLeaf() const;
    void setLeft(NodoTree<T>* child);
    void setRight(NodoTree<T>* child);
    unsigned int getHeight() const;
    NodoTree<T>* getLeftLeaf();
    const NodoTree<T>* getLeftLeaf() const;
    NodoTree<T>* getRightLeaf();
    const NodoTree<T>* getRightLeaf() const;
    NodoTree<T>* getRoot();
    const NodoTree<T>* getRoot() const;
};

template<typename T>
class AEDTree {
public:
    NodoTree<T>* root = nullptr;

    AEDTree() = default;
    explicit AEDTree(NodoTree<T>* rootNode) : root(rootNode) {
    }

    unsigned int getHeight() const;
    NodoTree<T>* getLeftLeaf();
    const NodoTree<T>* getLeftLeaf() const;
    NodoTree<T>* getRightLeaf();
    const NodoTree<T>* getRightLeaf() const;
    NodoTree<T>* getRoot();
    const NodoTree<T>* getRoot() const;
    std::vector<NodoTree<T>*> DFS() const;
    std::vector<NodoTree<T>*> BFS() const;

private:
    static void dfsRightToLeftWithoutLeaves(NodoTree<T>* node, std::vector<NodoTree<T>*>& recorrido);
};

}  // namespace AEDnames

#include "Tree.cpp"
