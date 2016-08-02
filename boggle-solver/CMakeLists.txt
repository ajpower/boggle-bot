find_package(Boost REQUIRED)

if (NOT Boost_FOUND)
	message(FATAL_ERROR "Boost libraries not found.")
endif ()

# Compile Trie class to a static library so it can be used in tests.
add_library(trie STATIC trie.cpp boggle.hpp)
