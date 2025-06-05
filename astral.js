```javascript
/** A* search algorithm for finding the shortest path between two nodes in a graph.
 * By: Jonathan Mitelman */
function aStar(graph, start, goal, heuristic) {
    const openSet = [{ fScore: 0, node: start }];
    const gScore = {};
    const fScore = {};
    const cameFrom = {};

    for (const node in graph) {
        gScore[node] = Infinity;
        fScore[node] = Infinity;
    }

    gScore[start] = 0;
    fScore[start] = heuristic(start, goal);

    while (openSet.length > 0) {
        openSet.sort((a, b) => a.fScore - b.fScore);
        const current = openSet.shift();
        const currentNode = current.node;

        if (currentNode === goal) {
            return reconstructPath(cameFrom, currentNode);
        }

        for (const neighbor in graph[currentNode]) {
            const weight = graph[currentNode][neighbor];
            const tentativeGScore = gScore[currentNode] + weight;

            if (tentativeGScore < gScore[neighbor]) {
                cameFrom[neighbor] = currentNode;
                gScore[neighbor] = tentativeGScore;
                fScore[neighbor] = tentativeGScore + heuristic(neighbor, goal);

                if (!openSet.some(item => item.node === neighbor)) {
                    openSet.push({ fScore: fScore[neighbor], node: neighbor });
                }
            }
        }
    }

    return null;
}

function reconstructPath(cameFrom, currentNode) {
    const path = [currentNode];
    while (cameFrom[currentNode]) {
        currentNode = cameFrom[currentNode];
        path.push(currentNode);
    }
    return path.reverse();
}

function euclideanDistance(node1, node2) {
    const x1 = node1[0];
    const y1 = node1[1];
    const x2 = node2[0];
    const y2 = node2[1];
    return Math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2);
}

function manhattanDistance(node1, node2) {
  const x1 = node1[0];
  const y1 = node1[1];
  const x2 = node2[0];
  const y2 = node2[1];
  return Math.abs(x1 - x2) + Math.abs(y1 - y2);
}

function generateRandomGraph(numNodes, connectivity) {
    const nodes = Array.from({ length: numNodes }, () => [Math.floor(Math.random() * 101), Math.floor(Math.random() * 101)]);
    const graph = {};
    nodes.forEach(node => {
        graph[node] = {};
    });

    for (let i = 0; i < numNodes; i++) {
        for (let j = i + 1; j < numNodes; j++) {
            if (Math.random() < connectivity) {
                const weight = Math.floor(Math.random() * 10) + 1;
                graph[nodes[i]][nodes[j]] = weight;
                graph[nodes[j]][nodes[i]] = weight;
            }
        }
    }

    return graph;
}

if (typeof require !== 'undefined' && require.main === module) {
    const graph = {
        "(0,0)": { "(1,0)": 1, "(0,1)": 1 },
        "(1,0)": { "(0,0)": 1, "(2,0)": 1, "(1,1)": 1 },
        "(0,1)": { "(0,0)": 1, "(1,1)": 1, "(0,2)": 1 },
        "(2,0)": { "(1,0)": 1, "(2,1)": 1 },
        "(1,1)": { "(1,0)": 1, "(0,1)": 1, "(2,0)": 1, "(1,2)": 1 },
        "(0,2)": { "(0,1)": 1, "(1,2)": 1 },
        "(2,1)": { "(2,0)": 1, "(1,2)": 1, "(2,2)": 1 },
        "(1,2)": { "(0,2)": 1, "(1,1)": 1, "(2,1)": 1 },
        "(2,2)": { "(2,1)": 1 }
    };

    const startNode = "(0,0)";
    const goalNode = "(2,2)";

    const path = aStar(graph, startNode, goalNode, euclideanDistance);

    if (path) {
        console.log(`Shortest path from ${startNode} to ${goalNode}: ${path}`);
    } else {
        console.log(`No path found from ${startNode} to ${goalNode}`);
    }

    const largeGraph = generateRandomGraph(100, 0.1);
    const start = Object.keys(largeGraph)[0];
    const goal = Object.keys(largeGraph)[Object.keys(largeGraph).length - 1];

    const startTime = performance.now();
    const largeGraphPath = aStar(largeGraph, start, goal, euclideanDistance);
    const endTime = performance.now();

    if (largeGraphPath) {
        console.log(`Path found in ${(endTime - startTime).toFixed(4)} milliseconds for large graph.`);
    } else {
        console.log("No path found in large graph.");
    }

}
```