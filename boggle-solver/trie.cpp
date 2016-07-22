/*
 * Implementation of the Trie class.
 */
#include <cstring>

#include "trie.hpp"

/* Constructors. */
Trie::Trie() :
		children_() { }

/* Destructors. */
Trie::~Trie() {
	for (Trie *p : children_) {
		delete p;
	}
}

/* Accessor functions. */
bool Trie::empty() const {
	for (const Trie *p : children_) {
		if (p) {
			return false;
		}
	}
	return true;
}

bool Trie::has_string(const char *string) const {
	const Trie *trie = this;
	for (unsigned int i = 0; i < std::strlen(string); ++i) {
		std::size_t child_index = static_cast<std::size_t>(string[i] - 'A');
		if (not trie->children_[child_index]) {
			return false;
		}
		trie = trie->children_[child_index];
	}

	// Check null character.
	return children_[ALPHABET - 1] != nullptr;
}

bool Trie::has_prefix(const char *prefix) const {
	const Trie *trie = this;
	for (unsigned int i = 0; i < std::strlen(prefix); ++i) {
		std::size_t child_index = static_cast<std::size_t>(prefix[i] - 'A');
		if (not trie->children_[child_index]) {
			return false;
		}
		trie = trie->children_[child_index];
	}
	return true;
}

/* Mutator functions. */
void Trie::insert(const char *string) {
	// Note that the null character is added to the trie as the 27th child.
	Trie *trie = this;
	for (unsigned int i = 0; i < std::strlen(string); ++i) {
		std::size_t child_index = static_cast<std::size_t>(string[i] - 'A');
		if (not trie->children_[child_index]) {
			trie->children_[child_index] = new Trie();
		}
		trie = trie->children_[child_index];
	}

	trie->children_[ALPHABET + 1] = new Trie();
}
