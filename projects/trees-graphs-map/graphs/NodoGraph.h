#pragma once

#include "Graph.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

namespace AEDnames {

template<typename T>
class NodoGraph {
public:
    T dato {};
    NodoGraph<T>* parent = nullptr;
    int distance = std::numeric_limits<int>::max();
    std::vector<std::pair<NodoGraph<T>*, int>> adjacents;

    NodoGraph() = default;
    explicit NodoGraph(const T& dato) : dato(dato) {
    }

    bool operator==(const NodoGraph<T>& other) const {
        return dato == other.dato;
    }

    bool operator<(const NodoGraph<T>& other) const {
        return dato < other.dato;
    }

    void addAdj(NodoGraph<T>* adj, int weight);
    void removeAdj(NodoGraph<T>* adj);
};

template<typename T>
void NodoGraph<T>::addAdj(NodoGraph<T>* adj, int weight) {
    if (adj != nullptr) {
        adjacents.push_back({adj, weight});
    }
}

template<typename T>
void NodoGraph<T>::removeAdj(NodoGraph<T>* adj) {
    adjacents.erase(
        std::remove_if(
            adjacents.begin(),
            adjacents.end(),
            [adj](const std::pair<NodoGraph<T>*, int>& edge) {
                return edge.first == adj;
            }
        ),
        adjacents.end()
    );
}

template<typename T>
void Graph<T>::addNode(NodoGraph<T>* node) {
    if (node != nullptr) {
        nodes.push_back(node);
    }
}

template<typename T>
bool Graph<T>::findPathDepthFirst(
    NodoGraph<T>* current,
    NodoGraph<T>* destination,
    std::unordered_set<NodoGraph<T>*>& visited,
    std::vector<NodoGraph<T>*>& path
) const {
    if (current == nullptr || destination == nullptr) {
        return false;
    }

    if (!visited.insert(current).second) {
        return false;
    }

    path.push_back(current);
    if (current == destination) {
        return true;
    }

    for (const auto& edge : current->adjacents) {
        if (findPathDepthFirst(edge.first, destination, visited, path)) {
            return true;
        }
    }

    path.pop_back();
    return false;
}

template<typename T>
std::vector<NodoGraph<T>*> Graph<T>::findPath(NodoGraph<T>* origin, NodoGraph<T>* destination) const {
    std::vector<NodoGraph<T>*> path;
    std::unordered_set<NodoGraph<T>*> visited;

    if (findPathDepthFirst(origin, destination, visited, path)) {
        return path;
    }

    return {};
}

template<typename T>
std::vector<NodoGraph<T>*> Graph<T>::findMinPath(NodoGraph<T>* origin, NodoGraph<T>* destination) const {
    if (origin == nullptr || destination == nullptr) {
        return {};
    }

    const int infinity = std::numeric_limits<int>::max();
    std::vector<NodoGraph<T>*> knownNodes = nodes;

    if (std::find(knownNodes.begin(), knownNodes.end(), origin) == knownNodes.end()) {
        knownNodes.push_back(origin);
    }
    if (std::find(knownNodes.begin(), knownNodes.end(), destination) == knownNodes.end()) {
        knownNodes.push_back(destination);
    }

    for (NodoGraph<T>* node : knownNodes) {
        if (node != nullptr) {
            node->distance = infinity;
            node->parent = nullptr;
        }
    }

    using QueueEntry = std::pair<int, NodoGraph<T>*>;
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> pending;

    origin->distance = 0;
    pending.push({0, origin});

    while (!pending.empty()) {
        const auto [currentDistance, current] = pending.top();
        pending.pop();

        if (current == nullptr || currentDistance != current->distance) {
            continue;
        }

        if (current == destination) {
            break;
        }

        for (const auto& edge : current->adjacents) {
            NodoGraph<T>* next = edge.first;
            const int weight = edge.second;

            if (next == nullptr || current->distance == infinity) {
                continue;
            }

            if (current->distance + weight < next->distance) {
                next->distance = current->distance + weight;
                next->parent = current;
                pending.push({next->distance, next});
            }
        }
    }

    if (destination->distance == infinity) {
        return {};
    }

    std::vector<NodoGraph<T>*> path;
    for (NodoGraph<T>* current = destination; current != nullptr; current = current->parent) {
        path.push_back(current);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

}  // namespace AEDnames
