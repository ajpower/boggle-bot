#pragma once

#include <array>
#include <memory>

/*
 * The trie is a data structure serving as a dynamic set of strings. The trie can test for
 * membership of both strings and their prefixes.
 *
 * This implementation of the trie only holds strings containing uppercase ASCII letters. Attempts
 * to use strings containing anything else will lead to undefined behaviour.
 *
 * Finally, note that Tries are not permitted to be copied, but can be moved.
 */
//TODO bitwise trie?
//TODO make case insensitive?
class Trie {
public:
	/*
	 * Create an empty trie.
	 */
	Trie();

	// Delete copy constructor and copy assignment.
	Trie(const Trie&) = delete;

	Trie& operator=(const Trie&) = delete;

	/*
	 * Move constructor.
	 */
	Trie(Trie&& other);

	/*
	 * Move assignment operator.
	 */
	Trie& operator=(Trie&& other);

	/*
	 * Return true if the trie is empty.
	 */
	bool empty() const;

	/*
	 * Return true if the trie contains the given string.
	 */
	bool has_string(const char *s) const;

	/*
	 * Return true if the trie contains a string with the given prefix.
	 */
	bool has_prefix(const char *prefix) const;

	/*
	 * Insert the given string into the trie.
	 */
	void insert(const char *s);

private:
	std::array<std::unique_ptr<Trie>, 27> children_; // The children of the root of the trie, one
	// child for each uppercase character plus the null character.
};
