#pragma once
//Linus Jansson Max Dahlgren
//lijs21 mafq21
#include <utility>
#include <vector>
#include <map>
#include <queue>
#include <climits>
#include <fstream>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;


class Graph {
    struct Node {

        string id;
        map<string, int> connections{};

        Node() : id("") {};

        Node(string id) : id(id) {};
    };

    map<string, Node> nodes;

    Node &getNode(const string &id) const;

    static vector<string> split(const string &str, char del);

    static string trim(const string &s);

public:
    Graph(const string &filename); // throws an exception as a string if not possible to open the file
    Graph(const Graph &other) = delete;

    Graph(Graph &&other) = delete;

    Graph &operator=(const Graph &other) = delete;

    Graph &operator=(Graph &&other) = delete;

    ~Graph();

    int nrOfNodes() const;

    int nrOfEdges() const;

    string toGraphviz() const;


    int shortestPathFrom(string &from, string &to, vector<std::pair<int, std::string>> &shortestPath) const;
};

//function to split string using del
vector<string> Graph::split(const string &str, char del) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while (getline(ss, tok, del)) {
        internal.push_back(trim(tok));
    }

    return internal;
}


Graph::Graph(const string &filename) {

    bool lookingForNodes = true;
    std::ifstream input;
    input.open(filename);
    if (!input.good())
        throw "Could not open file";

    for (std::string line; getline(input, line);) {
        if (line == "\r") {
            lookingForNodes = false;
            continue;
        }

        if (lookingForNodes) {
            // add new nodes
            string id = trim(line);
            nodes[id] = Node(id);
        } else {
            // add connections in format id#id#weight
            vector<string> connections = split(line, '#');
            nodes[connections[0]].connections[connections[1]] = stoi(connections[2]);
        }
    }
    input.close();
}

int Graph::nrOfNodes() const {
    return nodes.size();
}

Graph::Node &Graph::getNode(const string &id) const {
    if (nodes.find(id) == nodes.end()) {
        throw "Node not found";
    }
    return const_cast<Node &>(nodes.at(id));
}

inline std::string Graph::trim(const std::string &s) {
    auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) { return std::isspace(c); });
    auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) { return std::isspace(c); }).base();
    return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

int Graph::shortestPathFrom(std::string &from, std::string &to,
                            std::vector<std::pair<int, std::string>> &shortestPath) const {

    map<string, int> dist;                                                                          // 1
    map<string, string> prev;                                                                     // 1

  //  printf("Finding path from %s to %s\n", from.c_str(), to.c_str()); // 1

//2+V+1+log(V)+1+E( 1+1+log(V) + 1+ 1+(2*log(V))) +  3+V+6+1+V
    for (auto const &[id, node]: nodes) { //V
        dist[id] = INT_MAX; // 1
        prev[id] = ""; // 1
    }

    dist[from] = 0; // 1

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq; // 1
    pq.push(make_pair(0, from)); // log(V)
    int i = 0; // 1
    while (!pq.empty()) { // (E) 1+1+log(V) + 1+ 1+(log(V))
        i++; // 1
        auto current = pq.top(); // 1
        pq.pop();      // log(V)
        if (current.second == to) {
            break;
        }
        auto node = getNode(current.second); // 1
        for (auto const &[nextNode, weight]: node.connections) { // log(V)
            if (dist[current.second] + weight < dist[nextNode]) {
                dist[nextNode] = dist[current.second] + weight;
                prev[nextNode] = current.second;
                pq.push(make_pair(dist[nextNode], nextNode));
            }
        }
    }


    if (dist[to] != INT_MAX) { // 3+V+6+1+V
        //reconstruct path into shortestPath
        shortestPath.clear(); // 1
        string walker = to; // 1
        int totalCost = dist[to]; // 1
        while (!prev[walker].empty()) { // V + 6
            Node &prevNode = getNode(prev[walker]); // 1
            int cost = -1; // 1
            cost = prevNode.connections[walker]; // 1
            shortestPath.emplace_back(make_pair(totalCost, walker)); // 1
            totalCost -= cost; // 1
            walker = prev[walker]; // 1
        }
        shortestPath.emplace_back(make_pair(0, from)); // 1
        std::reverse(shortestPath.begin(), shortestPath.end()); // V / 2 = O(V)
    }
    return dist[to];
}

Graph::~Graph() =
default;

int Graph::nrOfEdges() const {
    int count = 0;
    for (auto const &[id, node]: nodes) {
        for (auto &connection: node.connections) {
            count++;
        }
    }

    return count;
}

string Graph::toGraphviz() const {
    string out = "digraph G {\n";
    for (auto const &[id, node]: nodes) {
        for (auto const &[nextNode, weight]: node.connections) {
            out += "\"" + node.id + "\" -> \"" + nextNode + "\" [label=\"" +
                   to_string(weight) + "\"];\n";
        }
    }

    out += "}";
    return out;
}