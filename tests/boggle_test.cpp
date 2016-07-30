/*
 * Unit tests for the Boggle class.
 */
#include "gtest/gtest.h"
#include "boggle.hpp"

/*
 * Test the Boggle constructor.
 */
TEST(BoggleTest, Constructor) {
	Boggle<2> boggle_2x2("ABCD");
	Boggle<2, 4> boggle_2x4("ABCDEFGH");
	Boggle<> boggle_4x4("ABCDEFGHIJKLMNOP");

	EXPECT_EQ(sizeof(boggle_2x2), 4 * sizeof(char));
	EXPECT_EQ(sizeof(boggle_2x4), 8 * sizeof(char));
	EXPECT_EQ(sizeof(boggle_4x4), 16 * sizeof(char));
}

/*
 * Test the Boggle access operator.
 */
TEST(BoggleTest, AccessOperator) {
	Boggle<2, 4> boggle("ABCDEFGH");

	EXPECT_EQ('A', boggle[0][0]);
	EXPECT_EQ('B', boggle[0][1]);
	EXPECT_EQ('C', boggle[0][2]);
	EXPECT_EQ('D', boggle[0][3]);
	EXPECT_EQ('E', boggle[1][0]);
	EXPECT_EQ('F', boggle[1][1]);
	EXPECT_EQ('G', boggle[1][2]);
	EXPECT_EQ('H', boggle[1][3]);
}

/*
 * Test the Boggle mutator operator.
 */
TEST(BoggleTest, MutatorOperator) {
	Boggle<2, 4> boggle("ABCDEFGH");

	boggle[0][0] = 'Z';
	boggle[0][1] = 'Y';
	boggle[0][2] = 'X';
	boggle[0][3] = 'W';
	boggle[1][0] = 'V';
	boggle[1][1] = 'U';
	boggle[1][2] = 'T';
	boggle[1][3] = 'S';

	EXPECT_EQ('Z', boggle[0][0]);
	EXPECT_EQ('Y', boggle[0][1]);
	EXPECT_EQ('X', boggle[0][2]);
	EXPECT_EQ('W', boggle[0][3]);
	EXPECT_EQ('V', boggle[1][0]);
	EXPECT_EQ('U', boggle[1][1]);
	EXPECT_EQ('T', boggle[1][2]);
	EXPECT_EQ('S', boggle[1][3]);
}

/*
 * Test the loading of a dictionary.
 */
TEST(BoggleTest, LoadDictionary) {
	Boggle<>::load_dictionary("/usr/share/dict/words");
}
