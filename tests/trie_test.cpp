/*
 * Unit tests for the Trie class.
 */
#include "gtest/gtest.h"
#include "trie.hpp"

/*
 * Test that the Trie default constructor executes successfully and creates an empty Trie.
 */
TEST(TrieTest, InitiallyEmpty) {
	Trie trie;
	EXPECT_TRUE(trie.empty());
}

/*
 * Test the insertion and lookup of non-overlapping strings.
 */
TEST(TrieTest, HasStringNoOverlap) {
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

/*
 * Test the insertion and lookup of overlapping strings.
 */
TEST(TrieTest, HasStringOverlap) {
	Trie trie;
	trie.insert("SOME");
	trie.insert("SOMETIMES");
	trie.insert("SPACETIME");
	trie.insert("SPACE");
	trie.insert("ABSOLUTE");
	trie.insert("ABSOLVE");

	EXPECT_FALSE(trie.empty());

	EXPECT_TRUE(trie.has_string("SOME"));
	EXPECT_TRUE(trie.has_string("SOMETIMES"));
	EXPECT_TRUE(trie.has_string("SPACETIME"));
	EXPECT_TRUE(trie.has_string("SPACE"));
	EXPECT_TRUE(trie.has_string("ABSOLUTE"));
	EXPECT_TRUE(trie.has_string("ABSOLVE"));

	EXPECT_FALSE(trie.has_string("S"));
	EXPECT_FALSE(trie.has_string("SOMET"));
	EXPECT_FALSE(trie.has_string("SOMETIME"));
	EXPECT_FALSE(trie.has_string("SPA"));
	EXPECT_FALSE(trie.has_string("SPACES"));
	EXPECT_FALSE(trie.has_string("AB"));
}

/*
 * Test the insertion of overlapping strings and the lookup of the strings' prefixes.
 */
TEST(TrieTest, HasPrefix) {
	Trie trie;
	trie.insert("SOME");
	trie.insert("SOMETIMES");
	trie.insert("SPACETIME");
	trie.insert("SPACE");
	trie.insert("ABSOLUTE");
	trie.insert("ABSOLVE");

	EXPECT_FALSE(trie.empty());

	EXPECT_TRUE(trie.has_prefix("SOME"));
	EXPECT_TRUE(trie.has_prefix("SOMETIMES"));
	EXPECT_TRUE(trie.has_prefix("SPACETIME"));
	EXPECT_TRUE(trie.has_prefix("SPACE"));
	EXPECT_TRUE(trie.has_prefix("ABSOLUTE"));
	EXPECT_TRUE(trie.has_prefix("ABSOLVE"));

	EXPECT_TRUE(trie.has_prefix("S"));
	EXPECT_TRUE(trie.has_prefix("SPA"));
	EXPECT_TRUE(trie.has_prefix("ABS"));
	EXPECT_TRUE(trie.has_prefix("SOMETIME"));

	EXPECT_FALSE(trie.has_prefix("SPACES"));
	EXPECT_FALSE(trie.has_prefix("TIME"));
	EXPECT_FALSE(trie.has_prefix("SME"));
	EXPECT_FALSE(trie.has_prefix("ABSOLVER"));
	EXPECT_FALSE(trie.has_prefix("PACES"));
}

TEST(TrieTest, MoveConstructor) {
	Trie trie;
	trie.insert("SOME");
	trie.insert("SOMETIMES");
	trie.insert("SPACETIME");
	trie.insert("SPACE");
	trie.insert("ABSOLUTE");
	trie.insert("ABSOLVE");

	Trie other(std::move(trie));

	EXPECT_TRUE(other.has_prefix("SOME"));
	EXPECT_TRUE(other.has_prefix("SOMETIMES"));
	EXPECT_TRUE(other.has_prefix("SPACETIME"));
	EXPECT_TRUE(other.has_prefix("SPACE"));
	EXPECT_TRUE(other.has_prefix("ABSOLUTE"));
	EXPECT_TRUE(other.has_prefix("ABSOLVE"));

	EXPECT_TRUE(trie.empty());
}

TEST(TrieTest, MoveAssignment) {
	Trie trie;
	trie.insert("SOME");
	trie.insert("SOMETIMES");
	trie.insert("SPACETIME");
	trie.insert("SPACE");
	trie.insert("ABSOLUTE");
	trie.insert("ABSOLVE");

	Trie other;
	other = std::move(trie);

	EXPECT_TRUE(other.has_prefix("SOME"));
	EXPECT_TRUE(other.has_prefix("SOMETIMES"));
	EXPECT_TRUE(other.has_prefix("SPACETIME"));
	EXPECT_TRUE(other.has_prefix("SPACE"));
	EXPECT_TRUE(other.has_prefix("ABSOLUTE"));
	EXPECT_TRUE(other.has_prefix("ABSOLVE"));

	EXPECT_TRUE(trie.empty());
}
