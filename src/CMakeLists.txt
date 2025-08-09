add_executable(${CMAN_TARGET}
    "main.cpp"
    "project.cpp"
    "utility/assert.cpp"
)

target_compile_definitions(${CMAN_TARGET}
    PRIVATE $<$<CONFIG:Debug>:DEBUG>
    PRIVATE $<$<CONFIG:Release>:NDEBUG>
)

target_include_directories(${CMAN_TARGET}
    PRIVATE "${CMAKE_SOURCE_DIR}/libs/tree-sitter/lib/include"
)

target_link_libraries(${CMAN_TARGET}
    PRIVATE CLI11::CLI11
    PRIVATE spdlog::spdlog
    PRIVATE pantor::inja
    PRIVATE pantor::nlohmann_json
    PRIVATE tree-sitter
    PRIVATE tree_sitter_cmake
)