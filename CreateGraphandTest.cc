// CSCI 335 Homework #6
// Shihab Islam

#include <iostream>
#include <vector>
#include <string>
#include "graph.h"

using namespace std;

int testGraphDriver(int argc, char** argv) {


    Graph test;
    test.CreateGraph(argv[1]);
    test.isConnected(argv[2]);

    return 0;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
        return 0;
    }

    testGraphDriver(argc, argv);

    return 0;
}