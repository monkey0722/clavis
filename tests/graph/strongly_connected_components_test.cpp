#include "../src/graph/strongly_connected_components.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

TEST(StronglyConnectedComponentsTest, PartitionsDirectedGraph) {
  const std::vector<std::vector<std::size_t>> graph = {
      {1}, {2}, {0, 3}, {4}, {3, 5}, {},
  };

  const StronglyConnectedComponentsResult result = stronglyConnectedComponents(graph);

  ASSERT_EQ(result.components.size(), 3);
  EXPECT_EQ(result.componentOf[0], result.componentOf[1]);
  EXPECT_EQ(result.componentOf[1], result.componentOf[2]);
  EXPECT_EQ(result.componentOf[3], result.componentOf[4]);
  EXPECT_NE(result.componentOf[2], result.componentOf[3]);
  EXPECT_NE(result.componentOf[4], result.componentOf[5]);

  std::vector<std::size_t> componentSizes;
  for (const auto& component : result.components) {
    componentSizes.push_back(component.size());
  }
  std::ranges::sort(componentSizes);
  EXPECT_EQ(componentSizes, (std::vector<std::size_t>{1, 2, 3}));
}

TEST(StronglyConnectedComponentsTest, PlacesDagVerticesInSeparateComponents) {
  const std::vector<std::vector<std::size_t>> graph = {
      {1},
      {2},
      {},
  };

  const StronglyConnectedComponentsResult result = stronglyConnectedComponents(graph);

  EXPECT_EQ(result.components.size(), 3);
  EXPECT_NE(result.componentOf[0], result.componentOf[1]);
  EXPECT_NE(result.componentOf[1], result.componentOf[2]);
}

TEST(StronglyConnectedComponentsTest, FindsSingleStrongComponent) {
  const std::vector<std::vector<std::size_t>> graph = {
      {1},
      {2},
      {0},
  };

  const StronglyConnectedComponentsResult result = stronglyConnectedComponents(graph);

  ASSERT_EQ(result.components.size(), 1);
  EXPECT_EQ(result.components.front().size(), 3);
}

TEST(StronglyConnectedComponentsTest, HandlesIsolatedVertices) {
  const std::vector<std::vector<std::size_t>> graph(4);

  const StronglyConnectedComponentsResult result = stronglyConnectedComponents(graph);

  EXPECT_EQ(result.components.size(), 4);
}

TEST(StronglyConnectedComponentsTest, AcceptsEmptyGraph) {
  const std::vector<std::vector<std::size_t>> graph;

  const StronglyConnectedComponentsResult result = stronglyConnectedComponents(graph);

  EXPECT_TRUE(result.componentOf.empty());
  EXPECT_TRUE(result.components.empty());
}

TEST(StronglyConnectedComponentsTest, RejectsInvalidEdgeEndpoint) {
  const std::vector<std::vector<std::size_t>> graph = {{1}, {2}};

  EXPECT_THROW((void)stronglyConnectedComponents(graph), std::out_of_range);
}
