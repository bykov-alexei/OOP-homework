#pragma once

#include <set>
#include <string>
#include "node.h"
using namespace std;

class Graph {
    set<Node *> nodes;
public:
    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end);
    void removeEdge(Node* begin, Node* end);
    auto begin() const { return nodes.begin(); };
    auto end() const { return nodes.end(); };
};