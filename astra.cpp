```cpp
// Implements the A* search algorithm to find the shortest path in a graph.
// By: Jonathan Mitelman

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <limits>

using namespace std;

typedef pair<double, string> Node;

pair<vector<string>, double> a_star_search(const map<string, map<string, double>>& graph, const string& start, const string& goal, double (*heuristic)(const string&, const string&)) {
    priority_queue<pair<double, pair<double, string>>, vector<pair<double, pair<double, string>>>, greater<pair<double, pair<double, string>>>> open_set;
    map<string, string> came_from;
    map<string, double> g_score;
    map<string, double> f_score;
    unordered_set<string> closed_set;

    g_score[start] = 0;
    f_score[start] = heuristic(start, goal);
    open_set.push({f_score[start], {0, start}});

    while (!open_set.empty()) {
        string current = open_set.top().second.second;
        double g = open_set.top().second.first;
        open_set.pop();

        if (current == goal) {
            vector<string> path;
            string node = current;
            while (came_from.count(node)) {
                path.insert(path.begin(), node);
                node = came_from[node];
            }
            path.insert(path.begin(), node);
            return {path, g_score[current]};
        }

        closed_set.insert(current);

        for (const auto& neighbor_pair : graph.at(current)) {
            string neighbor = neighbor_pair.first;
            double cost = neighbor_pair.second;

            if (closed_set.count(neighbor)) {
                continue;
            }

            double tentative_g_score = g_score[current] + cost;

            if (!g_score.count(neighbor) || tentative_g_score < g_score[neighbor]) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = tentative_g_score + heuristic(neighbor, goal);
                bool in_open_set = false;
                priority_queue<pair<double, pair<double, string>>, vector<pair<double, pair<double, string>>>, greater<pair<double, pair<double, string>>>> temp_queue = open_set;
                while (!temp_queue.empty()) {
                    if (temp_queue.top().second.second == neighbor && temp_queue.top().second.first == tentative_g_score){
                        in_open_set = true;
                        break;
                    }
                    temp_queue.pop();
                }

                if (!in_open_set) {
                    open_set.push({f_score[neighbor], {tentative_g_score, neighbor}});
                }
            }
        }
    }

    return {vector<string>(), numeric_limits<double>::infinity()};
}

double manhattan_distance(const string& node, const string& goal) {
    return 0;
}

int main() {
    map<string, map<string, double>> graph = {
        {"A", {{"B", 5}, {"C", 2}}},
        {"B", {{"A", 5}, {"D", 1}}},
        {"C", {{"A", 2}, {"D", 8}, {"E", 7}}},
        {"D", {{"B", 1}, {"C", 8}, {"E", 3}}},
        {"E", {{"C", 7}, {"D", 3}, {"F", 6}}},
        {"F", {{"E", 6}}}
    };

    string start_node = "A";
    string goal_node = "F";

    pair<vector<string>, double> result = a_star_search(graph, start_node, goal_node, manhattan_distance);

    if (!result.first.empty()) {
        cout << "Shortest path from " << start_node << " to " << goal_node << ": ";
        for (const string& node : result.first) {
            cout << node << " ";
        }
        cout << endl;
        cout << "Cost: " << result.second << endl;
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << endl;
    }

    return 0;
}
```