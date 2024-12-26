#include <gtest/gtest.h>

#include "../src/heap_sort.hpp"

TEST(HeapSortTest, SortsIntegerArray) {
  std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
  std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
  heapSort(arr);
  EXPECT_EQ(arr, expected);
}

TEST(HeapSortTest, SortsEmptyArray) {
  std::vector<int> arr;
  heapSort(arr);
  EXPECT_TRUE(arr.empty());
}

TEST(HeapSortTest, SortsSingleElementArray) {
  std::vector<int> arr = {1};
  heapSort(arr);
  EXPECT_EQ(arr, std::vector<int>{1});
}

TEST(HeapSortTest, HandlesRepeatedElements) {
  std::vector<int> arr = {3, 1, 4, 1, 5};
  std::vector<int> expected = {1, 1, 3, 4, 5};
  heapSort(arr);
  EXPECT_EQ(arr, expected);
}
