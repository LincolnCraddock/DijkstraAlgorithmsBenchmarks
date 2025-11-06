# DijkstraAlgorithmsBenchmarks
A few drivers, header files, and unit tests for benchmarking the runtime efficiency of two different implementations of Dijkstra's algorithm.

## Run
The releases section includes several executables:
- Driver
- RunDriver.sh
- BenchmarkRandomGraphs
- BenchmarkWorseCaseGraphs
- Tests

Run the **Driver** with the name of the algorithm to test, either `priority-queue` or `linear-search`. It will evaluate a random 250-node graph with that algorithm and print the runtime. You can also specify a number of samples to average, the kind of graph to evaluate (either `worse-case` or `random`), the number of nodes in each graph, and the seed to seed the RNG with (if evaluating a random graph). For example, to measure the average runtime of the priroity queue algorithm on a worse case graph of 100 nodes after 2000 samples, you could run:
```
> ./Driver priority-queue 2000 worse-case 100
Average Time (sample size 2000): 5.83037 ms
```

If you want to get the the runtime of every execution rather than just the average, running **RunDriver.sh** with `-t <number of times to run>` will call the Driver `<number of times to run>` times and print only the runtimes in ms. For example, you could concatenate the runtime of every execution from the above test into a file and then average those results like this:
```
> ./RunDriver.sh -t 2000 -a priority-queue -g worse-case -n 100 > results.txt
> awk '{sum+=$1} END {print sum/NR " ms"}' results.txt
6.02261
```

Two benchmarks are also included for measuring the performance of both algorithms using Catch2, **BenchmarkRandomGraphs** and **BenchmarkWorseCaseGraphs**. Running these programs runs both algorithms against various sized random and worse case graphs, respectively. You can also run numerous test cases to verify the correctness of both implemnentations of Dijkstra's algorithm by running **Tests**.

To compile the code for yourself, clone the repository and run ``make`` from the project directory.

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

A + N × (N + 1) ≈ **O[N<sup>2</sup>]**

With a worse case graph, each node has an arc going to and from every other node in the graph, so A = N × (N - 1) ≈ N × N. Substituting A with N<sup>2</sup> into the time complexity equation for the priority queue algorithm, we see that its time complexity is actually worse than the linear search algorithm in a worse case graph:

Priority Queue in a worse case graph: **O[N<sup>2</sup> log(N)]**

Linear Search in a worse case graph: **O[N<sup>2</sup>]**

## Results
The execution time of both algorithms on randomly generated and worse case graphs of various sizes was measured. The average runtimes over 50,000 sample executions for each graph type, size, and algorithm are shown below.

### Random Graph
| Graph Size | With Priority Queue | With Linear Search |
| ---------: | :------------------ | :----------------- |
|   10 nodes | 0.00149273 ms       | 0.00172045 ms      |
|  100 nodes | 0.0564334 ms        | 0.0604695 ms       |
|  500 nodes | 1.14905 ms          | 1.32704 ms         |
| 1000 nodes | 5.57145 ms          | 5.97749 ms         |

### Worse Case Graph
| Graph Size | With Priority Queue | With Linear Search |
| ---------: | :------------------ | :----------------- |
|   10 nodes | 0.00144939 ms       | 0.00088914 ms      |
|  100 nodes | 0.425032 ms         | 0.0389728 ms       |
|  500 nodes | 31.4694 ms          | 0.734609 ms        |
| 1000 nodes | ???????? ms         | 3.15329 ms         |

These times were gethered by compiling the Driver with -O3 optimizations and running it on an Intel(R) Xeon(R) Gold 6230 CPU (2.10GHz) running Arch Linux. Although exact runtimes may vary from machine to machine, these results clearly show how the implementation using a priority queue outperforms the implementation using a linear search for especially large randomly generated graphs, but becomes much slower in the worse case scenario.

Interestingly, the data shows that worse case graphs have much lower average runtimes when using linear search, and with priority queue on very small graphs. Profiling suggests that this is not due to increased heap usage or algorithmic inefficiency in the implementations themselves. Instead, the difference is likely due to the less predictable memory access and branch behavior when processing randomly connected graphs, which causes more CPU stalls even though the total number of operations is smaller.

## Author
Lincoln Craddock

[^1]: Many implementations of Dijkstra's algorithm store an adjacency list for each node and iterate over that inside the for loop. This implementation does essentially the same thing by iterating over all of the nodes in the loop and checking whether the arc from n to n2 exists instead.
    
    Even if the for loop was changed to iterate over adjacent nodes instead, the time complexity overall would stay the same since the if block would still run A times in the worse case.
