#include <iostream>
#include <vector>

#include "bubble_sort.hpp"
#include "heap_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "radix_sort.hpp"
#include "shell_sort.hpp"

template <typename T>
void printArray(const std::vector<T>& arr, const std::string& label) {
  std::cout << label << ": ";
  for (const auto& num : arr) {
    std::cout << num << " ";
  }
  std::cout << "\n";
}

int main() {
  std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
  std::vector<int> original = arr;

  printArray(arr, "Original array");

  std::cout << "\nBubble Sort:\n";
  bubbleSort(arr);
  printArray(arr, "After sorting");

  arr = original;
  std::cout << "\nQuick Sort:\n";
  quickSort(arr);
  printArray(arr, "After sorting");

  arr = original;
  std::cout << "\nMerge Sort:\n";
  mergeSort(arr);
  printArray(arr, "After sorting");

  arr = original;
  std::cout << "\nHeap Sort:\n";
  heapSort(arr);
  printArray(arr, "After sorting");

  arr = original;
  std::cout << "\nRadix Sort:\n";
  radixSort(arr);
  printArray(arr, "After sorting");

  arr = original;
  std::cout << "\nShell Sort:\n";
  shellSort(arr);
  printArray(arr, "After sorting");

  return 0;
}