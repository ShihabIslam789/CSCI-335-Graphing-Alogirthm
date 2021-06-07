#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH
#include "binary_heap.h"
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <cmath>
#include <cfloat>
using namespace std;


class Graph {
public:

    //Vertex struct
    struct Vertex {
        map<int, double> vertices;     //the map of vertices 
        int node;                      //the node that it is connected to
        double distance;
        list<int> path;             //path to the node

        bool operator<(const Vertex& rhs) const {
            if (distance == rhs.distance) {
                return (node < rhs.node);
            }
            return (distance < rhs.distance);
        }

    };


    Graph() {
        size = 0;
    }

    // func: this function opens the textfile, and parse through it by space.
    void CreateGraph(string filename) {
        string inputline;   //line in the text file
        string weight;      // weight of the edge
        string vecsize;     //first line in text file
        int nodeval;        
        string nodestr;     //string variable read by the line
        double weightval;   
        ifstream fin(filename);
        getline(fin, vecsize);
        size = stoi(vecsize);
        while (getline(fin, inputline)) {
            Vertex temp;        
            stringstream strstream(inputline);
            getline(strstream, nodestr, ' ');
            nodeval = stoi(nodestr);
            temp.node = nodeval;
            while (getline(strstream, nodestr, ' ')) {   
                getline(strstream, weight, ' ');
                nodeval = stoi(nodestr);
                weightval = stod(weight);
                temp.vertices[nodeval] = weightval;
            }
            adj_list.push_back(temp);
        }

    }


    // func: this function will iterate through the adjacency list and print out graph
    void PrintGraph() {
        for (list<Vertex>::iterator it = adj_list.begin(); it != adj_list.end(); it++) {
            cout << it->node;
            for (map<int, double>::iterator i = it->vertices.begin(); i != it->vertices.end(); i++) {
                cout << " " << i->first << " " << i->second;
            }
            cout << endl;
        }
    }


    // filename: the  file that we are getting from the terminal
    // func: this function will open the text file and iterate through our list of Vertices, and 
    //  iterate through the maps  to see node connections
    void isConnected(string filename) {
        int node1;                                  //storing  first vertex
        int node2;                                  //vertex  checking connections 
        string inputline;
        string nodestr;
        ifstream fin(filename);
        while (getline(fin, inputline)) {
            stringstream strstream(inputline);
            getline(strstream, nodestr, ' ');          //get the first node from  text file
            node1 = stoi(nodestr);
            getline(strstream, nodestr, ' ');         //next node in  text file
            node2 = stoi(nodestr);
            list<Vertex>::iterator it = adj_list.begin();
            advance(it, node1 - 1);                    
            if (it->vertices[node2] == 0.0) {
                cout << node1 << " " << node2 << ": not_connected" << endl;
            }
            else {
                cout << node1 << " " << node2 << ": connected " << it->vertices[node2] << endl;
            }
        }
    }


    // node: the node  looking for connections 
    // func: this function will performs  dijkstra algorithm on the nodes in the graph
    //  and finds the shortest possible path to node thats passed to the function
    void dijkstra(int node) {
        list<Vertex>::iterator first = adj_list.begin();
        advance(first, node - 1);
        list<Vertex>::iterator itr;

        //setting the distance of each node in the graph to the node passed through to infinity
        for (itr = adj_list.begin(); itr != adj_list.end(); itr++) {
            itr->distance = std::numeric_limits<double>::infinity();
        }
        itr = adj_list.begin();

     
        first->distance = 0.0;
        first->path.push_back(first->node);

        BinaryHeap<Vertex> vertexheap;
        unordered_set<int> visitednodes;
        vertexheap.insert(*first);
        Vertex current;

        while (!vertexheap.isEmpty()) {
            vertexheap.deleteMin(current);
            visitednodes.insert(current.node);
            map<int, double>::iterator itr;
            for (itr = current.vertices.begin(); itr != current.vertices.end(); itr++) {
                list<Vertex>::iterator node1 = adj_list.begin();
                advance(node1, itr->first - 1);
                Vertex& adj_node = *node1;
                //if the node is not in the unordered set of visited nodes
                if (!visitednodes.count(adj_node.node)) {
                    double potentialdistance = 0.0;     
                    potentialdistance = current.distance + current.vertices[adj_node.node];
                    //if the new distance is less than current distance, update distance variable
                    if (potentialdistance < adj_node.distance) {
                        adj_node.distance = potentialdistance;
                        adj_node.path = current.path;
                        adj_node.path.push_back(adj_node.node);
                    }
                    vertexheap.insert(adj_node);
                }
            }
        }
    }


    //func: this function prints out the results of the dijkstra algorithm,  prints
    //   the shortest path to a certain node from all other nodes in the graph
    void printDijkstra() {
        for (list<Vertex>::iterator itr = adj_list.begin(); itr != adj_list.end(); itr++) {
            cout << itr->node << ": ";
            for (auto const& i : itr->path) {
                cout << i << " ";
            }
            if (itr->distance == std::numeric_limits<double>::infinity()) {
                cout << "not_possible";
            }
            else {
                cout << "cost: " << itr->distance;
            }
            cout << endl;
        }
    }


private:
    list<Vertex> adj_list;   
    int size;
};




#endif