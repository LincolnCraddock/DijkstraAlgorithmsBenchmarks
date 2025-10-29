# DijkstraAlgorithmsBenchmark
A few drivers, header files, and unit tests for benchmarking the runtime efficiency of two different implementations of Dijkstra's algorithm.

## Run
The releases section includes several executables:
- BenchmarkDijkstraAlgorithms
- Driver
- TestDijkstraAlgorithms

## Background
When Dijkstra's algorithm is used to find the shortest path between two nodes in a graph, each node is 'visited' once, starting with the start node. Visiting a node means relaxing each of its neighbors' distances from the start, if possible. The next node to visit is always the closest unvisited node to the start as calculated by the algorithm so far. There are several ways to determine the next node to visit, but these benchmarks were designed to compare two of them.

The two implementations of Dijkstra's algorithm compared here use a proiority queue and a linked list to find the next vertex to visit. The linked list implementation linearly searches the list of unvisited nodes to find the next one to visit. Very rough pseudocode for these algorithms are provided below:

### Dijkstra's Algorithm
```
let nodes = every node in the graph
    start = the start node
    end = the end node
    edges[n1][n2] = the length of the edge between node n1 and n2
                    (or UNDEFINED if there is no edge)

let n = start
while (n ≠ end)
{
  for each (n2 in nodes)
  {
    if (edges[n][n2] is defined && n.distFromStart + edges[n][n2] < n2.distFromStart)
    {
      relax n2.distFromStart
    }
  }
  n = the next node to visit
}
```

### Priority Queue
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

### Linear Search
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
There are two ways to look at time complexity for these algorithms, worse case in a general graph (N nodes, E edges), or worse case with the very worse case graph (N nodes and approximately N × N edges, a fully connected graph!). In a general graph, the priority queue algorithm seems to have a slightly worse time complexity??? I thought it would be better:

#### Priority Queue: 
```
while ( )   -- runs E times
{
  for each ( )   -- runs N times
  {
    if ( )   -- evaluates true N × N times
    {
      ...   -- O[1]
      queue.push(n2)   -- O[log(E)]
    }
  }
  n = queue.pop()   -- O[log[E]]
}
```
In the worse case, the while loop will run **E** times (E = total # of edges) before it visits the end node. This is because the same node can get pushed multiple times into queue if multiple edges connect to it.

``queue.push()`` and ``queue.pop()`` each have time complexity **O[log(E)]** in the worse case; there will never be more than E nodes in the queue. If you thought it should be O[log(N)], remember that the queue might have the same node twice in it. The real limiting factor on the number of nodes in queue is E.

E × (log(E) × N + log(E)) ≈ **O[E*N*log(E)]**

#### Linear Search:
```
let list = a linked list of nodes that haven't been visited yet

while ( )   -- runs N times
{
  for each ( )   -- runs N times
  {
    if ( )   -- evaluates true N × N times
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

