#include "../src/data_structure/fenwick_tree.hpp"

#include <gtest/gtest.h>

class FenwickTreeTest : public ::testing::Test {
protected:
  // No special setup needed here, but we could create common data if required
};

TEST_F(FenwickTreeTest, BasicOperations) {
  FenwickTree fenw(10);

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(fenw.query(i), 0);
  }

  // Update index 3 by +5
  fenw.update(3, 5);
  EXPECT_EQ(fenw.query(3), 5);
  EXPECT_EQ(fenw.query(4), 5);

  // Update index 5 by +2
  fenw.update(5, 2);
  EXPECT_EQ(fenw.query(3), 5);
  EXPECT_EQ(fenw.query(5), 7);

  // Check range queries
  EXPECT_EQ(fenw.rangeQuery(3, 5), 5 + 0 + 2);

  // Update index 3 by +2 more => total at idx=3 becomes 7
  fenw.update(3, 2);
  EXPECT_EQ(fenw.query(3), 7);
  EXPECT_EQ(fenw.query(5), 9);
}

TEST_F(FenwickTreeTest, LargeUpdates) {
  const int N = 5;
  FenwickTree fenw(N);

  std::vector<int> arr = {10, -5, 0, 5, 1};

  for (int i = 0; i < N; i++) {
    fenw.update(i, arr[i]);
  }

  int runningSum = 0;
  for (int i = 0; i < N; i++) {
    runningSum += arr[i];
    EXPECT_EQ(fenw.query(i), runningSum) << "Mismatch in prefix sum at index " << i;
  }

  // Test range queries
  // sum of [1..3] => arr[1] + arr[2] + arr[3] = -5 + 0 + 5 = 0
  EXPECT_EQ(fenw.rangeQuery(1, 3), 0);
}
