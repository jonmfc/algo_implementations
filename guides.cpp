```cpp
// Finds the shortest path in a graph from start to end, optionally requiring the path to visit a specific node and/or avoid specific nodes.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

vector<string> shortest_path_with_constraints(const unordered_map<string, vector<string>>& graph, const string& start, const string& end, const string& must_visit = "", const unordered_set<string>& avoid = {}) {

    auto is_valid_node = [&](const string& node) {
        return avoid.find(node) == avoid.end();
    };

    auto find_shortest_path = [&](const string& start_node, const string& end_node, unordered_set<string> visited = {}) -> vector<string> {
        queue<pair<string, vector<string>>> q;
        q.push({start_node, {start_node}});
        visited.insert(start_node);

        while (!q.empty()) {
            string node = q.front().first;
            vector<string> path = q.front().second;
            q.pop();

            if (node == end_node) {
                return path;
            }

            auto it = graph.find(node);
            if (it != graph.end()) {
                for (const string& neighbor : it->second) {
                    if (visited.find(neighbor) == visited.end() && is_valid_node(neighbor)) {
                        visited.insert(neighbor);
                        vector<string> new_path = path;
                        new_path.push_back(neighbor);
                        q.push({neighbor, new_path});
                    }
                }
            }
        }

        return {};
    };

    if (!is_valid_node(start) || !is_valid_node(end)) {
        return {};
    }

    if (must_visit.empty()) {
        return find_shortest_path(start, end);
    } else {
        if (!is_valid_node(must_visit)) {
            return {};
        }

        vector<string> first_part_path = find_shortest_path(start, must_visit);
        if (first_part_path.empty()) {
            return {};
        }

        unordered_set<string> first_part_visited(first_part_path.begin(), first_part_path.end());
        vector<string> second_part_path = find_shortest_path(must_visit, end, first_part_visited);

        if (second_part_path.empty()) {
            return {};
        }

        vector<string> combined_path = first_part_path;
        combined_path.insert(combined_path.end(), second_part_path.begin() + 1, second_part_path.end());
        return combined_path;
    }
}

int main() {
    unordered_map<string, vector<string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"A", "D"}},
        {"C", {"A", "E"}},
        {"D", {"B", "F"}},
        {"E", {"C", "G"}},
        {"F", {"D"}},
        {"G", {"E"}},
        {"H", {}}
    };

    auto print_path = [](const vector<string>& path) {
        if (path.empty()) {
            cout << "No path" << endl;
        } else {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    };

    cout << "Path from A to F: ";
    print_path(shortest_path_with_constraints(graph, "A", "F"));

    cout << "Path from A to F, must visit D: ";
    print_path(shortest_path_with_constraints(graph, "A", "F", "D"));

    unordered_set<string> avoid_B = {"B"};
    cout << "Path from A to F, avoid B: ";
    print_path(shortest_path_with_constraints(graph, "A", "F", "", avoid_B));

    unordered_set<string> avoid_D = {"D"};
    cout << "Path from A to G, must visit C, avoid D: ";
    print_path(shortest_path_with_constraints(graph, "A", "G", "C", avoid_D));

    cout << "Path from A to G, must visit F: ";
    print_path(shortest_path_with_constraints(graph, "A", "G", "F"));

    cout << "Path from A to H: ";
    print_path(shortest_path_with_constraints(graph, "A", "H"));

    cout << "Path from A to A: ";
    print_path(shortest_path_with_constraints(graph, "A", "A"));

    unordered_set<string> avoid_A = {"A"};
    cout << "Path from A to F, avoid A: ";
    print_path(shortest_path_with_constraints(graph, "A", "F", "", avoid_A));

    unordered_map<string, vector<string>> empty_graph;
    cout << "Path from X to Y (empty graph): ";
    print_path(shortest_path_with_constraints(empty_graph, "X", "Y"));

    unordered_set<string> avoid_Z = {"Z"};
    cout << "Path from A to F, avoid Z: ";
    print_path(shortest_path_with_constraints(graph, "A", "F", "", avoid_Z));

    cout << "Path from A to F, must visit Z: ";
    print_path(shortest_path_with_constraints(graph, "A", "F", "Z"));
    return 0;
}
```