```python
# Finds the shortest path from start to end in a graph, that MUST visit all nodes in must_visit, and the total distance of the path must be less than or equal to max_distance.
# By: Jonathan Mitelman
def shortest_path_with_constraints(graph, start, end, must_visit, max_distance):
  import itertools

  shortest_path = None
  min_distance = float('inf')

  for permutation in itertools.permutations(must_visit):
    potential_path = [start] + list(permutation) + [end]
    total_distance = 0
    valid_path = True

    for i in range(len(potential_path) - 1):
      current_node = potential_path[i]
      next_node = potential_path[i+1]

      if next_node not in graph.get(current_node, {}):
        valid_path = False
        break

      total_distance += graph[current_node][next_node]

    if valid_path and total_distance <= max_distance:
      if total_distance < min_distance:
        min_distance = total_distance
        shortest_path = potential_path

  if shortest_path:
    return shortest_path, min_distance
  else:
    return None, float('inf')


example_graph = {
    'A': {'B': 5, 'C': 2},
    'B': {'A': 5, 'D': 1, 'E': 4},
    'C': {'A': 2, 'F': 9},
    'D': {'B': 1, 'G': 6},
    'E': {'B': 4, 'H': 3},
    'F': {'C': 9, 'I': 7},
    'G': {'D': 6},
    'H': {'E': 3},
    'I': {'F': 7, 'Z': 1},
    'Z': {'I': 1}
}

start_node = 'A'
end_node = 'Z'
must_visit_nodes = ['B', 'C', 'I']
max_allowed_distance = 30

path, distance = shortest_path_with_constraints(example_graph, start_node, end_node, must_visit_nodes, max_allowed_distance)

if path:
  print(f"Shortest Path: {path}")
  print(f"Total Distance: {distance}")
else:
  print("No path found that satisfies the constraints.")
```