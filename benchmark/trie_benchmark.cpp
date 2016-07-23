/*
 * Micro benchmarks for the Trie class.
 */
#include "benchmark/benchmark.h"
#include "trie.hpp"

static void trie_creation(benchmark::State& state) {
	while (state.KeepRunning()) {
		Trie trie;
	}
}

BENCHMARK(trie_creation);

BENCHMARK_MAIN()
