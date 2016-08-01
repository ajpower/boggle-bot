#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <boost/container/static_vector.hpp>

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

	std::vector<std::string> solve() const;

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
	 * Lookup table to find the neighbours of a square on the Boggle board.
	 */
	class NeighbourTable {
		friend Boggle;
	public:
		NeighbourTable() {
			// Find the range of rows and columns constituting the neighbours of each Boggle square.
			for (std::size_t i = 0; i < neighbours_.size(); ++i) {
				std::size_t min_row, max_row, min_col, max_col;
				min_row = i / M == 0 ? 0 : i / M - 1;
				max_row = i / M == N - 1 ? N - 1 : i / M + 1;
				min_col = i % M == 0 ? 0 : i % M - 1;
				max_col = i % M == M - 1 ? M - 1 : i % M + 1;

				for (std::size_t row = min_row; row <= max_row; ++row) {
					for (std::size_t col = min_col; col <= max_col; ++col) {
						if (row * M + col != i) {
							neighbours_[i].push_back(row * M + col);
						}
					}
				}
			}
		}

		boost::container::static_vector<std::size_t, 8> operator[](std::size_t i) const {
			return neighbours_[i];
		}

		boost::container::static_vector<std::size_t, 8>& operator[](std::size_t i) {
			return neighbours_[i];
		}

	private:
		std::array<boost::container::static_vector<std::size_t, 8>, N * M> neighbours_;
	};

	static const NeighbourTable neighbour_table;

	/*
	 * Find all words that start from the ith element of the Boggle board and place them in the
	 * given vector. No bounds checks are made.
	 */
	void solve(std::size_t i, std::vector<std::string>& words) const;

	/*
	 * Return the word formed by following the given path through the Boggle board.
	 */
	std::string path2word(const std::vector<std::size_t>& path) const;

	/*
	 * Return true if string contains only ASCII letters.
	 */
	static bool ascii_word(const std::string& s);
};

/* Redeclaration of static data members. */
template <std::size_t N, std::size_t M>
Trie Boggle<N, M>::trie;

template <std::size_t N, std::size_t M>
const typename Boggle<N, M>::NeighbourTable Boggle<N, M>::neighbour_table;

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
std::vector<std::string> Boggle<N, M>::solve() const {
	// TODO make multithreaded
	std::vector<std::string> words;
	for (std::size_t i = 0; i < board_.size(); ++i) {
		solve(i, words);
	}

	return words;
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
void Boggle<N, M>::solve(std::size_t i, std::vector<std::string>& words) const {
	//TODO explain algorithm
	//TODO use Boost static/small vector
	using path_t = std::vector<std::size_t>;

	std::stack<path_t> paths;
	paths.emplace(1, i);

	while (not paths.empty()) {
		path_t path = paths.top();
		paths.pop();

		std::string word = path2word(path);
		if (not trie.has_prefix(word.c_str())) {
			continue;
		}
		if (word.size() >= 3 and trie.has_string(word.c_str())) {
			// Make sure word is unique.
			if (std::find(words.begin(), words.end(), word) == words.end()) {
				words.push_back(std::move(word));
			}
		}

		std::size_t last_square = path.back();
		auto neighbours = neighbour_table[last_square];
		for (std::size_t neighbour : neighbours) {
			if (std::find(path.begin(), path.end(), neighbour) == path.end()) {
				path_t new_path = path;
				new_path.push_back(neighbour);
				paths.push(std::move(new_path));
			}
		}
	}
}

template <std::size_t N, std::size_t M>
bool Boggle<N, M>::ascii_word(const std::string& s) {
	return std::all_of(s.begin(), s.end(), [](char c) {
		return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z');
	});
}

template <std::size_t N, std::size_t M>
std::string Boggle<N, M>::path2word(const std::vector<std::size_t>& path) const {
	std::string word;
	for (auto i : path) {
		char c = board_[i];
		word.push_back(c);
		if (c == 'Q') {
			word.push_back('U');
		}
	}
	return word;
}
