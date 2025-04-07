```javascript
/** Finds the shortest path from start to end in a graph, visiting all nodes in must_visit, with a maximum allowed total distance.
By: Jonathan Mitelman */
function shortestPathWithConstraints(graph, start, end, mustVisit, maxDistance) {
    function getNeighbors(node) {
        return graph[node] || {};
    }

    let shortestPath = null;
    let shortestDistance = Infinity;

    function backtrack(currentNode, visited, currentPath, currentDistance) {
        if (
            Array.from(mustVisit).every(node => visited.has(node)) &&
            currentNode === end
        ) {
            if (currentDistance < shortestDistance) {
                shortestDistance = currentDistance;
                shortestPath = [...currentPath];
            }
            return;
        }

        if (currentDistance >= shortestDistance || currentDistance > maxDistance) {
            return;
        }

        const neighbors = getNeighbors(currentNode);
        for (const neighbor in neighbors) {
            const distance = neighbors[neighbor];
            if (!visited.has(neighbor)) {
                visited.add(neighbor);
                currentPath.push(neighbor);
                backtrack(neighbor, visited, currentPath, currentDistance + distance);
                currentPath.pop();
                visited.delete(neighbor);
            }
        }
    }

    const visited = new Set([start]);
    backtrack(start, visited, [start], 0);

    return [shortestPath, shortestDistance];
}

if (typeof require !== 'undefined' && require.main === module) {
    const graph = {
        'A': { 'B': 5, 'C': 2 },
        'B': { 'A': 5, 'D': 1 },
        'C': { 'A': 2, 'D': 8 },
        'D': { 'B': 1, 'C': 8, 'E': 7 },
        'E': { 'D': 7 }
    };

    let path, distance;

    path, distance = shortestPathWithConstraints(graph, 'A', 'E', new Set(), 20);
    console.log(`Path: ${path}, Distance: ${distance}`);

    path, distance = shortestPathWithConstraints(graph, 'A', 'E', new Set(['B']), 30);
    console.log(`Path: ${path}, Distance: ${distance}`);

    path, distance = shortestPathWithConstraints(graph, 'A', 'E', new Set(['B']), 10);
    console.log(`Path: ${path}, Distance: ${distance}`);

    path, distance = shortestPathWithConstraints(graph, 'A', 'E', new Set(['B', 'C']), 30);
    console.log(`Path: ${path}, Distance: ${distance}`);

    path, distance = shortestPathWithConstraints(graph, 'A', 'F', new Set(['B']), 30);
    console.log(`Path: ${path}, Distance: ${distance}`);

    path, distance = shortestPathWithConstraints(graph, 'A', 'E', new Set(), 15);
    console.log(`Path: ${path}, Distance: ${distance}`);

    const graph2 = {
        'A': { 'B': 2, 'C': 5 },
        'B': { 'A': 2, 'D': 3, 'E': 7 },
        'C': { 'A': 5, 'F': 8 },
        'D': { 'B': 3, 'G': 4 },
        'E': { 'B': 7, 'H': 6 },
        'F': { 'C': 8, 'I': 9 },
        'G': { 'D': 4, 'J': 5 },
        'H': { 'E': 6, 'K': 10 },
        'I': { 'F': 9, 'L': 11 },
        'J': { 'G': 5 },
        'K': { 'H': 10 },
        'L': { 'I': 11 }
    };

    path, distance = shortestPathWithConstraints(graph2, 'A', 'J', new Set(['B', 'D']), 20);
    console.log(`Path: ${path}, Distance: ${distance}`);
}
```