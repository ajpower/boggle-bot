#include "pyboggle.hpp"

PyBoggle::PyBoggle(const bpy::object& pyobject) {
	for (std::size_t row = 0; row < 4; ++row) {
		for (std::size_t col = 0; col < 4; ++col) {
			boggle_[row][col] = bpy::extract<char>(pyobject[4 * row + col]);
		}
	}
}

bpy::list PyBoggle::board() const {
	bpy::list character_list;
	for (std::size_t row = 0; row < 4; ++row) {
		for (std::size_t col = 0; col < 4; ++col) {
			character_list.append(boggle_[row][col]);
		}
	}

	return character_list;
}

std::vector<std::string> PyBoggle::solve() const {
	std::vector<std::string> words = boggle_.solve();
	return words;
}

void PyBoggle::load_dictionary(const std::string& dictionary_path) {
	Boggle<4, 4>::load_dictionary(dictionary_path);
}
