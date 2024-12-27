#include "../../src/sorting/bubble_sort.hpp"

#include <gtest/gtest.h>

TEST(BubbleSortTest, SortsIntegerArray) {
  std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
  std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};

  bubbleSort(arr);

  EXPECT_EQ(arr, expected);
}

TEST(BubbleSortTest, SortsEmptyArray) {
  std::vector<int> arr;
  bubbleSort(arr);
  EXPECT_TRUE(arr.empty());
}

TEST(BubbleSortTest, SortsSingleElementArray) {
  std::vector<int> arr = {1};
  bubbleSort(arr);
  EXPECT_EQ(arr, std::vector<int>{1});
}

TEST(BubbleSortTest, HandlesRepeatedElements) {
  std::vector<int> arr = {3, 1, 4, 1, 5};
  std::vector<int> expected = {1, 1, 3, 4, 5};

  bubbleSort(arr);

  EXPECT_EQ(arr, expected);
}