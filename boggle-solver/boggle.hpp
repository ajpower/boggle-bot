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
class Boggle {
public:
	/* Constructors. */
	/*
	 * Creates a boggle board out of a Python container.
	 */
	Boggle(bpy::object board);

	/* Accessor functions. */
	/*
	 * Returns a Python list consisting of the characters in the ith row. Called by __getitem__.
	 */
	bpy::list get(std::size_t i) const;

private:
	/* Data members. */
	std::array<char, 16> board_; // Boggle board.
};

BOOST_PYTHON_MODULE (boggle) {
	bpy::class_<Boggle>("Boggle", bpy::init<bpy::object>())
			.def("__getitem__", &Boggle::get);
}
