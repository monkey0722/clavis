#include "../../src/sorting/radix_sort.hpp"

#include <gtest/gtest.h>

TEST(RadixSortTest, SortsPositiveIntegers) {
  std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
  std::vector<int> expected = {2, 24, 45, 66, 75, 90, 170, 802};
  radixSort(arr);
  EXPECT_EQ(arr, expected);
}

TEST(RadixSortTest, HandlesEmptyArray) {
  std::vector<int> arr;
  radixSort(arr);
  EXPECT_TRUE(arr.empty());
}

TEST(RadixSortTest, HandlesSingleDigitNumbers) {
  std::vector<int> arr = {9, 4, 1, 7, 2, 5};
  std::vector<int> expected = {1, 2, 4, 5, 7, 9};
  radixSort(arr);
  EXPECT_EQ(arr, expected);
}
