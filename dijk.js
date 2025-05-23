```javascript
/* Finds the shortest path between two nodes in a graph using Dijkstra's algorithm.
By: Jonathan Mitelman*/
function findShortestPathDijkstra(graph, startNode, endNode) {
  const distances = {};
  const predecessors = {};
  const unvisitedNodes = new Set();

  for (const node in graph) {
    distances[node] = Infinity;
    predecessors[node] = null;
    unvisitedNodes.add(node);
  }

  distances[startNode] = 0;

  while (unvisitedNodes.size > 0) {
    let current_node = null;
    let minDistance = Infinity;

    for (const node of unvisitedNodes) {
      if (distances[node] < minDistance) {
        minDistance = distances[node];
        current_node = node;
      }
    }


    if (current_node === null || distances[current_node] === Infinity) {
      break;
    }

    unvisitedNodes.delete(current_node);

    if (current_node === endNode) {
        break;
    }


    for (const neighbor in graph[current_node]) {
      const weight = graph[current_node][neighbor];
      const alternativePathDistance = distances[current_node] + weight;

      if (alternativePathDistance < distances[neighbor]) {
        distances[neighbor] = alternativePathDistance;
        predecessors[neighbor] = current_node;
      }
    }
  }

  const path = [];
  let currentNode = endNode;
  while (currentNode !== null && currentNode !== undefined) {
    path.unshift(currentNode);
    currentNode = predecessors[currentNode];
  }

  if (distances[endNode] === Infinity) {
    return [null, Infinity];
  } else if (path[0] !== startNode) {
      return [null, Infinity];
  }
  else {
    return [path, distances[endNode]];
  }
}
```