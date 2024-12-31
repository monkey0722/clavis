#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <concepts>
#include <iostream>
#include <ranges>
#include <vector>

#include "sorting_concepts.hpp"

template <Pivotable T>
size_t partition(std::vector<T>& arr, size_t low, size_t high) {
  T pivot = std::move(arr[high]);
  size_t i = low;

  for (size_t j = low; j < high; ++j) {
    if (arr[j] <= pivot) {
      std::swap(arr[i++], arr[j]);
    }
  }
  arr[high] = std::move(arr[i]);
  arr[i] = std::move(pivot);
  return i;
}

template <Pivotable T>
void quickSortImpl(std::vector<T>& arr, size_t low, size_t high) {
  std::cout << "QuickSort: low=" << low << " high=" << high << std::endl;
  if (low < high) {
    size_t pi = partition(arr, low, high);
    if (pi > 0) quickSortImpl(arr, low, pi - 1);
    quickSortImpl(arr, pi + 1, high);
  }
}

template <Pivotable T>
void quickSort(std::vector<T>& arr) {
  std::cout << "Starting quickSort with array size: " << arr.size() << std::endl;
  if (arr.size() > 1) {
    quickSortImpl(arr, 0, arr.size() - 1);
  }
}

#endif  // QUICK_SORT_HPP