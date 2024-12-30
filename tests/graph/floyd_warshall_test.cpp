#include "../src/graph/floyd_warshall.hpp"

#include <gtest/gtest.h>

#include <limits>

class FloydWarshallTest : public ::testing::Test {
protected:
  const double INF = std::numeric_limits<double>::infinity();
};

// Basic test: a small directed graph with 4 vertices
TEST_F(FloydWarshallTest, SimpleGraph) {
  // We'll create a 4x4 distance matrix with the following edges:
  // 0 -> 1 (5), 0 -> 3 (10), 1 -> 2 (3), 2 -> 3 (1)
  // If there's no direct edge, we set it to INF.
  // dist[i][i] = 0 for all i.

  std::vector<std::vector<double>> dist = {
      {0.0, 5.0, INF, 10.0}, {INF, 0.0, 3.0, INF}, {INF, INF, 0.0, 1.0}, {INF, INF, INF, 0.0}};

  // Run Floyd–Warshall
  floydWarshall(dist);
  // After computing:
  // 0 -> 1 = 5
  // 0 -> 2 = 5 + 3 = 8
  // 0 -> 3 = 0->2->3 = 8 + 1 = 9  (direct edge was 10, but cheaper path exists)
  EXPECT_DOUBLE_EQ(dist[0][1], 5.0);
  EXPECT_DOUBLE_EQ(dist[0][2], 8.0);
  EXPECT_DOUBLE_EQ(dist[0][3], 9.0);
  // 1 -> 3 = 3 + 1 = 4
  EXPECT_DOUBLE_EQ(dist[1][3], 4.0);
  // 2 -> 3 = 1
  EXPECT_DOUBLE_EQ(dist[2][3], 1.0);
}

// Test a graph with no paths between distinct vertices
TEST_F(FloydWarshallTest, NoPaths) {
  // 3 vertices, no edges (except self-loops with cost 0)
  std::vector<std::vector<double>> dist = {{0.0, INF, INF}, {INF, 0.0, INF}, {INF, INF, 0.0}};
  floydWarshall(dist);
  // No paths between different vertices remain INF
  EXPECT_DOUBLE_EQ(dist[0][0], 0.0);
  EXPECT_TRUE(dist[0][1] == INF);
  EXPECT_TRUE(dist[1][2] == INF);
  EXPECT_DOUBLE_EQ(dist[2][2], 0.0);
}
