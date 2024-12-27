#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include <concepts>
#include <ranges>
#include <span>

#include "sorting_concepts.hpp"

template <Sortable T>
void shellSort(std::vector<T>& arr) {
  std::span s{arr};
  size_t n = s.size();

  for (size_t gap = n / 2; gap > 0; gap /= 2) {
    for (size_t i = gap; i < n; i++) {
      T temp = std::move(s[i]);
      size_t j;
      for (j = i; j >= gap && s[j - gap] > temp; j -= gap) {
        s[j] = std::move(s[j - gap]);
      }
      s[j] = std::move(temp);
    }
  }
}

#endif  // SHELL_SORT_HPP