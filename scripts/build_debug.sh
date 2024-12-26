#!/bin/bash

# build_debug.sh
# Usage: ./build_debug.sh <source_file> [options]

print_usage() {
echo "Usage: $0 <source_file> [options]"
echo "Options:"
echo "  -c, --clean     Remove old executable before building"
echo "  -r, --run       Run program after building" 
echo "  -h, --help      Show this help message"
echo ""
echo "Example: $0 sort.cpp -r"
}

# Set default values 
CLEAN_MODE=0
RUN_AFTER_BUILD=0

# Create build directory
BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
mkdir -p "$BUILD_DIR"
fi

# Show usage if no arguments
if [ $# -eq 0 ]; then
print_usage
exit 1
fi

SOURCE_FILE=$1
shift  # Remove source file from argument list

# Set output file path
FILENAME=$(basename "${SOURCE_FILE%.*}")
OUTPUT_FILE="$BUILD_DIR/${FILENAME}_debug"

# Parse options
while [ $# -gt 0 ]; do
case "$1" in
  -c|--clean)
    CLEAN_MODE=1
    ;;
  -r|--run)
    RUN_AFTER_BUILD=1
    ;;
  -h|--help)
    print_usage
    exit 0
    ;;
  *)
    echo "Unknown option: $1"
    print_usage
    exit 1
    ;;
esac
shift
done

# Cleanup
if [ $CLEAN_MODE -eq 1 ]; then
echo "Removing old executable..."
rm -f "$OUTPUT_FILE"
fi

# Run debug build
echo "Building in debug mode..."
g++ -std=c++20 -DDEBUG_LOG -g "$SOURCE_FILE" -o "$OUTPUT_FILE"

echo "Build complete: $OUTPUT_FILE"

# Run after build if requested
if [ $RUN_AFTER_BUILD -eq 1 ]; then
echo "Running program..."
"$OUTPUT_FILE"
fi
