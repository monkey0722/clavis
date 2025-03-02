#ifndef DFS_HPP
#define DFS_HPP

#include <algorithm>
#include <concepts>
#include <iostream>
#include <stack>
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
class DFS {
private:
  using Graph = std::unordered_map<NodeType, std::vector<NodeType>>;
  Graph adjacencyList;

  void logVisit(const NodeType& node) const {
    std::cout << "Visiting node: " << node << std::endl;
  }

  // Helper function for recursive DFS traversal
  void traverseRecursive(const NodeType& node, std::unordered_map<NodeType, bool>& visited,
                         std::vector<NodeType>& result) const {
    visited[node] = true;
    logVisit(node);
    result.push_back(node);

    if (auto it = adjacencyList.find(node); it != adjacencyList.end()) {
      for (const auto& neighbor : it->second) {
        if (!visited[neighbor]) {
          std::cout << "Moving from " << node << " to " << neighbor << std::endl;
          traverseRecursive(neighbor, visited, result);
        }
      }
    }
  }

public:
  void addEdge(const NodeType& from, const NodeType& to) {
    adjacencyList[from].push_back(to);
    // In the case of an isolated point, create an empty adjacent list
    if (adjacencyList.find(to) == adjacencyList.end()) {
      adjacencyList[to] = std::vector<NodeType>();
    }
  }

  // Iterative DFS traversal using a stack
  [[nodiscard]] std::vector<NodeType> traverse(const NodeType& start) const {
    std::stack<NodeType> stack;
    std::unordered_map<NodeType, bool> visited;
    std::vector<NodeType> result;

    std::cout << "Starting DFS traversal from node: " << start << std::endl;

    stack.push(start);

    while (!stack.empty()) {
      NodeType current = stack.top();
      stack.pop();

      if (!visited[current]) {
        logVisit(current);
        result.push_back(current);
        visited[current] = true;

        if (auto it = adjacencyList.find(current); it != adjacencyList.end()) {
          // Push neighbors in reverse order to process them in the original order
          for (auto it2 = it->second.rbegin(); it2 != it->second.rend(); ++it2) {
            const auto& neighbor = *it2;
            if (!visited[neighbor]) {
              std::cout << "Pushing " << neighbor << " to stack" << std::endl;
              stack.push(neighbor);
            }
          }
        }
      }
    }

    return result;
  }

  // Recursive DFS traversal
  [[nodiscard]] std::vector<NodeType> traverseRecursive(const NodeType& start) const {
    std::unordered_map<NodeType, bool> visited;
    std::vector<NodeType> result;

    std::cout << "Starting recursive DFS traversal from node: " << start << std::endl;
    traverseRecursive(start, visited, result);

    return result;
  }

  // Find path using DFS (not necessarily the shortest)
  [[nodiscard]] std::vector<NodeType> findPath(const NodeType& start, const NodeType& target) const {
    std::stack<NodeType> stack;
    std::unordered_map<NodeType, bool> visited;
    std::unordered_map<NodeType, NodeType> parent;

    std::cout << "Finding path from " << start << " to " << target << std::endl;

    stack.push(start);
    visited[start] = true;

    bool found = false;
    while (!stack.empty() && !found) {
      NodeType current = stack.top();
      stack.pop();

      if (current == target) {
        std::cout << "Target " << target << " found!" << std::endl;
        found = true;
        break;
      }

      if (auto it = adjacencyList.find(current); it != adjacencyList.end()) {
        for (const auto& neighbor : it->second) {
          if (!visited[neighbor]) {
            stack.push(neighbor);
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

  // Detect cycles in the graph
  [[nodiscard]] bool hasCycle() const {
    std::unordered_map<NodeType, bool> visited;
    std::unordered_map<NodeType, bool> inStack;

    for (const auto& [node, _] : adjacencyList) {
      if (!visited[node]) {
        if (hasCycleUtil(node, visited, inStack)) {
          return true;
        }
      }
    }
    return false;
  }

private:
  bool hasCycleUtil(const NodeType& node, std::unordered_map<NodeType, bool>& visited,
                    std::unordered_map<NodeType, bool>& inStack) const {
    visited[node] = true;
    inStack[node] = true;

    if (auto it = adjacencyList.find(node); it != adjacencyList.end()) {
      for (const auto& neighbor : it->second) {
        if (!visited[neighbor]) {
          if (hasCycleUtil(neighbor, visited, inStack)) {
            return true;
          }
        } else if (inStack[neighbor]) {
          // If the neighbor is already in the recursion stack, we found a cycle
          return true;
        }
      }
    }

    inStack[node] = false;  // Remove the node from recursion stack
    return false;
  }

public:
  // Topological sort (only works for DAGs)
  [[nodiscard]] std::vector<NodeType> topologicalSort() const {
    if (hasCycle()) {
      std::cout << "Graph has a cycle, topological sort not possible" << std::endl;
      return {};
    }

    std::unordered_map<NodeType, bool> visited;
    std::stack<NodeType> stack;
    std::vector<NodeType> result;

    for (const auto& [node, _] : adjacencyList) {
      if (!visited[node]) {
        topologicalSortUtil(node, visited, stack);
      }
    }

    while (!stack.empty()) {
      result.push_back(stack.top());
      stack.pop();
    }

    return result;
  }

private:
  void topologicalSortUtil(const NodeType& node, std::unordered_map<NodeType, bool>& visited,
                          std::stack<NodeType>& stack) const {
    visited[node] = true;

    if (auto it = adjacencyList.find(node); it != adjacencyList.end()) {
      for (const auto& neighbor : it->second) {
        if (!visited[neighbor]) {
          topologicalSortUtil(neighbor, visited, stack);
        }
      }
    }

    // All descendants processed, push current node to stack
    stack.push(node);
  }

public:
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

#endif  // DFS_HPP
