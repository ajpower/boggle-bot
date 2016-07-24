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
	 * Copy the contents of the given string into the Boggle board. No check are made to verify if
	 * the string is of the appropriate size.
	 */
	Boggle(const std::string& s);

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
