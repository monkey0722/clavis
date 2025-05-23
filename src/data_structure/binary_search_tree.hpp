#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <concepts>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <stack>

template <typename T>
concept Comparable = std::totally_ordered<T> && std::copyable<T>;

template <Comparable T>
class BinarySearchTree {
private:
  struct Node {
    T value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    explicit Node(const T& val) : value(val) {}
  };

  std::unique_ptr<Node> root;
  size_t nodeCount = 0;

public:
  BinarySearchTree() = default;

  void insert(const T& value) {
    if (!root) {
      std::cout << "Creating root node with value: " << value << std::endl;
      root = std::make_unique<Node>(value);
      nodeCount++;
      return;
    }

    Node* current = root.get();
    while (true) {
      if (value < current->value) {
        if (!current->left) {
          std::cout << "Inserting " << value << " as left child of " << current->value << std::endl;
          current->left = std::make_unique<Node>(value);
          nodeCount++;
          break;
        }
        current = current->left.get();
      } else if (value > current->value) {
        if (!current->right) {
          std::cout << "Inserting " << value << " as right child of " << current->value
                    << std::endl;
          current->right = std::make_unique<Node>(value);
          nodeCount++;
          break;
        }
        current = current->right.get();
      } else {
        // Duplicates are ignored.
        return;
      }
    }
  }

  [[nodiscard]] bool contains(const T& value) const {
    const Node* current = root.get();
    while (current) {
      if (value < current->value) {
        current = current->left.get();
      } else if (value > current->value) {
        current = current->right.get();
      } else {
        return true;
      }
    }
    return false;
  }

  [[nodiscard]] std::optional<T> minimum() const {
    if (!root) return std::nullopt;

    const Node* current = root.get();
    while (current->left) {
      current = current->left.get();
    }
    return current->value;
  }

  [[nodiscard]] std::optional<T> maximum() const {
    if (!root) return std::nullopt;

    const Node* current = root.get();
    while (current->right) {
      current = current->right.get();
    }
    return current->value;
  }

  bool remove(const T& value) {
    std::cout << "Attempting to remove value: " << value << std::endl;

    Node* parent = nullptr;
    Node* current = root.get();
    bool isLeftChild = false;

    // Search for the node to be deleted.
    while (current && current->value != value) {
      parent = current;
      if (value < current->value) {
        current = current->left.get();
        isLeftChild = true;
      } else {
        current = current->right.get();
        isLeftChild = false;
      }
    }

    if (!current) return false;

    // Case　1:　No child nodes.
    if (!current->left && !current->right) {
      if (!parent) {
        root.reset();
      } else if (isLeftChild) {
        parent->left.reset();
      } else {
        parent->right.reset();
      }
    }
    // Case 2: One of the child nodes.
    else if (!current->left) {
      if (!parent) {
        root = std::move(current->right);
      } else if (isLeftChild) {
        parent->left = std::move(current->right);
      } else {
        parent->right = std::move(current->right);
      }
    } else if (!current->right) {
      if (!parent) {
        root = std::move(current->left);
      } else if (isLeftChild) {
        parent->left = std::move(current->left);
      } else {
        parent->right = std::move(current->left);
      }
    }
    // Case 3: Both child nodes.
    else {
      Node* successor = current->right.get();
      Node* successorParent = current;

      while (successor->left) {
        successorParent = successor;
        successor = successor->left.get();
      }

      current->value = successor->value;

      if (successorParent == current) {
        current->right = std::move(successor->right);
      } else {
        successorParent->left = std::move(successor->right);
      }
    }
    std::cout << "Successfully removed value: " << value << std::endl;
    nodeCount--;
    return true;
  }

  // Middle-order scan (ascending order).
  void inorderTraversal(const std::function<void(const T&)>& visitor) const {
    std::stack<const Node*> stack;
    const Node* current = root.get();

    while (current || !stack.empty()) {
      while (current) {
        stack.push(current);
        current = current->left.get();
      }
      current = stack.top();
      stack.pop();
      visitor(current->value);
      current = current->right.get();
    }
  }

  // Width-priority run
  void levelOrderTraversal(const std::function<void(const T&)>& visitor) const {
    if (!root) return;

    std::queue<const Node*> queue;
    queue.push(root.get());

    while (!queue.empty()) {
      const Node* current = queue.front();
      queue.pop();

      visitor(current->value);

      if (current->left) {
        queue.push(current->left.get());
      }
      if (current->right) {
        queue.push(current->right.get());
      }
    }
  }
  [[nodiscard]] size_t size() const noexcept { return nodeCount; }
  [[nodiscard]] bool empty() const noexcept { return nodeCount == 0; }
};

#endif  // BINARY_SEARCH_TREE_HPP