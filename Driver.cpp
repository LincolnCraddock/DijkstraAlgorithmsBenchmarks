/*
  Author     : Lincoln Craddock
  Description: A program that finds the shortest distance between two nodes
               in a directed graph in two different ways, and tracks the time
               taken to compute using either method.
  Compile    : g++ Driver.cpp -o Driver
*/

/************************************************************/
// System includes

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>

#include "DijkstraAlgorithms.hpp"
#include "GraphGenerators.hpp"
#include "Timer.hpp"

/************************************************************/
// Macros

#define BOLD(TEXT) "\u001b[1m" << TEXT << "\u001b[22m"
#define ITALICS(TEXT) "\u001b[3m" << TEXT << "\u001b[23m"
#define UNDERLINE(TEXT) "\u001b[4m" << TEXT << "\u001b[24m"
#define RED(TEXT) "\u001b[31m" << TEXT << "\u001b[39m"

#define FORMAT "Format:\n" \
<< BOLD ("./Driver") << " " << UNDERLINE("ALG") << " [" << UNDERLINE("SAMPLES") << "] [" << UNDERLINE("GRAPH") << "] [" << UNDERLINE("N") << "] [" << UNDERLINE("SEED") << "]\n\n" \
<< "    " << UNDERLINE("ALG\n") \
<< "        either \"priority-queue\" or \"linear-search\"\n\n" \
<< "    " << UNDERLINE("SAMPLES\n") \
<< "        the number of samples to average\n\n" \
<< "        defaults to timing one execution of Dijkstra's and printing the runtime\n\n" \
<< "    " << UNDERLINE("GRAPH\n") \
<< "        the kind of graph to evaluate Dijkstra's on, either \"random\" or \"worse-case\"\n\n" \
<< "        if " << UNDERLINE("GRAPH") << " is provided " << UNDERLINE("SAMPLES") << " " << ITALICS("must") << " be provided, otherwise defaults to \"random\"\n\n" \
<< "    " << UNDERLINE("N\n") \
<< "        the number of nodes in a graph (2 ≤ N < max_unsigned_value)\n\n" \
<< "        if " << UNDERLINE("N") << " is provided " << UNDERLINE("GRAPH") << " " << ITALICS("must") << " be provided, otherwise defaults to 250 nodes\n\n" \
<< "    " << UNDERLINE("SEED\n") \
<< "        optionally an integer to seed the random number generator with, if the graph\n" \
<< "        type is \"random\"\n\n" \
<< "        if " << UNDERLINE("SEED") << " is provided " << UNDERLINE("N") << " " << ITALICS("must") << " be provided, otherwise the current time according\n" \
<< "        to the system clock is used instead\n"

/************************************************************/
// Forward declarations

std::tuple<bool, unsigned, bool, unsigned>
parseArgs (int argc, char* argv[]);

/************************************************************/

int
main (int argc, char* argv[])
{
  /* set up */
  auto [doPriorityQueue, numSamples, doWorseCase, N] = parseArgs(argc, argv);

  double totalExecutionTime = 0.0;
  volatile long long totalComputedDist = 0; // sum of all calls to Dijkstra so that compiler doesn't optimize them out

  for (unsigned i = 0; i < numSamples; ++i)
  {
    /* create 2D array of directed arcs */
    std::vector<std::vector<unsigned>> arcs;
    if (doWorseCase)
      arcs = generateWorseCaseArcs(N);
    else
      arcs = generateArcs(N);

    /* decide start and end nodes */
    // there might not be a path from start to end
    unsigned start, end;
    if (doWorseCase)
    {
      start = 0;
      end = N - 1;
    }
    else
      std::tie(start, end) = generateStartAndEnd(N);

    /* execute one test and print result */
    Timer t;
    if (doPriorityQueue)
    {
      t.start();
      totalComputedDist += priorityQueueDijkstra(arcs, start, end);
      t.stop();
    }
    else
    {
      t.start();
      totalComputedDist += linearSearchDijkstra(arcs, start, end);
      t.stop();
    }

    totalExecutionTime += t.getElapsedMs();
  }

  /* print results */
  if (numSamples == 1)
    std::cout << "Time: " << totalExecutionTime;
  else
    std::cout << "Average Time " << ITALICS("(sample size " << numSamples << ")") << ": " << (totalExecutionTime / numSamples);
  std::cout << " ms" << std::endl;

  /* clean up */
  delete rb;
}

