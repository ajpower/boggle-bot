/*
 * Declares the Boggle class.
 */
#pragma once

#include <array>
#include <boost/python.hpp>

namespace bpy = boost::python;

/*
 * Class for representing and solving a 4x4 boggle board, meant to be used within Python.
 */
// TODO len, str, docstrings.
class Boggle {
public:
	/* Constructors. */
	/*
	 * Creates a boggle board out of a Python container.
	 */
	Boggle(bpy::object board);

	/* Accessor functions. */
	/*
	 * Returns the ith char in the board. Called by __getitem__.
	 */
	// TODO implement exceptions, slices, negative indices.
	char get(std::size_t i) const;

	/* Mutator functions. */
	/*
	 * Sets the value of the ith char in the board. Called by _setitem__.
	 */
	// TODO implement exceptions, slices, negative indices.
	void set(std::size_t i, char c);

private:
	/* Data members. */
	std::array<char, 16> board_; // Boggle board.
};

BOOST_PYTHON_MODULE (boggle) {
	bpy::class_<Boggle>("Boggle", bpy::init<bpy::object>())
			.def("__getitem__", &Boggle::get)
			.def("__setitem__", &Boggle::set);
}
