#include <gtest/gtest.h>

#include "../src/merge_sort.hpp"

TEST(MergeSortTest, SortsIntegerArray) {
  std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
  std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
  mergeSort(arr);
  EXPECT_EQ(arr, expected);
}

TEST(MergeSortTest, SortsEmptyArray) {
  std::vector<int> arr;
  mergeSort(arr);
  EXPECT_TRUE(arr.empty());
}

TEST(MergeSortTest, SortsSingleElementArray) {
  std::vector<int> arr = {1};
  mergeSort(arr);
  EXPECT_EQ(arr, std::vector<int>{1});
}

TEST(MergeSortTest, HandlesRepeatedElements) {
  std::vector<int> arr = {3, 1, 4, 1, 5};
  std::vector<int> expected = {1, 1, 3, 4, 5};
  mergeSort(arr);
  EXPECT_EQ(arr, expected);
}
