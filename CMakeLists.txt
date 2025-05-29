cmake_minimum_required(VERSION 3.14)
project(signaltree)

option(BUILD_TESTING "Build the tests" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Compilation flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -fno-inline -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "No CMAKE_BUILD_TYPE specified. Defaulting to Release mode.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Find LuaJIT
find_package(PkgConfig REQUIRED)
pkg_check_modules(LUAJIT REQUIRED luajit)

# Gather source files
file(GLOB SRC_FILES src/*.cpp)

# Create the library
add_library(signaltree SHARED ${SRC_FILES})
target_include_directories(signaltree PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties(signaltree PROPERTIES OUTPUT_NAME "signaltree")

# Build examples/tests
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(examples)
endif()
