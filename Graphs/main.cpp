#include <iostream>
#include <fstream>

#include "graph.h"

int main() {
    ifstream in("TestGraph.txt");
    Graph * graph = new Graph;
    while (!in.eof()) {
        string source, target;
        in >> source >> target;
        // cout << source << " " << target << endl;
        Node * sourceNode = new Node(source);
        Node * targetNode = new Node(target); 
        sourceNode = graph->addNode(sourceNode);
        targetNode = graph->addNode(targetNode);
        graph->addEdge(sourceNode, targetNode);
    }
    int n = n_components(graph);
    cout << n << endl;
    return 0;
}
