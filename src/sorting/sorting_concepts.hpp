#ifndef SORTING_CONCEPTS_HPP
#define SORTING_CONCEPTS_HPP

#include <concepts>

// clang-format off (compound requirements formatting unstable across versions)
template <typename T>
concept Sortable = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
};
// clang-format on

template <typename T>
concept Pivotable = Sortable<T> && std::movable<T>;

template <typename T>
concept Mergeable = Sortable<T> && std::copyable<T>;

template <typename T>
concept Heapable = Sortable<T> && std::swappable<T>;

#endif  // 　SORTING_CONCEPTS_HPP