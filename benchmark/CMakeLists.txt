option(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(benchmark)

include_directories(${PROJECT_SOURCE_DIR}/boggle-solver/)
include_directories(benchmark/include/)

add_executable(trie_bench trie_bench.cpp)
target_link_libraries(trie_bench
                      trie
                      benchmark)
add_dependencies(trie_bench trie)

add_executable(boggle_bench boggle_bench.cpp)
target_link_libraries(boggle_bench
                      trie
                      benchmark)
add_dependencies(boggle_bench trie)

# Disable warnings when building Google Benchmark.
target_compile_options(boggle_bench PRIVATE -w)
target_compile_options(trie_bench PRIVATE -w)
target_compile_options(benchmark PRIVATE -w)

# Add path to dictionary.
add_definitions(-DDICT_PATH="${PROJECT_SOURCE_DIR}/boggle-bot/dict.list")
