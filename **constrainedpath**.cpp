```cpp
// Finds the shortest path between two nodes in a graph, subject to must-visit nodes and a maximum cost.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef unordered_map<string, unordered_map<string, int>> Graph;

pair<vector<string>, double> shortest_path_with_constraints(const Graph& graph, const string& start, const string& end, const unordered_set<string>& must_visit, const int& max_cost) {

    function<vector<string>(unordered_map<string, string>, string)> reconstruct_path = 
        [&](unordered_map<string, string> came_from, string current) {
        vector<string> path = {current};
        while (came_from.count(current)) {
            current = came_from[current];
            path.insert(path.begin(), current);
        }
        return path;
    };

    function<pair<unordered_map<string, double>, unordered_map<string, string>>(string, string, unordered_set<string>)> dijkstra =
        [&](string start_node, string end_node, unordered_set<string> visited) {
        unordered_map<string, double> distances;
        unordered_map<string, string> came_from;
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> priority_queue;

        for (const auto& node : graph) {
            distances[node.first] = numeric_limits<double>::infinity();
        }
        distances[start_node] = 0;
        priority_queue.push({0, start_node});

        while (!priority_queue.empty()) {
            double cost = priority_queue.top().first;
            string current_node = priority_queue.top().second;
            priority_queue.pop();

            if (current_node == end_node) {
                return make_pair(distances, came_from);
            }

            if (cost > distances[current_node]) {
                continue;
            }

            for (const auto& neighbor : graph.at(current_node)) {
                string next_node = neighbor.first;
                int edge_cost = neighbor.second;

                if (!visited.count(next_node)) {
                    double new_cost = cost + edge_cost;
                    if (new_cost < distances[next_node]) {
                        distances[next_node] = new_cost;
                        priority_queue.push({new_cost, next_node});
                        came_from[next_node] = current_node;
                    }
                }
            }
        }

        return make_pair(distances, came_from);
    };

    function<pair<vector<string>, double>()> find_optimal_path = [&]() {
        double min_cost = numeric_limits<double>::infinity();
        vector<string> best_path;

        vector<string> must_visit_vec(must_visit.begin(), must_visit.end());
        vector<int> indices(must_visit_vec.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }

        do {
            double total_cost = 0;
            vector<string> current_path = {start};
            bool valid_path = true;
            unordered_set<string> visited_nodes = {start};
            string current_node = start;

            for (int index : indices) {
                string next_must_visit = must_visit_vec[index];
                auto [distances, came_from] = dijkstra(current_node, next_must_visit, visited_nodes);

                if (distances[next_must_visit] == numeric_limits<double>::infinity()) {
                    valid_path = false;
                    break;
                }

                total_cost += distances[next_must_visit];
                if (total_cost > max_cost) {
                    valid_path = false;
                    break;
                }

                vector<string> segment_path = reconstruct_path(came_from, next_must_visit);
                current_path.insert(current_path.end(), segment_path.begin() + 1, segment_path.end());

                visited_nodes.insert(segment_path.begin(), segment_path.end());
                current_node = next_must_visit;
            }

            if (valid_path) {
                auto [distances, came_from] = dijkstra(current_node, end, visited_nodes);
                if (distances[end] == numeric_limits<double>::infinity()) {
                    valid_path = false;
                } else {
                    total_cost += distances[end];

                    if (total_cost <= max_cost) {
                        vector<string> final_segment_path = reconstruct_path(came_from, end);
                        current_path.insert(current_path.end(), final_segment_path.begin() + 1, final_segment_path.end());

                        if (total_cost < min_cost) {
                            min_cost = total_cost;
                            best_path = current_path;
                        }
                    }
                }
            }

        } while (next_permutation(indices.begin(), indices.end()));

        if (min_cost == numeric_limits<double>::infinity())
          return make_pair(vector<string>(), numeric_limits<double>::infinity());

        return make_pair(best_path, min_cost);
    };

    return find_optimal_path();
}

int main() {
    Graph graph = {
        {"A", {{"B", 10}, {"C", 5}}},
        {"B", {{"A", 10}, {"D", 8}}},
        {"C", {{"A", 5}, {"D", 3}, {"E", 7}}},
        {"D", {{"B", 8}, {"C", 3}, {"E", 2}}},
        {"E", {{"C", 7}, {"D", 2}, {"F", 5}}},
        {"F", {{"E", 5}}}
    };

    string start = "A";
    string end = "F";
    unordered_set<string> must_visit = {"D"};
    int max_cost = 25;
    auto [path, cost] = shortest_path_with_constraints(graph, start, end, must_visit, max_cost);
    cout << "Path: ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << ", Cost: " << cost << endl;

    start = "A";
    end = "F";
    must_visit = {"D", "E"};
    max_cost = 30;
    tie(path, cost) = shortest_path_with_constraints(graph, start, end, must_visit, max_cost);
    cout << "Path: ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << ", Cost: " << cost << endl;

    start = "A";
    end = "F";
    must_visit = {"D", "E"};
    max_cost = 15;
    tie(path, cost) = shortest_path_with_constraints(graph, start, end, must_visit, max_cost);
    cout << "Path: ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << ", Cost: " << cost << endl;

    Graph graph2 = {
      {"A", {{"B", 10}, {"C", 5}}},
      {"B", {{"A", 10}, {"D", 8}}},
      {"C", {{"A", 5}, {"D", 3}}},
      {"D", {{"B", 8}, {"C", 3}}}
    };
    start = "A";
    end = "E";
    must_visit = {"D"};
    max_cost = 30;
    tie(path, cost) = shortest_path_with_constraints(graph2, start, end, must_visit, max_cost);
    cout << "Path: ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << ", Cost: " << cost << endl;

    start = "A";
    end = "A";
    must_visit = {};
    max_cost = 10;
    tie(path, cost) = shortest_path_with_constraints(graph, start, end, must_visit, max_cost);
    cout << "Path: ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << ", Cost: " << cost << endl;

    start = "A";
    end = "A";
    must_visit = {"B", "C"};
    max_cost = 30;
    tie(path, cost) = shortest_path_with_constraints(graph, start, end, must_visit, max_cost);
    cout << "Path: ";
    for (const auto& node : path) {
        cout << node << " ";
    }
    cout << ", Cost: " << cost << endl;

    return 0;
}
```