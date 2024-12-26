#include "sample.h"

std::vector<int> filter_even_numbers(const std::vector<int>& input) {
  std::vector<int> result;
  for (int n : input | std::views::filter([](int n) { return n % 2 == 0; })) {
    result.push_back(n);
  }
  return result;
}
