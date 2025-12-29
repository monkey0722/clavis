#ifndef EXTENDED_GCD_HPP
#define EXTENDED_GCD_HPP

#include <cstdint>
#include <tuple>

/**
 * @brief Result of Extended Euclidean Algorithm
 *
 * For inputs a and b, computes:
 * - gcd: the greatest common divisor of a and b
 * - x, y: coefficients such that a*x + b*y = gcd(a, b)
 */
struct ExtGcdResult {
  int64_t gcd;
  int64_t x;
  int64_t y;
};

/**
 * @brief Extended Euclidean Algorithm
 *
 * Computes the greatest common divisor of a and b, and finds coefficients
 * x and y such that a*x + b*y = gcd(a, b) (Bezout's identity).
 *
 * Time Complexity: O(log(min(a, b)))
 * Space Complexity: O(1) iterative, O(log(min(a, b))) recursive
 *
 * @param a First integer
 * @param b Second integer
 * @return ExtGcdResult containing gcd, x, and y
 */
ExtGcdResult extended_gcd(int64_t a, int64_t b) {
  if (b == 0) {
    return {.gcd = a, .x = 1, .y = 0};
  }

  auto [g, x1, y1] = extended_gcd(b, a % b);
  int64_t x = y1;
  int64_t y = x1 - (a / b) * y1;

  return {.gcd = g, .x = x, .y = y};
}

/**
 * @brief Iterative Extended Euclidean Algorithm
 *
 * Same as extended_gcd but uses iteration instead of recursion.
 * More efficient for very large numbers due to no stack overhead.
 *
 * @param a First integer
 * @param b Second integer
 * @return ExtGcdResult containing gcd, x, and y
 */
ExtGcdResult extended_gcd_iterative(int64_t a, int64_t b) {
  int64_t x0 = 1, x1 = 0;
  int64_t y0 = 0, y1 = 1;

  while (b != 0) {
    int64_t q = a / b;
    int64_t temp = b;
    b = a % b;
    a = temp;

    temp = x1;
    x1 = x0 - q * x1;
    x0 = temp;

    temp = y1;
    y1 = y0 - q * y1;
    y0 = temp;
  }

  return {.gcd = a, .x = x0, .y = y0};
}

/**
 * @brief Compute greatest common divisor using Euclidean algorithm
 *
 * @param a First integer
 * @param b Second integer
 * @return gcd(a, b)
 */
int64_t gcd(int64_t a, int64_t b) {
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  while (b != 0) {
    int64_t temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

/**
 * @brief Compute least common multiple
 *
 * @param a First integer
 * @param b Second integer
 * @return lcm(a, b)
 */
int64_t lcm(int64_t a, int64_t b) {
  if (a == 0 || b == 0) return 0;
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  return a / gcd(a, b) * b;  // Divide first to avoid overflow
}

/**
 * @brief Compute modular multiplicative inverse using Extended GCD
 *
 * Finds x such that (a * x) ≡ 1 (mod m)
 * The inverse exists if and only if gcd(a, m) = 1
 *
 * @param a The number to find inverse of
 * @param m The modulus
 * @return The modular inverse, or -1 if it doesn't exist
 */
int64_t mod_inverse(int64_t a, int64_t m) {
  auto [g, x, y] = extended_gcd(a, m);

  if (g != 1) {
    return -1;  // Inverse doesn't exist
  }

  // Make sure result is positive
  return ((x % m) + m) % m;
}

#endif  // EXTENDED_GCD_HPP
