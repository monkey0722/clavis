#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

struct BellmanFordEdge {
  std::size_t from;
  std::size_t to;
  long long weight;
};

struct BellmanFordResult {
  std::vector<long long> distances;
  bool hasNegativeCycle;
};

/**
 * @brief Computes single-source shortest paths in a directed weighted graph.
 *
 * Edge weights may be negative. A negative cycle is reported only when it is
 * reachable from the source vertex.
 *
 * @param vertexCount Number of vertices in the graph.
 * @param edges Directed weighted edges.
 * @param source Source vertex.
 * @return Shortest distances and whether a reachable negative cycle exists.
 * @throws std::out_of_range If the source or an edge endpoint is invalid.
 *
 * @note Finite path costs must fit in a long long.
 * @complexity O(VE) time and O(V) additional space.
 */
[[nodiscard]] inline BellmanFordResult bellmanFord(std::size_t vertexCount,
                                                   const std::vector<BellmanFordEdge>& edges,
                                                   std::size_t source) {
  if (source >= vertexCount) {
    throw std::out_of_range("Source vertex is out of range");
  }

  for (const auto& edge : edges) {
    if (edge.from >= vertexCount || edge.to >= vertexCount) {
      throw std::out_of_range("Edge endpoint is out of range");
    }
  }

  constexpr long long infinity = std::numeric_limits<long long>::max();
  std::vector<long long> distances(vertexCount, infinity);
  distances[source] = 0;

  for (std::size_t pass = 1; pass < vertexCount; ++pass) {
    bool updated = false;
    for (const auto& edge : edges) {
      if (distances[edge.from] == infinity) {
        continue;
      }

      const long long candidate = distances[edge.from] + edge.weight;
      if (candidate < distances[edge.to]) {
        distances[edge.to] = candidate;
        updated = true;
      }
    }

    if (!updated) {
      break;
    }
  }

  bool hasNegativeCycle = false;
  for (const auto& edge : edges) {
    if (distances[edge.from] != infinity &&
        distances[edge.from] + edge.weight < distances[edge.to]) {
      hasNegativeCycle = true;
      break;
    }
  }

  return {
      .distances = std::move(distances),
      .hasNegativeCycle = hasNegativeCycle,
  };
}

#endif  // BELLMAN_FORD_HPP
