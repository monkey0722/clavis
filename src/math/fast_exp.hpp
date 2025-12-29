#ifndef FAST_EXP_HPP
#define FAST_EXP_HPP

#include <concepts>
#include <cstdint>

/**
 * @brief Concept for types that support modular exponentiation
 */
template <typename T>
concept ModularArithmetic = std::integral<T> || requires(T a, T b) {
  { a * b } -> std::convertible_to<T>;
  { a % b } -> std::convertible_to<T>;
};

/**
 * @brief Fast Exponentiation (Binary Exponentiation) with modulo
 *
 * Computes (base^exp) % mod efficiently using the binary exponentiation method.
 *
 * Time Complexity: O(log exp)
 * Space Complexity: O(1)
 *
 * @param base The base number
 * @param exp The exponent (must be non-negative)
 * @param mod The modulo value (must be positive)
 * @return (base^exp) % mod
 */
int64_t mod_pow(int64_t base, int64_t exp, int64_t mod) {
  if (mod == 1) return 0;

  int64_t result = 1;
  base %= mod;
  if (base < 0) base += mod;  // Handle negative base

  while (exp > 0) {
    // If exp is odd, multiply base with result
    if (exp & 1) {
      result = static_cast<int64_t>((__int128_t)result * base % mod);
    }
    // exp must be even now
    exp >>= 1;
    base = static_cast<int64_t>((__int128_t)base * base % mod);
  }

  return result;
}

/**
 * @brief Fast Exponentiation without modulo
 *
 * Computes base^exp efficiently using the binary exponentiation method.
 * Warning: May overflow for large values.
 *
 * Time Complexity: O(log exp)
 * Space Complexity: O(1)
 *
 * @param base The base number
 * @param exp The exponent (must be non-negative)
 * @return base^exp
 */
template <ModularArithmetic T>
T fast_pow(T base, int64_t exp) {
  T result = 1;

  while (exp > 0) {
    if (exp & 1) {
      result *= base;
    }
    exp >>= 1;
    base *= base;
  }

  return result;
}

/**
 * @brief Compute modular multiplicative inverse using Fermat's little theorem
 *
 * Computes a^(-1) mod p where p is prime.
 * Based on Fermat's little theorem: a^(p-1) ≡ 1 (mod p)
 * Therefore: a^(-1) ≡ a^(p-2) (mod p)
 *
 * @param a The number to find inverse of
 * @param p A prime modulus
 * @return a^(-1) mod p
 */
int64_t mod_inverse_fermat(int64_t a, int64_t p) { return mod_pow(a, p - 2, p); }

#endif  // FAST_EXP_HPP
