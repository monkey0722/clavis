# Clavis 🔑

## A Treasury of Algorithms That Make Even Computers Laugh

Welcome to Clavis! Here, efficient algorithms and unnecessarily complex C++ code form an unstable relationship. If you find a bug, please call it a "feature." Big O notation is our only lover, computational complexity our best friend.

## Requirements

| Tool | Version | Install (macOS) |
|------|---------|-----------------|
| CMake | 3.25+ | `brew install cmake` |
| Ninja | any | `brew install ninja` |
| GTest | any | `brew install googletest` |
| LLVM | 16+ | `brew install llvm` |

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

## Code Quality

```bash
# Format
cmake --build build/debug -t format

# Format check
cmake --build build/debug -t format-check

# Lint
cmake --build build/debug -t lint
```
