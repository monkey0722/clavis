#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#include <concepts>
#include <functional>
#include <vector>

namespace clavis {
namespace search {

/**
 * @brief Binary search algorithm for finding an element in a sorted array
 * 
 * @tparam T Type of elements in the array (must be comparable)
 * @param arr Sorted array to search in
 * @param target Element to search for
 * @return Index of the target element if found, -1 otherwise
 */
template <typename T>
requires std::totally_ordered<T>
int binary_search(const std::vector<T>& arr, const T& target) {
  int left = 0;
  int right = arr.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;  // Avoid potential overflow

    if (arr[mid] == target) {
      return mid;  // Found the target
    } else if (arr[mid] < target) {
      left = mid + 1;  // Search in the right half
    } else {
      right = mid - 1;  // Search in the left half
    }
  }

  return -1;  // Target not found
}

/**
 * @brief Lower bound binary search - finds the first element not less than the target
 * 
 * @tparam T Type of elements in the array (must be comparable)
 * @param arr Sorted array to search in
 * @param target Element to search for
 * @return Index of the first element not less than target, or arr.size() if all elements are less than target
 */
template <typename T>
requires std::totally_ordered<T>
int lower_bound(const std::vector<T>& arr, const T& target) {
  int left = 0;
  int right = arr.size();  // Note: right is arr.size(), not arr.size() - 1

  while (left < right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return left;  // Returns arr.size() if all elements are less than target
}

/**
 * @brief Upper bound binary search - finds the first element greater than the target
 * 
 * @tparam T Type of elements in the array (must be comparable)
 * @param arr Sorted array to search in
 * @param target Element to search for
 * @return Index of the first element greater than target, or arr.size() if no such element exists
 */
template <typename T>
requires std::totally_ordered<T>
int upper_bound(const std::vector<T>& arr, const T& target) {
  int left = 0;
  int right = arr.size();  // Note: right is arr.size(), not arr.size() - 1

  while (left < right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] <= target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return left;  // Returns arr.size() if all elements are less than or equal to target
}

/**
 * @brief Binary search on a predicate function
 * 
 * @tparam T Type of elements in the search space
 * @param left Left boundary of the search space (inclusive)
 * @param right Right boundary of the search space (exclusive)
 * @param predicate Function that returns true for elements that satisfy the condition
 * @return The first element in the range [left, right) for which predicate returns true, or right if none exists
 */
template <typename T>
requires std::integral<T>
T binary_search_predicate(T left, T right, const std::function<bool(T)>& predicate) {
  while (left < right) {
    T mid = left + (right - left) / 2;

    if (predicate(mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }

  return left;  // Returns right if no element satisfies the predicate
}

} // namespace search
} // namespace clavis

#endif  // BINARY_SEARCH_HPP
