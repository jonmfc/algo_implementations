```javascript
/** Finds the shortest path between two nodes in a graph, subject to forbidden nodes and a maximum cost.
By: Jonathan Mitelman */
function shortestPathWithConstraints(graph, start, end, forbiddenNodes, maxCost) {
    if (forbiddenNodes.has(start) || forbiddenNodes.has(end)) {
        return null;
    }

    const priorityQueue = [[0, [start]]];
    const visited = new Set();

    while (priorityQueue.length > 0) {
        priorityQueue.sort((a, b) => a[0] - b[0]);
        const [cost, path] = priorityQueue.shift();
        const currentNode = path[path.length - 1];

        const pathTuple = path.join(',');
        if (cost > maxCost || visited.has(pathTuple)) {
            continue;
        }

        if (currentNode === end) {
            return path;
        }

        visited.add(pathTuple);

        const neighbors = graph[currentNode] || {};
        for (const neighbor in neighbors) {
            if (!forbiddenNodes.has(neighbor)) {
                const weight = neighbors[neighbor];
                const newCost = cost + weight;
                const newPath = [...path, neighbor];
                priorityQueue.push([newCost, newPath]);
            }
        }
    }

    return null;
}

if (typeof require !== 'undefined' && require.main === module) {
    const graph = {
        'A': {'B': 5, 'C': 2},
        'B': {'A': 5, 'D': 1},
        'C': {'A': 2, 'D': 8},
        'D': {'B': 1, 'C': 8, 'E': 7},
        'E': {'D': 7}
    };

    const startNode = 'A';
    const endNode = 'E';
    const forbidden = new Set(['C']);
    const maxCost = 15;

    const path = shortestPathWithConstraints(graph, startNode, endNode, forbidden, maxCost);

    if (path) {
        console.log(`Shortest path from ${startNode} to ${endNode} (forbidden=${Array.from(forbidden)}, max_cost=${maxCost}): ${path}`);
    } else {
        console.log(`No path found from ${startNode} to ${endNode} with the given constraints.`);
    }

    function generateRandomGraph(numNodes, connectivity, costRange) {
        const nodes = Array.from({ length: numNodes }, (_, i) => String.fromCharCode(65 + i));
        const graph = {};
        nodes.forEach(node => graph[node] = {});

        for (let i = 0; i < numNodes; i++) {
            for (let j = i + 1; j < numNodes; j++) {
                if (Math.random() < connectivity) {
                    const cost = Math.floor(Math.random() * (costRange[1] - costRange[0] + 1)) + costRange[0];
                    graph[nodes[i]][nodes[j]] = cost;
                    graph[nodes[j]][nodes[i]] = cost;
                }
            }
        }
        return graph;
    }

    const randomGraph = generateRandomGraph(10, 0.3, [1, 10]);
    console.log("\nRandomly Generated Graph:");
    for (const node in randomGraph) {
        console.log(`${node}: ${JSON.stringify(randomGraph[node])}`);
    }
    const startNodeRandom = 'A';
    const endNodeRandom = 'J';
    const forbiddenRandom = new Set(['C', 'D']);
    const maxCostRandom = 30;
    const pathRandom = shortestPathWithConstraints(randomGraph, startNodeRandom, endNodeRandom, forbiddenRandom, maxCostRandom);

    if (pathRandom) {
        console.log(`Shortest path from ${startNodeRandom} to ${endNodeRandom} (forbidden=${Array.from(forbiddenRandom)}, max_cost=${maxCostRandom}): ${pathRandom}`);
    } else {
        console.log(`No path found from ${startNodeRandom} to ${endNodeRandom} with the given constraints in the random graph.`);
    }
}
```