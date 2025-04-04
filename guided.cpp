```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

// Finds the shortest path between two nodes in a graph, subject to constraints on path length and forbidden nodes.
// By: Jonathan Mitelman
using namespace std;

vector<string> find_shortest_path_with_constraints(
    const unordered_map<string, vector<string>>& graph,
    const string& start_node,
    const string& end_node,
    int max_nodes,
    const vector<string>& forbidden_nodes) {

    if (start_node == end_node) {
        return {start_node};
    }

    if (graph.find(start_node) == graph.end() || graph.find(end_node) == graph.end()) {
        return {};
    }

    for (const string& node : forbidden_nodes) {
        if (node == start_node || node == end_node) {
            return {};
        }
    }

    queue<vector<string>> q;
    q.push({start_node});

    unordered_set<string> visited;
    visited.insert(start_node);

    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();

        string last_node = path.back();

        if (last_node == end_node) {
            return path;
        }

        auto it = graph.find(last_node);
        if(it != graph.end()){
            for (const string& neighbor : it->second) {
                bool is_forbidden = false;
                for (const string& forbidden_node : forbidden_nodes) {
                    if (neighbor == forbidden_node) {
                        is_forbidden = true;
                        break;
                    }
                }
                if (!visited.count(neighbor) && !is_forbidden && path.size() < max_nodes) {
                    vector<string> new_path = path;
                    new_path.push_back(neighbor);
                    q.push(new_path);
                    visited.insert(neighbor);
                }
            }
        }
    }

    return {};
}

int main() {
    unordered_map<string, vector<string>> graph = {
        {"A", {"B", "C"}},
        {"B", {"A", "D", "E"}},
        {"C", {"A", "F"}},
        {"D", {"B"}},
        {"E", {"B", "F"}},
        {"F", {"C", "E", "G"}},
        {"G", {"F"}}
    };

    string start = "A";
    string end = "G";
    int max_length = 5;
    vector<string> forbidden = {"E"};

    vector<string> shortest_path = find_shortest_path_with_constraints(graph, start, end, max_length, forbidden);

    if (!shortest_path.empty()) {
        cout << "Shortest path from " << start << " to " << end << " (max " << max_length << " nodes, forbidden: ";
        for (const string& node : forbidden) {
            cout << node << " ";
        }
        cout << "): ";
        for (const string& node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from " << start << " to " << end << " with the given constraints." << endl;
    }

    start = "A";
    end = "G";
    max_length = 5;
    forbidden = {};

    shortest_path = find_shortest_path_with_constraints(graph, start, end, max_length, forbidden);

    if (!shortest_path.empty()) {
        cout << "Shortest path from " << start << " to " << end << " (max " << max_length << " nodes, forbidden: ";
        for (const string& node : forbidden) {
            cout << node << " ";
        }
        cout << "): ";
        for (const string& node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from " << start << " to " << end << " with the given constraints." << endl;
    }

    start = "A";
    end = "E";
    max_length = 2;
    forbidden = {};

    shortest_path = find_shortest_path_with_constraints(graph, start, end, max_length, forbidden);

    if (!shortest_path.empty()) {
        cout << "Shortest path from " << start << " to " << end << " (max " << max_length << " nodes, forbidden: ";
        for (const string& node : forbidden) {
            cout << node << " ";
        }
        cout << "): ";
        for (const string& node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from " << start << " to " << end << " with the given constraints." << endl;
    }
    
    start = "A";
    end = "A";
    max_length = 5;
    forbidden = {};

    shortest_path = find_shortest_path_with_constraints(graph, start, end, max_length, forbidden);

    if (!shortest_path.empty()) {
        cout << "Shortest path from " << start << " to " << end << " (max " << max_length << " nodes, forbidden: ";
        for (const string& node : forbidden) {
            cout << node << " ";
        }
        cout << "): ";
        for (const string& node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from " << start << " to " << end << " with the given constraints." << endl;
    }

    return 0;
}
```