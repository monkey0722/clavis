#ifndef RADIX_SORT_HPP
#define RADIX_SORT_HPP

#include <concepts>
#include <iostream>
#include <ranges>
#include <span>
#include <vector>

template <std::integral T>
void radixSort(std::vector<T>& arr) {
  std::cout << "Starting radixSort with array size: " << arr.size() << std::endl;
  if (arr.empty()) {
    return;
  };

  auto max = std::ranges::max(arr);
  std::span s{arr};

  for (T exp = 1; max / exp > 0; exp *= 10) {
    std::cout << "Processing digit position: " << exp << std::endl;
    std::vector<T> output(s.size());
    std::array<size_t, 10> count{};

    for (const auto& val : s) {
      count[(val / exp) % 10]++;
    }
    for (size_t i = 1; i < 10; i++) {
      count[i] += count[i - 1];
    }
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      size_t idx = (*it / exp) % 10;
      output[count[idx] - 1] = *it;
      count[idx]--;
    }
    std::ranges::move(output, arr.begin());
    std::cout << "Radix sort complete" << std::endl;
  }
}

#endif // RADIX_SORT_HPP