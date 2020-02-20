#include "node.h"

void Node::addNeighbour(Node * node) {
    neighbours.insert(node);
}

void Node::removeNeighbour(Node * node) {
    auto foundNode = neighbours.find(node);
    if (foundNode == neighbours.end()) {
        return;
    }
    neighbours.erase(node);
}