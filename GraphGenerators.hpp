/*
  Author     : Lincoln Craddock
  Description: A class containing several functions useful for generating
               directed graphs.
*/

/************************************************************/
// Macro guard to prevent multiple inclusions

#ifndef GRAPHGENERATORS_H
#define GRAPHGENERATORS_H

/************************************************************/
// System includes

#include <vector>
#include <random>

#include "RandomBool.hpp"
#include "DijkstraAlgorithms.hpp" // needed for MAX_DIST_FROM_START

/************************************************************/

std::mt19937 rng;
RandomBool* const rb = new RandomBool;

// Seed the random number generators defined in this file
// The same calls to the same functions in the same order should return the same output whenever
// the same seed is specified.
void
seedGenerators (unsigned seed)
{
    rng.seed(seed);
    rb->seed(seed);
}

// Generate a random 2D array of arcs so that all possible configurations of arcs are equally likely.
std::vector<std::vector<unsigned>>
generateArcs (unsigned n)
{
    std::uniform_int_distribution<unsigned> arcLenDistr(1, MAX_DIST_FROM_START / n); // because 'max dist from start' == 'max arc len' * n
    std::vector<std::vector<unsigned>> arcs(n, std::vector<unsigned>(n, 0)); // no arc between i and j => arcs[i][j] == 0
    for (unsigned i = 0; i < n; ++i)
      for (unsigned j = 0; j < n; ++j)
        if (rb->nextBool())
          arcs[i][j] = arcLenDistr(rng);
    return arcs;
}

// Generate a 2D array of arcs in the worse possible configuration to get the maximum possible runtime
// out of Dijkstra's algorithm.
std::vector<std::vector<unsigned>>
generateWorseCaseArcs (unsigned n)
{
  std::vector<std::vector<unsigned>> arcs(n, std::vector<unsigned>(n));
  for (unsigned i = 0; i < n; ++i)
    for (unsigned j = 0; j < n; ++j)
      arcs[i][j] = j <= i ? 0 : 2 * (j - i) - 1;
  return arcs;
}

// Randomly pick a start and end node, such that start != end.
std::pair<unsigned, unsigned>
generateStartAndEnd (unsigned n)
{
    std::uniform_int_distribution<unsigned> nDistr(0, n - 1);
    unsigned start = nDistr(rng);
    unsigned end;
    do {
      end = nDistr(rng);
    } while (start == end);
    return {start, end};
}

/************************************************************/

#endif

/************************************************************/