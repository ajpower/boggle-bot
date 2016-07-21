/*
 * Unit tests for the Trie class.
 */
#define BOOST_TEST_MODULE TrieTests

#include <boost/test/included/unit_test.hpp>

#include "trie.hpp"

BOOST_AUTO_TEST_CASE(trie_simple_insertions) {
	Trie trie;

	// Insert some strings.
	trie.insert("HELLO");
	trie.insert("SOME");
	trie.insert("SOMETIME");

	BOOST_REQUIRE(trie.has_string("HELLO"));
	BOOST_REQUIRE(trie.has_string("SOME"));
	BOOST_REQUIRE(trie.has_string("SOMETIME"));

	BOOST_REQUIRE(not trie.has_string("FOO"));
	BOOST_REQUIRE(not trie.has_string("BAR"));
	BOOST_REQUIRE(not trie.has_string("SOMET"));
	//BOOST_REQUIRE(not trie.has_string("SOMETIMES"));
}
