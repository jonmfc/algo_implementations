```cpp
// This program finds the shortest path between two nodes in a graph using Dijkstra's algorithm.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <string>

using namespace std;

pair<vector<string>, double> find_shortest_path(const unordered_map<string, unordered_map<string, double>>& graph, const string& start, const string& end) {
    unordered_map<string, double> distances;
    unordered_map<string, string> previous;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

    for (const auto& node : graph) {
        distances[node.first] = numeric_limits<double>::infinity();
    }
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        double dist = pq.top().first;
        string current_node = pq.top().second;
        pq.pop();

        if (dist > distances[current_node]) {
            continue;
        }

        if (current_node == end) break;

        for (const auto& neighbor : graph.at(current_node)) {
            string next_node = neighbor.first;
            double weight = neighbor.second;
            double new_distance = distances[current_node] + weight;

            if (new_distance < distances[next_node]) {
                distances[next_node] = new_distance;
                previous[next_node] = current_node;
                pq.push({new_distance, next_node});
            }
        }
    }

    vector<string> path;
    string current = end;
    while (previous.count(current)) {
        path.insert(path.begin(), current);
        current = previous[current];
    }
    if(current != start)
        return {vector<string>(), numeric_limits<double>::infinity()};
    else
        path.insert(path.begin(), start);

    if (distances[end] == numeric_limits<double>::infinity()) {
        return {vector<string>(), numeric_limits<double>::infinity()};
    }

    return {path, distances[end]};
}

void test_shortest_path() {
    unordered_map<string, unordered_map<string, double>> graph1 = {
        {"A", {{"B", 5}, {"C", 2}}},
        {"B", {{"A", 5}, {"D", 1}, {"E", 4}}},
        {"C", {{"A", 2}, {"E", 6}}},
        {"D", {{"B", 1}}},
        {"E", {{"B", 4}, {"C", 6}}}
    };

    cout << "Graph 1:" << endl;
    auto result = find_shortest_path(graph1, "A", "D");
    cout << "Shortest path from A to D: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    result = find_shortest_path(graph1, "A", "E");
    cout << "Shortest path from A to E: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    result = find_shortest_path(graph1, "D", "A");
    cout << "Shortest path from D to A: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    unordered_map<string, unordered_map<string, double>> graph2 = {
        {"A", {{"B", 1}}},
        {"B", {{"C", 1}}},
        {"C", {{"D", 1}}},
        {"E", {}}
    };

    cout << "\nGraph 2:" << endl;
    result = find_shortest_path(graph2, "A", "D");
    cout << "Shortest path from A to D: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    result = find_shortest_path(graph2, "A", "E");
    cout << "Shortest path from A to E: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    result = find_shortest_path(graph2, "E", "A");
    cout << "Shortest path from E to A: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    unordered_map<string, unordered_map<string, double>> graph3 = {
        {"A", {{"B", 1}}},
        {"B", {{"A", 1}, {"C", 1}}},
        {"C", {{"B", 1}, {"D", 1}}},
        {"D", {{"C", 1}, {"E", 1}}},
        {"E", {{"D", 1}, {"F", 1}}},
        {"F", {{"E", 1}}}
    };

    cout << "\nGraph 3 (Symmetric Graph):" << endl;
    result = find_shortest_path(graph3, "A", "F");
    cout << "Shortest path from A to F: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    unordered_map<string, unordered_map<string, double>> graph4 = {
        {"A", {}},
        {"B", {}}
    };

    cout << "\nGraph 4 (Empty Edges):" << endl;
    result = find_shortest_path(graph4, "A", "B");
    cout << "Shortest path from A to B: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;

    unordered_map<string, unordered_map<string, double>> graph5 = {
      {"A", {{"B", 10}, {"C", 3}}},
      {"B", {{"C", 1}, {"D", 2}}},
      {"C", {{"B", 4}, {"D", 8}, {"E", 2}}},
      {"D", {{"E", 7}}},
      {"E", {{"D", 9}}}
    };
    cout << "\nGraph 5:" << endl;
    result = find_shortest_path(graph5, "A", "D");
    cout << "Shortest path from A to D: ";
    for (const string& node : result.first) {
        cout << node << " ";
    }
    cout << ", Cost: " << result.second << endl;
}

int main() {
    test_shortest_path();
    return 0;
}
```