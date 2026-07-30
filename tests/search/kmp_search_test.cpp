#include "../src/search/kmp_search.hpp"

#include <gtest/gtest.h>

#include <cstddef>
#include <optional>

TEST(KmpSearchTest, FindsPatternAtBeginning) {
  const std::optional<std::size_t> result = clavis::search::kmp_search("algorithm", "algo");

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 0);
}

TEST(KmpSearchTest, FindsPatternInMiddle) {
  const std::optional<std::size_t> result =
      clavis::search::kmp_search("the quick brown fox", "quick");

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 4);
}

TEST(KmpSearchTest, FindsPatternAtEnd) {
  const std::optional<std::size_t> result = clavis::search::kmp_search("searching", "ing");

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 6);
}

TEST(KmpSearchTest, ReturnsFirstOccurrence) {
  const std::optional<std::size_t> result = clavis::search::kmp_search("aaaaa", "aaa");

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 0);
}

TEST(KmpSearchTest, HandlesPrefixFallback) {
  const std::optional<std::size_t> result = clavis::search::kmp_search("abababac", "ababac");

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 2);
}

TEST(KmpSearchTest, ReturnsNulloptWhenPatternIsAbsent) {
  EXPECT_EQ(clavis::search::kmp_search("algorithm", "rhythm"), std::nullopt);
}

TEST(KmpSearchTest, EmptyPatternMatchesAtBeginning) {
  const std::optional<std::size_t> result = clavis::search::kmp_search("algorithm", "");

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(*result, 0);
}

TEST(KmpSearchTest, NonEmptyPatternDoesNotMatchEmptyText) {
  EXPECT_EQ(clavis::search::kmp_search("", "pattern"), std::nullopt);
}
