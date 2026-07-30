#include "../src/graph/prim.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

void addUndirectedEdge(std::vector<std::vector<PrimEdge>>& graph, std::size_t first,
                       std::size_t second, long long weight) {
  graph[first].push_back({second, weight});
  graph[second].push_back({first, weight});
}

}  // namespace

TEST(PrimTest, ComputesMinimumSpanningTree) {
  std::vector<std::vector<PrimEdge>> graph(4);
  addUndirectedEdge(graph, 0, 1, 1);
  addUndirectedEdge(graph, 0, 2, 4);
  addUndirectedEdge(graph, 1, 2, 2);
  addUndirectedEdge(graph, 1, 3, 5);
  addUndirectedEdge(graph, 2, 3, 3);

  const PrimResult result = prim(graph);

  EXPECT_TRUE(result.isConnected);
  EXPECT_EQ(result.edges.size(), 3);
  EXPECT_EQ(result.totalWeight, 6);
}

TEST(PrimTest, SupportsNegativeWeights) {
  std::vector<std::vector<PrimEdge>> graph(3);
  addUndirectedEdge(graph, 0, 1, -2);
  addUndirectedEdge(graph, 1, 2, 1);
  addUndirectedEdge(graph, 0, 2, 4);

  const PrimResult result = prim(graph);

  EXPECT_TRUE(result.isConnected);
  EXPECT_EQ(result.edges.size(), 2);
  EXPECT_EQ(result.totalWeight, -1);
}

TEST(PrimTest, ReportsDisconnectedGraph) {
  std::vector<std::vector<PrimEdge>> graph(4);
  addUndirectedEdge(graph, 0, 1, 2);
  addUndirectedEdge(graph, 2, 3, 1);

  const PrimResult result = prim(graph);

  EXPECT_FALSE(result.isConnected);
  EXPECT_EQ(result.edges.size(), 1);
  EXPECT_EQ(result.totalWeight, 2);
}

TEST(PrimTest, SupportsDifferentStartVertex) {
  std::vector<std::vector<PrimEdge>> graph(3);
  addUndirectedEdge(graph, 0, 1, 3);
  addUndirectedEdge(graph, 1, 2, 1);
  addUndirectedEdge(graph, 0, 2, 2);

  const PrimResult result = prim(graph, 2);

  EXPECT_TRUE(result.isConnected);
  EXPECT_EQ(result.totalWeight, 3);
}

TEST(PrimTest, AcceptsEmptyGraph) {
  const std::vector<std::vector<PrimEdge>> graph;

  const PrimResult result = prim(graph);

  EXPECT_TRUE(result.isConnected);
  EXPECT_TRUE(result.edges.empty());
  EXPECT_EQ(result.totalWeight, 0);
}

TEST(PrimTest, RejectsInvalidStartVertex) {
  const std::vector<std::vector<PrimEdge>> graph(2);

  EXPECT_THROW((void)prim(graph, 2), std::out_of_range);
}

TEST(PrimTest, RejectsInvalidEdgeEndpoint) {
  const std::vector<std::vector<PrimEdge>> graph = {{{2, 1}}, {}};

  EXPECT_THROW((void)prim(graph), std::out_of_range);
}
