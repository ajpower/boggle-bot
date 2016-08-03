#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <mutex>
#include <stack>
#include <string>
#include <thread>
#include <vector>
#include <boost/container/static_vector.hpp>

#include "trie.hpp"

/*
 * Represents an N by M Boggle board.
 */
template <std::size_t N = 4, std::size_t M = N>
class Boggle {
public:
	/*
	 * Initializes Boggle board with null characters.
	 */
	Boggle();

	/*
	 * Copy the contents of the given string into the Boggle board. The string must contain only
	 * uppercase ASCII letters. No checks are made to verify that the string is of the appropriate
	 * size. The character 'Q' is interpreted as the square 'QU'.
	 */
	Boggle(const char *s);

	/*
	 * Copy the contents of the given container into the Boggle board. The container must contain
	 * only uppercase ASCII letters. No checks are made to verify that the container is of the
	 * appropriate size. The character 'Q' is interpreted as the square 'QU'.
	 */
	template <typename T>
	Boggle(const T& c);

	/*
	 * Return a constant pointer to the first element in the ith row. No bounds checks are made.
	 */
	const char *operator[](std::size_t i) const;

	/*
	 * Return a pointer to the first element in the ith row. No bounds checks are made.
	 */
	char *operator[](std::size_t i);

	/*
	 * Return the words in the Boggle board.
	 */
	std::vector<std::string> solve() const;

	/*
	 * Load the words from file, transform them to uppercase, and insert them into the trie. Words
	 * containing non-ASCII letters are ignored.
	 */
	static void load_dictionary(const std::string& file);

protected:
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
						// Make sure not to add the square itself.
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
		std::array<boost::container::static_vector<std::size_t, 8>, N * M> neighbours_; // The ith
		// element contains the neighbours of the ith Boggle square.
	};

	static const NeighbourTable neighbour_table;

	/*
	 * Find all words that start from the ith element of the Boggle board and place them in the
	 * given vector. No bounds checks are made and duplicates are not removed.
	 */
	void solve(std::size_t i, std::vector<std::string>& words) const;

	/*
	 * Find all the words that start from squares in the range [start, end) and place them in the
	 * given vector. No bounds checks are made and duplicates are not removed.
	 */
	void solve(std::size_t start, std::size_t end, std::vector<std::string>& words) const;

	/*
	 * Return the word formed by following the given path through the Boggle board.
	 */
	template <typename T>
	std::string path2word(const T& path) const;

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
Boggle<N, M>::Boggle() :
		board_() { };

template <std::size_t N, std::size_t M>
Boggle<N, M>::Boggle(const char *s) {
	std::copy(s, s + std::strlen(s), board_.begin());
}

template <std::size_t N, std::size_t M>
template <typename T>
Boggle<N, M>::Boggle(const T& c) {
	std::copy(c.begin(), c.end(), board_.begin());
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
	std::vector<std::string> words;
	words.reserve(512); // There is typically at most 500 words in a 4 by 4 Boggle board.

	auto n_threads = std::thread::hardware_concurrency();
	auto squares_per_thread = board_.size() / n_threads;
	std::vector<std::thread> threads(n_threads - 1);
	std::mutex words_mutex;

	// Find the words in the Boggle squares with indices in the range [start, end) and place them
	// in words, removing duplicates in the process. This function will be executed by a thread, so
	// mutex is used to protect 'words'.
	std::function<void(std::size_t, std::size_t)> thread_fn = [=, &words, &words_mutex](
			std::size_t start, std::size_t end) {
		std::vector<std::string> partial_words;
		partial_words.reserve(words.capacity());
		solve(start, end, partial_words);

		std::lock_guard<std::mutex> guard(words_mutex);
		for (auto& word : partial_words) {
			if (std::find(words.begin(), words.end(), word) == words.end()) {
				words.push_back(std::move(word));
			}
		}
	};

	// Create n - 1 threads, where n is the number of hardware threads supported. Divide the Boggle
	// board into n groups of squares and assign each group to a thread. A thread finds all the
	// words starting from the squares in its group and places them into 'words'.
	for (unsigned int i = 0; i < n_threads - 1; ++i) {
		std::size_t start_square = squares_per_thread * i;
		std::size_t end_square = squares_per_thread * (i + 1);
		threads[i] = std::thread(thread_fn, start_square, end_square);
	}

	// Main thread takes care of last remaining squares.
	thread_fn(squares_per_thread * (n_threads - 1), board_.size());

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

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
	// A modified DFS algorithm is used to find all words in the Boggle board.
	// A typical non-recursive DFS uses a stack to hold the nodes of a graph that need to be
	// visited, and a separate data structure keeps track of which nodes have been visited.
	// In this implementation, a stack is used to hold the *paths* through the Boggle board that
	// need to be analyzed and extended. Analysis means 1) checking whether the path makes a valid
	// word; and 2) whether the path forms the prefix of a valid word (if not, path is discarded).
	// Paths are extended by joining the neighbours of the last square of the path that are not
	// already in the path.

	using path_t = boost::container::static_vector<std::size_t, N * M>;

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
			words.push_back(std::move(word));
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
void
Boggle<N, M>::solve(std::size_t start, std::size_t end, std::vector<std::string>& words) const {
	for (auto i = start; i < end; ++i) {
		solve(i, words);
	}
};

template <std::size_t N, std::size_t M>
bool Boggle<N, M>::ascii_word(const std::string& s) {
	return std::all_of(s.begin(), s.end(), [](char c) {
		return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z');
	});
}

template <std::size_t N, std::size_t M>
template <typename T>
std::string Boggle<N, M>::path2word(const T& path) const {
	std::string word;
	word.reserve(path.size() + 2);
	for (auto i : path) {
		char c = board_[i];
		word.push_back(c);
		if (c == 'Q') {
			word.push_back('U');
		}
	}
	return word;
}
