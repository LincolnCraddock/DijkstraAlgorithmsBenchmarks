/*
  Author     : Lincoln Craddock
  Description: A class containing two similar versions of Dijkstra's algorithm.
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef DIJKSTRAALGORITHMS_H
#define DIJKSTRAALGORITHMS_H

/************************************************************/
// System includes

#include <vector>
#include <limits>
#include <queue>
#include <list>

/************************************************************/

struct node
{
  unsigned id;
  unsigned distFromStart;
  bool operator<(const node &other) const
  {
    return distFromStart > other.distFromStart;
  }
};

const unsigned MAX_DIST_FROM_START = std::numeric_limits<unsigned>::max();

// Returns the minimum distance from start to end following arcs, or 0 if no such path exists.
// Implemented using a priority queue to find the next node to visit.
unsigned
priorityQueueDijkstra (std::vector<std::vector<unsigned>> arcs, unsigned start, unsigned end)
{
  /* create array of nodes, and a priority queue of nodes to visit */
  // nodes are copied, changes in one container won't affect the nodes in the other
  std::vector<node> nodes;
  for (unsigned i = 0; i < arcs.size(); ++i)
    nodes.push_back({i, i == start ? 0 : MAX_DIST_FROM_START});
  std::priority_queue<node> nodesToVisit;

  /* visit each node */
  node n = nodes[start];
  do
  {
    for (node& n2 : nodes)
    {
      unsigned arcLen = arcs[n.id][n2.id];
      if (arcLen && n.distFromStart + arcLen < n2.distFromStart)
      {
        n2.distFromStart = n.distFromStart + arcLen;

        // vvvv  priority queue specific code  vvvv
        nodesToVisit.push(n2);
      }
    }

    if (nodesToVisit.empty()) // there is no path to end
      break;
    
    n = nodesToVisit.top();
    nodesToVisit.pop();
    // ^^^^  priority queue specific code  ^^^^
  } while (n.id != end);

  unsigned result = nodes[end].distFromStart;
  return result == MAX_DIST_FROM_START ? 0 : result;
}

// Returns the minimum distance from start to end following arcs, or 0 if no such path exists.
// Implemented by searching a vector linearly to find the next node to visit.
unsigned
linearSearchDijkstra (std::vector<std::vector<unsigned>> arcs, unsigned start, unsigned end)
{
  /* create array of nodes, and a list of nodes to visit */
  // nodes are copied, changes in one container won't affect the nodes in the other
  std::vector<node> nodes;
  std::list<unsigned> nodesToVisit;
  for (unsigned i = 0; i < arcs.size(); ++i)
  {
    nodes.push_back({i, i == start ? 0 : MAX_DIST_FROM_START});
    nodesToVisit.push_back(i);
  }

  /* visit each node */
  node n = nodes[start];
  do
  {
    for (node& n2 : nodes)
    {
      unsigned arcLen = arcs[n.id][n2.id];
      if (arcLen && n.distFromStart + arcLen < n2.distFromStart)
        n2.distFromStart = n.distFromStart + arcLen;
    }

    // vvvv  linear search specific code  vvv
    std::list<unsigned>::iterator nodeToVisitNext = nodesToVisit.begin();
    for (std::list<unsigned>::iterator it = ++nodesToVisit.begin(); it != nodesToVisit.end(); ++it)
      if (nodes[*nodeToVisitNext] < nodes[*it]) // find the greatest node
        nodeToVisitNext = it;
      
    if (nodes[*nodeToVisitNext].distFromStart == MAX_DIST_FROM_START) // there is no path to end
      break;
    
    n = nodes[*nodeToVisitNext];
    nodesToVisit.erase(nodeToVisitNext);
    // ^^^^  linear search specific code  ^^^^
  } while (n.id != end);

  unsigned result = nodes[end].distFromStart;
  return result == MAX_DIST_FROM_START ? 0 : result;
}

/************************************************************/

#endif

/************************************************************/
