#include "graph.h"

Node * Graph::addNode(Node* node) {
    for (auto it = this->begin(); it != this->end(); it++) {
        if ((*it)->getName() == node->getName()) {
            return *it;
        }
    }
    nodes.insert(node);
    return node;
}

void Graph::removeNode(Node* node) {
    nodes.erase(nodes.find(node));
}

void Graph::addEdge(Node* begin, Node* end) {
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

void walk(Node * node, set<Node *> & visited) {
    visited.insert(node);
    for (auto it = node->begin(); it != node->end(); it++) {
        Node * child = *it;
        if (visited.find(child) == visited.end()) {
            walk(child, visited);
        }
    }
}

#include <iostream>
int n_components(Graph * graph) {
    set<Node *> visited = *(new set<Node *>());
    int n = 0;
    for (auto it = graph->begin(); it != graph->end(); it++) {
        Node * node = *it;
        if (visited.find(node) == visited.end()) {
            set<Node *> visited2 = *(new set<Node *>());
            walk(node, visited);
            walk(node, visited2);
            cout << "visited " << endl;
            for (auto v : visited2) {
                cout << v->getName() << " ";
            }
            cout << endl;
            n++;
        }
    }
    return n;
}