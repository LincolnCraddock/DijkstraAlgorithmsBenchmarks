/*
  Author     : Lincoln Craddock
  Description: A few benchmarks for testing the runtime of the different implementations
               of Dijkstra's algorithm in DijkstraAlgorithms.hpp on worse case graphs.
  Compile    : g++ BenchmarkWorseCaseGraphs.cpp -o BenchmarkWorseCaseGraphs -lCatch2Main -lCatch2
*/

/************************************************************/
// System includes

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "DijkstraAlgorithms.hpp"
#include "GraphGenerators.hpp"

/************************************************************/

TEST_CASE("Several n × n worse case graphs", "[dijkstra]") {

  // 3 × 3

  BENCHMARK_ADVANCED("Priority Queue -- 3 × 3")(Catch::Benchmark::Chronometer meter) {
    std::vector<std::vector<unsigned>> arcs = {
      {0, 1, 3},
      {0, 0, 1},
      {0, 0, 0}
    };

    meter.measure([arcs] { return priorityQueueDijkstra(arcs, 0, 2); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 3 × 3")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 3;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 4 × 4

  BENCHMARK_ADVANCED("Priority Queue -- 4 × 4")(Catch::Benchmark::Chronometer meter) {
    std::vector<std::vector<unsigned>> arcs = {
      {0, 1, 3, 5},
      {0, 0, 1, 3},
      {0, 0, 0, 1},
      {0, 0, 0, 0}
    };

    meter.measure([arcs] { return priorityQueueDijkstra(arcs, 0, 3); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 4 × 4")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 4;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 5 × 5

  BENCHMARK_ADVANCED("Priority Queue -- 5 × 5")(Catch::Benchmark::Chronometer meter) {
    std::vector<std::vector<unsigned>> arcs = {
      {0, 1, 3, 5, 7},
      {0, 0, 1, 3, 5},
      {0, 0, 0, 1, 3},
      {0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0}
    };

    meter.measure([arcs] { return priorityQueueDijkstra(arcs, 0, 4); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 5 × 5")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 5;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 10 × 10

  BENCHMARK_ADVANCED("Priority Queue -- 10 × 10")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 10;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 10 × 10")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 10;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 100 × 100

  BENCHMARK_ADVANCED("Priority Queue -- 100 × 100")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 100;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 100 × 100")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 100;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 200 × 200

  BENCHMARK_ADVANCED("Priority Queue -- 200 × 200")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 200;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 200 × 200")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 200;
    std::vector<std::vector<unsigned>> arcs = generateWorseCaseArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

}

/************************************************************/
