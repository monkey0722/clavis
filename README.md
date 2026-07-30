# Clavis 🔑

## A Treasury of Algorithms That Make Even Computers Laugh

Welcome to Clavis! Here, efficient algorithms and unnecessarily complex C++ code form an unstable relationship. If you find a bug, please call it a "feature." Big O notation is our only lover, computational complexity our best friend.

## Requirements

| Tool | Version | Install (macOS) |
|------|---------|-----------------|
| C++ compiler | C++23 support | Xcode Command Line Tools |
| CMake | 3.25+ | `brew install cmake` |
| Ninja | any | `brew install ninja` |
| GTest | any | `brew install googletest` |
| LLVM | 17+ | `brew install llvm` |

CI validates the project with GCC 13.

### Quick Setup (macOS)

```bash
brew install cmake ninja googletest llvm
```

## Build & Test

```bash
# Build
cmake --preset debug
cmake --build --preset debug

# Test
ctest --preset debug

# Test (verbose)
ctest --preset debug --verbose
```

### Available Presets

| Preset | Generator | Use Case |
|--------|-----------|----------|
| `debug` | Ninja | Local development |
| `release` | Ninja | Production build |
| `ci` | Ninja | GitHub Actions |
| `quality` | Ninja | Code-quality tools |

## Code Quality

```bash
# Configure code-quality tools without requiring GTest
cmake --preset quality

# Format
cmake --build --preset format

# Format check
cmake --build --preset format-check

# Lint
cmake --build --preset lint
```
