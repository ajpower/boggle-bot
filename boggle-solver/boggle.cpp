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

/* Accessor functions. */
char Boggle::get(std::size_t i) const {
	return board_[i];
}

/* Mutator functions. */
void Boggle::set(std::size_t i, char c) {
	board_[i] = c;
}
