#pragma once

#include <set>
#include <string>
using namespace std;

class Node {
    string name;
    set<Node *> neighbours;
public:
    Node(const string& aname) : name(aname) {};
    string& getName() { return name; }
    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);

    auto begin() const { return neighbours.begin(); };
    auto end() const { return neighbours.end(); };
};