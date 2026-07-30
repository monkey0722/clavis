#ifndef EXPONENTIAL_SEARCH_HPP
#define EXPONENTIAL_SEARCH_HPP

#include <concepts>
#include <cstddef>
#include <optional>
#include <vector>

namespace clavis::search {

/**
 * @brief Finds the first occurrence of a value using exponential search.
 *
 * The search range grows exponentially from the beginning of the sorted
 * sequence, then a binary search locates the first matching value.
 *
 * @tparam T A totally ordered value type.
 * @param values Values sorted in ascending order.
 * @param target Value to locate.
 * @return The first matching position, or std::nullopt if the value is absent.
 *
 * @complexity O(log(i + 1)) time for a match at position i, O(log N) worst case,
 * and O(1) additional space.
 */
template <typename T>
  requires std::totally_ordered<T>
[[nodiscard]] std::optional<std::size_t> exponential_search(const std::vector<T>& values,
                                                            const T& target) {
  if (values.empty()) {
    return std::nullopt;
  }

  std::size_t bound = 1;
  while (bound < values.size() && values[bound] < target) {
    if (bound > values.size() / 2) {
      bound = values.size();
      break;
    }
    bound *= 2;
  }

  std::size_t left = bound / 2;
  std::size_t right = bound < values.size() ? bound + 1 : values.size();

  while (left < right) {
    const std::size_t middle = left + (right - left) / 2;
    if (values[middle] < target) {
      left = middle + 1;
    } else {
      right = middle;
    }
  }

  if (left < values.size() && values[left] == target) {
    return left;
  }
  return std::nullopt;
}

}  // namespace clavis::search

#endif  // EXPONENTIAL_SEARCH_HPP
