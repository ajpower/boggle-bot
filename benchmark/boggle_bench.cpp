#include <chrono>
#include <random>
#include <string>

#include "benchmark/benchmark.h"
#include "boggle.hpp"

namespace {
constexpr char UPPERCASE_LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*
 * Return a string of random characters of the given length.
 */
std::string random_string(std::size_t length) {
	std::string random_str;
	random_str.reserve(length);

	auto time = std::chrono::system_clock::now().time_since_epoch().count();
	std::minstd_rand eng(time);
	std::uniform_int_distribution<std::size_t> dist(0, 25);

	for (std::size_t i = 0; i < length; ++i) {
		char random_char = UPPERCASE_LETTERS[dist(eng)];
		random_str.push_back(random_char);
	}

	return random_str;
}
}

/*
 * Benchmark the solving of a random N by M Boggle board.
 */
template <std::size_t N, std::size_t M>
static void boggle_solve(benchmark::State& state) {
	Boggle<N, M>::load_dictionary("/usr/share/dict/words");
	while (state.KeepRunning()) {
		std::string random_str = random_string(N * M);
		Boggle<N, M> boggle(random_str);
		benchmark::DoNotOptimize(boggle.solve());
	}
}

BENCHMARK_TEMPLATE(boggle_solve, 2, 2)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(boggle_solve, 4, 4)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(boggle_solve, 8, 8)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(boggle_solve, 16, 16)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(boggle_solve, 32, 32)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(boggle_solve, 64, 64)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(boggle_solve, 128, 128)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
