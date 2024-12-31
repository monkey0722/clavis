#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <algorithm>
#include <concepts>
#include <iostream>
#include <memory>
#include <span>
#include <vector>

#include "sorting_concepts.hpp"

template <Mergeable T>
void merge(std::span<T> arr, size_t left, size_t mid, size_t right) {
  std::cout << "Merging: left=" << left << " mid=" << mid << " right=" << right << std::endl;
  std::vector<T> temp(right - left + 1);
  size_t i = left, j = mid + 1, k = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = std::move(arr[i++]);
    } else {
      temp[k++] = std::move(arr[j++]);
    }
  }
  /*
   * Commented out because it causes errors in the CI environment.
   ** std::ranges::move(arr.subspan(i, mid - i + 1), temp.begin() + k);
   ** std::ranges::move(arr.subspan(j, right - j + 1), temp.begin() + k);
   ** std::ranges::move(temp, arr.begin() + left);
   */
  std::move(arr.begin() + i, arr.begin() + i + (mid - i + 1), temp.begin() + k);
  std::move(arr.begin() + j, arr.begin() + j + (right - j + 1), temp.begin() + k);
  std::move(temp.begin(), temp.end(), arr.begin() + left);
}

template <Mergeable T>
void mergeSortImpl(std::span<T> arr, size_t left, size_t right) {
  if (left >= arr.size() || right >= arr.size() || left >= right) {
    return;
  }
  std::cout << "MergeSort: left=" << left << " right=" << right << std::endl;
  size_t mid = left + (right - left) / 2;
  mergeSortImpl(arr, left, mid);
  mergeSortImpl(arr, mid + 1, right);
  merge(arr, left, mid, right);
}

template <Mergeable T>
void mergeSort(std::vector<T>& arr) {
  std::cout << "Starting mergeSort with array size: " << arr.size() << std::endl;
  std::span s{arr};
  mergeSortImpl(s, 0, arr.size() - 1);
}

#endif  // MERGE_SORT_HPP