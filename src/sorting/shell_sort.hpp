#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include <concepts>
#include <iostream>
#include <ranges>
#include <span>
#include <vector>

#include "sorting_concepts.hpp"

template <Sortable T>
void shellSort(std::vector<T>& arr) {
  std::cout << "Starting shellSort with array size: " << arr.size() << '\n';
  std::span s{arr};
  size_t n = s.size();

  for (size_t gap = n / 2; gap > 0; gap /= 2) {
    std::cout << "Current gap size: " << gap << '\n';
    for (size_t i = gap; i < n; i++) {
      T temp = std::move(s[i]);
      size_t j = i;
      for (; j >= gap && s[j - gap] > temp; j -= gap) {
        std::cout << "Moving element from " << j - gap << " to " << j << '\n';
        s[j] = std::move(s[j - gap]);
      }
      s[j] = std::move(temp);
    }
  }
  std::cout << "Shell sort complete" << '\n';
}

#endif  // SHELL_SORT_HPP