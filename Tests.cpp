/*
  Author     : Lincoln Craddock
  Description: A few tests for verifying that DijkstraAlgorithms.hpp is
               implemented correctly.
  Compile    : g++ Tests.cpp -o Tests -lCatch2Main -lCatch2
*/

/************************************************************/
// System includes

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "DijkstraAlgorithms.hpp"
#include "GraphGenerators.hpp"

/************************************************************/

TEST_CASE("Simple one line path", "[dijkstra]") {
  /*
    S ──1──> E
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1},
    {0, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 1) == 1);
  REQUIRE(linearSearchDijkstra(arcs, 0, 1) == 1);
}

TEST_CASE("Simple multi-line path", "[dijkstra]") {
  /*
    S ──1──> ● ──2──> ● ──3──> E
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 0, 0},
    {0, 0, 2, 0},
    {0, 0, 0, 3},
    {0, 0, 0, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 3) == 6);
  REQUIRE(linearSearchDijkstra(arcs, 0, 3) == 6);
}

TEST_CASE("2 nodes, no path", "[dijkstra]") {
  /*
    S        E
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 0},
    {0, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 1) == 0);
  REQUIRE(linearSearchDijkstra(arcs, 0, 1) == 0);
}

TEST_CASE("4 nodes, no path", "[dijkstra]") {
  /*
    S        ●        ●        E
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 3) == 0);
  REQUIRE(linearSearchDijkstra(arcs, 0, 3) == 0);
}

TEST_CASE("Two equal paths", "[dijkstra]") {
  /*
    S ──1──> ● ──1─┐
    │              v
    └1──> ● ──1──> E
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 1, 0},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 3) == 2);
  REQUIRE(linearSearchDijkstra(arcs, 0, 3) == 2);
}

TEST_CASE("Two unequal paths", "[dijkstra]") {
  /*
    S ──1──> ● ──1─┐
    │              v
    └2──> ● ──4──> E
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 2, 0},
    {0, 0, 0, 1},
    {0, 0, 0, 4},
    {0, 0, 0, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 3) == 2);
  REQUIRE(linearSearchDijkstra(arcs, 0, 3) == 2);
}

TEST_CASE("Path going down a tree", "[dijkstra]") {
  /*
    S ──1──> ● ──1──> ●
    │        │
    │        └1──> ●
    1
    └─> ● ──1──> ●
        │
        └1──> E
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 3) == 2);
  REQUIRE(linearSearchDijkstra(arcs, 0, 3) == 2);
}

TEST_CASE("Path going up a tree", "[dijkstra]") {
  /*
    S ──1──> ● ──1──> E
             ^        ^
       ● ──1─┘        │
                      │
         ● ──1──> ● ──1
                  ^
            ● ──1─┘
  */
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 2) == 2);
  REQUIRE(linearSearchDijkstra(arcs, 0, 2) == 2);
}

TEST_CASE("3 × 3 complete graph", "[dijkstra]") {
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 2) == 1);
  REQUIRE(linearSearchDijkstra(arcs, 0, 2) == 1);
}

TEST_CASE("4 × 4 complete graph", "[dijkstra]") {
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 1, 1},
    {1, 0, 1, 1},
    {1, 1, 0, 1},
    {1, 1, 1, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 3) == 1);
  REQUIRE(linearSearchDijkstra(arcs, 0, 3) == 1);
}

TEST_CASE("3 × 3 complete graph with a best path", "[dijkstra]") {
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 9},
    {2, 0, 1},
    {2, 2, 0},
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 2) == 2);
  REQUIRE(linearSearchDijkstra(arcs, 0, 2) == 2);
}

TEST_CASE("4 × 4 complete graph with a best path", "[dijkstra]") {
  std::vector<std::vector<unsigned>> arcs = {
    {0, 1, 2, 9},
    {2, 0, 1, 5},
    {2, 2, 0, 1},
    {2, 2, 2, 0}
  };

  REQUIRE(priorityQueueDijkstra(arcs, 0, 3) == 3);
  REQUIRE(linearSearchDijkstra(arcs, 0, 3) == 3);
}

TEST_CASE("Both Dijkstra's algorithms should equal for random graphs", "[dijkstra]") {
  for (int i = 0; i < 100; ++i)
  {
    std::vector<std::vector<unsigned>> arcs = generateArcs(100);
    auto [start, end] = generateStartAndEnd(100);

    REQUIRE(priorityQueueDijkstra(arcs, start, end) == linearSearchDijkstra(arcs, start, end));
  }
}

/************************************************************/
