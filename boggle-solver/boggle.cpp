/*
 * Implements the Boggle class.
 */
#include "boggle.hpp"

/* Constructors. */
Boggle::Boggle(bpy::object board) {
	for (std::size_t i = 0; i < 16; ++i) {
		board_[i] = bpy::extract<char>(board[i]);
	}
}

/* Subscript operators. */
bpy::list Boggle::get(std::size_t i) const {
	bpy::list row;
	for (std::size_t j = 0; j < 4; ++j) {
		row.append(board_[4 * i + j]);
	}
	return row;
}
