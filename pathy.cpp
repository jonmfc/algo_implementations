```cpp
// Finds the shortest path from a start node to a goal node in a grid using the A* algorithm.
// By: Jonathan Mitelman
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <random>

using namespace std;

int heuristic(tuple<int, int> a, tuple<int, int> b) {
    return abs(get<0>(a) - get<0>(b)) + abs(get<1>(a) - get<1>(b));
}

vector<tuple<int, int>> get_neighbors(const vector<vector<int>>& grid, tuple<int, int> node) {
    int row = get<0>(node);
    int col = get<1>(node);
    vector<tuple<int, int>> neighbors;
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        if (new_row >= 0 && new_row < grid.size() && new_col >= 0 && new_col < grid[0].size() && grid[new_row][new_col] == 0) {
            neighbors.emplace_back(new_row, new_col);
        }
    }
    return neighbors;
}

vector<tuple<int, int>> a_star_pathfinding(const vector<vector<int>>& grid, tuple<int, int> start, tuple<int, int> goal) {
    priority_queue<pair<int, tuple<int, int>>, vector<pair<int, tuple<int, int>>>, greater<pair<int, tuple<int, int>>>> open_set;
    open_set.push({0, start});

    map<tuple<int, int>, tuple<int, int>> came_from;
    map<tuple<int, int>, int> g_score;
    map<tuple<int, int>, int> f_score;

    g_score[start] = 0;
    f_score[start] = heuristic(start, goal);

    while (!open_set.empty()) {
        tuple<int, int> current_node = open_set.top().second;
        open_set.pop();

        if (current_node == goal) {
            vector<tuple<int, int>> path;
            tuple<int, int> node = current_node;
            while (came_from.count(node)) {
                path.push_back(node);
                node = came_from[node];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (tuple<int, int> neighbor : get_neighbors(grid, current_node)) {
            int tentative_g_score = g_score[current_node] + 1;

            if (!g_score.count(neighbor) || tentative_g_score < g_score[neighbor]) {
                came_from[neighbor] = current_node;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = tentative_g_score + heuristic(neighbor, goal);
                open_set.push({f_score[neighbor], neighbor});
            }
        }
    }

    return {};
}

vector<vector<int>> generate_random_grid(int rows, int cols, double obstacle_probability) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = (dis(gen) > obstacle_probability) ? 0 : 1;
        }
    }
    return grid;
}

int main() {
    int rows = 10;
    int cols = 15;
    vector<vector<int>> grid = generate_random_grid(rows, cols, 0.2);

    tuple<int, int> start = {0, 0};
    tuple<int, int> goal = {rows - 1, cols - 1};

    while (grid[get<0>(start)][get<1>(start)] == 1) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> row_dis(0, rows - 1);
        uniform_int_distribution<> col_dis(0, cols - 1);
        start = {row_dis(gen), col_dis(gen)};
    }

    while (grid[get<0>(goal)][get<1>(goal)] == 1) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> row_dis(0, rows - 1);
        uniform_int_distribution<> col_dis(0, cols - 1);
        goal = {row_dis(gen), col_dis(gen)};
    }

    vector<tuple<int, int>> path = a_star_pathfinding(grid, start, goal);

    if (!path.empty()) {
        cout << "Path found:" << endl;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                bool in_path = false;
                for (const auto& node : path) {
                    if (get<0>(node) == row && get<1>(node) == col) {
                        in_path = true;
                        break;
                    }
                }
                if (in_path) {
                    cout << "P ";
                } else if (grid[row][col] == 1) {
                    cout << "X ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
```