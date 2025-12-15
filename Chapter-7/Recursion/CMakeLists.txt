cmake_minimum_required(VERSION 3.15)
project(recursion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- GoogleTest via FetchContent ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Keep runtimes consistent on MSVC (harmless elsewhere)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)  # provides GTest::gtest and GTest::gtest_main

# --- Your executable (tests + code in one file) ---
add_executable(${PROJECT_NAME} src/main.cpp)

# --- Threads (Linux) ---
find_package(Threads REQUIRED)

# You provide your own main(), so link GTest::gtest (NOT gtest_main)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    GTest::gtest
    Threads::Threads
)

# (Optional) Enable `ctest` so you can run `ctest -V`
include(CTest)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

