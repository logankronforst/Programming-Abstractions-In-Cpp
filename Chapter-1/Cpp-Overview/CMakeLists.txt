cmake_minimum_required(VERSION 3.15)
project(cpp_overview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    GTest::gtest
    Threads::Threads
)

include(CTest)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
