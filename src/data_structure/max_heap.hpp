#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <stdexcept>
#include <vector>

// A simple MaxHeap implementation using a dynamic array (std::vector).
// This class provides the main operations of a max-heap.
template <typename T>
class MaxHeap {
public:
  MaxHeap() = default;

  // Insert a new value into the heap
  void push(const T& value) {
    data_.push_back(value);
    siftUp(data_.size() - 1);
  }

  // Remove and return the largest value in the heap
  // Throws std::runtime_error if the heap is empty
  T pop() {
    if (empty()) {
      throw std::runtime_error("Heap is empty. Cannot pop.");
    }
    // Swap the root with the last element and pop it
    T topValue = data_.front();
    data_.front() = data_.back();
    data_.pop_back();

    if (!empty()) {
      siftDown(0);
    }
    return topValue;
  }

  // Return the largest value without removing
  // Throws std::runtime_error if the heap is empty
  const T& top() const {
    if (empty()) {
      throw std::runtime_error("Heap is empty. No top element.");
    }
    return data_.front();
  }

  // Returns true if the heap has no elements
  bool empty() const { return data_.empty(); }

  // Returns the number of elements in the heap
  std::size_t size() const { return data_.size(); }

private:
  std::vector<T> data_;

  // Restore the heap property by moving the element at index 'idx'
  // up the tree until it's no longer bigger than its parent.
  void siftUp(std::size_t idx) {
    while (idx > 0) {
      std::size_t parent = (idx - 1) / 2;
      if (data_[idx] > data_[parent]) {
        std::swap(data_[idx], data_[parent]);
        idx = parent;
      } else {
        break;
      }
    }
  }

  // Restore the heap property by moving the element at index 'idx'
  // down the tree until it's no longer smaller than its children.
  void siftDown(std::size_t idx) {
    while (true) {
      std::size_t leftChild = 2 * idx + 1;
      std::size_t rightChild = 2 * idx + 2;
      std::size_t largest = idx;

      if (leftChild < data_.size() && data_[leftChild] > data_[largest]) {
        largest = leftChild;
      }
      if (rightChild < data_.size() && data_[rightChild] > data_[largest]) {
        largest = rightChild;
      }

      if (largest == idx) {
        break;  // no need to sift down further
      }
      std::swap(data_[idx], data_[largest]);
      idx = largest;
    }
  }
};

#endif  // MAX_HEAP_HPP
