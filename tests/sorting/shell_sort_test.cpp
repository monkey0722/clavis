#include "../../src/sorting/shell_sort.hpp"

#include <gtest/gtest.h>

TEST(ShellSortTest, SortsIntegerArray) {
  std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
  std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
  shellSort(arr);
  EXPECT_EQ(arr, expected);
}

TEST(ShellSortTest, SortsEmptyArray) {
  std::vector<int> arr;
  shellSort(arr);
  EXPECT_TRUE(arr.empty());
}

TEST(ShellSortTest, HandlesRepeatedElements) {
  std::vector<int> arr = {3, 1, 4, 1, 5};
  std::vector<int> expected = {1, 1, 3, 4, 5};
  shellSort(arr);
  EXPECT_EQ(arr, expected);
}
