```cpp
// Finds the shortest paths from a source node to all other nodes in a graph using Dijkstra's algorithm with a priority queue.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <random>
#include <algorithm>
#include <set>

using namespace std;

class Graph {
public:
    Graph() {}

    void add_node(int node) {
        if (graph.find(node) == graph.end()) {
            graph[node] = {};
        }
    }

    void add_edge(int node1, int node2, int weight) {
        add_node(node1);
        add_node(node2);
        graph[node1][node2] = weight;
        graph[node2][node1] = weight;
    }

    pair<unordered_map<int, int>, unordered_map<int, int>> dijkstra(int start_node) {
        if (graph.find(start_node) == graph.end()) {
            return { {}, {} };
        }

        unordered_map<int, int> distances;
        unordered_map<int, int> predecessors;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priority_queue;

        for (auto const& [node, neighbors] : graph) {
            distances[node] = numeric_limits<int>::max();
            predecessors[node] = -1;
        }

        distances[start_node] = 0;
        priority_queue.push({ 0, start_node });

        while (!priority_queue.empty()) {
            int dist = priority_queue.top().first;
            int current_node = priority_queue.top().second;
            priority_queue.pop();

            if (dist > distances[current_node]) continue;

            for (auto const& [neighbor, weight] : graph[current_node]) {
                int new_dist = dist + weight;
                if (new_dist < distances[neighbor]) {
                    distances[neighbor] = new_dist;
                    predecessors[neighbor] = current_node;
                    priority_queue.push({ new_dist, neighbor });
                }
            }
        }

        return { distances, predecessors };
    }

    void generate_random_connected_graph(int num_nodes, double edge_density) {
        if (num_nodes <= 0) return;

        vector<int> nodes(num_nodes);
        for (int i = 0; i < num_nodes; ++i) {
            nodes[i] = i;
        }

        for (int i = 0; i < num_nodes - 1; ++i) {
            add_edge(nodes[i], nodes[i + 1], random_weight());
        }

        int num_edges = static_cast<int>(edge_density * num_nodes * (num_nodes - 1) / 2);
        set<pair<int, int>> existing_edges;

        for (auto const& [node1, neighbors] : graph) {
            for (auto const& [node2, weight] : neighbors) {
                existing_edges.insert({ min(node1, node2), max(node1, node2) });
            }
        }


        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, num_nodes - 1);


        while (existing_edges.size() < num_edges) {
            int node1 = distrib(gen);
            int node2 = distrib(gen);

            if (node1 != node2) {
                int min_node = min(node1, node2);
                int max_node = max(node1, node2);
                pair<int, int> edge = { min_node, max_node };

                if (existing_edges.find(edge) == existing_edges.end()) {
                    add_edge(node1, node2, random_weight());
                    existing_edges.insert(edge);
                }
            }
        }
    }

private:
    unordered_map<int, unordered_map<int, int>> graph;

    int random_weight() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10);
        return distrib(gen);
    }
};

vector<int> reconstruct_path(unordered_map<int, int>& predecessors, int start_node, int end_node) {
    vector<int> path;
    int current_node = end_node;

    while (current_node != -1) {
        path.insert(path.begin(), current_node);
        current_node = predecessors[current_node];
    }

    if (path.empty() || path[0] != start_node) {
        return {};
    }

    return path;
}

int main() {
    Graph graph;

    graph.generate_random_connected_graph(10, 0.4);


    int start_node = 0;
    int end_node = 5;

    auto [distances, predecessors] = graph.dijkstra(start_node);

    if (!distances.empty()) {
        cout << "Shortest distances from node " << start_node << ":\n";
        for (auto const& [node, dist] : distances) {
            cout << "Node " << node << ": " << dist << "\n";
        }

        cout << "Predecessors:\n";
        for (auto const& [node, pred] : predecessors) {
            cout << "Node " << node << ": " << pred << "\n";
        }

        vector<int> path = reconstruct_path(predecessors, start_node, end_node);
        if (!path.empty()) {
            cout << "Shortest path from " << start_node << " to " << end_node << ": ";
            for (int node : path) {
                cout << node << " ";
            }
            cout << "\n";
        }
        else {
            cout << "No path found from " << start_node << " to " << end_node << "\n";
        }
    }
    else {
        cout << "Node " << start_node << " not found in the graph.\n";
    }

    return 0;
}
```