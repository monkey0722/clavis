#include "../src/graph/bellman_ford.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <vector>

TEST(BellmanFordTest, ComputesShortestPathsWithNegativeEdges) {
  const std::vector<BellmanFordEdge> edges = {
      {0, 1, 6},  {0, 2, 7}, {1, 2, 8},  {1, 3, 5}, {1, 4, -4},
      {2, 3, -3}, {2, 4, 9}, {3, 1, -2}, {4, 0, 2}, {4, 3, 7},
  };

  const BellmanFordResult result = bellmanFord(5, edges, 0);

  EXPECT_FALSE(result.hasNegativeCycle);
  EXPECT_EQ(result.distances, (std::vector<long long>{0, 2, 7, 4, -2}));
}

TEST(BellmanFordTest, LeavesUnreachableVerticesAtInfinity) {
  const std::vector<BellmanFordEdge> edges = {{0, 1, 3}};

  const BellmanFordResult result = bellmanFord(3, edges, 0);

  EXPECT_FALSE(result.hasNegativeCycle);
  EXPECT_EQ(result.distances[0], 0);
  EXPECT_EQ(result.distances[1], 3);
  EXPECT_EQ(result.distances[2], std::numeric_limits<long long>::max());
}

TEST(BellmanFordTest, DetectsReachableNegativeCycle) {
  const std::vector<BellmanFordEdge> edges = {
      {0, 1, 1},
      {1, 2, -2},
      {2, 1, -2},
  };

  const BellmanFordResult result = bellmanFord(3, edges, 0);

  EXPECT_TRUE(result.hasNegativeCycle);
}

TEST(BellmanFordTest, IgnoresUnreachableNegativeCycle) {
  const std::vector<BellmanFordEdge> edges = {
      {0, 1, 2},
      {2, 3, -1},
      {3, 2, -1},
  };

  const BellmanFordResult result = bellmanFord(4, edges, 0);

  EXPECT_FALSE(result.hasNegativeCycle);
}

TEST(BellmanFordTest, RejectsInvalidSource) {
  const std::vector<BellmanFordEdge> edges;

  EXPECT_THROW((void)bellmanFord(3, edges, 3), std::out_of_range);
}

TEST(BellmanFordTest, RejectsInvalidEdgeEndpoint) {
  const std::vector<BellmanFordEdge> edges = {{0, 3, 1}};

  EXPECT_THROW((void)bellmanFord(3, edges, 0), std::out_of_range);
}
