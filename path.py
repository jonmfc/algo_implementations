```python
"""Finds the shortest path between two nodes in a graph using Dijkstra's algorithm.
By: Jonathan Mitelman"""
def shortest_path_dijkstra(graph, start_node, end_node):
    distances = {node: float('inf') for node in graph}
    distances[start_node] = 0
    predecessors = {}
    unvisited_nodes = set(graph)

    while unvisited_nodes:
        current_node = min(unvisited_nodes, key=distances.get)

        if distances[current_node] == float('inf'):
            break

        if current_node == end_node:
            path = []
            node = end_node
            while node:
                path.insert(0, node)
                node = predecessors.get(node)
            return distances[end_node], path

        unvisited_nodes.remove(current_node)

        for neighbor, weight in graph[current_node].items():
            new_distance = distances[current_node] + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                predecessors[neighbor] = current_node

    return float('inf'), []

if __name__ == '__main__':
    graph = {
        'A': {'B': 5, 'C': 2},
        'B': {'A': 5, 'D': 1, 'E': 4},
        'C': {'A': 2, 'F': 9},
        'D': {'B': 1, 'G': 6},
        'E': {'B': 4, 'H': 3},
        'F': {'C': 9, 'I': 7},
        'G': {'D': 6},
        'H': {'E': 3},
        'I': {'F': 7}
    }

    start_node = 'A'
    end_node = 'I'

    distance, path = shortest_path_dijkstra(graph, start_node, end_node)

    if distance == float('inf'):
        print(f"No path found from {start_node} to {end_node}")
    else:
        print(f"Shortest distance from {start_node} to {end_node}: {distance}")
        print(f"Shortest path: {path}")

    start_node = 'A'
    end_node = 'G'

    distance, path = shortest_path_dijkstra(graph, start_node, end_node)

    if distance == float('inf'):
        print(f"No path found from {start_node} to {end_node}")
    else:
        print(f"Shortest distance from {start_node} to {end_node}: {distance}")
        print(f"Shortest path: {path}")
```