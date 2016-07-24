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
	Boggle<4> boggle_4x4("ABCDEFGHIJKLMNOP");

	EXPECT_EQ(4 * sizeof(char), sizeof(boggle_2x2));
	EXPECT_EQ(8 * sizeof(char), sizeof(boggle_2x4));
	EXPECT_EQ(16 * sizeof(char), sizeof(boggle_4x4));
}
