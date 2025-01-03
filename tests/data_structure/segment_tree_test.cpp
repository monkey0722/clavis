#include "../src/data_structure/segment_tree.hpp"

#include <gtest/gtest.h>

/**
 * @brief Test fixture for SegmentTree.
 */
class SegmentTreeTest : public ::testing::Test {
protected:
  // We can define common setup or data here if needed.
};

/**
 * @test Basic test for sum operation
 */
TEST_F(SegmentTreeTest, SumOperation) {
  // Prepare data
  std::vector<int> data = {1, 2, 3, 4, 5};

  // Create a segment tree for sum operation
  auto sumOp = [](int a, int b) { return a + b; };
  SegmentTree<int> segTree(data, sumOp, 0);

  // Check query results
  // Query for the sum of the entire range [0, 5)
  EXPECT_EQ(segTree.query(0, 5), 15);

  // Query for [1, 3) -> 2 + 3 = 5
  EXPECT_EQ(segTree.query(1, 3), 5);

  // Query for [2, 5) -> 3 + 4 + 5 = 12
  EXPECT_EQ(segTree.query(2, 5), 12);

  // Update index 2 to 10 -> data becomes {1, 2, 10, 4, 5}
  segTree.update(2, 10);

  // Check queries after update
  // [0, 5) -> 1 + 2 + 10 + 4 + 5 = 22
  EXPECT_EQ(segTree.query(0, 5), 22);
  // [2, 5) -> 10 + 4 + 5 = 19
  EXPECT_EQ(segTree.query(2, 5), 19);
}

/**
 * @test Basic test for minimum operation
 */
TEST_F(SegmentTreeTest, MinOperation) {
  std::vector<int> data = {5, 4, 3, 2, 1};

  // Create a segment tree for min operation
  auto minOp = [](int a, int b) { return std::min(a, b); };
  int inf = std::numeric_limits<int>::max();
  SegmentTree<int> segTree(data, minOp, inf);

  // [0, 5) -> Min among 5,4,3,2,1 = 1
  EXPECT_EQ(segTree.query(0, 5), 1);

  // [1, 4) -> Min among 4,3,2 = 2
  EXPECT_EQ(segTree.query(1, 4), 2);

  // Update index 4 to 6 -> data becomes {5, 4, 3, 2, 6}
  segTree.update(4, 6);

  // Now the min in [0, 5) -> 2
  EXPECT_EQ(segTree.query(0, 5), 2);
}
