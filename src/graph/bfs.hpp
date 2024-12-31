#ifndef BFS_HPP
#define BFS_HPP

#include <algorithm>
#include <concepts>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
concept GraphNode = std::equality_comparable<T> && std::copy_constructible<T>;

template <typename T>
concept HashableNode = GraphNode<T> && requires(T x) {
  { std::hash<T>{}(x) } -> std::convertible_to<std::size_t>;
};

template <HashableNode NodeType>
class BFS {
private:
  using Graph = std::unordered_map<NodeType, std::vector<NodeType>>;
  Graph adjacencyList;

  void logVisit(const NodeType& node) const {
    std::cout << "Visiting node: " << node << std::endl;
  }

public:
  void addEdge(const NodeType& from, const NodeType& to) {
    adjacencyList[from].push_back(to);
    // In the case of an isolated point, create an empty adjacent list
    if (adjacencyList.find(to) == adjacencyList.end()) {
      adjacencyList[to] = std::vector<NodeType>();
    }
  }

  [[nodiscard]] std::vector<NodeType> traverse(const NodeType& start) const {
    std::queue<NodeType> queue;
    std::unordered_map<NodeType, bool> visited;
    std::vector<NodeType> result;

    std::cout << "Starting BFS traversal from node: " << start << std::endl;

    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
      NodeType current = queue.front();
      queue.pop();

      logVisit(current);
      result.push_back(current);

      if (auto it = adjacencyList.find(current); it != adjacencyList.end()) {
        for (const auto& neighbor : it->second) {
          if (!visited[neighbor]) {
            std::cout << "Moving from " << current << " to " << neighbor << std::endl;
            queue.push(neighbor);
            visited[neighbor] = true;
          }
        }
      }
    }

    return result;
  }

  [[nodiscard]] std::vector<NodeType> findShortestPath(const NodeType& start,
                                                       const NodeType& target) const {
    std::queue<NodeType> queue;
    std::unordered_map<NodeType, bool> visited;
    std::unordered_map<NodeType, NodeType> parent;

    std::cout << "Finding shortest path from " << start << " to " << target << std::endl;

    queue.push(start);
    visited[start] = true;

    bool found = false;
    while (!queue.empty() && !found) {
      NodeType current = queue.front();
      queue.pop();

      if (current == target) {
        std::cout << "Target " << target << " found!" << std::endl;
        found = true;
        break;
      }

      if (auto it = adjacencyList.find(current); it != adjacencyList.end()) {
        for (const auto& neighbor : it->second) {
          if (!visited[neighbor]) {
            queue.push(neighbor);
            visited[neighbor] = true;
            parent[neighbor] = current;
          }
        }
      }
    }

    std::vector<NodeType> path;
    if (found) {
      NodeType current = target;
      while (current != start) {
        path.push_back(current);
        current = parent[current];
      }
      path.push_back(start);
      std::reverse(path.begin(), path.end());
    }

    return path;
  }

  [[nodiscard]] size_t countConnectedComponents() const {
    std::unordered_set<NodeType> unvisited;
    for (const auto& [node, _] : adjacencyList) {
      unvisited.insert(node);
    }

    size_t components = 0;
    while (!unvisited.empty()) {
      NodeType start = *unvisited.begin();
      std::cout << "Starting new component exploration from node: " << start << std::endl;
      auto visited = traverse(start);
      for (const auto& node : visited) {
        unvisited.erase(node);
      }
      components++;
    }

    return components;
  }
};

#endif  // BFS_HPP
