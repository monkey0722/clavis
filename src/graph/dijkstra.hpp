#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <limits>
#include <queue>
#include <vector>

/**
 * @brief Edge structure representing an edge in a graph
 */
struct Edge {
  int to;
  long long cost;
};

/**
 * @brief Dijkstra's Algorithm to find the shortest path from a single source
 *        to all other vertices in a weighted graph with non-negative edge costs
 *
 * @param graph A graph represented as an adjacency list:
 *        graph[u] is a list of Edge structures from vertex u to others
 * @param start The starting vertex
 * @return A vector of distances where dist[i] is the shortest distance from start to i
 */
std::vector<long long> dijkstra(const std::vector<std::vector<Edge>>& graph, int start) {
  // Create a distance array, initialized to the maximum possible value
  std::vector<long long> dist(graph.size(), std::numeric_limits<long long>::max());
  dist[start] = 0;

  // Priority queue that always returns the pair with the smallest distance
  using Pi = std::pair<long long, int>;  // (distance, node)
  std::priority_queue<Pi, std::vector<Pi>, std::greater<Pi>> pq;
  pq.push({0, start});

  while (!pq.empty()) {
    auto [curDist, u] = pq.top();
    pq.pop();

    // If the current distance is already greater than the known shortest distance, skip
    if (curDist > dist[u]) continue;

    // Explore adjacent vertices
    for (const auto& e : graph[u]) {
      long long nd = curDist + e.cost;
      if (dist[e.to] > nd) {
        dist[e.to] = nd;
        pq.push({nd, e.to});
      }
    }
  }
  return dist;
}

#endif  // DIJKSTRA_HPP
