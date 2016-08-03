#pragma once

#include <boost/python.hpp>

#include "boggle.hpp"

namespace bpy = boost::python;

/*
 * Wraps Boggle<4, 4> in a Pythonic interface.
 */
class PyBoggle : public Boggle<4, 4> {
public:
	/*
	 * Create a Boggle object from a Python container of characters.
	 */
	PyBoggle(const bpy::object& pyobject);
};

BOOST_PYTHON_MODULE (boggle) {
	bpy::class_<PyBoggle>("Boggle", bpy::init<const bpy::object&>());
}
