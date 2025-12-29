#ifndef SIEVE_HPP
#define SIEVE_HPP

#include <cstdint>
#include <vector>

/**
 * @brief Sieve of Eratosthenes - generates all prime numbers up to n
 *
 * Time Complexity: O(n log log n)
 * Space Complexity: O(n)
 *
 * @param n The upper bound (inclusive) for prime number generation
 * @return A vector of all prime numbers from 2 to n
 */
std::vector<int64_t> sieve_of_eratosthenes(int64_t n) {
  if (n < 2) {
    return {};
  }

  // is_prime[i] indicates whether i is prime
  std::vector<bool> is_prime(n + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;

  // Mark all multiples of each prime as composite
  for (int64_t i = 2; i * i <= n; ++i) {
    if (is_prime[i]) {
      for (int64_t j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }

  // Collect all primes
  std::vector<int64_t> primes;
  for (int64_t i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }

  return primes;
}

/**
 * @brief Check if a number is prime using the sieve result
 *
 * @param n The number to check
 * @param sieve_result The result from sieve_of_eratosthenes (must include n)
 * @return true if n is prime, false otherwise
 */
bool is_prime_with_sieve(int64_t n, const std::vector<bool>& sieve_result) {
  if (n < 0 || n >= static_cast<int64_t>(sieve_result.size())) {
    return false;
  }
  return sieve_result[n];
}

/**
 * @brief Generate a boolean sieve array
 *
 * @param n The upper bound (inclusive)
 * @return A vector where result[i] is true if i is prime
 */
std::vector<bool> sieve_bool(int64_t n) {
  if (n < 0) {
    return {};
  }

  std::vector<bool> is_prime(n + 1, true);
  if (n >= 0) is_prime[0] = false;
  if (n >= 1) is_prime[1] = false;

  for (int64_t i = 2; i * i <= n; ++i) {
    if (is_prime[i]) {
      for (int64_t j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }

  return is_prime;
}

#endif  // SIEVE_HPP
