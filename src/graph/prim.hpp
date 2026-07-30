#ifndef PRIM_HPP
#define PRIM_HPP

#include <cstddef>
#include <functional>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

struct PrimEdge {
  std::size_t to;
  long long weight;
};

struct PrimTreeEdge {
  std::size_t from;
  std::size_t to;
  long long weight;
};

struct PrimResult {
  std::vector<PrimTreeEdge> edges;
  long long totalWeight;
  bool isConnected;
};

/**
 * @brief Computes a minimum spanning tree using Prim's algorithm.
 *
 * The graph must be undirected, with each edge present in both adjacency
 * lists. For a disconnected graph, the result contains the tree for the
 * connected component containing the start vertex.
 *
 * @param graph Undirected weighted graph represented as an adjacency list.
 * @param start Vertex from which to grow the tree.
 * @return Tree edges, their total weight, and whether every vertex was reached.
 * @throws std::out_of_range If the start vertex or an edge endpoint is invalid.
 *
 * @note The total tree weight must fit in a long long.
 * @complexity O(E log E) time and O(V + E) additional space.
 */
[[nodiscard]] inline PrimResult prim(const std::vector<std::vector<PrimEdge>>& graph,
                                     std::size_t start = 0) {
  if (graph.empty()) {
    return {
        .edges = {},
        .totalWeight = 0,
        .isConnected = true,
    };
  }
  if (start >= graph.size()) {
    throw std::out_of_range("Start vertex is out of range");
  }

  for (const auto& adjacentEdges : graph) {
    for (const auto& edge : adjacentEdges) {
      if (edge.to >= graph.size()) {
        throw std::out_of_range("Edge endpoint is out of range");
      }
    }
  }

  using QueueEntry = std::tuple<long long, std::size_t, std::size_t>;
  std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<>> queue;
  std::vector<bool> visited(graph.size(), false);
  std::vector<PrimTreeEdge> treeEdges;
  long long totalWeight = 0;
  std::size_t visitedCount = 1;

  visited[start] = true;
  for (const auto& edge : graph[start]) {
    queue.emplace(edge.weight, start, edge.to);
  }

  while (!queue.empty() && visitedCount < graph.size()) {
    const auto [weight, from, to] = queue.top();
    queue.pop();

    if (visited[to]) {
      continue;
    }

    visited[to] = true;
    ++visitedCount;
    treeEdges.push_back({
        .from = from,
        .to = to,
        .weight = weight,
    });
    totalWeight += weight;

    for (const auto& edge : graph[to]) {
      if (!visited[edge.to]) {
        queue.emplace(edge.weight, to, edge.to);
      }
    }
  }

  return {
      .edges = std::move(treeEdges),
      .totalWeight = totalWeight,
      .isConnected = visitedCount == graph.size(),
  };
}

#endif  // PRIM_HPP
