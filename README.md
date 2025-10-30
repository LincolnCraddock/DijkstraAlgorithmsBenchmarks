# DijkstraAlgorithmsBenchmarks
A few drivers, header files, and unit tests for benchmarking the runtime efficiency of two different implementations of Dijkstra's algorithm.

## Run
The releases section includes several executables:
- BenchmarkDijkstraAlgorithms
- Driver
- TestDijkstraAlgorithms

## Background
Using Dijkstra's algorithm to find the shortest path between two nodes in a graph involves 'visiting' a number of nodes, starting with the start node. Visiting a node means relaxing each of its neighbors' distances from the start as calculated so far. The next node to visit is determined by finding the closest unvisited node to the start. There are several ways to do this, so these benchmarks were designed to compare two of them.

The two implementations of Dijkstra's algorithm here use a proiority queue and a linked list respectively to find the next vertex to visit. The linked list implementation linearly searches the list of unvisited nodes to find the next one to visit. Very rough pseudocode for these algorithms are provided below.

### Dijkstra's Algorithm
Both implementations follow roughly the same pattern, with the main difference being how the ``n = the next node to visit`` line below is implemented:
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
There are two ways to look at time complexity for these algorithms: the worse case in a typical graph (N nodes, A arcs), or the worse case with the very worse possible graph (N nodes and approximately N × N arcs, a fully connected graph!). In a typical graph, the priority queue algorithm seems to have a slightly better time complexity:

#### Priority Queue
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
In the worse case, the while loop will run **A times** _(A = total # of arcs)_ before it visits the end node. The reason it's A times instead of N _(N = total # of nodes)_ is because the same node can actually get pushed multiple times into the queue. This will happen if the node's shortest distance from start is relaxed more than once if several arcs connect to it.

The for loop always runs **N times** (N = total # of nodes), iterating over each node in the graph.[^1]

Even though the condition of the if statement in the worse case is checked A × N times, it won't evaluate to true more than **A times**. This is because the condition, ``arcs[n][n2] is defined && n.distFromStart + arcs[n][n2] < n2.distFromStart``, is really only true if he arc is defined and _the node hasn't been visited yet_. Once a node is visited, its shortest distance from start has been found, so ``n.distFromStart + arcs[n][n2] < n2.distFromStart`` will always return false from then on.

Therefore, ``queue.push()`` and ``queue.pop()`` each have time complexity **O[log(A)]** in the worse case. Since the if block won't run more than A times, ``queue.push()`` won't get be called more than A times, so the queue will never have more than A nodes.

A × log(A) + A × log(A) ≈ **O\[A log(A)\]**

#### Linear Search
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
  for each ( )   -- O[N]
  {
    ...   -- O[1]
  }

  n = list.remove(nextN)   -- O[1]
}
```
Unlike the priority queue implementation, this version of Dijkstra's algorithm won't ever visit the same node twice, so the outer while loop doesn't run more than **N times**. Even so, the block of the if statement can still run up to **A times** in the worse case, once for every arc leaving each node that gets visited.

The time complexity of finding the next node in the list is simply **O[N]**, since it involves checking every node in the graph in the worse case. The ``list.remove()`` is constant time in the actual code, since it takes an iterator already pointing to the element to remove.

N × (N + N) ≈ **O[N<sup>2</sup>]**

With a worse case graph, each node has an arc going to and from every other node in the graph, so A = N × (N - 1) ≈ N × N. Substituting A with N<sup>2</sup> into the time complexity equation for thr priority queue algorithm, we see that the complexity of the linear search algorithm is actually better in a worse case graph:

Priority Queue in a worse case graph: **O[N<sup>2</sup> log(N)]**

Linear Search in a worse case graph: **O[N<sup>2</sup>]**

## Results
//TODO

## Author
Lincoln Craddock

[^1]: Many implementations of Dijkstra's algorithm store an adjacency list for each node and iterate over that inside the for loop. This implementation does essentially the same thing by iterating over all of the nodes in the for loop and checking whether the arc from n to n2 exists instead.
    
    Even if the for loop was changed to iterate over adjacent nodes instead, the time complexity overall would stay the same since the if block would still run A times in the worse case.
