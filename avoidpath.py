```python
# Finds the shortest path between two nodes in a graph, avoiding specified edges.
# By: Jonathan Mitelman
def shortest_path_with_constraints(graph, start, end, forbidden_edges):
    queue = [(start, [start])]
    visited = {start}

    while queue:
        (node, path) = queue.pop(0)

        if node == end:
            return path

        for neighbor in graph.get(node, []):
            if (node, neighbor) in forbidden_edges or (neighbor, node) in forbidden_edges:
                continue

            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, path + [neighbor]))

    return None

graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E', 'G'],
    'G': ['F']
}

forbidden_edges = {('A', 'B'), ('E', 'F')}

start_node = 'A'
end_node = 'G'

shortest_path = shortest_path_with_constraints(graph, start_node, end_node, forbidden_edges)

if shortest_path:
    print(f"Shortest path from {start_node} to {end_node}: {shortest_path}")
else:
    print(f"No path found from {start_node} to {end_node} avoiding forbidden edges.")
```