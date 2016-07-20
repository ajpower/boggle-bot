/*
 * Implements the Boggle class.
 */
#include <algorithm>
#include <fstream>
#include <regex>
#include <stack>

#include "boggle.hpp"

namespace {
// Each element of the array holds an array of the indices of the boggle board it borders.
//@formatter:off
constexpr std::array<std::array<unsigned int, 8>, 16> NEIGHBOURS = { {
		{ 1, 4, 5 },
		{ 0, 2, 4, 5, 6 },
		{ 1, 3, 5, 6, 7 },
		{ 2, 6, 7 },
		{ 0, 1, 5, 8, 9 },
		{ 0, 1, 2, 4, 6, 8, 9, 10 },
		{ 1, 2, 3, 5, 7, 9, 10, 11 },
		{ 2, 3, 6, 10, 11 },
		{ 4, 5, 9, 12, 13 },
		{ 4, 5, 6, 8, 10, 12, 13, 14 },
		{ 5, 6, 7, 9, 11, 13, 14, 15 },
		{ 6, 7, 10, 14, 15 },
		{ 8, 9, 13 },
		{ 8, 9, 10, 12, 14 },
		{ 9, 10, 11, 13, 15 },
		{ 10, 11, 14 }
} };
//@formatter:on

// Each element of the array holds the number of squares it borders.
constexpr std::array<unsigned int, 16> N_NEIGHBOURS = {
		3, 5, 5, 3,
		5, 8, 8, 5,
		5, 8, 8, 5,
		3, 5, 5, 3
};
}

/* Declare static data members. */
Trie<bool> Boggle::trie;

/* Constructors. */
Boggle::Boggle(bpy::object board) {
	for (std::size_t i = 0; i < 16; ++i) {
		board_[i] = bpy::extract<char>(board[i]);
	}
}

/* Accessor functions. */
char Boggle::get(std::size_t i) const {
	return board_[i];
}

/* Mutator functions. */
void Boggle::set(std::size_t i, char c) {
	board_[i] = c;
}

/* Static functions. */
void Boggle::add_dictionary(const std::string& dictionary_path) {
	std::ifstream file(dictionary_path);
	std::string line;
	while (std::getline(file, line)) {
		if (std::regex_match(line, std::regex("\\w+"))) {
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			trie.add_string(line.c_str(), true);
		}
	}
}

/* Helper functions. */
std::vector<char[MAX_WORD_LENGTH]> Boggle::solve(unsigned int i) const {
	std::vector<char[MAX_WORD_LENGTH]> solutions;
	std::stack<unsigned int> vertices; // Vertices in current search path.
	std::array<bool, 16> visited{ }; // Whether vertex has been visited in current search
	// path.

	vertices.push(i);

	while (not vertices.empty()) {
		unsigned int vertex = vertices.top();
		vertices.pop();

		if (not visited[vertex]) {
			visited[vertex] = true;

			std::array<unsigned int, 8> edges;
			unsigned int n_edges = neighbours(vertex, edges);
			for (unsigned int j = 0; j < n_edges; ++j) {
				unsigned int edge = edges[j];
				if (not visited[edge]) {
					vertices.push(edge);
				}
			}
		}
	}

	return solutions;
}

/* Static helper functions. */
unsigned int Boggle::neighbours(unsigned int i, std::array<unsigned int, 8>& neighbour_array) {
	for (unsigned int j = 0; j < N_NEIGHBOURS[i]; ++j) {
		neighbour_array[j] = NEIGHBOURS[i][j];
	}

	return N_NEIGHBOURS[i];
}
