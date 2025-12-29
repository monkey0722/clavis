#include "math/fast_exp.hpp"

#include <gtest/gtest.h>

/**
 * @brief Test fixture for Fast Exponentiation
 */
class FastExpTest : public ::testing::Test {
 protected:
};

/**
 * @test Basic modular exponentiation
 */
TEST_F(FastExpTest, BasicModPow) {
  // 2^10 = 1024, 1024 % 1000 = 24
  EXPECT_EQ(mod_pow(2, 10, 1000), 24);

  // 3^5 = 243, 243 % 100 = 43
  EXPECT_EQ(mod_pow(3, 5, 100), 43);

  // 7^3 = 343, 343 % 50 = 43
  EXPECT_EQ(mod_pow(7, 3, 50), 43);
}

/**
 * @test Edge cases for mod_pow
 */
TEST_F(FastExpTest, ModPowEdgeCases) {
  // Any number to the power of 0 is 1
  EXPECT_EQ(mod_pow(5, 0, 100), 1);
  EXPECT_EQ(mod_pow(123, 0, 7), 1);

  // Any number mod 1 is 0
  EXPECT_EQ(mod_pow(5, 10, 1), 0);

  // 0 to any positive power is 0
  EXPECT_EQ(mod_pow(0, 5, 100), 0);

  // 1 to any power is 1
  EXPECT_EQ(mod_pow(1, 1000000, 999), 1);
}

/**
 * @test Large exponents
 */
TEST_F(FastExpTest, LargeExponents) {
  // 2^30 = 1073741824, 1073741824 mod 1000000007 = 73741817
  EXPECT_EQ(mod_pow(2, 30, 1000000007), 73741817);

  // 2^62 mod 1000000007
  // Verify it doesn't overflow and produces valid result
  int64_t result = mod_pow(2, 62, 1000000007);
  EXPECT_GE(result, 0);
  EXPECT_LT(result, 1000000007);
}

/**
 * @test Negative base
 */
TEST_F(FastExpTest, NegativeBase) {
  // (-2)^3 = -8, -8 mod 10 should be 2
  EXPECT_EQ(mod_pow(-2, 3, 10), 2);

  // (-3)^2 = 9, 9 mod 10 = 9
  EXPECT_EQ(mod_pow(-3, 2, 10), 9);
}

/**
 * @test fast_pow without modulo
 */
TEST_F(FastExpTest, FastPowNoMod) {
  EXPECT_EQ(fast_pow(2, 10), 1024);
  EXPECT_EQ(fast_pow(3, 5), 243);
  EXPECT_EQ(fast_pow(5, 0), 1);
  EXPECT_EQ(fast_pow(7, 1), 7);
}

/**
 * @test Modular inverse using Fermat's theorem
 */
TEST_F(FastExpTest, ModInverseFermat) {
  // Inverse of 3 mod 7: 3 * x ≡ 1 (mod 7) -> x = 5 (since 3*5=15≡1)
  EXPECT_EQ(mod_inverse_fermat(3, 7), 5);

  // Inverse of 2 mod 5: 2 * x ≡ 1 (mod 5) -> x = 3 (since 2*3=6≡1)
  EXPECT_EQ(mod_inverse_fermat(2, 5), 3);

  // Verify: a * inverse(a) ≡ 1 (mod p)
  int64_t p = 1000000007;
  int64_t a = 12345;
  int64_t inv = mod_inverse_fermat(a, p);
  EXPECT_EQ((__int128_t)a * inv % p, 1);
}
