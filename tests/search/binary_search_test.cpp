#include "../src/search/binary_search.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>

/**
 * @brief Test fixture for Binary Search algorithms
 */
class BinarySearchTest : public ::testing::Test {
 protected:
  // Test vectors
  std::vector<int> sortedInts;
  std::vector<double> sortedDoubles;
  std::vector<std::string> sortedStrings;

  void SetUp() override {
    // Setup sorted integer array
    sortedInts = {-10, -5, 0, 1, 2, 5, 10, 20, 50, 100};

    // Setup sorted double array
    sortedDoubles = {-10.5, -5.5, 0.0, 1.5, 2.5, 5.5, 10.5, 20.5, 50.5, 100.5};

    // Setup sorted string array
    sortedStrings = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
  }
};

/**
 * @test Test basic binary search with integers
 */
TEST_F(BinarySearchTest, BasicIntSearch) {
  // Using a lambda to explicitly specify the template parameter
  auto int_binary_search = [](const std::vector<int>& arr, const int& target) {
    return clavis::search::binary_search<int>(arr, target);
  };

  // Test finding existing elements
  EXPECT_EQ(int_binary_search(sortedInts, -10), 0);
  EXPECT_EQ(int_binary_search(sortedInts, 0), 2);
  EXPECT_EQ(int_binary_search(sortedInts, 10), 6);
  EXPECT_EQ(int_binary_search(sortedInts, 100), 9);

  // Test finding non-existing elements
  EXPECT_EQ(int_binary_search(sortedInts, -100), -1);
  EXPECT_EQ(int_binary_search(sortedInts, 3), -1);
  EXPECT_EQ(int_binary_search(sortedInts, 200), -1);
}

/**
 * @test Test binary search with doubles
 */
TEST_F(BinarySearchTest, DoubleSearch) {
  // Using a lambda to explicitly specify the template parameter
  auto double_binary_search = [](const std::vector<double>& arr, const double& target) {
    return clavis::search::binary_search<double>(arr, target);
  };

  // Test finding existing elements
  EXPECT_EQ(double_binary_search(sortedDoubles, -10.5), 0);
  EXPECT_EQ(double_binary_search(sortedDoubles, 0.0), 2);
  EXPECT_EQ(double_binary_search(sortedDoubles, 10.5), 6);
  EXPECT_EQ(double_binary_search(sortedDoubles, 100.5), 9);

  // Test finding non-existing elements
  EXPECT_EQ(double_binary_search(sortedDoubles, -100.5), -1);
  EXPECT_EQ(double_binary_search(sortedDoubles, 3.5), -1);
  EXPECT_EQ(double_binary_search(sortedDoubles, 200.5), -1);
}

/**
 * @test Test binary search with strings
 */
TEST_F(BinarySearchTest, StringSearch) {
  // Using a lambda to explicitly specify the template parameter
  auto string_binary_search = [](const std::vector<std::string>& arr, const std::string& target) {
    return clavis::search::binary_search<std::string>(arr, target);
  };

  // Test finding existing elements
  EXPECT_EQ(string_binary_search(sortedStrings, "apple"), 0);
  EXPECT_EQ(string_binary_search(sortedStrings, "cherry"), 2);
  EXPECT_EQ(string_binary_search(sortedStrings, "grape"), 6);

  // Test finding non-existing elements
  EXPECT_EQ(string_binary_search(sortedStrings, "apricot"), -1);
  EXPECT_EQ(string_binary_search(sortedStrings, "kiwi"), -1);
  EXPECT_EQ(string_binary_search(sortedStrings, "zebra"), -1);
}

/**
 * @test Test lower_bound function
 */
TEST_F(BinarySearchTest, LowerBound) {
  // Test with integers
  EXPECT_EQ(clavis::search::lower_bound(sortedInts, -20), 0);  // First element
  EXPECT_EQ(clavis::search::lower_bound(sortedInts, -10), 0);  // Existing element
  EXPECT_EQ(clavis::search::lower_bound(sortedInts, -7), 1);   // Between elements
  EXPECT_EQ(clavis::search::lower_bound(sortedInts, 3), 5);    // Between elements
  EXPECT_EQ(clavis::search::lower_bound(sortedInts, 100), 9);  // Last element
  EXPECT_EQ(clavis::search::lower_bound(sortedInts, 200), 10); // Beyond last element

  // Test with empty vector
  std::vector<int> empty;
  EXPECT_EQ(clavis::search::lower_bound(empty, 5), 0);
}

/**
 * @test Test upper_bound function
 */
TEST_F(BinarySearchTest, UpperBound) {
  // Test with integers
  EXPECT_EQ(clavis::search::upper_bound(sortedInts, -20), 0);  // Before first element
  EXPECT_EQ(clavis::search::upper_bound(sortedInts, -10), 1);  // Existing element
  EXPECT_EQ(clavis::search::upper_bound(sortedInts, -7), 1);   // Between elements
  EXPECT_EQ(clavis::search::upper_bound(sortedInts, 3), 5);    // Between elements
  EXPECT_EQ(clavis::search::upper_bound(sortedInts, 100), 10); // Last element
  EXPECT_EQ(clavis::search::upper_bound(sortedInts, 200), 10); // Beyond last element

  // Test with empty vector
  std::vector<int> empty;
  EXPECT_EQ(clavis::search::upper_bound(empty, 5), 0);
}

/**
 * @test Test binary_search_predicate function
 */
TEST_F(BinarySearchTest, PredicateSearch) {
  // Find the first number >= 10 in range [0, 20)
  auto result1 = clavis::search::binary_search_predicate<int>(0, 20, [](int x) { return x >= 10; });
  EXPECT_EQ(result1, 10);

  // Find the first square number >= 100 in range [0, 20)
  auto result2 = clavis::search::binary_search_predicate<int>(0, 20, [](int x) { return x * x >= 100; });
  EXPECT_EQ(result2, 10);

  // Find the first number that doesn't satisfy any condition
  auto result3 = clavis::search::binary_search_predicate<int>(0, 10, [](int x) { return x > 15; });
  EXPECT_EQ(result3, 10); // Should return the right boundary
}

/**
 * @test Test edge cases
 */
TEST_F(BinarySearchTest, EdgeCases) {
  // Using a lambda to explicitly specify the template parameter
  auto int_binary_search = [](const std::vector<int>& arr, const int& target) {
    return clavis::search::binary_search<int>(arr, target);
  };

  // Test with single element vector
  std::vector<int> singleElement = {42};
  EXPECT_EQ(int_binary_search(singleElement, 42), 0);
  EXPECT_EQ(int_binary_search(singleElement, 41), -1);
  EXPECT_EQ(clavis::search::lower_bound(singleElement, 41), 0);
  EXPECT_EQ(clavis::search::lower_bound(singleElement, 42), 0);
  EXPECT_EQ(clavis::search::lower_bound(singleElement, 43), 1);
  EXPECT_EQ(clavis::search::upper_bound(singleElement, 41), 0);
  EXPECT_EQ(clavis::search::upper_bound(singleElement, 42), 1);
  EXPECT_EQ(clavis::search::upper_bound(singleElement, 43), 1);

  // Test with empty vector
  std::vector<int> empty;
  EXPECT_EQ(int_binary_search(empty, 42), -1);
}
