#ifndef FENWICK_TREE_HPP
#define FENWICK_TREE_HPP

#include <stdexcept>
#include <vector>

// Fenwick Tree (Binary Indexed Tree) for handling
// prefix sums over a 1D array with point updates.
class FenwickTree {
public:
  explicit FenwickTree(std::size_t n) : size_(n), fenw_(n + 1, 0) {}

  // Add 'delta' to element at index 'idx'
  // Assumes 0-based indexing externally
  void update(std::size_t idx, int delta) {
    if (idx >= size_) {
      throw std::out_of_range("Index out of range in FenwickTree::update");
    }
    // Internally, Fenwick Tree often uses 1-based indexing
    idx += 1;
    while (idx < fenw_.size()) {
      fenw_[idx] += delta;
      idx += idx & (-static_cast<int>(idx));
    }
  }

  // Returns the sum of elements in [0..idx]
  // If idx < 0, returns 0
  int query(std::size_t idx) const {
    if (idx >= size_) {
      throw std::out_of_range("Index out of range in FenwickTree::query");
    }
    idx += 1;
    int result = 0;
    while (idx > 0) {
      result += fenw_[idx];
      idx -= idx & (-static_cast<int>(idx));
    }
    return result;
  }

  // Returns the sum of elements in [left..right]
  // If left > right, returns 0
  int rangeQuery(std::size_t left, std::size_t right) const {
    if (left > right) {
      return 0;
    }
    return query(right) - (left == 0 ? 0 : query(left - 1));
  }

private:
  std::size_t size_;
  std::vector<int> fenw_;
};

#endif  // FENWICK_TREE_HPP
