```cpp
// This program finds the shortest path between two nodes in a graph using Dijkstra's algorithm.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>

using namespace std;

pair<double, vector<string>> find_shortest_path_dijkstra(
    const unordered_map<string, unordered_map<string, double>>& graph,
    const string& start_node,
    const string& end_node) {

    unordered_map<string, double> distances;
    unordered_map<string, string> predecessors;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

    for (const auto& node_pair : graph) {
        distances[node_pair.first] = numeric_limits<double>::infinity();
        predecessors[node_pair.first] = "";
    }

    distances[start_node] = 0;
    pq.push({0, start_node});

    while (!pq.empty()) {
        double current_distance = pq.top().first;
        string current_node = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_node]) {
            continue;
        }

        if (graph.find(current_node) == graph.end()) continue;

        for (const auto& neighbor_pair : graph.at(current_node)) {
            string neighbor = neighbor_pair.first;
            double weight = neighbor_pair.second;

            double new_distance = distances[current_node] + weight;

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                predecessors[neighbor] = current_node;
                pq.push({new_distance, neighbor});
            }
        }
    }

    vector<string> path;
    string current_node = end_node;

    while (current_node != "") {
        path.insert(path.begin(), current_node);
        if(predecessors[current_node]=="") break;
        current_node = predecessors[current_node];
    }

    if (distances[end_node] == numeric_limits<double>::infinity()) {
        return {numeric_limits<double>::infinity(), {}};
    } else {
        return {distances[end_node], path};
    }
}

int main() {
    unordered_map<string, unordered_map<string, double>> graph = {
        {"A", {{"B", 5}, {"C", 2}}},
        {"B", {{"A", 5}, {"D", 1}}},
        {"C", {{"A", 2}, {"D", 4}, {"E", 8}}},
        {"D", {{"B", 1}, {"C", 4}, {"E", 3}}},
        {"E", {{"C", 8}, {"D", 3}}}
    };

    string start_node = "A";
    string end_node = "E";

    auto [shortest_distance, shortest_path] = find_shortest_path_dijkstra(graph, start_node, end_node);

    if (shortest_distance == numeric_limits<double>::infinity()) {
        cout << "No path found from " << start_node << " to " << end_node << endl;
    } else {
        cout << "Shortest distance from " << start_node << " to " << end_node << ": " << shortest_distance << endl;
        cout << "Shortest path: ";
        for (const string& node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    }

    start_node = "A";
    end_node = "Z";

    tie(shortest_distance, shortest_path) = find_shortest_path_dijkstra(graph, start_node, end_node);

    if (shortest_distance == numeric_limits<double>::infinity()) {
        cout << "No path found from " << start_node << " to " << end_node << endl;
    } else {
        cout << "Shortest distance from " << start_node << " to " << end_node << ": " << shortest_distance << endl;
        cout << "Shortest path: ";
        for (const string& node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
```