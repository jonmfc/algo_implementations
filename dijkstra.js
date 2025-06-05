```javascript
/** Implements Dijkstra's algorithm to find the shortest path between two nodes in a graph.
By: Jonathan Mitelman */
function shortestPathDijkstra(graph, startNode, endNode) {
  const unvisitedNodes = new Set(Object.keys(graph));
  const shortestDistances = {};
  const predecessors = {};

  for (const node in graph) {
    shortestDistances[node] = Infinity;
    predecessors[node] = null;
  }

  shortestDistances[startNode] = 0;

  while (unvisitedNodes.size > 0) {
    let currentNode = null;
    for (const node of unvisitedNodes) {
      if (currentNode === null || shortestDistances[node] < shortestDistances[currentNode]) {
        currentNode = node;
      }
    }

    if (currentNode === null) {
      break;
    }

    unvisitedNodes.delete(currentNode);

    if (graph[currentNode]) {
      for (const neighbor in graph[currentNode]) {
        const weight = graph[currentNode][neighbor];
        const distance = shortestDistances[currentNode] + weight;
        if (distance < shortestDistances[neighbor]) {
          shortestDistances[neighbor] = distance;
          predecessors[neighbor] = currentNode;
        }
      }
    }
  }

  const shortestPath = [];
  let currentNode = endNode;
  while (currentNode !== null) {
    shortestPath.unshift(currentNode);
    currentNode = predecessors[currentNode];
  }

  if (shortestDistances[endNode] === Infinity) {
    return [Infinity, null];
  } else {
    return [shortestDistances[endNode], shortestPath];
  }
}

const graph = {
  'A': {'B': 5, 'C': 2},
  'B': {'A': 5, 'D': 1, 'E': 4},
  'C': {'A': 2, 'E': 6},
  'D': {'B': 1, 'E': 8},
  'E': {'B': 4, 'C': 6, 'D': 8}
};

let startNode = 'A';
let endNode = 'E';

let [distance, path] = shortestPathDijkstra(graph, startNode, endNode);

if (path) {
  console.log(`Shortest distance from ${startNode} to ${endNode}: ${distance}`);
  console.log(`Shortest path: ${path}`);
} else {
  console.log(`No path found from ${startNode} to ${endNode}`);
}

startNode = 'A';
endNode = 'D';

[distance, path] = shortestPathDijkstra(graph, startNode, endNode);

if (path) {
  console.log(`Shortest distance from ${startNode} to ${endNode}: ${distance}`);
  console.log(`Shortest path: ${path}`);
} else {
  console.log(`No path found from ${startNode} to ${endNode}`);
}

graph['F'] = {};
startNode = 'A';
endNode = 'F';

[distance, path] = shortestPathDijkstra(graph, startNode, endNode);

if (path) {
  console.log(`Shortest distance from ${startNode} to ${endNode}: ${distance}`);
  console.log(`Shortest path: ${path}`);
} else {
  console.log(`No path found from ${startNode} to ${endNode}`);
}
```