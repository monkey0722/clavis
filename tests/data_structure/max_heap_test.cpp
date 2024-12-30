#include "../src/data_structure/max_heap.hpp"

#include <gtest/gtest.h>

class MaxHeapTest : public ::testing::Test {
protected:
  MaxHeap<int> heap;

  void SetUp() override {
    // but before each test.
  }

  void TearDown() override {
    // but before the destructor.
  }
};

TEST_F(MaxHeapTest, HeapIsInitiallyEmpty) {
  EXPECT_TRUE(heap.empty());
  EXPECT_EQ(heap.size(), 0u);
}

TEST_F(MaxHeapTest, PushIncreasesSize) {
  heap.push(10);
  EXPECT_FALSE(heap.empty());
  EXPECT_EQ(heap.size(), 1u);

  heap.push(20);
  EXPECT_EQ(heap.size(), 2u);
  EXPECT_EQ(heap.top(), 20);
}

TEST_F(MaxHeapTest, PopDecreasesSizeAndReturnsMax) {
  heap.push(5);
  heap.push(10);
  heap.push(3);

  EXPECT_EQ(heap.size(), 3u);
  EXPECT_EQ(heap.top(), 10);

  int popped = heap.pop();
  EXPECT_EQ(popped, 10);
  EXPECT_EQ(heap.size(), 2u);
  EXPECT_EQ(heap.top(), 5);  // Now 5 should be the largest element
}

TEST_F(MaxHeapTest, TopOnEmptyHeapThrows) {
  EXPECT_TRUE(heap.empty());
  EXPECT_THROW(heap.top(), std::runtime_error);
}

TEST_F(MaxHeapTest, PopOnEmptyHeapThrows) {
  EXPECT_TRUE(heap.empty());
  EXPECT_THROW(heap.pop(), std::runtime_error);
}

TEST_F(MaxHeapTest, PushMultipleAndCheckOrder) {
  heap.push(42);
  heap.push(15);
  heap.push(100);
  heap.push(7);
  heap.push(99);

  int firstPop = heap.pop();
  EXPECT_EQ(firstPop, 100);

  int secondPop = heap.pop();
  EXPECT_EQ(secondPop, 99);

  int thirdPop = heap.pop();
  EXPECT_EQ(thirdPop, 42);

  int fourthPop = heap.pop();
  EXPECT_EQ(fourthPop, 15);

  int fifthPop = heap.pop();
  EXPECT_EQ(fifthPop, 7);

  EXPECT_TRUE(heap.empty());
}
