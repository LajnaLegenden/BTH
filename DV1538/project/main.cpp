#include "Graph.h"
#include <iostream>
#include <queue>
//
// Created by lajna on 2022-05-18.
//

using namespace std;


int main() {
    Graph g("graph09.txt");
    cout << g.toGraphviz() << endl;
    vector<pair<int, string>>  shortestPath;
    string from = "S";
    string to = "A";
    int cost = g.shortestPathFrom(from,to, shortestPath);

    //print shortest path
    for(auto &p : shortestPath) {
        cout << p.second << " " << p.first << endl;
    }

    //print node count
    cout << "Nodes " << g.nrOfNodes() << endl;
    cout << "Edges " << g.nrOfEdges() << endl;
    cout << "Cost " << cost << endl;



    return 0;
}

