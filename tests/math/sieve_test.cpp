#include "math/sieve.hpp"

#include <gtest/gtest.h>

/**
 * @brief Test fixture for Sieve of Eratosthenes
 */
class SieveTest : public ::testing::Test {
 protected:
};

/**
 * @test Basic test for small range
 */
TEST_F(SieveTest, SmallRange) {
  auto primes = sieve_of_eratosthenes(10);

  std::vector<int64_t> expected = {2, 3, 5, 7};
  EXPECT_EQ(primes, expected);
}

/**
 * @test Test for primes up to 30
 */
TEST_F(SieveTest, PrimesUpTo30) {
  auto primes = sieve_of_eratosthenes(30);

  std::vector<int64_t> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  EXPECT_EQ(primes, expected);
}

/**
 * @test Edge case: n = 0
 */
TEST_F(SieveTest, ZeroInput) {
  auto primes = sieve_of_eratosthenes(0);
  EXPECT_TRUE(primes.empty());
}

/**
 * @test Edge case: n = 1
 */
TEST_F(SieveTest, OneInput) {
  auto primes = sieve_of_eratosthenes(1);
  EXPECT_TRUE(primes.empty());
}

/**
 * @test Edge case: n = 2
 */
TEST_F(SieveTest, TwoInput) {
  auto primes = sieve_of_eratosthenes(2);

  std::vector<int64_t> expected = {2};
  EXPECT_EQ(primes, expected);
}

/**
 * @test Edge case: negative input
 */
TEST_F(SieveTest, NegativeInput) {
  auto primes = sieve_of_eratosthenes(-5);
  EXPECT_TRUE(primes.empty());
}

/**
 * @test Larger range for performance check
 */
TEST_F(SieveTest, LargerRange) {
  auto primes = sieve_of_eratosthenes(100);

  // There are 25 primes below 100
  EXPECT_EQ(primes.size(), 25u);
  EXPECT_EQ(primes.front(), 2);
  EXPECT_EQ(primes.back(), 97);
}

/**
 * @test Boolean sieve function
 */
TEST_F(SieveTest, BooleanSieve) {
  auto is_prime = sieve_bool(20);

  EXPECT_FALSE(is_prime[0]);
  EXPECT_FALSE(is_prime[1]);
  EXPECT_TRUE(is_prime[2]);
  EXPECT_TRUE(is_prime[3]);
  EXPECT_FALSE(is_prime[4]);
  EXPECT_TRUE(is_prime[5]);
  EXPECT_FALSE(is_prime[6]);
  EXPECT_TRUE(is_prime[7]);
  EXPECT_FALSE(is_prime[8]);
  EXPECT_FALSE(is_prime[9]);
  EXPECT_FALSE(is_prime[10]);
  EXPECT_TRUE(is_prime[11]);
  EXPECT_TRUE(is_prime[13]);
  EXPECT_TRUE(is_prime[17]);
  EXPECT_TRUE(is_prime[19]);
}
