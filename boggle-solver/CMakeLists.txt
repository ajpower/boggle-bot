# Compile Trie class to a static library so it can be used in tests.
add_library(trie STATIC trie.cpp)
set_target_properties(trie PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
