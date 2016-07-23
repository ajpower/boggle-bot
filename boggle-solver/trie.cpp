/*
 * Implementation of the Trie class.
 */
#include <cstring>

#include "trie.hpp"

/* Constructors. */
Trie::Trie() :
		children_() { }

/* Accessor functions. */
bool Trie::empty() const {
	for (const auto& p_trie : children_) {
		if (p_trie) {
			return false;
		}
	}
	return true;
}

bool Trie::has_string(const char *string) const {
	const Trie *p_trie = this;
	for (unsigned int i = 0; i < std::strlen(string); ++i) {
		std::size_t child_index = static_cast<std::size_t>(string[i] - 'A');
		if (not p_trie->children_[child_index]) {
			return false;
		}
		p_trie = p_trie->children_[child_index].get();
	}

	// Check null character.
	return p_trie->children_[children_.size() - 1] != nullptr;
}

bool Trie::has_prefix(const char *prefix) const {
	const Trie *p_trie = this;
	for (unsigned int i = 0; i < std::strlen(prefix); ++i) {
		std::size_t child_index = static_cast<std::size_t>(prefix[i] - 'A');
		if (not p_trie->children_[child_index]) {
			return false;
		}
		p_trie = p_trie->children_[child_index].get();
	}
	return true;
}

/* Mutator functions. */
void Trie::insert(const char *string) {
	Trie *p_trie = this;
	for (unsigned int i = 0; i < std::strlen(string); ++i) {
		std::size_t child_index = static_cast<std::size_t>(string[i] - 'A');
		if (not p_trie->children_[child_index]) {
			p_trie->children_[child_index] = std::make_unique<Trie>();
		}
		p_trie = p_trie->children_[child_index].get();
	}

	// Add null character.
	p_trie->children_[children_.size() - 1] = std::make_unique<Trie>();
}
