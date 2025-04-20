#include "../src/graph/kruskal.hpp"

#include <gtest/gtest.h>

/**
 * @brief Test fixture for Kruskal's Algorithm
 */
class KruskalTest : public ::testing::Test {
 protected:
};

/**
 * @test Basic test for small graph
 */
TEST_F(KruskalTest, SmallGraph) {
  // Create a small graph with 4 vertices
  // 0 -- (1, weight=1) -- 1
  // |                     |
  // (2, weight=2)         (4, weight=4)
  // |                     |
  // 2 -- (3, weight=3) -- 3
  std::vector<KruskalEdge> edges = {
      {0, 1, 1},  // Edge 0-1 with weight 1
      {0, 2, 2},  // Edge 0-2 with weight 2
      {2, 3, 3},  // Edge 2-3 with weight 3
      {1, 3, 4},  // Edge 1-3 with weight 4
  };

  auto [mst, totalWeight] = kruskal(4, edges);

  // The MST should include edges 0-1, 0-2, and 2-3
  // Total weight should be 1 + 2 + 3 = 6
  EXPECT_EQ(mst.size(), 3);
  EXPECT_EQ(totalWeight, 6);

  // Check if the graph is connected
  EXPECT_TRUE(isConnected(4, mst));

  // Verify the edges in the MST
  // The first edge should be 0-1 with weight 1
  EXPECT_EQ(mst[0].from, 0);
  EXPECT_EQ(mst[0].to, 1);
  EXPECT_EQ(mst[0].weight, 1);

  // The second edge should be 0-2 with weight 2
  EXPECT_EQ(mst[1].from, 0);
  EXPECT_EQ(mst[1].to, 2);
  EXPECT_EQ(mst[1].weight, 2);

  // The third edge should be 2-3 with weight 3
  EXPECT_EQ(mst[2].from, 2);
  EXPECT_EQ(mst[2].to, 3);
  EXPECT_EQ(mst[2].weight, 3);
}

/**
 * @test Test with a disconnected graph
 */
TEST_F(KruskalTest, DisconnectedGraph) {
  // Create a disconnected graph with 5 vertices
  // Component 1: 0 -- (1, weight=1) -- 1
  // Component 2: 2 -- (3, weight=3) -- 3 -- (4, weight=4) -- 4
  std::vector<KruskalEdge> edges = {
      {0, 1, 1},  // Edge 0-1 with weight 1
      {2, 3, 3},  // Edge 2-3 with weight 3
      {3, 4, 4},  // Edge 3-4 with weight 4
  };

  auto [mst, totalWeight] = kruskal(5, edges);

  // The MST should include all 3 edges
  // Total weight should be 1 + 3 + 4 = 8
  EXPECT_EQ(mst.size(), 3);
  EXPECT_EQ(totalWeight, 8);

  // Check if the graph is disconnected
  EXPECT_FALSE(isConnected(5, mst));
}

/**
 * @test Test with a cycle in the graph
 */
TEST_F(KruskalTest, CycleGraph) {
  // Create a graph with a cycle
  // 0 -- (1, weight=1) -- 1
  // |                     |
  // (4, weight=4)         (2, weight=2)
  // |                     |
  // 3 -- (3, weight=3) -- 2
  std::vector<KruskalEdge> edges = {
      {0, 1, 1},  // Edge 0-1 with weight 1
      {1, 2, 2},  // Edge 1-2 with weight 2
      {2, 3, 3},  // Edge 2-3 with weight 3
      {0, 3, 4},  // Edge 0-3 with weight 4
  };

  auto [mst, totalWeight] = kruskal(4, edges);

  // The MST should include edges 0-1, 1-2, and 2-3
  // Total weight should be 1 + 2 + 3 = 6
  EXPECT_EQ(mst.size(), 3);
  EXPECT_EQ(totalWeight, 6);

  // Check if the graph is connected
  EXPECT_TRUE(isConnected(4, mst));

  // The edge 0-3 should not be in the MST because it creates a cycle
  bool hasEdge03 = false;
  for (const auto& edge : mst) {
    if ((edge.from == 0 && edge.to == 3) || (edge.from == 3 && edge.to == 0)) {
      hasEdge03 = true;
      break;
    }
  }
  EXPECT_FALSE(hasEdge03);
}

/**
 * @test Test with multiple possible MSTs
 */
TEST_F(KruskalTest, MultipleMSTs) {
  // Create a graph where multiple MSTs are possible
  // 0 -- (1, weight=1) -- 1
  // |                     |
  // (1, weight=1)         (1, weight=1)
  // |                     |
  // 2 -- (1, weight=1) -- 3
  std::vector<KruskalEdge> edges = {
      {0, 1, 1},  // Edge 0-1 with weight 1
      {0, 2, 1},  // Edge 0-2 with weight 1
      {1, 3, 1},  // Edge 1-3 with weight 1
      {2, 3, 1},  // Edge 2-3 with weight 1
  };

  auto [mst, totalWeight] = kruskal(4, edges);

  // The MST should include 3 edges, all with weight 1
  // Total weight should be 3
  EXPECT_EQ(mst.size(), 3);
  EXPECT_EQ(totalWeight, 3);

  // Check if the graph is connected
  EXPECT_TRUE(isConnected(4, mst));
}
