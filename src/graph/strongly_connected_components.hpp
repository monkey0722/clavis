#ifndef STRONGLY_CONNECTED_COMPONENTS_HPP
#define STRONGLY_CONNECTED_COMPONENTS_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

struct StronglyConnectedComponentsResult {
  std::vector<std::size_t> componentOf;
  std::vector<std::vector<std::size_t>> components;
};

/**
 * @brief Partitions a directed graph using the Kosaraju-Sharir algorithm.
 *
 * @param graph Directed graph represented as an adjacency list.
 * @return A component ID for every vertex and the vertices in each component.
 * @throws std::out_of_range If an edge endpoint is invalid.
 *
 * @complexity O(V + E) time and O(V + E) additional space.
 */
[[nodiscard]] inline StronglyConnectedComponentsResult stronglyConnectedComponents(
    const std::vector<std::vector<std::size_t>>& graph) {
  std::vector<std::vector<std::size_t>> reversedGraph(graph.size());
  for (std::size_t from = 0; from < graph.size(); ++from) {
    for (const std::size_t to : graph[from]) {
      if (to >= graph.size()) {
        throw std::out_of_range("Edge endpoint is out of range");
      }
      reversedGraph[to].push_back(from);
    }
  }

  std::vector<bool> visited(graph.size(), false);
  std::vector<std::size_t> finishOrder;
  finishOrder.reserve(graph.size());

  for (std::size_t start = 0; start < graph.size(); ++start) {
    if (visited[start]) {
      continue;
    }

    std::vector<std::pair<std::size_t, std::size_t>> stack;
    stack.emplace_back(start, 0);
    visited[start] = true;

    while (!stack.empty()) {
      auto& [vertex, nextNeighbor] = stack.back();
      if (nextNeighbor < graph[vertex].size()) {
        const std::size_t neighbor = graph[vertex][nextNeighbor];
        ++nextNeighbor;
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          stack.emplace_back(neighbor, 0);
        }
      } else {
        finishOrder.push_back(vertex);
        stack.pop_back();
      }
    }
  }

  std::vector<bool> assigned(graph.size(), false);
  std::vector<std::size_t> componentOf(graph.size());
  std::vector<std::vector<std::size_t>> components;

  for (std::size_t index = finishOrder.size(); index > 0; --index) {
    const std::size_t root = finishOrder[index - 1];
    if (assigned[root]) {
      continue;
    }

    const std::size_t componentId = components.size();
    std::vector<std::size_t> component;
    std::vector<std::size_t> stack = {root};
    assigned[root] = true;

    while (!stack.empty()) {
      const std::size_t vertex = stack.back();
      stack.pop_back();
      componentOf[vertex] = componentId;
      component.push_back(vertex);

      for (const std::size_t neighbor : reversedGraph[vertex]) {
        if (!assigned[neighbor]) {
          assigned[neighbor] = true;
          stack.push_back(neighbor);
        }
      }
    }

    components.push_back(std::move(component));
  }

  return {
      .componentOf = std::move(componentOf),
      .components = std::move(components),
  };
}

#endif  // STRONGLY_CONNECTED_COMPONENTS_HPP
