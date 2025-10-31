# DijkstraAlgorithmsBenchmarks
A few drivers, header files, and unit tests for benchmarking the runtime efficiency of two different implementations of Dijkstra's algorithm.

## Run
The releases section includes several executables:
- Driver
- BenchmarkRandomGraphs
- BenchmarkWorseCaseGraphs
- Tests

The Driver can be used to

## Background
Using Dijkstra's algorithm to find the shortest path between two nodes in a graph involves 'visiting' a number of nodes, starting with the start node. Visiting a node means relaxing each of its neighbors' distances from the start as calculated by the algorithm so far. The next node to visit is determined by finding the closest unvisited node to the start. There are several different ways to find the next node, and it isn't obvious which is best, so these benchmarks were designed to compare two of them.

The two implementations of Dijkstra's algorithm tested here use a proiority queue and a linked list respectively to find the next vertex to visit. The linked list implementation linearly searches the list of unvisited nodes to find the next one to visit. Very rough pseudocode for these algorithms are provided below.

## Algorithms
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
Both implementations follow roughly the same pattern, the main difference being how the ``n = the next node to visit`` line is implemented.

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

## Time complexity
There are at least two ways to measure time complexity for Dijkstra's algorithm: the worse case in a completely random graph (N nodes, A arcs), or the worse case with the very worse possible graph (N nodes and approximately N × N arcs, a fully connected graph!). In a random graph, the priority queue algorithm seems to have a much better time complexity:

### Priority Queue
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
  n = queue.pop()   -- O[log(A)]
}
```
In the worse case, the while loop will run **A times** _(A = total # of arcs)_ before it visits the end node. This is because the same node can be visited more than once if it's pushed multiple times into the queue. This happens if the node's shortest distance from start is relaxed repeatedly because several arcs connect to it.

The for loop always runs **N times** _(N = total # of nodes)_, iterating over each node in the graph.[^1]

Even though the condition of the if statement can be checked checked up to A × N times, it won't evaluate to true more than **A times**. This is because the condition, ``arcs[n][n2] is defined && n.distFromStart + arcs[n][n2] < n2.distFromStart`` is only ever true if the node hasn't been visited yet. Once a node is visited, its shortest distance from start has been found, so ``n.distFromStart + arcs[n][n2] < n2.distFromStart`` will always return false from then on.

Therefore, ``queue.push()`` and ``queue.pop()`` each have time complexity **O[log(A)]** in the worse case. Since the if block won't run more than A times, ``queue.push()`` won't get be called more than A times, so the queue will never have more than A nodes in it.

A × (1 + log(A)) + A × log(A) ≈ **O\[A log(A)\]**

### Linear Search
```
let list = a linked list of nodes that haven't been visited yet

while ( )   -- runs ≤ N times
{
  for each ( )   -- runs N times
  {
    if ( )   -- evaluates true ≤ A times
    {
      ...   -- O[1]
    }
  }

  let nextN = UNDEFINED
  for each ( )   -- runs ≤ N times
  {
    ...   -- O[1]
  }

  n = list.remove(nextN)   -- O[1]
}
```
Unlike the priority queue implementation, this version of Dijkstra's algorithm won't ever visit the same node twice, so the outer while loop doesn't run more than **N times**. Even so, the block of the if statement can still run up to **A times** in the worse case, once for every arc leaving each node that gets visited.

The time complexity of finding the next node in the list is **O[N]**, since it involves checking every node in the graph in the worse case. The ``list.remove()`` is constant time in the code, since it takes an iterator already pointing to the element to remove.

N × (N + N + 1) ≈ **O[N<sup>2</sup>]**

With a worse case graph, each node has an arc going to and from every other node in the graph, so A = N × (N - 1) ≈ N × N. Substituting A with N<sup>2</sup> into the time complexity equation for the priority queue algorithm, we see that its time complexity is actually worse than the linear search algorithm in a worse case graph:

Priority Queue in a worse case graph: **O[N<sup>2</sup> log(N)]**

Linear Search in a worse case graph: **O[N<sup>2</sup>]**

## Results
### Random Graph
| Graph Size | With Priority Queue | With Linear Search |
| ---------: | :------------------ | :----------------- |
|   10 nodes | 0.0112203 ms        | 0.00562637 ms      |
|  100 nodes | 0.234808 ms         | 0.34385 ms         |
|  500 nodes | 4.29251 ms          | 7.51058 ms         |
| 1000 nodes | 17.5654 ms          | 30.5001 ms         |

### Worse Case Graph
| Graph Size | With Priority Queue | With Linear Search |
| ---------: | :------------------ | :----------------- |
|   10 nodes | 0.0182991 ms        | 0.00991817 ms      |
|  100 nodes | 5.83757 ms          | 0.465639 ms        |
|  500 nodes | 43.1003 ms          | 10.7225 ms         |
| 1000 nodes | ???????? ms         | ??????? ms         |

## Author
Lincoln Craddock

[^1]: Many implementations of Dijkstra's algorithm store an adjacency list for each node and iterate over that inside the for loop. This implementation does essentially the same thing by iterating over all of the nodes in the loop and checking whether the arc from n to n2 exists instead.
    
    Even if the for loop was changed to iterate over adjacent nodes instead, the time complexity overall would stay the same since the if block would still run A times in the worse case.
