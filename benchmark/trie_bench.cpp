#include <algorithm>
#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "benchmark/benchmark.h"
#include "trie.hpp"

namespace {
/*
 * Return true if string only contains ASCII letters.
 */
bool ascii_word(const std::string& s) {
	return std::all_of(s.begin(), s.end(), [](char c) {
		return (c >= 'A' and c <= 'Z') or (c >= 'a' and c <= 'z');
	});
}

/*
 * Load the words in dictionary into a vector. Words are converted to uppercase characters and
 * excluded if they include non-ASCII letters.
 */
std::vector<std::string> load_dictionary() {
	std::vector<std::string> words;
	words.reserve(80000); // Approximately 80,000 words in the dictionary.

	std::ifstream file(DICT_PATH);
	std::string line;
	while (std::getline(file, line)) {
		if (ascii_word(line)) {
			std::transform(line.begin(), line.end(), line.begin(), ::toupper);
			words.push_back(line);
		}
	}

	return words;
}
}

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
static void trie_single_insertion(benchmark::State& state) {
	while (state.KeepRunning()) {
		Trie trie;
		trie.insert("HELLO");
	}
}

BENCHMARK(trie_single_insertion);

/*
 * Benchmark the insertion of a string when inserting an entire dictionary.
 */
static void trie_dictionary_insertion(benchmark::State& state) {
	std::vector<std::string> dictionary = load_dictionary();
	std::vector<std::string>::size_type i = 0;
	Trie trie;
	while (state.KeepRunning()) {
		trie.insert(dictionary[i].c_str());
		i == dictionary.size() - 1 ? i = 0 : ++i;
	}
}

BENCHMARK(trie_dictionary_insertion);

/*
 * Benchmark the lookup of the string "THE" in a trie that has been loaded with a dictionary.
 */
static void trie_single_short_lookup(benchmark::State& state) {
	std::vector<std::string> dictionary = load_dictionary();
	Trie trie;
	for (const auto& word : dictionary) {
		trie.insert(word.c_str());
	}
	while (state.KeepRunning()) {
		trie.has_string("THE");
	}
}

BENCHMARK(trie_single_short_lookup);

/*
 * Benchmark the lookup of the string "ELECTROENCEPHALOGRAPHS" in a trie that has been loaded with a
 * dictionary.
 */
static void trie_single_long_lookup(benchmark::State& state) {
	std::vector<std::string> dictionary = load_dictionary();
	Trie trie;
	for (const auto& word : dictionary) {
		trie.insert(word.c_str());
	}
	while (state.KeepRunning()) {
		trie.has_string("ELECTROENCEPHALOGRAPHS");
	}
}

BENCHMARK(trie_single_long_lookup);

/*
 * Benchmark the lookup of every word in the dictionary in a trie that has been loaded with a
 * dictionary.
 */
static void trie_dictionary_lookup(benchmark::State& state) {
	std::vector<std::string> dictionary = load_dictionary();
	Trie trie;
	for (const auto& word : dictionary) {
		trie.insert(word.c_str());
	}

	std::vector<std::array<char, 24>>::size_type i = 0;
	while (state.KeepRunning()) {
		trie.has_string(dictionary[i].c_str());
		i == dictionary.size() - 1 ? i = 0 : ++i;
	}
}

BENCHMARK(trie_dictionary_lookup);

BENCHMARK_MAIN()
