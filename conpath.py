```python
"""Finds the shortest path between two nodes in a graph, subject to forbidden edges and a maximum weight constraint.
By: Jonathan Mitelman"""
import heapq

def shortest_path_with_constraints(graph, start, end, forbidden_edges, max_weight):
    pq = [(0, [start])]
    while pq:
        weight, path = heapq.heappop(pq)
        current_node = path[-1]
        if current_node == end:
            return (path, weight)
        if weight > max_weight:
            continue
        if current_node not in graph:
            continue
        for neighbor, edge_weight in graph[current_node]:
            if (current_node, neighbor) in forbidden_edges:
                continue
            if neighbor not in path:
                new_weight = weight + edge_weight
                new_path = path + [neighbor]
                heapq.heappush(pq, (new_weight, new_path))
    return (None, float('inf'))

if __name__ == '__main__':
    graph1 = {
        'A': [('B', 5), ('C', 2)],
        'B': [('D', 3)],
        'C': [('B', 1), ('D', 8)],
        'D': []
    }
    start1 = 'A'
    end1 = 'D'
    forbidden_edges1 = {('A', 'B')}
    max_weight1 = 10

    result1 = shortest_path_with_constraints(graph1, start1, end1, forbidden_edges1, max_weight1)
    print(f"Test Case 1: {result1}")

    graph2 = {
        'A': [('B', 5), ('C', 2)],
        'B': [('D', 3)],
        'C': [('B', 1), ('D', 8)],
        'D': []
    }
    start2 = 'A'
    end2 = 'D'
    forbidden_edges2 = {('A', 'B'), ('C', 'D')}
    max_weight2 = 10

    result2 = shortest_path_with_constraints(graph2, start2, end2, forbidden_edges2, max_weight2)
    print(f"Test Case 2: {result2}")

    graph3 = {
        'A': [('B', 5), ('C', 2)],
        'B': [('D', 3)],
        'C': [('B', 1), ('D', 8)],
        'D': []
    }
    start3 = 'A'
    end3 = 'D'
    forbidden_edges3 = {('A', 'B')}
    max_weight3 = 5

    result3 = shortest_path_with_constraints(graph3, start3, end3, forbidden_edges3, max_weight3)
    print(f"Test Case 3: {result3}")

    graph4 = {
        'A': [('B', 10)],
        'B': [('C', 5)],
        'C': [('D', 2)],
        'D': []
    }
    start4 = 'A'
    end4 = 'D'
    forbidden_edges4 = set()
    max_weight4 = 16
    result4 = shortest_path_with_constraints(graph4, start4, end4, forbidden_edges4, max_weight4)
    print(f"Test Case 4: {result4}")

    graph5 = {
        'A': [('B', 1), ('C', 1)],
        'B': [('A', 1)],
        'C': [('D', 1)],
        'D': []
    }
    start5 = 'A'
    end5 = 'D'
    forbidden_edges5 = set()
    max_weight5 = 3
    result5 = shortest_path_with_constraints(graph5, start5, end5, forbidden_edges5, max_weight5)
    print(f"Test Case 5: {result5}")
```