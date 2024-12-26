#include <gtest/gtest.h>

#include "../src/quick_sort.hpp"

TEST(QuickSortTest, SortsIntegerArray) {
  std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
  std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
  quickSort(arr);
  EXPECT_EQ(arr, expected);
}

TEST(QuickSortTest, SortsEmptyArray) {
  std::vector<int> arr;
  quickSort(arr);
  EXPECT_TRUE(arr.empty());
}

TEST(QuickSortTest, SortsSingleElementArray) {
  std::vector<int> arr = {1};
  quickSort(arr);
  EXPECT_EQ(arr, std::vector<int>{1});
}

TEST(QuickSortTest, HandlesRepeatedElements) {
  std::vector<int> arr = {3, 1, 4, 1, 5};
  std::vector<int> expected = {1, 1, 3, 4, 5};
  quickSort(arr);
  EXPECT_EQ(arr, expected);
}
