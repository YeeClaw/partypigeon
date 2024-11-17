# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PartyPigeon C)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Make this available to LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set global output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories for wing and partypigeon
add_subdirectory(src/wing)
add_subdirectory(src/partypigeon/client)
add_subdirectory(src/partypigeon/server)

