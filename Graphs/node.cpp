#include "node.h"

void Node::addNeighbour(Node * node) {
    neighbours.insert(node);
}

void Node::removeNeighbour(Node * node) {
    neighbours.erase(neighbours.find(node));
}