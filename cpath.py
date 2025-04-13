```python
"""Finds the shortest path between two nodes in a graph, subject to constraints: only certain nodes are allowed in the path, and the total cost of the path must not exceed a maximum value.
By: Jonathan Mitelman"""
def shortest_path_with_constraints(graph, start, end, allowed_nodes, max_cost):
    import heapq

    if start not in graph or end not in graph:
        return None, float('inf')
    if start not in allowed_nodes or end not in allowed_nodes:
        return None, float('inf')


    priority_queue = [(0, [start])]
    visited = set()

    while priority_queue:
        cost, path = heapq.heappop(priority_queue)
        current_node = path[-1]

        if current_node == end:
            return path, cost

        if (current_node, tuple(path)) in visited:
            continue

        visited.add((current_node, tuple(path)))

        for neighbor, edge_cost in graph.get(current_node, {}).items():

            if neighbor in allowed_nodes:
                new_cost = cost + edge_cost
                if new_cost <= max_cost:
                    new_path = path + [neighbor]
                    heapq.heappush(priority_queue, (new_cost, new_path))

    return None, float('inf')

if __name__ == '__main__':
    graph = {
        'A': {'B': 5, 'C': 2},
        'B': {'A': 5, 'D': 1},
        'C': {'A': 2, 'D': 4, 'E':8},
        'D': {'B': 1, 'C': 4, 'F':3},
        'E': {'C': 8, 'F': 7},
        'F': {'D': 3, 'E': 7}
    }

    start_node = 'A'
    end_node = 'F'
    allowed_nodes = {'A', 'B', 'C', 'D', 'E', 'F'}
    max_cost = 10

    path, cost = shortest_path_with_constraints(graph, start_node, end_node, allowed_nodes, max_cost)

    if path:
        print(f"Shortest path from {start_node} to {end_node}: {path}")
        print(f"Cost of the path: {cost}")
    else:
        print(f"No path found from {start_node} to {end_node} within the constraints.")


    max_cost = 5
    path, cost = shortest_path_with_constraints(graph, start_node, end_node, allowed_nodes, max_cost)
    if path:
        print(f"Shortest path from {start_node} to {end_node}: {path}")
        print(f"Cost of the path: {cost}")
    else:
        print(f"No path found from {start_node} to {end_node} within the constraints.")

    allowed_nodes = {'B', 'C', 'D', 'E', 'F'}
    path, cost = shortest_path_with_constraints(graph, start_node, end_node, allowed_nodes, max_cost)
    if path:
        print(f"Shortest path from {start_node} to {end_node}: {path}")
        print(f"Cost of the path: {cost}")
    else:
        print(f"No path found from {start_node} to {end_node} within the constraints.")
```