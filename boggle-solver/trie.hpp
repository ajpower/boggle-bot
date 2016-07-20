/*
 * Declares and implements the Trie class.
 */
#pragma once

#include <array>
#include <cassert>
#include <cstring>
#include <utility>

namespace {
constexpr std::size_t ALPHABET = 26;
}

/*
 * Represents a trie, an ordered tree data structure representing an associative array where the
 * the keys are strings. Note that all strings are assumed to consist of lower case ASCII
 * characters only.
 */
//TODO bitwise trie?
template<typename V>
class Trie {
public:
	/* Constructors. */
	/*
	 * Create a trie whose root has no children and whose value is the default value of V.
	 */
	Trie();

	/*
	 * Create a trie whose root has the given value and has no children.
	 */
	Trie(V value);

	/*
	 * Create a trie whose root has the given value and children.
	 */
	Trie(V value, const std::array<Trie<V> *, ALPHABET> children);

	/* Destructor. */
	~Trie();

	/* Accessor functions. */
	/*
	 * Return the value at the root of the trie.
	 */
	V value() const;

	/*
	 * Return the value of the given string. Note that this results in undefined behaviour if the
	 * trie does not contain the string.
	 */
	V value(const char *str) const;

	/*
	 * Return true if trie contains the given string.
	 */
	bool has(const char *str) const;

	/*
	 * Return a pair of values, the first of which is a boolean stating whether or not the given
	 * string is inside the trie, and the second the value of the given string if indeed it is
	 * located inside the trie. If the trie does not contain the string, then the second value will
	 * be meaningless.
	 */
	std::pair<bool, V> has_value(const char *str) const;

	/*
	 * Return a pointer to the child of the trie's root with character c. Note that this will return
	 * a nullptr if there is no such child.
	 */
	Trie<V> *child(char c) const;

	/* Mutator functions. */
	/*
	 * Set the value of the trie's root.
	 */
	void set_value(V value);

	/*
	 * Add a child to the trie's root with given character and value. Note that this child will not
	 * have any children.
	 */
	void add_child(char c, V value);

	/*
	 * Add a string to the trie's root with the given value.
	 */
	void add_string(const char *str, V value);

private:
	/* Data members. */
	V value_; // Value stored at root of trie.
	std::array<Trie<V> *, ALPHABET> children_; // Children of the root of trie. The length of the
	// array is 26, so that the ith element corresponds to the ith letter of the alphabet.
};

/* Constructors. */
template<typename V>
Trie<V>::Trie() :
		value_(),
		children_() { }

template<typename V>
Trie<V>::Trie(V value) :
		value_(value),
		children_() { }

template<typename V>
Trie<V>::Trie(V value, const std::array<Trie<V> *, ALPHABET> children) :
		value_(value),
		children_(children) { }

/* Destructor. */
template<typename V>
Trie<V>::~Trie() {
	for (unsigned int i = 0; i < ALPHABET; ++i) {
		delete children_[i];
	}
}

/* Accessor functions. */
template<typename V>
V Trie<V>::value() const {
	return value_;
}

template<typename V>
V Trie<V>::value(const char *str) const {
	const Trie<V> *node = this;
	for (std::size_t i = 0; i < std::strlen(str); ++i) {
		node = node->child(str[i]);
	}

	return node->value();
}

template<typename V>
bool Trie<V>::has(const char *str) const {
	const Trie<V> *node = this;
	for (std::size_t i = 0; i < std::strlen(str); ++i) {
		if (not node->child(str[i])) {
			return false;
		}
		node = node->child(str[i]);
	}

	return true;
}

template<typename V>
std::pair<bool, V> Trie<V>::has_value(const char *str) const {
	const Trie<V> *node = this;
	for (std::size_t i = 0; i < std::strlen(str); ++i) {
		if (not node->child(str[i])) {
			return std::pair<bool, V>(false, V());
		}
		node = node->child(str[i]);
	}

	return std::pair<bool, V>(true, node->value());
}

template<typename V>
Trie<V> *Trie<V>::child(char c) const {
	assert('a' <= c and c <= 'z');
	return children_[static_cast<std::size_t>(c - 'a')];
}

/* Mutator functions. */
template<typename V>
void Trie<V>::set_value(V value) {
	value_ = value;
}

template<typename V>
void Trie<V>::add_child(char c, V value) {
	assert('a' <= c and c <= 'z');
	children_[static_cast<std::size_t>(c - 'a')] = new Trie(value);
}

template<typename V>
void Trie<V>::add_string(const char *str, V value) {
	Trie<V> *node = this;
	for (std::size_t i = 0; i < std::strlen(str); ++i) {
		if (not node->child(str[i])) {
			node->add_child(str[i], false);
		}
		node = node->child(str[i]);
	}
	node->set_value(value);
}
