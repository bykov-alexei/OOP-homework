#include "graph.h"

void Graph::addNode(Node* node) {
    nodes.insert(node);
}

void Graph::removeNode(Node* node) {
    auto foundNode = nodes.find(node);
    if (foundNode == nodes.end()) {
        return;
    }
    nodes.erase(node);
}

void Graph::addEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end()) {
        return;
    }
    if (nodes.find(end) == nodes.end()) {
        return;
    }
    begin->addNeighbour(end);
}

void Graph::removeEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end()) {
        return;
    }
    if (nodes.find(end) == nodes.end()) {
        return;
    }
    begin->removeNeighbour(end);
}