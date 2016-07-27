/*
 * Declaration and implementation of the Boggle class.
 */
#pragma once

#include <array>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

#include "trie.hpp"

/*
 * Represents an N by M Boggle board.
 */
template<std::size_t N = 4, std::size_t M = N>
class Boggle {
public:
	Boggle() = delete;

	/*
	 * Copy the contents of the given string into the Boggle board. No checks are made to verify
	 * that the string is of the appropriate size.
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
	 * Return all the words in the Boggle board that start at the ith index. Note that a dictionary
	 * MUST have been loaded before this function is called, or else no words will be returned.
	 */
	//TODO make private
	std::vector<std::string> solve(std::size_t i) const;

	/*
	 * Load the words from file, transform them to uppercase, and insert them into the trie. Words
	 * containing non-ASCII letters are ignored.
	 */
	static void load_dictionary(const std::string& file);

private:
	std::array<char, N * M> board_; // The N by M Boggle board. Must contain only uppercase ASCII
	// characters. Note that the QU boggle piece is represented simply by Q.

	static Trie trie; // Trie containing the words in a dictionary in uppercase letters.

	/*
	 * Finds the indices of all squares adjacent to given square.
	 */
	static std::vector<std::size_t> neighbours(std::size_t square_index);

	/*
	 * Return true if string contains only ASCII letters.
	 */
	static bool ascii_word(const std::string& s);

	/*
	 * Place the characters formed by traversing the given path in the Boggle board into the string.
	 */
	static void path_to_string(const std::vector<std::size_t>& path, char *s);
};

/* Redeclaration of static data members. */
template<std::size_t N, std::size_t M>
Trie Boggle<N, M>::trie;

template<std::size_t N, std::size_t M>
Boggle<N, M>::Boggle(const std::string& s) {
	std::copy(s.begin(), s.end(), board_.begin());
}

template<std::size_t N, std::size_t M>
const char *Boggle<N, M>::operator[](std::size_t i) const {
	return &board_[M * i];
}

template<std::size_t N, std::size_t M>
char *Boggle<N, M>::operator[](std::size_t i) {
	return &board_[M * i];
}

template<std::size_t N, std::size_t M>
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

template<std::size_t N, std::size_t M>
std::vector<std::string> Boggle<N, M>::solve(std::size_t starting_index) const {
	//TODO add algorithm description.
	using path_t = std::vector<std::size_t>;

	std::vector<std::string> words;
	std::stack<path_t> paths; // Contains the paths to be checked and extended.
	paths.push({ starting_index });

	while (not paths.empty()) {
		path_t path = paths.top();
		paths.pop();

		char current_string[2 * N * M + 1]; // Large enough to fit any possible Boggle word.
		path_to_string(path, current_string);

		// TODO avoid duplicating search
		if (not trie.has_prefix(current_string)) {
			continue;
		}
		if (trie.has_string(current_string)) {
			words.emplace_back(current_string);
		}

		std::size_t last_square = path.back();
		for (std::size_t neighbour : neighbours(last_square)) {
			if (std::find(path.begin(), path.end(), neighbour) == path.end()) {
				path_t new_path = path;
				new_path.push_back(neighbour);
				paths.push(new_path);
			}
		}
	}

	return words;
}

//TODO statically create table
template<std::size_t N, std::size_t M>
std::vector<std::size_t> Boggle<N, M>::neighbours(std::size_t square_index) {

}

template<std::size_t N, std::size_t M>
bool Boggle<N, M>::ascii_word(const std::string& s) {
	for (char c : s) {
		if (c < 'A' or (c > 'Z' and c < 'a') or c > 'z') {
			return false;
		}
	}
	return true;
}

template<std::size_t N, std::size_t M>
void Boggle<N, M>::path_to_string(const std::vector<std::size_t>& path, char *s) {
	std::size_t i = 0;
	for (std::size_t board_index : path) {
		char c = path[board_index];
		s[i++] = c;
		if (c == 'Q') {
			s[i++] = 'U';
		}
	}
	s[i] = '\0';
}
