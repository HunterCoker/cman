add_library(tree_sitter_cmake STATIC)

target_sources(tree_sitter_cmake
    PRIVATE
        parser.c
        scanner.c
)

target_include_directories(tree_sitter_cmake
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)
