#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <concepts>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

template <typename T>
concept Integral = std::is_integral_v<T>;

class UnionFind {
private:
  std::vector<int> parent;
  std::vector<int> rank;
  int groupCount;

  [[nodiscard]] bool isValidIndex(int x) const noexcept {
    return x >= 0 && static_cast<size_t>(x) < parent.size();
  }

public:
  explicit UnionFind(size_t size)
      : parent(size), rank(size, 0), groupCount(static_cast<int>(size)) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  template <Integral T>
  [[nodiscard]] int find(T x) {
    if (!isValidIndex(x)) {
      throw std::out_of_range("Index out of range");
    }
    if (parent[x] == x) {
      return x;
    }
    return parent[x] = find(parent[x]);
  }

  template <Integral T1, Integral T2>
  void unite(T1 x, T2 y) {
    if (!isValidIndex(x) || !isValidIndex(y)) {
      throw std::out_of_range("Index out of range");
    }

    int rx = find(x);
    int ry = find(y);

    if (rx == ry) return;

    std::cout << "Uniting groups: " << rx << " and " << ry << " (ranks: " << rank[rx] << ", "
              << rank[ry] << ")" << std::endl;

    if (rank[rx] < rank[ry]) {
      parent[rx] = ry;
    } else {
      parent[ry] = rx;
      if (rank[rx] == rank[ry]) rank[rx]++;
    }

    groupCount--;
  }

  template <Integral T1, Integral T2>
  [[nodiscard]] bool same(T1 x, T2 y) {
    return find(x) == find(y);
  }

  [[nodiscard]] int groups() const noexcept { return groupCount; }

  template <Integral T>
  [[nodiscard]] int groupSize(T x) {
    if (!isValidIndex(x)) {
      throw std::out_of_range("Index out of range");
    }

    int root = find(x);
    int size = 0;
    for (size_t i = 0; i < parent.size(); ++i) {
      if (find(static_cast<int>(i)) == root) size++;
    }
    return size;
  }

  [[nodiscard]] size_t size() const noexcept { return parent.size(); }
};

#endif  // UNION_FIND_HPP
