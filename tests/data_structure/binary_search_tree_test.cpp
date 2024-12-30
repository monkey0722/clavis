#include "../src/data_structure/binary_search_tree.hpp"

#include <gtest/gtest.h>

TEST(BinarySearchTreeTest, BasicOperations) {
  BinarySearchTree<int> bst;

  EXPECT_TRUE(bst.empty());
  EXPECT_EQ(bst.size(), 0);

  bst.insert(5);
  bst.insert(3);
  bst.insert(7);

  EXPECT_FALSE(bst.empty());
  EXPECT_EQ(bst.size(), 3);
  EXPECT_TRUE(bst.contains(5));
  EXPECT_TRUE(bst.contains(3));
  EXPECT_TRUE(bst.contains(7));
  EXPECT_FALSE(bst.contains(4));
}

TEST(BinarySearchTreeTest, MinMax) {
  BinarySearchTree<int> bst;

  EXPECT_FALSE(bst.minimum().has_value());
  EXPECT_FALSE(bst.maximum().has_value());

  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  bst.insert(1);
  bst.insert(9);

  EXPECT_EQ(bst.minimum().value(), 1);
  EXPECT_EQ(bst.maximum().value(), 9);
}

TEST(BinarySearchTreeTest, Removal) {
  BinarySearchTree<int> bst;

  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  bst.insert(1);
  bst.insert(9);

  EXPECT_TRUE(bst.remove(3));
  EXPECT_FALSE(bst.contains(3));
  EXPECT_TRUE(bst.contains(1));

  EXPECT_TRUE(bst.remove(5));
  EXPECT_FALSE(bst.contains(5));

  EXPECT_FALSE(bst.remove(10));
}

TEST(BinarySearchTreeTest, Traversal) {
  BinarySearchTree<int> bst;
  std::vector<int> result;

  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  bst.insert(1);
  bst.insert(9);

  // Test inorder traversal
  bst.inorderTraversal([&result](const int& value) { result.push_back(value); });

  std::vector<int> expected = {1, 3, 5, 7, 9};
  EXPECT_EQ(result, expected);

  // Test level order traversal
  result.clear();
  bst.levelOrderTraversal([&result](const int& value) { result.push_back(value); });

  expected = {5, 3, 7, 1, 9};
  EXPECT_EQ(result, expected);
}
