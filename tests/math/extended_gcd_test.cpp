#include "math/extended_gcd.hpp"

#include <gtest/gtest.h>

/**
 * @brief Test fixture for Extended GCD
 */
class ExtendedGcdTest : public ::testing::Test {
 protected:
};

/**
 * @test Basic GCD computation
 */
TEST_F(ExtendedGcdTest, BasicGcd) {
  EXPECT_EQ(gcd(12, 8), 4);
  EXPECT_EQ(gcd(17, 13), 1);
  EXPECT_EQ(gcd(100, 25), 25);
  EXPECT_EQ(gcd(48, 18), 6);
}

/**
 * @test GCD edge cases
 */
TEST_F(ExtendedGcdTest, GcdEdgeCases) {
  EXPECT_EQ(gcd(0, 5), 5);
  EXPECT_EQ(gcd(5, 0), 5);
  EXPECT_EQ(gcd(0, 0), 0);
  EXPECT_EQ(gcd(-12, 8), 4);
  EXPECT_EQ(gcd(12, -8), 4);
  EXPECT_EQ(gcd(-12, -8), 4);
}

/**
 * @test LCM computation
 */
TEST_F(ExtendedGcdTest, BasicLcm) {
  EXPECT_EQ(lcm(4, 6), 12);
  EXPECT_EQ(lcm(3, 5), 15);
  EXPECT_EQ(lcm(12, 8), 24);
  EXPECT_EQ(lcm(7, 7), 7);
}

/**
 * @test LCM edge cases
 */
TEST_F(ExtendedGcdTest, LcmEdgeCases) {
  EXPECT_EQ(lcm(0, 5), 0);
  EXPECT_EQ(lcm(5, 0), 0);
  EXPECT_EQ(lcm(-4, 6), 12);
}

/**
 * @test Extended GCD recursive
 */
TEST_F(ExtendedGcdTest, ExtendedGcdRecursive) {
  // gcd(30, 20) = 10
  // 30*x + 20*y = 10 -> x=1, y=-1 (30*1 + 20*(-1) = 10)
  auto [g1, x1, y1] = extended_gcd(30, 20);
  EXPECT_EQ(g1, 10);
  EXPECT_EQ(30 * x1 + 20 * y1, 10);

  // gcd(35, 15) = 5
  auto [g2, x2, y2] = extended_gcd(35, 15);
  EXPECT_EQ(g2, 5);
  EXPECT_EQ(35 * x2 + 15 * y2, 5);

  // gcd(17, 13) = 1 (coprime)
  auto [g3, x3, y3] = extended_gcd(17, 13);
  EXPECT_EQ(g3, 1);
  EXPECT_EQ(17 * x3 + 13 * y3, 1);
}

/**
 * @test Extended GCD iterative
 */
TEST_F(ExtendedGcdTest, ExtendedGcdIterative) {
  auto [g1, x1, y1] = extended_gcd_iterative(30, 20);
  EXPECT_EQ(g1, 10);
  EXPECT_EQ(30 * x1 + 20 * y1, 10);

  auto [g2, x2, y2] = extended_gcd_iterative(35, 15);
  EXPECT_EQ(g2, 5);
  EXPECT_EQ(35 * x2 + 15 * y2, 5);

  auto [g3, x3, y3] = extended_gcd_iterative(17, 13);
  EXPECT_EQ(g3, 1);
  EXPECT_EQ(17 * x3 + 13 * y3, 1);
}

/**
 * @test Recursive and iterative give same results
 */
TEST_F(ExtendedGcdTest, RecursiveEqualsIterative) {
  std::vector<std::pair<int64_t, int64_t>> test_cases = {
      {48, 18}, {100, 35}, {17, 13}, {1000, 7}, {252, 105}};

  for (auto [a, b] : test_cases) {
    auto [g_rec, x_rec, y_rec] = extended_gcd(a, b);
    auto [g_iter, x_iter, y_iter] = extended_gcd_iterative(a, b);

    EXPECT_EQ(g_rec, g_iter);
    // Bezout coefficients may differ but should satisfy the identity
    EXPECT_EQ(a * x_rec + b * y_rec, g_rec);
    EXPECT_EQ(a * x_iter + b * y_iter, g_iter);
  }
}

/**
 * @test Modular inverse
 */
TEST_F(ExtendedGcdTest, ModInverse) {
  // Inverse of 3 mod 7: 3 * 5 = 15 ≡ 1 (mod 7)
  EXPECT_EQ(mod_inverse(3, 7), 5);

  // Inverse of 2 mod 5: 2 * 3 = 6 ≡ 1 (mod 5)
  EXPECT_EQ(mod_inverse(2, 5), 3);

  // Inverse of 7 mod 11: 7 * 8 = 56 ≡ 1 (mod 11)
  EXPECT_EQ(mod_inverse(7, 11), 8);

  // No inverse exists when gcd != 1
  EXPECT_EQ(mod_inverse(4, 8), -1);
  EXPECT_EQ(mod_inverse(6, 9), -1);
}

/**
 * @test Modular inverse verification
 */
TEST_F(ExtendedGcdTest, ModInverseVerification) {
  // For coprime pairs, verify a * inverse(a) ≡ 1 (mod m)
  std::vector<std::pair<int64_t, int64_t>> test_cases = {
      {3, 7}, {5, 11}, {17, 23}, {100, 101}, {12345, 1000000007}};

  for (auto [a, m] : test_cases) {
    int64_t inv = mod_inverse(a, m);
    EXPECT_NE(inv, -1);
    EXPECT_EQ((a * inv) % m, 1);
  }
}
