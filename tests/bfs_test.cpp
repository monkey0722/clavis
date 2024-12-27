#include "../src/bfs.hpp"

#include <gtest/gtest.h>

TEST(BFSTest, BasicTraversal) {
  BFS<int> bfs;

  bfs.addEdge(0, 1);
  bfs.addEdge(0, 2);
  bfs.addEdge(2, 3);
  bfs.addEdge(2, 4);

  auto result = bfs.traverse(0);

  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0], 0);
  EXPECT_TRUE(result[1] == 1 || result[1] == 2);
  EXPECT_TRUE(result[2] == 1 || result[2] == 2);
  EXPECT_TRUE(result[3] == 3 || result[3] == 4);
  EXPECT_TRUE(result[4] == 3 || result[4] == 4);
}

TEST(BFSTest, ShortestPath) {
  BFS<int> bfs;

  // Add an edge as an unoriented graph
  bfs.addEdge(0, 1);
  bfs.addEdge(1, 0);  // Follow the opposite direction too
  bfs.addEdge(0, 2);
  bfs.addEdge(2, 0);
  bfs.addEdge(0, 3);
  bfs.addEdge(3, 0);
  bfs.addEdge(2, 3);
  bfs.addEdge(3, 2);

  auto path = bfs.findShortestPath(1, 3);

  ASSERT_EQ(path.size(), 3);
  EXPECT_EQ(path[0], 1);
  EXPECT_EQ(path[1], 0);
  EXPECT_EQ(path[2], 3);
}

TEST(BFSTest, ConnectedComponents) {
  BFS<int> bfs;

  // As an undirected graph, follow the edges
  bfs.addEdge(0, 1);
  bfs.addEdge(1, 0);
  bfs.addEdge(1, 2);
  bfs.addEdge(2, 1);

  bfs.addEdge(3, 4);
  bfs.addEdge(4, 3);

  // Isolated points are also tracked
  bfs.addEdge(5, 5);

  EXPECT_EQ(bfs.countConnectedComponents(), 3);
}

TEST(BFSTest, CustomNodeType) {
  BFS<std::string> bfs;

  bfs.addEdge("A", "B");
  bfs.addEdge("B", "A");
  bfs.addEdge("B", "C");
  bfs.addEdge("C", "B");

  auto result = bfs.traverse("A");

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "A");
  EXPECT_EQ(result[1], "B");
  EXPECT_EQ(result[2], "C");
}
