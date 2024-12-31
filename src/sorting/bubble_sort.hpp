#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

#include <concepts>
#include <iostream>
#include <vector>
#include <version>

#include "sorting_concepts.hpp"

template <Sortable T>
void bubbleSort(std::vector<T>& arr) {
  std::cout << "Sorting " << arr.size() << " elements\n";
  for (size_t i = 0; i < arr.size(); ++i) {
    for (size_t j = 1; j < arr.size() - i; ++j) {
      if (arr[j - 1] > arr[j]) {
        std::cout << "Swapping " << arr[j - 1] << " and " << arr[j] << '\n';
        std::swap(arr[j - 1], arr[j]);
      }
    }
  }
}

#endif // BUBBLE_SORT_HPP