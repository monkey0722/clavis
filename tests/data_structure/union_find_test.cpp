#include "../src/data_structure/union_find.hpp"

#include <gtest/gtest.h>

TEST(UnionFindTest, BasicOperations) {
  UnionFind uf(10);
  EXPECT_EQ(uf.size(), 10);
  EXPECT_EQ(uf.groups(), 10);

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(uf.find(i), i);
    EXPECT_EQ(uf.groupSize(i), 1);
  }
}

TEST(UnionFindTest, UniteAndSameTest) {
  UnionFind uf(10);
  uf.unite(1, 2);
  EXPECT_TRUE(uf.same(1, 2));
  EXPECT_EQ(uf.groups(), 9);
  EXPECT_EQ(uf.groupSize(1), 2);

  uf.unite(2, 3);
  EXPECT_TRUE(uf.same(1, 3));
  EXPECT_EQ(uf.groups(), 8);
  EXPECT_EQ(uf.groupSize(1), 3);

  uf.unite(1, 3);
  EXPECT_EQ(uf.groups(), 8);
}

TEST(UnionFindTest, DifferentIntegralTypes) {
  UnionFind uf(10);
  short s = 1;
  long l = 2;
  uf.unite(s, l);
  EXPECT_TRUE(uf.same(s, l));

  unsigned u = 3;
  uf.unite(l, u);
  EXPECT_TRUE(uf.same(s, u));
}

TEST(UnionFindTest, OutOfRangeTest) {
  UnionFind uf(10);
  auto testFind = [&](int x) { return uf.find(x); };
  EXPECT_THROW(testFind(-1), std::out_of_range);
  EXPECT_THROW(testFind(10), std::out_of_range);
  EXPECT_THROW(uf.unite(-1, 5), std::out_of_range);
  EXPECT_THROW(uf.unite(5, 10), std::out_of_range);
}

TEST(UnionFindTest, LargeGroupTest) {
  UnionFind uf(10);
  for (int i = 0; i < 4; i++) {
    uf.unite(i, i + 1);
    EXPECT_TRUE(uf.same(0, i + 1));
    EXPECT_EQ(uf.groupSize(0), i + 2);
  }
  EXPECT_EQ(uf.groups(), 6);
}
