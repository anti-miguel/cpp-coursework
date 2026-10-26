#include <iostream>
#include <vector>

#include "graphs/Graph.h"
#include "maps/Map.h"
#include "trees/Tree.h"

namespace {

template<typename T>
void printTreeTraversal(const std::vector<AEDnames::NodoTree<T>*>& traversal) {
    for (const auto* node : traversal) {
        std::cout << node->dato << ' ';
    }
    std::cout << '\n';
}

template<typename T>
void printGraphPath(const std::vector<AEDnames::NodoGraph<T>*>& path) {
    for (const auto* node : path) {
        std::cout << node->dato << ' ';
    }
    std::cout << '\n';
}

}  // namespace

int main() {
    using namespace AEDnames;

    AEDTree<int> tree;
    tree.root = new NodoTree<int>(1);
    tree.root->setLeft(new NodoTree<int>(2));
    tree.root->setRight(new NodoTree<int>(3));
    tree.root->right->setLeft(new NodoTree<int>(6));
    tree.root->right->setRight(new NodoTree<int>(7));

    std::cout << "Tree height: " << tree.getHeight() << '\n';
    std::cout << "Left leaf: " << tree.getLeftLeaf()->dato << '\n';
    std::cout << "Right leaf: " << tree.getRightLeaf()->dato << '\n';
    std::cout << "DFS right-to-left without leaves: ";
    printTreeTraversal(tree.DFS());
    std::cout << "BFS right-to-left without leaves: ";
    printTreeTraversal(tree.BFS());

    NodoGraph<int> nodeA(1);
    NodoGraph<int> nodeB(2);
    NodoGraph<int> nodeC(3);
    NodoGraph<int> nodeD(4);

    nodeA.addAdj(&nodeB, 4);
    nodeA.addAdj(&nodeC, 1);
    nodeC.addAdj(&nodeB, 2);
    nodeB.addAdj(&nodeD, 1);
    nodeC.addAdj(&nodeD, 5);

    Graph<int> graph;
    graph.addNode(&nodeA);
    graph.addNode(&nodeB);
    graph.addNode(&nodeC);
    graph.addNode(&nodeD);

    std::cout << "Any path from 1 to 4: ";
    printGraphPath(graph.findPath(&nodeA, &nodeD));
    std::cout << "Minimum path from 1 to 4: ";
    printGraphPath(graph.findMinPath(&nodeA, &nodeD));

    Map<int> myMap;
    myMap.insert(42);
    myMap.insert(99);
    std::cout << "Map contains 42: " << (myMap.search(42) ? "yes" : "no") << '\n';

    delete tree.root;
    return 0;
}
