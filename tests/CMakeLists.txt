set(DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../boggle-solver)

add_compile_options(-std=c++14)
add_compile_options(-O3)

add_executable(trie_tests trie_tests.cpp)
set_target_properties(trie_tests PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${DESTINATION})
target_link_libraries(trie_tests
                      trie
                      boost_unit_test_framework)
