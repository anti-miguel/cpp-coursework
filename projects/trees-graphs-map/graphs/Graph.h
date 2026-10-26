#pragma once

#include <unordered_set>
#include <vector>

namespace AEDnames {

template<typename T>
class NodoGraph;

template<typename T>
class Graph {
public:
    std::vector<NodoGraph<T>*> nodes;

    void addNode(NodoGraph<T>* node);
    std::vector<NodoGraph<T>*> findPath(NodoGraph<T>* origin, NodoGraph<T>* destination) const;
    std::vector<NodoGraph<T>*> findMinPath(NodoGraph<T>* origin, NodoGraph<T>* destination) const;

private:
    bool findPathDepthFirst(
        NodoGraph<T>* current,
        NodoGraph<T>* destination,
        std::unordered_set<NodoGraph<T>*>& visited,
        std::vector<NodoGraph<T>*>& path
    ) const;
};

}  // namespace AEDnames

#include "NodoGraph.h"
