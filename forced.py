```python
"""Finds the shortest path between two nodes in a graph, ensuring a specific node is visited along the path.
By: Jonathan Mitelman"""
import heapq

def shortest_path_with_constraints(graph, start, end, must_visit):
    def dijkstra(start_node, end_node, visited_nodes=None):
        distances = {node: float('inf') for node in graph}
        paths = {node: [] for node in graph}
        distances[start_node] = 0
        paths[start_node] = [start_node]
        priority_queue = [(0, start_node)]

        while priority_queue:
            dist, current_node = heapq.heappop(priority_queue)

            if dist > distances[current_node]:
                continue

            if current_node == end_node:
                return distances[end_node], paths[end_node]

            for neighbor, weight in graph.get(current_node, {}).items():
                new_distance = distances[current_node] + weight
                if visited_nodes and neighbor not in visited_nodes:
                  continue
                if new_distance < distances[neighbor]:
                    distances[neighbor] = new_distance
                    paths[neighbor] = paths[current_node] + [neighbor]
                    heapq.heappush(priority_queue, (new_distance, neighbor))

        return float('inf'), []

    dist1, path1 = dijkstra(start, must_visit)

    if dist1 == float('inf'):
        return float('inf'), []

    dist2, path2 = dijkstra(must_visit, end, set(path1))

    if dist2 == float('inf'):
        return float('inf'), []

    total_distance = dist1 + dist2
    total_path = path1 + path2[1:]

    return total_distance, total_path

if __name__ == '__main__':
    graph = {
        'A': {'B': 5, 'C': 2},
        'B': {'A': 5, 'D': 1, 'E': 8},
        'C': {'A': 2, 'B': 8, 'F': 7},
        'D': {'B': 1, 'E': 3},
        'E': {'B': 8, 'D': 3, 'Z': 9},
        'F': {'C': 7, 'Z': 4},
        'Z': {'E': 9, 'F': 4}
    }

    start_node = 'A'
    end_node = 'Z'
    must_visit_node = 'B'

    distance, path = shortest_path_with_constraints(graph, start_node, end_node, must_visit_node)

    if distance == float('inf'):
        print(f"No path found from {start_node} to {end_node} visiting {must_visit_node}.")
    else:
        print(f"Shortest distance from {start_node} to {end_node} visiting {must_visit_node}: {distance}")
        print(f"Path: {path}")

    start_node = 'A'
    end_node = 'Z'
    must_visit_node = 'G'

    distance, path = shortest_path_with_constraints(graph, start_node, end_node, must_visit_node)

    if distance == float('inf'):
        print(f"No path found from {start_node} to {end_node} visiting {must_visit_node}.")
    else:
        print(f"Shortest distance from {start_node} to {end_node} visiting {must_visit_node}: {distance}")
        print(f"Path: {path}")
```