```python
"""Finds the shortest path between two points in a grid with obstacles using the A* search algorithm.
By: Jonathan Mitelman"""
def shortest_path_with_obstacles(grid, start, end, obstacle_cost=float('inf')):
    def heuristic(a, b):
        return abs(a[0] - b[0]) + abs(a[1] - b[1])

    def get_neighbors(node):
        row, col = node
        neighbors = [(row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)]
        valid_neighbors = []
        for r, c in neighbors:
            if 0 <= r < len(grid) and 0 <= c < len(grid[0]):
                valid_neighbors.append((r, c))
        return valid_neighbors

    open_set = {start}
    closed_set = set()
    came_from = {}
    g_score = {start: 0}
    f_score = {start: heuristic(start, end)}

    while open_set:
        current = min(open_set, key=lambda node: f_score[node])

        if current == end:
            path = []
            while current in came_from:
                path.append(current)
                current = came_from[current]
            path.append(start)
            path.reverse()
            return path

        open_set.remove(current)
        closed_set.add(current)

        for neighbor in get_neighbors(current):
            if neighbor in closed_set:
                continue

            tentative_g_score = g_score[current] + (obstacle_cost if grid[neighbor[0]][neighbor[1]] == 1 else 1)

            if neighbor not in open_set:
                open_set.add(neighbor)
            elif tentative_g_score >= g_score.get(neighbor, float('inf')):
                continue

            came_from[neighbor] = current
            g_score[neighbor] = tentative_g_score
            f_score[neighbor] = tentative_g_score + heuristic(neighbor, end)

    return None

if __name__ == '__main__':
    grid = [
        [0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0],
        [0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0]
    ]

    start_point = (0, 0)
    end_point = (4, 4)

    path = shortest_path_with_obstacles(grid, start_point, end_point)

    if path:
        print("Shortest path:", path)
    else:
        print("No path found.")
```