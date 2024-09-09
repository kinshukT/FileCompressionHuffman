cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(HuffmanCoding VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/HuffmanCoding.cpp
    src/HuffmanNode.cpp
)

# Add the executable
add_executable(HuffmanCoding ${SOURCES})

# Install targets (optional)
install(TARGETS HuffmanCoding DESTINATION bin)