```cpp
// Finds the shortest path between two nodes in a graph using Dijkstra's algorithm.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>

using namespace std;

typedef pair<int, string> Pair;

pair<vector<string>, int> shortest_path_dijkstra(map<string, map<string, int>>& graph, string start, string end) {
    map<string, int> distances;
    map<string, string> predecessors;

    for (auto const& [node, neighbors] : graph) {
        distances[node] = numeric_limits<int>::max();
        predecessors[node] = "";
    }

    distances[start] = 0;

    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int dist = pq.top().first;
        string current_node = pq.top().second;
        pq.pop();

        if (dist > distances[current_node]) {
            continue;
        }

        if (current_node == end) {
            break;
        }

        for (auto const& [neighbor, weight] : graph[current_node]) {
            int new_dist = dist + weight;

            if (new_dist < distances[neighbor]) {
                distances[neighbor] = new_dist;
                predecessors[neighbor] = current_node;
                pq.push({new_dist, neighbor});
            }
        }
    }

    vector<string> path;
    string current = end;
    while (current != "") {
        path.insert(path.begin(), current);
        if(predecessors[current] == "" && current != start){
            return {vector<string>(), numeric_limits<int>::max()};
        }
        current = predecessors[current];
    }

    if (distances[end] == numeric_limits<int>::max()) {
        return {vector<string>(), numeric_limits<int>::max()};
    } else {
        return {path, distances[end]};
    }
}

int main() {
    map<string, map<string, int>> graph = {
        {"A", {{"B", 5}, {"C", 2}}},
        {"B", {{"A", 5}, {"D", 1}}},
        {"C", {{"A", 2}, {"D", 8}}},
        {"D", {{"B", 1}, {"C", 8}, {"E", 7}}},
        {"E", {{"D", 7}}}
    };

    string start_node = "A";
    string end_node = "E";

    pair<vector<string>, int> result = shortest_path_dijkstra(graph, start_node, end_node);
    vector<string> path = result.first;
    int cost = result.second;

    if (!path.empty()) {
        cout << "Shortest path from " << start_node << " to " << end_node << ": ";
        for (const string& node : path) {
            cout << node << " ";
        }
        cout << endl;
        cout << "Total cost: " << cost << endl;
    } else {
        cout << "No path found from " << start_node << " to " << end_node << endl;
    }

    return 0;
}
```