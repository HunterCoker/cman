cmake_minimum_required(VERSION {{ minimum_supported }})
project({{ project_name }} LANGUAGES C CXX)

set({{ project_name | upper }}_TARGET "{{ project_name }}")

set(CMAKE_CXX_STANDARD 17)
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
