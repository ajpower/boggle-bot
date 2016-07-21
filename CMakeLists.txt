cmake_minimum_required(VERSION 3.0.2)

project(boggle-bot CXX)
add_subdirectory(boggle-solver)
add_subdirectory(tests)

enable_testing()
add_test(NAME trie_tests COMMAND trie_tests)
