cmake_minimum_required(VERSION 3.20)
project(cman LANGUAGES C CXX)

set(CMAN_TARGET ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(EXISTS "${CMAKE_SOURCE_DIR}/libs")
    add_subdirectory(libs)
endif()

add_subdirectory(src)

if(CMAN_BUILD_TESTS AND EXISTS "${CMAKE_SOURCE_DIR}/tests")
    enable_testing()
    add_subdirectory(tests)
endif()
