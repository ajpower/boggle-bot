#pragma once

#include <string>
#include <vector>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "boggle.hpp"

namespace bpy = boost::python;

/*
 * Wraps Boggle<4, 4> in a Pythonic interface.
 */
class PyBoggle {
public:
	/*
	 * Create a Boggle object from a Python container of characters.
	 */
	PyBoggle(const bpy::object& pyobject);

	/*
	 * Return a Python list of characters in the Boggle board.
	 */
	bpy::list board() const;

	/*
	 * Return the words in the Boggle board.
	 */
	std::vector<std::string> solve() const;

	/*
	 * Load a dictionary. Must be called before 'solve'.
	 */
	static void load_dictionary(const std::string& dictionary_path);

private:
	Boggle<4, 4> boggle_;
};

BOOST_PYTHON_MODULE (boggle) {
	using WordList = std::vector<std::string>;

	/*
	 * Wrap std::vector<std::string> into a Python object.
	 */
	bpy::class_<WordList>("WordList")
			.def(bpy::vector_indexing_suite<WordList>());

	bpy::class_<PyBoggle>("Boggle", bpy::init<const bpy::object&>())
			.def("board", &PyBoggle::board)
			.def("load_dictionary", &PyBoggle::load_dictionary).staticmethod("load_dictionary")
			.def("solve", &PyBoggle::solve);
}
