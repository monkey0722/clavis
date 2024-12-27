#include "../src/sample.h"

#include <gtest/gtest.h>

// Extract even numbers
TEST(FilterEvenNumbersTest, BasicTest) {
  std::vector<int> input = {1, 2, 3, 4, 5, 6};
  std::vector<int> expected = {2, 4, 6};
  EXPECT_EQ(filter_even_numbers(input), expected);
}

// Blank entry
TEST(FilterEvenNumbersTest, EmptyInput) {
  std::vector<int> input = {};
  std::vector<int> expected = {};
  EXPECT_EQ(filter_even_numbers(input), expected);
}

// If all numbers are odd
TEST(FilterEvenNumbersTest, AllOddNumbers) {
  std::vector<int> input = {1, 3, 5, 7};
  std::vector<int> expected = {};
  EXPECT_EQ(filter_even_numbers(input), expected);
}

// If all numbers are even
TEST(FilterEvenNumbersTest, AllEvenNumbers) {
  std::vector<int> input = {2, 4, 6, 8};
  std::vector<int> expected = {2, 4, 6, 8};
  EXPECT_EQ(filter_even_numbers(input), expected);
}
