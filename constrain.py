```python
"""Finds the shortest path from a start node to an end node in a graph, while ensuring a specific node is visited and the path cost is within a limit.
By: Jonathan Mitelman"""
import heapq

def shortest_path_with_constraints(graph, start, end, must_visit, max_cost):
    def reconstruct_path(came_from, current):
        path = [current]
        while current in came_from:
            current = came_from[current]
            path.insert(0, current)
        return path

    def dijkstra(start_node, end_node, disallowed_nodes=None):
        dist = {node: float('inf') for node in graph}
        dist[start_node] = 0
        came_from = {}
        pq = [(0, start_node)]

        while pq:
            d, current_node = heapq.heappop(pq)

            if d > dist[current_node]:
                continue

            if current_node == end_node:
                break

            for neighbor, weight in graph.get(current_node, {}).items():
                if disallowed_nodes and neighbor in disallowed_nodes:
                    continue
                new_dist = d + weight
                if new_dist < dist[neighbor]:
                    dist[neighbor] = new_dist
                    came_from[neighbor] = current_node
                    heapq.heappush(pq, (new_dist, neighbor))

        return came_from, dist

    came_from_start, dist_start = dijkstra(start, must_visit)
    if dist_start[must_visit] == float('inf'):
        return None, float('inf')

    came_from_must_visit, dist_must_visit = dijkstra(must_visit, end)
    if dist_must_visit[end] == float('inf'):
        return None, float('inf')

    total_cost = dist_start[must_visit] + dist_must_visit[end]

    if total_cost > max_cost:
        return None, float('inf')

    path1 = reconstruct_path(came_from_start, must_visit)
    path2 = reconstruct_path(came_from_must_visit, end)

    full_path = path1[:-1] + path2

    return full_path, total_cost

if __name__ == '__main__':
    graph = {
        'A': {'B': 5, 'C': 2},
        'B': {'A': 5, 'D': 1, 'E': 10},
        'C': {'A': 2, 'D': 8},
        'D': {'B': 1, 'C': 8, 'E': 7},
        'E': {'B': 10, 'D': 7, 'F': 2},
        'F': {'E': 2}
    }

    start_node = 'A'
    end_node = 'F'
    must_visit_node = 'D'
    max_path_cost = 15

    path, cost = shortest_path_with_constraints(graph, start_node, end_node, must_visit_node, max_path_cost)

    if path:
        print(f"Shortest path from {start_node} to {end_node} visiting {must_visit_node}: {path}")
        print(f"Total cost: {cost}")
    else:
        print(f"No path found from {start_node} to {end_node} visiting {must_visit_node} within the cost constraint.")


    start_node = 'A'
    end_node = 'F'
    must_visit_node = 'G'
    max_path_cost = 20

    path, cost = shortest_path_with_constraints(graph, start_node, end_node, must_visit_node, max_path_cost)

    if path:
        print(f"Shortest path from {start_node} to {end_node} visiting {must_visit_node}: {path}")
        print(f"Total cost: {cost}")
    else:
        print(f"No path found from {start_node} to {end_node} visiting {must_visit_node} within the cost constraint.")

    start_node = 'A'
    end_node = 'F'
    must_visit_node = 'D'
    max_path_cost = 8

    path, cost = shortest_path_with_constraints(graph, start_node, end_node, must_visit_node, max_path_cost)

    if path:
        print(f"Shortest path from {start_node} to {end_node} visiting {must_visit_node}: {path}")
        print(f"Total cost: {cost}")
    else:
        print(f"No path found from {start_node} to {end_node} visiting {must_visit_node} within the cost constraint.")
```