/*
 * Declaration of the Trie class.
 */
#pragma once

#include <array>

namespace {
constexpr std::size_t ALPHABET = 27; // Each uppercase letter plus the null character.
}

/*
 * The trie is a data structure used as a dynamic set of strings. The trie can test for
 * membership of both strings and their prefixes.
 *
 * This implementation of the trie holds only strings containing uppercase ASCII letters. Attempts
 * to use strings containing anything else will lead to undefined behaviour.
 *
 * Deletion of strings is not supported as there is currently no reason to remove items from the
 * trie during a Boggle game.
 */
//TODO bitwise trie?
class Trie {
public:
	/* Constructors. */
	/*
	 * Create an empty trie.
	 */
	Trie();

	/* Destructors. */
	~Trie();

	/* Accessor functions. */
	/*
	 * Return true if the trie is empty.
	 */
	bool empty() const;

	/*
	 * Return true if the trie contains the given string.
	 */
	bool has_string(const char *string) const;

	/*
	 * Return true if the trie contains a string with the given prefix.
	 */
	bool has_prefix(const char *prefix) const;

	/* Mutator functions. */
	/*
	 * Insert the given string into the trie.
	 */
	void insert(const char *string);

private:
	/* Data members. */
	std::array<Trie *, ALPHABET> children_; // The children of the root of the trie.
};
