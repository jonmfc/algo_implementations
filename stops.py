```python
# Finds the shortest path between two nodes in a graph with at most k stops.
# By: Jonathan Mitelman
import heapq
from collections import defaultdict

def shortest_path_with_k_stops(graph, start, end, k):
    pq = [(0, 0, start)]
    visited = set()

    while pq:
        cost, stops, node = heapq.heappop(pq)

        if node == end:
            return cost

        if (node, stops) in visited:
            continue
        visited.add((node, stops))

        if stops <= k:
            for neighbor, weight in graph.get(node, []):
                heapq.heappush(pq, (cost + weight, stops + 1, neighbor))

    return -1

if __name__ == "__main__":
    example_graph = {
        'A': [('B', 10), ('C', 5)],
        'B': [('D', 5)],
        'C': [('B', 2), ('D', 15)],
        'D': [('E', 3)],
        'E': []
    }

    start_node = 'A'
    end_node = 'E'
    max_stops = 2

    shortest_distance = shortest_path_with_k_stops(example_graph, start_node, end_node, max_stops)

    if shortest_distance != -1:
        print(f"Shortest distance from {start_node} to {end_node} with at most {max_stops} stops: {shortest_distance}")
    else:
        print(f"No path found from {start_node} to {end_node} with at most {max_stops} stops.")

    start_node = 'A'
    end_node = 'D'
    max_stops = 1

    shortest_distance = shortest_path_with_k_stops(example_graph, start_node, end_node, max_stops)

    if shortest_distance != -1:
        print(f"Shortest distance from {start_node} to {end_node} with at most {max_stops} stops: {shortest_distance}")
    else:
        print(f"No path found from {start_node} to {end_node} with at most {max_stops} stops.")

    start_node = 'C'
    end_node = 'D'
    max_stops = 1

    shortest_distance = shortest_path_with_k_stops(example_graph, start_node, end_node, max_stops)

    if shortest_distance != -1:
        print(f"Shortest distance from {start_node} to {end_node} with at most {max_stops} stops: {shortest_distance}")
    else:
        print(f"No path found from {start_node} to {end_node} with at most {max_stops} stops.")
```