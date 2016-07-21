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
	for (unsigned int i = 0; i < children_.size(); ++i) {
		if (children_[i]) {
			return false;
		}
	}
	return true;
}

bool Trie::has_string(const char *string) const {
	const Trie *trie = this;
	for (unsigned int i = 0; i < std::strlen(string); ++i) {
		char c = string[i];
		if (not trie->children_[static_cast<std::size_t>(c - 'A')]) {
			return false;
		}
		trie = trie->children_[static_cast<std::size_t>(c - 'A')];
	}

	// Check null character.
	return children_[ALPHABET + 1] != nullptr;
}

bool Trie::has_prefix(const char *prefix) const {
	const Trie *trie = this;
	for (unsigned int i = 0; i < std::strlen(prefix); ++i) {
		char c = prefix[i];
		if (not trie->children_[static_cast<std::size_t>(c - 'A')]) {
			return false;
		}
		trie = trie->children_[static_cast<std::size_t>(c - 'A')];
	}
	return true;
}

/* Mutator functions. */
void Trie::insert(const char *string) {
	// Note that the null character is added to the trie as the 27th child.
	Trie *trie = this;
	for (unsigned int i = 0; i < std::strlen(string); ++i) {
		char c = string[i];
		if (not trie->children_[static_cast<std::size_t>(c - 'A')]) {
			trie->children_[static_cast<std::size_t>(c - 'A')] = new Trie();
		}
		trie = trie->children_[static_cast<std::size_t>(c - 'A')];
	}

	trie->children_[ALPHABET + 1] = new Trie();
}
