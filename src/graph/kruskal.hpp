#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <algorithm>
#include <concepts>
#include <iostream>
#include <vector>

/**
 * @brief Edge structure for Kruskal's algorithm
 */
struct KruskalEdge {
  int from;
  int to;
  long long weight;

  // Operator for sorting edges by weight
  bool operator<(const KruskalEdge& other) const {
    return weight < other.weight;
  }
};

/**
 * @brief Disjoint Set Union (DSU) data structure for Kruskal's algorithm
 */
class DisjointSet {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  /**
   * @brief Initialize a DSU with n elements
   * @param n Number of elements
   */
  DisjointSet(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; i++) {
      parent[i] = i;  // Each element is its own parent initially
    }
  }

  /**
   * @brief Find the representative of the set containing x
   * @param x Element to find
   * @return Representative of the set
   */
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);  // Path compression
    }
    return parent[x];
  }

  /**
   * @brief Union of two sets
   * @param x First element
   * @param y Second element
   * @return True if x and y were in different sets, false otherwise
   */
  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return false;  // Already in the same set
    }

    // Union by rank
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }

    return true;
  }
};

/**
 * @brief Kruskal's algorithm for finding the Minimum Spanning Tree (MST) of a graph
 *
 * @param n Number of vertices in the graph
 * @param edges Vector of edges in the graph
 * @return Vector of edges that form the MST and the total weight of the MST
 */
std::pair<std::vector<KruskalEdge>, long long> kruskal(int n, std::vector<KruskalEdge>& edges) {
  // Sort edges by weight
  std::sort(edges.begin(), edges.end());

  DisjointSet dsu(n);
  std::vector<KruskalEdge> mst;
  long long totalWeight = 0;

  for (const auto& edge : edges) {
    if (dsu.unite(edge.from, edge.to)) {
      // This edge is part of the MST
      mst.push_back(edge);
      totalWeight += edge.weight;

      // If we have n-1 edges, we have a complete MST
      if (mst.size() == n - 1) {
        break;
      }
    }
  }

  return {mst, totalWeight};
}

/**
 * @brief Check if the graph is connected
 *
 * @param n Number of vertices
 * @param mst The MST edges
 * @return True if the graph is connected, false otherwise
 */
bool isConnected(int n, const std::vector<KruskalEdge>& mst) {
  return mst.size() == n - 1;
}

#endif  // KRUSKAL_HPP
