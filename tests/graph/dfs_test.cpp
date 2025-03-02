#include "../src/graph/dfs.hpp"

#include <gtest/gtest.h>

TEST(DFSTest, BasicTraversal) {
  DFS<int> dfs;

  dfs.addEdge(0, 1);
  dfs.addEdge(0, 2);
  dfs.addEdge(2, 3);
  dfs.addEdge(2, 4);

  auto result = dfs.traverse(0);

  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], 0);
  // DFS will go deep first, so we expect a different order than BFS
  EXPECT_TRUE((result[1] == 1 && result[2] == 2) || (result[1] == 2 && result[3] == 3));
}

TEST(DFSTest, RecursiveTraversal) {
  DFS<int> dfs;

  dfs.addEdge(0, 1);
  dfs.addEdge(0, 2);
  dfs.addEdge(2, 3);
  dfs.addEdge(2, 4);

  auto result = dfs.traverseRecursive(0);

  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], 0);
  // The recursive DFS should follow the order of adjacency list
}

TEST(DFSTest, FindPath) {
  DFS<int> dfs;

  // Add an edge as an unoriented graph
  dfs.addEdge(0, 1);
  dfs.addEdge(1, 0);
  dfs.addEdge(0, 2);
  dfs.addEdge(2, 0);
  dfs.addEdge(0, 3);
  dfs.addEdge(3, 0);
  dfs.addEdge(2, 3);
  dfs.addEdge(3, 2);

  auto path = dfs.findPath(1, 3);

  ASSERT_GT(path.size(), 0);
  EXPECT_EQ(path[0], 1);
  EXPECT_EQ(path[path.size() - 1], 3);
}

TEST(DFSTest, CycleDetection) {
  DFS<int> dfs1;

  // Create a graph with a cycle
  dfs1.addEdge(0, 1);
  dfs1.addEdge(1, 2);
  dfs1.addEdge(2, 0);

  EXPECT_TRUE(dfs1.hasCycle());

  DFS<int> dfs2;

  // Create a graph without a cycle (DAG)
  dfs2.addEdge(0, 1);
  dfs2.addEdge(0, 2);
  dfs2.addEdge(1, 3);
  dfs2.addEdge(2, 3);

  EXPECT_FALSE(dfs2.hasCycle());
}

TEST(DFSTest, TopologicalSort) {
  DFS<int> dfs;

  // Create a DAG
  dfs.addEdge(5, 2);
  dfs.addEdge(5, 0);
  dfs.addEdge(4, 0);
  dfs.addEdge(4, 1);
  dfs.addEdge(2, 3);
  dfs.addEdge(3, 1);

  auto result = dfs.topologicalSort();

  ASSERT_EQ(result.size(), 6);
  
  // Check that for each edge (u, v), u comes before v in the topological sort
  std::unordered_map<int, int> position;
  for (size_t i = 0; i < result.size(); ++i) {
    position[result[i]] = i;
  }
  
  EXPECT_LT(position[5], position[2]);
  EXPECT_LT(position[5], position[0]);
  EXPECT_LT(position[4], position[0]);
  EXPECT_LT(position[4], position[1]);
  EXPECT_LT(position[2], position[3]);
  EXPECT_LT(position[3], position[1]);
}

TEST(DFSTest, ConnectedComponents) {
  DFS<int> dfs;

  // As an undirected graph, follow the edges
  dfs.addEdge(0, 1);
  dfs.addEdge(1, 0);
  dfs.addEdge(1, 2);
  dfs.addEdge(2, 1);

  dfs.addEdge(3, 4);
  dfs.addEdge(4, 3);

  // Isolated points are also tracked
  dfs.addEdge(5, 5);

  EXPECT_EQ(dfs.countConnectedComponents(), 3);
}

TEST(DFSTest, CustomNodeType) {
  DFS<std::string> dfs;

  dfs.addEdge("A", "B");
  dfs.addEdge("B", "A");
  dfs.addEdge("B", "C");
  dfs.addEdge("C", "B");

  auto result = dfs.traverse("A");

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "A");
  // The order may vary depending on the implementation
  EXPECT_TRUE((result[1] == "B" && result[2] == "C") || (result[1] == "C" && result[2] == "B"));
}
