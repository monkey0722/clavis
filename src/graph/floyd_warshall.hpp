#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <limits>
#include <vector>

// Floyd–Warshall Algorithm
// This function computes the shortest paths between all pairs of vertices
// in a weighted graph (which may include negative edge weights, but no negative cycles).
//
// 'dist' is a 2D matrix of size n x n (n = dist.size()) representing the edge costs.
//   - If there is no direct edge between i and j, dist[i][j] should be set to
//     a large value, like std::numeric_limits<double>::infinity().
//   - dist[i][i] should be 0 for all i.
//
// The function updates 'dist' in place so that dist[i][j] will represent
// the shortest path cost from i to j after the algorithm finishes.
inline void floydWarshall(std::vector<std::vector<double>>& dist) {
  std::size_t n = dist.size();
  for (std::size_t k = 0; k < n; k++) {
    for (std::size_t i = 0; i < n; i++) {
      for (std::size_t j = 0; j < n; j++) {
        // If going through k offers a shorter path i->k->j, update it.
        // dist[i][k] + dist[k][j] < dist[i][j]
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
}

#endif  // FLOYD_WARSHALL_HPP
