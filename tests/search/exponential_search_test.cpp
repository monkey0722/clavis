#include "../src/search/exponential_search.hpp"

#include <gtest/gtest.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

TEST(ExponentialSearchTest, FindsValueAtBeginning) {
  const std::vector<int> values = {1, 3, 5, 7, 9};

  EXPECT_EQ(clavis::search::exponential_search(values, 1), std::optional<std::size_t>{0});
}

TEST(ExponentialSearchTest, FindsValueInMiddle) {
  const std::vector<int> values = {1, 3, 5, 7, 9, 11, 13, 15, 17};

  EXPECT_EQ(clavis::search::exponential_search(values, 9), std::optional<std::size_t>{4});
}

TEST(ExponentialSearchTest, FindsValueAtEnd) {
  const std::vector<int> values = {1, 3, 5, 7, 9};

  EXPECT_EQ(clavis::search::exponential_search(values, 9), std::optional<std::size_t>{4});
}

TEST(ExponentialSearchTest, ReturnsFirstDuplicate) {
  const std::vector<int> values = {1, 2, 2, 2, 3};

  EXPECT_EQ(clavis::search::exponential_search(values, 2), std::optional<std::size_t>{1});
}

TEST(ExponentialSearchTest, ReturnsNulloptWhenValueIsAbsent) {
  const std::vector<int> values = {1, 3, 5, 7, 9};

  EXPECT_EQ(clavis::search::exponential_search(values, 0), std::nullopt);
  EXPECT_EQ(clavis::search::exponential_search(values, 6), std::nullopt);
  EXPECT_EQ(clavis::search::exponential_search(values, 10), std::nullopt);
}

TEST(ExponentialSearchTest, HandlesSingleValue) {
  const std::vector<int> values = {42};

  EXPECT_EQ(clavis::search::exponential_search(values, 42), std::optional<std::size_t>{0});
  EXPECT_EQ(clavis::search::exponential_search(values, 7), std::nullopt);
}

TEST(ExponentialSearchTest, HandlesEmptySequence) {
  const std::vector<int> values;

  EXPECT_EQ(clavis::search::exponential_search(values, 1), std::nullopt);
}

TEST(ExponentialSearchTest, SupportsStrings) {
  const std::vector<std::string> values = {"ant", "bee", "cat", "dog"};
  const std::string target = "dog";

  EXPECT_EQ(clavis::search::exponential_search(values, target), std::optional<std::size_t>{3});
}