/************************************************************/

// Returns the algorithm, number of samples, graph type, and number of nodes specified by the user, or default values if unspecified.
// If the user specifies the seed, seeds the graph generators with it.
// Also prints verbose output if the user's args weren't quite in the right format,
std::tuple<bool, unsigned, bool, unsigned>
parseArgs (int argc, char* argv[])
{
  /* not enough arguments */
  if (argc < 2)
  {
    std::cerr << RED("The algorithm type must be specified as a command line argument.\n")
              << FORMAT
              << std::endl;
    exit (EXIT_FAILURE);
  }

  /* 1. algorithm */
  std::string algorithm = std::string(argv[1]);
  bool doPriorityQueue = false;
  bool printAlgorithmMessage = false;
  if (algorithm == "priority-queue") // check algorithm is valid
    doPriorityQueue = true;
  else if (algorithm != "linear-search")
  {
    std::transform(algorithm.begin(), algorithm.end(), algorithm.begin(), ::tolower);
    algorithm.erase(std::remove_if(algorithm.begin(), algorithm.end(), std::not_fn(::isalnum)), algorithm.end());
    if (algorithm == "priorityqueue" || algorithm == "priority" || algorithm == "queue")
      doPriorityQueue = true;
    else if (algorithm != "linearsearch" && algorithm != "linear" && algorithm != "priority")
    {
      std::cerr << RED("The specified algorithm was invalid.\n")
                << FORMAT
                << std::endl;
      exit (EXIT_FAILURE);
    }
    printAlgorithmMessage = true;
  }

  /* 2. number of samples */
  const unsigned numSamples = argc > 2 ? std::stoul (argv[2]) : 1;
  if (numSamples < 1)
  {
    std::cerr << RED("The number of samples must be at least 1.\n")
              << FORMAT
              << std::endl;
    exit (EXIT_FAILURE);
  }

  /* 3. graph type */
  std::string graphType;
  bool doWorseCase = false;
  bool printGraphMessage = false;
  if (argc > 3)
  {
    graphType = std::string(argv[3]);
    if (graphType == "worse-case") // check graph type is valid
      doWorseCase = true;
    else if (graphType != "random")
    {
      std::transform(graphType.begin(), graphType.end(), graphType.begin(), ::tolower);
      graphType.erase(std::remove_if(graphType.begin(), graphType.end(), std::not_fn(::isalnum)), graphType.end());
      if (graphType == "worsecase")
        doWorseCase = true;
      else if (graphType != "random")
      {
        std::cerr << RED("The specified graph type was invalid.\n")
                  << FORMAT
                  << std::endl;
        exit (EXIT_FAILURE);
      }
      printGraphMessage = true;
    }
  }

  /* 4. number of nodes */
  const unsigned N = argc > 4 ? std::stoul (argv[4]) : 250;
  if (N < 2)
  {
    std::cerr << RED("The graph must have at least two nodes.\n")
              << FORMAT
              << std::endl;
    exit (EXIT_FAILURE);
  }
  
  /* 5. seed */
  if (argc > 5)
    seedGenerators(std::stoul (argv[5]));

  /* be verbose if the user slightly misspelled something or specified too many arguments */
  if (printAlgorithmMessage || argc > 6)
    if (printGraphMessage || argc > 6)
      std::cout << "Running with " << (doPriorityQueue ? "priority queue" : "linear search") << " on a " << (doWorseCase ? "worse case" : "random") << " graph:"
                << std::endl;
    else
      std::cout << "Running with " << (doPriorityQueue ? "priority queue" : "linear search") << ":"
                << std::endl;
  else
    if (printGraphMessage)
      std::cout << "Running on a " << (doWorseCase ? "worse case" : "random") << " graph:"
                << std::endl;
  
  return {doPriorityQueue, numSamples, doWorseCase, N};
}

/************************************************************/
