add_subdirectory(benchmark)

include_directories(${PROJECT_SOURCE_DIR}/boggle-solver/)
include_directories(benchmark/include/)

add_executable(trie_bench trie_bench.cpp)
set_target_properties(trie_bench PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
target_link_libraries(trie_bench
                      trie
                      benchmark)
add_dependencies(trie_bench trie)

# Disable warnings when building Google Benchmark.
target_compile_options(trie_bench PRIVATE -w)
target_compile_options(benchmark PRIVATE -w)
