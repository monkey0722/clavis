#ifndef RADIX_SORT_HPP
#define RADIX_SORT_HPP

#include <concepts>
#include <ranges>
#include <span>

template <std::integral T>
void radixSort(std::vector<T>& arr) {
  if (arr.empty()) {
    return;
  };

  auto max = std::ranges::max(arr);
  std::span s{arr};

  for (T exp = 1; max / exp > 0; exp *= 10) {
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
  }
}

#endif // RADIX_SORT_HPP