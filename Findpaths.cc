// CSCI 335 Homework #6
// Shihab Islam

#include <iostream>
#include <vector>
#include <string>
#include "graph.h"

using namespace std;


int findPathDriver(int argc, char** argv) {

    Graph test;
    test.CreateGraph(argv[1]);
    int nodeinput = stoi(argv[2]);
    test.dijkstra(nodeinput);
    test.printDijkstra();

    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <GRAPH_FILE>" << "<STARTING_VERTEX>" << endl;
        return 0;
    }

   findPathDriver(argc, argv);

    return 0;
}