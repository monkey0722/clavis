#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include <concepts>
#include <ranges>

#include "sorting_concepts.hpp"

template <Heapable T>
void heapify(std::vector<T>& arr, size_t n, size_t i) {
  std::cout << "Heapify at index " << i << " with size " << n << std::endl;
  size_t largest = i;
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest]) {
    largest = left;
  }
  if (right < n && arr[right] > arr[largest]) {
    largest = right;
  }
  if (largest != i) {
    std::cout << "Swapping elements at " << i << " and " << largest << std::endl;
    std::swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

template <Heapable T>
void heapSort(std::vector<T>& arr) {
  std::cout << "Starting heapSort with array size: " << arr.size() << std::endl;
  for (int i = arr.size() / 2 - 1; i >= 0; --i) {
    heapify(arr, arr.size(), i);
  }
  for (int i = arr.size() - 1; i > 0; --i) {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

#endif  // HEAP_SORT_HPP