#pragma once

#include <array>
#include <memory>

/*
 * The trie is a data structure used as a dynamic set of strings. The trie can test for
 * membership of both strings and their prefixes.
 *
 * This implementation of the trie holds only strings containing uppercase ASCII letters. Attempts
 * to use strings containing anything else will lead to undefined behaviour.
 *
 * Deletion of strings is not presently supported as there is currently no reason to remove items
 * from the trie during a boggle game.
 */
//TODO bitwise trie?
//TODO make case insensitive
class Trie {
public:
	/*
	 * Create an empty trie.
	 */
	Trie();

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

	/*
	 * Insert the given string into the trie.
	 */
	void insert(const char *string);

private:
	std::array<std::unique_ptr<Trie>, 27> children_; // The children of the root of the trie, one
	// child for each uppercase character plus the null character.
};
