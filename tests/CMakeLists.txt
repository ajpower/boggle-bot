add_subdirectory(googletest/)

include_directories(googletest/googletest/include/)
include_directories(${PROJECT_SOURCE_DIR}/boggle-solver)

add_executable(trie_test trie_test.cpp)
target_link_libraries(trie_test
                      gtest gtest_main)

# Disable warnings when building Google Test.
target_compile_options(trie_test PRIVATE -w)
target_compile_options(gmock PRIVATE -w)
target_compile_options(gmock_main PRIVATE -w)
target_compile_options(gtest PRIVATE -w)
target_compile_options(gtest_main PRIVATE -w)

add_test(trie_test trie_test)
