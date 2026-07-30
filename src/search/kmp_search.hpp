#ifndef KMP_SEARCH_HPP
#define KMP_SEARCH_HPP

#include <cstddef>
#include <optional>
#include <string_view>
#include <vector>

namespace clavis::search {

namespace detail {

[[nodiscard]] inline std::vector<std::size_t> buildKmpPrefixTable(std::string_view pattern) {
  std::vector<std::size_t> prefixTable(pattern.size(), 0);
  std::size_t matched = 0;

  for (std::size_t index = 1; index < pattern.size(); ++index) {
    while (matched > 0 && pattern[index] != pattern[matched]) {
      matched = prefixTable[matched - 1];
    }
    if (pattern[index] == pattern[matched]) {
      ++matched;
    }
    prefixTable[index] = matched;
  }

  return prefixTable;
}

}  // namespace detail

/**
 * @brief Finds the first occurrence of a pattern using Knuth-Morris-Pratt search.
 *
 * @param text Text to search.
 * @param pattern Pattern to locate.
 * @return The starting position of the first match, or std::nullopt if absent.
 *
 * @note An empty pattern matches at position 0.
 * @complexity O(N + M) time and O(M) additional space.
 */
[[nodiscard]] inline std::optional<std::size_t> kmp_search(std::string_view text,
                                                           std::string_view pattern) {
  if (pattern.empty()) {
    return 0;
  }

  const std::vector<std::size_t> prefixTable = detail::buildKmpPrefixTable(pattern);
  std::size_t matched = 0;

  for (std::size_t index = 0; index < text.size(); ++index) {
    while (matched > 0 && text[index] != pattern[matched]) {
      matched = prefixTable[matched - 1];
    }
    if (text[index] == pattern[matched]) {
      ++matched;
    }
    if (matched == pattern.size()) {
      return index + 1 - pattern.size();
    }
  }

  return std::nullopt;
}

}  // namespace clavis::search

#endif  // KMP_SEARCH_HPP
