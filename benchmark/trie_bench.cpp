/*
 * Micro benchmarks for the Trie class.
 */
#include "benchmark/benchmark.h"
#include "trie.hpp"

/*
 * Benchmark the creation of an empty Trie.
 */
static void trie_creation(benchmark::State& state) {
	while (state.KeepRunning()) {
		Trie trie;
	}
}

BENCHMARK(trie_creation);

/*
 * Benchmark the creation of an empty Trie and the insertion of the string "HELLO".
 */
static void trie_insertion(benchmark::State& state) {
	while (state.KeepRunning()) {
		Trie trie;
		trie.insert("HELLO");
	}
}

BENCHMARK(trie_insertion);

BENCHMARK_MAIN()
