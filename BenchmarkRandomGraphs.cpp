/*
  Author     : Lincoln Craddock
  Description: A few benchmarks for testing the runtime of the different implementations
               of Dijkstra's algorithm in DijkstraAlgorithms.hpp on random graphs.
  Compile    : g++ BenchmarkRandomGraphs.cpp -o BenchmarkRandomGraphs -lCatch2Main -lCatch2
*/

/************************************************************/
// System includes

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "DijkstraAlgorithms.hpp"
#include "GraphGenerators.hpp"

/************************************************************/

TEST_CASE("Several n-size graphs", "[dijkstra]") {

  // 5 nodes

  BENCHMARK_ADVANCED("Priority Queue -- 5 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 5;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 5 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 5;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 10 nodes

  BENCHMARK_ADVANCED("Priority Queue -- 10 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 10;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 10 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 10;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 100 nodes

  BENCHMARK_ADVANCED("Priority Queue -- 100 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 100;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 100 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 100;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 500 nodes

  BENCHMARK_ADVANCED("Priority Queue -- 500 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 500;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 500 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 500;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

  // 1000 nodes

  BENCHMARK_ADVANCED("Priority Queue -- 1000 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 1000;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return priorityQueueDijkstra(arcs, 0, n - 1); });
  };

  BENCHMARK_ADVANCED("Linear Search -- 1000 nodes")(Catch::Benchmark::Chronometer meter) {
    unsigned n = 1000;
    std::vector<std::vector<unsigned>> arcs = generateArcs(n);

    meter.measure([n, arcs] { return linearSearchDijkstra(arcs, 0, n - 1); });
  };

}

/************************************************************/