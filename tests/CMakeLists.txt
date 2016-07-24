add_subdirectory(googletest)

include_directories(googletest/googletest/include/)
include_directories(${PROJECT_SOURCE_DIR}/boggle-solver/)

add_executable(trie_test trie_test.cpp)
set_target_properties(trie_test PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE})
target_link_libraries(trie_test
                      trie
                      gtest
                      gtest_main)
add_dependencies(trie_test trie)

add_executable(boggle_test boggle_test.cpp)
set_target_properties(boggle_test PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE})
target_link_libraries(boggle_test
                      gtest
                      gtest_main)

# Disable warnings when building Google Test
target_compile_options(boggle_test PRIVATE -w)
target_compile_options(trie_test PRIVATE -w)
target_compile_options(gmock PRIVATE -w)
target_compile_options(gmock_main PRIVATE -w)
target_compile_options(gtest PRIVATE -w)
target_compile_options(gtest_main PRIVATE -w)
