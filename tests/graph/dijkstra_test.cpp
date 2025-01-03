#include "../src/graph/dijkstra.hpp"

#include <gtest/gtest.h>

/**
 * @brief Test fixture for Dijkstra's Algorithm
 */
class DijkstraTest : public ::testing::Test {
 protected:
  // Optional: Setup or teardown can be defined here if needed
};

/**
 * @test Basic test for small graph
 */
TEST_F(DijkstraTest, SmallGraph) {
  // Create a small graph
  // 0 -> (1, cost=2), (2, cost=4)
  // 1 -> (2, cost=1)
  // 2 -> (3, cost=3)
  // 3 -> none
  std::vector<std::vector<Edge>> graph(4);
  graph[0].push_back({1, 2});
  graph[0].push_back({2, 4});
  graph[1].push_back({2, 1});
  graph[2].push_back({3, 3});

  // Run Dijkstra from node 0
  std::vector<long long> dist = dijkstra(graph, 0);

  // Check distances
  // - dist[0] should be 0
  // - dist[1] should be 2
  // - dist[2] should be 3 (via 0->1->2)
  // - dist[3] should be 6 (0->1->2->3 with cost = 2+1+3 = 6)
  EXPECT_EQ(dist[0], 0);
  EXPECT_EQ(dist[1], 2);
  EXPECT_EQ(dist[2], 3);
  EXPECT_EQ(dist[3], 6);
}

/**
 * @test Test with disconnected nodes
 */
TEST_F(DijkstraTest, DisconnectedGraph) {
  // Create a graph with 5 nodes, and some edges:
  // 0 -> (1, cost=2)
  // 1 -> no edges
  // 2 -> (3, cost=1)
  // 3 -> no edges
  // 4 -> no edges (completely isolated)
  std::vector<std::vector<Edge>> graph(5);
  graph[0].push_back({1, 2});
  graph[2].push_back({3, 1});

  // Run Dijkstra from node 0
  std::vector<long long> dist = dijkstra(graph, 0);

  // Check distances
  // - dist[0] = 0
  // - dist[1] = 2
  // - dist[2] = INF (since there's no path from 0 to 2)
  // - dist[3] = INF (since there's no path from 0 to 3)
  // - dist[4] = INF (isolated)
  EXPECT_EQ(dist[0], 0);
  EXPECT_EQ(dist[1], 2);
  EXPECT_EQ(dist[2], std::numeric_limits<long long>::max());
  EXPECT_EQ(dist[3], std::numeric_limits<long long>::max());
  EXPECT_EQ(dist[4], std::numeric_limits<long long>::max());
}
