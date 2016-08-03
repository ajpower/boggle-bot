find_package(Boost COMPONENTS python REQUIRED)

if (NOT Boost_FOUND)
	message(FATAL_ERROR "Boost libraries not found.")
endif ()

# Compile Trie class to a static library so it can be used in tests.
add_library(trie STATIC trie.cpp)

# Compile a Python module for the Boggle class.
# Remove missing-prototype warning if compiling with Clang so Boost.Python can compile without
# warnings.
if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	add_compile_options(-Wno-missing-prototypes)
endif ()
add_library(boggle SHARED pyboggle.cpp boggle.hpp)
include_directories(/usr/include/python3.5)
set_target_properties(boggle PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/boggle-bot/
                      PREFIX "")
target_link_libraries(boggle
                      trie
                      boost_python-py35)
add_dependencies(boggle trie)
