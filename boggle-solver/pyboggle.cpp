#include "pyboggle.hpp"

PyBoggle::PyBoggle(const bpy::object& pyobject) {
	for (bpy::ssize_t i = 0; i < bpy::len(pyobject); ++i) {
		board_[static_cast<std::size_t>(i)] = bpy::extract<char>(pyobject[i]);
	}
}
