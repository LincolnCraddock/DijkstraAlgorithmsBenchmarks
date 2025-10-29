# DijkstraAlgorithmsBenchmark
A few drivers, header files, and unit tests for benchmarking the runtime efficiency of two different implementations of Dijkstra's algorithm.

## Run
The releases section includes several executables:
- BenchmarkDijkstraAlgorithms
- Driver
- TestDijkstraAlgorithms

## Background
Using Dijkstra's algorithm to find the shortest path between two nodes in a graph involves 'visiting' a number of nodes, starting with the start node. Visiting a node means relaxing each of its neighbors' distances from the start as calculated so far. The next node to visit is determined by finding the closest unvisited node to the start. There are several ways to do this, so these benchmarks were designed to compare two of them.

The two implementations of Dijkstra's algorithm here use a proiority queue and a linked list respectively to find the next vertex to visit. The linked list implementation linearly searches the list of unvisited nodes to find the next one to visit. Very rough pseudocode for these algorithms are provided below:

### Dijkstra's Algorithm
```
let nodes = every node in the graph
    start = the start node
    end = the end node
    arcs[n1][n2] = the length of the arc going from node n1 to n2
                    (or UNDEFINED if there is no arc)

let n = start
while (n ≠ end)
{
  for each (n2 in nodes)
  {
    if (arcs[n][n2] is defined && n.distFromStart + arcs[n][n2] < n2.distFromStart)
    {
      relax n2.distFromStart
    }
  }
  n = the next node to visit
}
```
Both implementations follow roughly the same pattern, with the main difference being how the ``n = the next node to visit`` line is implemented.

### With a Priority Queue
```
let queue = a priority queue of nodes, sorted by their current calculated distFromStart

while ( )
{
  for each ( )
  {
    if ( )
    {
      ...
      queue.push(n2)
    }
  }
  n = queue.pop()
}
```

### With a Linear Search
```
let list = a linked list of nodes that haven't been visited yet

while ( )
{
  for each ( )
  {
      if ( )
      {
        ...
      }
  }

  let nextN = UNDEFINED
  for each (n2 in list)
  {
    if (n2.distFromStart < nextN.distFromStart)
    {
      nextN = n2
    }
  }

  n = list.remove(nextN)
}
```

### Time complexity
There are two ways to look at time complexity for these algorithms: the worse case in a typical graph (N nodes, A arcs), or the worse case with the very worse possible graph (N nodes and approximately N × N arcs, a fully connected graph!). In a typical graph, the priority queue algorithm has a slightly improved time complexity:

#### Priority Queue: 
```
while ( )   -- runs ≤ A times
{
  for each ( )   -- runs N times
  {
    if ( )   -- evaluates true ≤ A times
    {
      ...   -- O[1]
      queue.push(n2)   -- O[log(A)]
    }
  }
  n = queue.pop()   -- O[log[A]]
}
```
In the worse case, the while loop will run **A times** (A = total # of arcs) before it visits the end node. This is because the same node can be visited multiple times if it gets pushed into the queue more than once. This can happen if the node's shortest distance from start is relaxed more than once because several arcs connect to it.

The for loop always runs **N times** (N = total # of nodes), iterating over each node in the graph.[^1]

Even though the condition of the if statement in the worse case runs A × N times (N = total # of nodes), it won't evaluate true more than **A times**. This is because the condition, ``arcs[n][n2] is defined && n.distFromStart + arcs[n][n2] < n2.distFromStart``, is really only true if he arc is defined and the node hasn't been visited yet. Once a node is visited, its shortest distance from start has been found, so ``n.distFromStart + arcs[n][n2] < n2.distFromStart`` will always return false from then on.

Therefore, ``queue.push()`` and ``queue.pop()`` each have time complexity **O[log(A)]** in the worse case. Since the if block won't run more than A times, ``queue.push()`` won't get be called more than A times, so the queue will never have more than A nodes.

E × (log(E) × N + log(E)) ≈ **O[E\*N\*log(E)]**

#### Linear Search:
```
let list = a linked list of nodes that haven't been visited yet

while ( )   -- runs N times
{
  for each ( )   -- runs N times
  {
    if ( )   -- evaluates true E times
    {
      ...   -- O[1]
    }
  }

  let nextN = UNDEFINED
  for each ( )   -- O[N]
  {
    ...
  }

  n = nextN
  list.remove(nextN)   -- O[1]
}
```
This version of Dijkstra's algorithm will never visit the same node twice, so the outer while loop won't run more than N.

The time complexity of finding the next node in the list is simply **O[N]**, since it involves checking every node in the graph in the worse case. The ``list.remove()`` is constant time in the actual code, since it takes an iterator already pointing to the element to remove.

N × (N + N + 1) ≈ **O[N<sup>2</sup>]**

With a worse case graph, all of the nodes are connected by edges, so E = N × (N - 1) ≈ N × N. Substituting E for N<sup>2</sup> into the equations, we see that the time complexity of the linear search algorithm is actually better than the priority queue one when for a worse case graph:

Priority Queue: **O[N<sup>3</sup>log(N)]**

Linear Search: **O[N<sup>2</sup>]**

## Results
//TODO

## Author
Lincoln Craddock

### Implementation Notes

[^1]: Many implementations of Dijkstra's algorithm store an adjacency list for each node and iterate over that inside the for loop. This implementation does essentially the same thing by iterating over all of the nodes in the for loop and checking whether the arc from n to n2 exists instead.
