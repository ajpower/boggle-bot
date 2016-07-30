#include <algorithm>
#include <cstring>

#include "trie.hpp"

Trie::Trie() :
		children_() { }

Trie::Trie(Trie&& other) :
		children_(std::move(other.children_)) { }

Trie& Trie::operator=(Trie&& other) {
	children_ = std::move(other.children_);
	return *this;
}

bool Trie::empty() const {
	return std::all_of(children_.begin(), children_.end(), [](const auto& p) {
		return p == nullptr;
	});
}

bool Trie::has_string(const char *s) const {
	const Trie *p_trie = this;
	for (unsigned int i = 0; i < std::strlen(s); ++i) {
		std::size_t child_index = static_cast<std::size_t>(s[i] - 'A');
		if (not p_trie->children_[child_index]) {
			return false;
		}
		p_trie = p_trie->children_[child_index].get();
	}

	// Check null character.
	return p_trie->children_.back() != nullptr;
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

void Trie::insert(const char *s) {
	Trie *p_trie = this;
	for (unsigned int i = 0; i < std::strlen(s); ++i) {
		std::size_t child_index = static_cast<std::size_t>(s[i] - 'A');
		if (not p_trie->children_[child_index]) {
			p_trie->children_[child_index] = std::make_unique<Trie>();
		}
		p_trie = p_trie->children_[child_index].get();
	}

	// Add null character.
	p_trie->children_.back() = std::make_unique<Trie>();
}
