#pragma once

#include "Tree.h"

#include <queue>

namespace AEDnames {

template<class T>
T Nodo<T>::getDato() const {
    return dato;
}

template<class T>
bool Nodo<T>::setDato(const T& nuevoDato) {
    dato = nuevoDato;
    return true;
}

template<class T>
void Nodo<T>::setAnterior(Nodo<T>* nuevoAnterior) {
    anterior = nuevoAnterior;
}

template<class T>
Nodo<T>* Nodo<T>::getAnterior() const {
    return anterior;
}

template<class T>
void Nodo<T>::setSiguiente(Nodo<T>* nuevoSiguiente) {
    siguiente = nuevoSiguiente;
}

template<class T>
Nodo<T>* Nodo<T>::getSiguiente() const {
    return siguiente;
}

template<class T>
NodoTree<T>::NodoTree(
    const T& dato,
    NodoTree<T>* leftChild,
    NodoTree<T>* rightChild,
    NodoTree<T>* parentNode
) : dato(dato), left(leftChild), right(rightChild), parent(parentNode) {
    if (left != nullptr) {
        left->parent = this;
    }
    if (right != nullptr) {
        right->parent = this;
    }
}

template<class T>
NodoTree<T>::~NodoTree() {
    delete left;
    delete right;
}

template<class T>
bool NodoTree<T>::isRoot() const {
    return parent == nullptr;
}

template<class T>
bool NodoTree<T>::isLeaf() const {
    return left == nullptr && right == nullptr;
}

template<class T>
void NodoTree<T>::setLeft(NodoTree<T>* child) {
    left = child;
    if (left != nullptr) {
        left->parent = this;
    }
}

template<class T>
void NodoTree<T>::setRight(NodoTree<T>* child) {
    right = child;
    if (right != nullptr) {
        right->parent = this;
    }
}

template<class T>
unsigned int NodoTree<T>::getHeight() const {
    const unsigned int leftHeight = (left != nullptr) ? left->getHeight() : 0U;
    const unsigned int rightHeight = (right != nullptr) ? right->getHeight() : 0U;
    return 1U + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

template<class T>
NodoTree<T>* NodoTree<T>::getLeftLeaf() {
    if (isLeaf()) {
        return this;
    }
    if (left != nullptr) {
        return left->getLeftLeaf();
    }
    return right->getLeftLeaf();
}

template<class T>
const NodoTree<T>* NodoTree<T>::getLeftLeaf() const {
    if (isLeaf()) {
        return this;
    }
    if (left != nullptr) {
        return left->getLeftLeaf();
    }
    return right->getLeftLeaf();
}

template<class T>
NodoTree<T>* NodoTree<T>::getRightLeaf() {
    if (isLeaf()) {
        return this;
    }
    if (right != nullptr) {
        return right->getRightLeaf();
    }
    return left->getRightLeaf();
}

template<class T>
const NodoTree<T>* NodoTree<T>::getRightLeaf() const {
    if (isLeaf()) {
        return this;
    }
    if (right != nullptr) {
        return right->getRightLeaf();
    }
    return left->getRightLeaf();
}

template<class T>
NodoTree<T>* NodoTree<T>::getRoot() {
    NodoTree<T>* actual = this;
    while (actual->parent != nullptr) {
        actual = actual->parent;
    }
    return actual;
}

template<class T>
const NodoTree<T>* NodoTree<T>::getRoot() const {
    const NodoTree<T>* actual = this;
    while (actual->parent != nullptr) {
        actual = actual->parent;
    }
    return actual;
}

template<class T>
unsigned int AEDTree<T>::getHeight() const {
    return (root != nullptr) ? root->getHeight() : 0U;
}

template<class T>
NodoTree<T>* AEDTree<T>::getLeftLeaf() {
    return (root != nullptr) ? root->getLeftLeaf() : nullptr;
}

template<class T>
const NodoTree<T>* AEDTree<T>::getLeftLeaf() const {
    return (root != nullptr) ? root->getLeftLeaf() : nullptr;
}

template<class T>
NodoTree<T>* AEDTree<T>::getRightLeaf() {
    return (root != nullptr) ? root->getRightLeaf() : nullptr;
}

template<class T>
const NodoTree<T>* AEDTree<T>::getRightLeaf() const {
    return (root != nullptr) ? root->getRightLeaf() : nullptr;
}

template<class T>
NodoTree<T>* AEDTree<T>::getRoot() {
    return (root != nullptr) ? root->getRoot() : nullptr;
}

template<class T>
const NodoTree<T>* AEDTree<T>::getRoot() const {
    return (root != nullptr) ? root->getRoot() : nullptr;
}

template<class T>
void AEDTree<T>::dfsRightToLeftWithoutLeaves(NodoTree<T>* node, std::vector<NodoTree<T>*>& recorrido) {
    if (node == nullptr || node->isLeaf()) {
        return;
    }

    recorrido.push_back(node);
    dfsRightToLeftWithoutLeaves(node->right, recorrido);
    dfsRightToLeftWithoutLeaves(node->left, recorrido);
}

template<class T>
std::vector<NodoTree<T>*> AEDTree<T>::DFS() const {
    std::vector<NodoTree<T>*> recorrido;
    dfsRightToLeftWithoutLeaves(root, recorrido);
    return recorrido;
}

template<class T>
std::vector<NodoTree<T>*> AEDTree<T>::BFS() const {
    std::vector<NodoTree<T>*> recorrido;
    if (root == nullptr || root->isLeaf()) {
        return recorrido;
    }

    std::queue<NodoTree<T>*> pendientes;
    pendientes.push(root);

    while (!pendientes.empty()) {
        NodoTree<T>* actual = pendientes.front();
        pendientes.pop();

        if (actual == nullptr || actual->isLeaf()) {
            continue;
        }

        recorrido.push_back(actual);

        if (actual->right != nullptr && !actual->right->isLeaf()) {
            pendientes.push(actual->right);
        }
        if (actual->left != nullptr && !actual->left->isLeaf()) {
            pendientes.push(actual->left);
        }
    }

    return recorrido;
}

}  // namespace AEDnames
