/*
 * Unit tests for the Boggle class.
 */
#include <fstream>
#include <sstream>

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
	Boggle<>::load_dictionary(DICT_PATH);
}

/*
 * Test the solving of 100 4x4 Boggle boards. Test data extracted from wordplays.com, which uses the
 * TWL dictionary, and stored in a CSV file.
 */
#if 1
TEST(BoggleTest, Solve4x4) {
	Boggle<4>::load_dictionary(DICT_PATH);

	std::ifstream file(TEST_DATA_DIR"/boggle_4x4.csv");
	std::string line;
	while (std::getline(file, line)) {
		std::string boggle_board;
		std::string n_solutions_str;

		std::stringstream ss(line);
		char c;
		while (ss.peek() != ',') {
			ss >> c;
			if (c != 'u') {
				boggle_board.push_back(c);
			}
		}
		ss.ignore();
		while (ss >> c) {
			n_solutions_str.push_back(c);
		}

		Boggle<4> boggle(boggle_board);
		auto solution = boggle.solve();
		int n_solutions = std::stoi(n_solutions_str);
		EXPECT_EQ(solution.size(), n_solutions) << "Boggle board: " << boggle_board;
	}
}

#endif

#if 0
TEST(BoggleTest, Foo) {
	Boggle<>::load_dictionary(DICT_PATH);
	Boggle<> boggle("PSLAMSEMAYEKAEUR");
	auto words = boggle.solve();
	std::cout << std::endl;
	for (auto word : words) {
		std::cout << word << std::endl;
	}
}

#endif
