/*
 * Declares the Boggle class.
 */
#pragma once

#include <array>
#include <vector>
#include <boost/python.hpp>

#include "trie.hpp"

constexpr std::size_t MAX_WORD_LENGTH = 18; // The longest word in 4x4 boggle is 17 letters.

namespace bpy = boost::python;

/*
 * Class for representing and solving a 4x4 boggle board, meant to be used within Python.
 */
// TODO len, str, docstrings, make setter and getters 2D?
// TODO use unsigned instead of std::size_t when possible
// TODO deal with exit time desctructor warning.
class Boggle {
public:
	/* Constructors. */
	/*
	 * Create a boggle board out of a Python container.
	 */
	Boggle(bpy::object board);

	/* Accessor functions. */
	/*
	 * Return the ith char in the board. Called by __getitem__.
	 */
	// TODO implement exceptions, slices, negative indices.
	char get(std::size_t i) const;

	/* Mutator functions. */
	/*
	 * Set the value of the ith char in the board. Called by _setitem__.
	 */
	// TODO implement exceptions, slices, negative indices.
	void set(std::size_t i, char c);

	// Static functions.
	/*
	 * Add contents of dictionary to collection of legal words (implemented internally as a trie).
	 * Words containing non-ASCII letters are ignored, and the words are reduced to lower case.
	 */
	static void add_dictionary(const std::string& dictionary_path);

private:
	/* Data members. */
	std::array<char, 16> board_; // Boggle board.

	/* Static data members. */
	static Trie trie; // Trie containing all legal words.

	/* Helper functions. */
	std::vector<char[MAX_WORD_LENGTH]> solve(unsigned i) const;

	/* Static helper functions. */
	/*
	 * Place the indices of the boggle board that the square with index i neighbours into the given
	 * array and return the number of neighbouring squares.
	 */
	static unsigned int neighbours(unsigned int i, std::array<unsigned int, 8>& neighbour_array);
};

BOOST_PYTHON_MODULE (boggle) {
	bpy::class_<Boggle>("Boggle", bpy::init<bpy::object>())
			.def("__getitem__", &Boggle::get)
			.def("__setitem__", &Boggle::set)
			.def("add_dictionary", &Boggle::add_dictionary)
			.staticmethod("add_dictionary");
}
