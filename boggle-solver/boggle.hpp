#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <string>

#include "trie.hpp"

/*
 * Represents an N by M Boggle board.
 */
template <std::size_t N = 4, std::size_t M = N>
class Boggle {
public:
	Boggle() = delete;

	/*
	 * Copy the contents of the given string into the Boggle board. The string must contain only
	 * uppercase ASCII letters. No checks are made to verify that the string is of the appropriate
	 * size.
	 */
	Boggle(const std::string& s);

	/*
	 * Return a constant pointer to the first element in the ith row. No bounds checks are made.
	 */
	const char *operator[](std::size_t i) const;

	/*
	 * Return a pointer to the first element in the ith row. No bounds checks are made.
	 */
	char *operator[](std::size_t i);

	/*
	 * Load the words from file, transform them to uppercase, and insert them into the trie. Words
	 * containing non-ASCII letters are ignored.
	 */
	static void load_dictionary(const std::string& file);

private:
	std::array<char, N * M> board_; // The N by M Boggle board. Must contain only uppercase ASCII
	// characters. Note that the QU boggle piece is represented simply by the character Q.

	static Trie trie; // Trie containing the words in a dictionary in uppercase letters.

	/*
	 * Return true if string contains only ASCII letters.
	 */
	static bool ascii_word(const std::string& s);
};

/* Redeclaration of static data members. */
template <std::size_t N, std::size_t M>
Trie Boggle<N, M>::trie;

template <std::size_t N, std::size_t M>
Boggle<N, M>::Boggle(const std::string& s) {
	std::copy(s.begin(), s.end(), board_.begin());
}

template <std::size_t N, std::size_t M>
const char *Boggle<N, M>::operator[](std::size_t i) const {
	return &board_[M * i];
}

template <std::size_t N, std::size_t M>
char *Boggle<N, M>::operator[](std::size_t i) {
	return &board_[M * i];
}

template <std::size_t N, std::size_t M>
void Boggle<N, M>::load_dictionary(const std::string& file) {
	std::vector<std::string> words;
	std::ifstream infile(file);
	std::string line;

	while (std::getline(infile, line)) {
		if (not ascii_word(line)) {
			continue;
		}
		std::transform(line.begin(), line.end(), line.begin(), ::toupper);
		words.push_back(line);
	}

	for (const auto& word : words) {
		trie.insert(word.c_str());
	}
}

template <std::size_t N, std::size_t M>
bool Boggle<N, M>::ascii_word(const std::string& s) {
	return std::all_of(s.begin(), s.end(), [](char c) {
		return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z');
	});
}
