```python
# Finds the shortest path between two nodes in a graph using Dijkstra's algorithm.
# By: Jonathan Mitelman
def find_shortest_path_dijkstra(graph, start_node, end_node):
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    previous_nodes = {node: None for node in graph}
    unvisited_nodes = set(graph.keys())

    while unvisited_nodes:
        current_node = None
        min_distance = float('inf')

        for node in unvisited_nodes:
            if distances[node] < min_distance:
                min_distance = distances[node]
                current_node = node

        if current_node is None:
            break

        unvisited_nodes.remove(current_node)

        if current_node == end_node:
            break

        for neighbor, weight in graph[current_node].items():
            alternative_path_distance = distances[current_node] + weight
            if alternative_path_distance < distances[neighbor]:
                distances[neighbor] = alternative_path_distance
                previous_nodes[neighbor] = current_node

    path = []
    current = end_node
    while current is not None:
        path.insert(0, current)
        current = previous_nodes[current]

    if distances[end_node] == float('inf'):
        return None, float('inf')
    else:
        return path, distances[end_node]


if __name__ == '__main__':
    graph = {
        'A': {'B': 5, 'C': 2},
        'B': {'A': 5, 'D': 1},
        'C': {'A': 2, 'D': 4},
        'D': {'B': 1, 'C': 4},
        'E': {}
    }

    start = 'A'
    end = 'D'
    path, cost = find_shortest_path_dijkstra(graph, start, end)

    if path:
        print(f"Shortest path from {start} to {end}: {path}")
        print(f"Total cost: {cost}")
    else:
        print(f"No path found from {start} to {end}")

    start = 'A'
    end = 'E'
    path, cost = find_shortest_path_dijkstra(graph, start, end)

    if path:
        print(f"Shortest path from {start} to {end}: {path}")
        print(f"Total cost: {cost}")
    else:
        print(f"No path found from {start} to {end}")
```