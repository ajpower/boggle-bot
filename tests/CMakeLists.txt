add_subdirectory(googletest)

include_directories(googletest/googletest/include/)
include_directories(${PROJECT_SOURCE_DIR}/boggle-solver/)

add_executable(trie_test trie_test.cpp)
set_target_properties(trie_test PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
target_link_libraries(trie_test
                      trie
                      gtest
                      gtest_main)
add_dependencies(trie_test trie)

# Disable warnings when building Google Test.
target_compile_options(trie_test PRIVATE -w)
target_compile_options(gmock PRIVATE -w)
target_compile_options(gmock_main PRIVATE -w)
target_compile_options(gtest PRIVATE -w)
target_compile_options(gtest_main PRIVATE -w)

add_test(trie_test trie_test)
