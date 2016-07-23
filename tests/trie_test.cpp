/*
 * Unit test for the Trie class.
 */
#include "gtest/gtest.h"
#include "trie.hpp"

TEST(TrieTest, InitiallyEmpty) {
	Trie trie;
	EXPECT_TRUE(trie.empty());
}

TEST(TrieTest, NoOverlap) {
	Trie trie;
	trie.insert("A");
	trie.insert("HELLO");
	trie.insert("QUANTUM");
	trie.insert("PARAMETERS");
	trie.insert("PSYCHOLOGICAL");

	EXPECT_FALSE(trie.empty());

	EXPECT_TRUE(trie.has_string("A"));
	EXPECT_TRUE(trie.has_string("HELLO"));
	EXPECT_TRUE(trie.has_string("QUANTUM"));
	EXPECT_TRUE(trie.has_string("PARAMETERS"));
	EXPECT_TRUE(trie.has_string("PSYCHOLOGICAL"));

	EXPECT_FALSE(trie.has_string("FOO"));
	EXPECT_FALSE(trie.has_string("B"));
	EXPECT_FALSE(trie.has_string("H"));
	EXPECT_FALSE(trie.has_string("HELL"));
	EXPECT_FALSE(trie.has_string("UANTUM"));
	EXPECT_FALSE(trie.has_string("PSYCHOLOGY"));
}
