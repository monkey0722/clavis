#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include <functional>
#include <limits>
#include <vector>

/**
 * @brief SegmentTree class
 *
 * @tparam T Type of the elements in the segment tree
 */
template <typename T>
class SegmentTree {
private:
  int n;                      // Number of leaves
  std::vector<T> tree;        // Container to store the segment tree
  std::function<T(T, T)> op;  // Binary operation to merge intervals
  T identity;                 // Identity element for the operation

  /**
   * @brief Builds the segment tree from the given data
   *
   * @param data Original array to build from
   */
  void build(const std::vector<T>& data) {
    // Set leaves
    for (int i = 0; i < (int)data.size(); i++) {
      tree[n + i] = data[i];
    }
    // Build internal nodes from bottom to top
    for (int i = n - 1; i > 0; i--) {
      tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
  }

public:
  /**
   * @brief Constructor
   *
   * @param data Source array to build the tree from
   * @param op Binary operation for merging two segments
   * @param identity Identity element for the operation
   */
  SegmentTree(const std::vector<T>& data, std::function<T(T, T)> op, T identity)
      : op(op), identity(identity) {
    // Expand n to the next power of two
    int size = (int)data.size();
    n = 1;
    while (n < size) n <<= 1;

    tree.assign(2 * n, identity);
    build(data);
  }

  /**
   * @brief Queries the result of the operation in the interval [l, r)
   *
   * @param l Left boundary (inclusive)
   * @param r Right boundary (exclusive)
   * @return T Result of the operation over [l, r)
   */
  T query(int l, int r) {
    T resL = identity;
    T resR = identity;
    l += n;  // Convert to the leaf index
    r += n;
    while (l < r) {
      if (l & 1) resL = op(resL, tree[l++]);
      if (r & 1) resR = op(tree[--r], resR);
      l >>= 1;
      r >>= 1;
    }
    return op(resL, resR);
  }

  /**
   * @brief Updates the element at index idx with a new value
   *
   * @param idx Zero-based index of the element to update
   * @param value New value to set
   */
  void update(int idx, T value) {
    idx += n;
    tree[idx] = value;
    while (idx > 1) {
      idx >>= 1;
      tree[idx] = op(tree[idx << 1], tree[idx << 1 | 1]);
    }
  }
};

#endif  // SEGMENT_TREE_HPP
