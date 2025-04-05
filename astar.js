```javascript
/* Implements the A* search algorithm to find the shortest path between two nodes in a graph using a heuristic.
By: Jonathan Mitelman */

function aStarSearch(graph, start, goal, heuristic) {
    const openSet = [{ fScore: heuristic(start), gScore: 0, node: start, path: [] }];
    const visited = new Set();

    while (openSet.length > 0) {
        openSet.sort((a, b) => a.fScore - b.fScore);
        const current = openSet.shift();
        const fScore = current.fScore;
        const gScore = current.gScore;
        const currentNode = current.node;
        const path = current.path;

        if (currentNode === goal) {
            return path.concat(currentNode);
        }

        if (visited.has(currentNode)) {
            continue;
        }
        visited.add(currentNode);

        const neighbors = graph[currentNode] || {};
        for (const neighbor in neighbors) {
            if (neighbors.hasOwnProperty(neighbor)) {
                const cost = neighbors[neighbor];
                const newGScore = gScore + cost;
                const newFScore = newGScore + heuristic(neighbor);
                openSet.push({ fScore: newFScore, gScore: newGScore, node: neighbor, path: path.concat(currentNode) });
            }
        }
    }

    return null;
}

function manhattanDistance(node, goal) {
    return Math.abs(node[0] - goal[0]) + Math.abs(node[1] - goal[1]);
}

if (typeof require !== 'undefined' && require.main === module) {
    const graph = {
        '0,0': { '0,1': 1, '1,0': 1 },
        '0,1': { '0,0': 1, '0,2': 1, '1,1': 1 },
        '0,2': { '0,1': 1, '1,2': 1 },
        '1,0': { '0,0': 1, '1,1': 1, '2,0': 1 },
        '1,1': { '0,1': 1, '1,0': 1, '1,2': 1, '2,1': 1 },
        '1,2': { '0,2': 1, '1,1': 1, '2,2': 1 },
        '2,0': { '1,0': 1, '2,1': 1 },
        '2,1': { '1,1': 1, '2,0': 1, '2,2': 1 },
        '2,2': { '1,2': 1, '2,1': 1 }
    };

    const startNode = '0,0';
    const goalNode = '2,2';

    const path = aStarSearch(graph, startNode, goalNode, (node) => {
        const coords = node.split(',').map(Number);
        const goalCoords = goalNode.split(',').map(Number);
        return manhattanDistance(coords, goalCoords);
    });

    if (path) {
        console.log(`Shortest path from ${startNode} to ${goalNode}: ${path}`);
    } else {
        console.log(`No path found from ${startNode} to ${goalNode}`);
    }
}
```