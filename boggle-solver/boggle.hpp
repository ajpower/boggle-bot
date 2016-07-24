/*
 * Declaration and implementation of the Boggle class.
 */
#pragma once

#include <array>
#include <string>

/*
 * Represents an N by M Boggle board.
 */
template<std::size_t N, std::size_t M = N>
class Boggle {
public:
	/* Constructors. */
	Boggle() = delete;

	/*
	 * Copy the contents of the given string into the Boggle board. No checks are made to verify
	 * that the string is of the appropriate size.
	 */
	Boggle(const std::string& s);

	/* Accessor functions. */
	/*
	 * Return a copy of the elements in the ith row. No bounds checks are made.
	 */
	std::array<char, M> operator[](std::size_t i) const;

	/* Mutator functions. */
	char *operator[](std::size_t i);

private:
	/* Data members. */
	std::array<char, N * M> board_; // The N by M Boggle board. Must contain only uppercase ASCII
	// character. Note that the QU boggle piece is represented simply by Q.
};

/* Constructors. */
template<std::size_t N, std::size_t M>
Boggle<N, M>::Boggle(const std::string& s) {
	std::copy(s.begin(), s.end(), board_.begin());
}

/* Accessor functions. */
template<std::size_t N, std::size_t M>
std::array<char, M> Boggle<N, M>::operator[](std::size_t i) const {
	std::array<char, M> row;
	std::copy(board_.begin(), board_.end(), row.begin());
	return row;
}

/* Mutator functions. */
template<std::size_t N, std::size_t M>
char *Boggle<N, M>::operator[](std::size_t i) {
	return &board_[M * i];
}
