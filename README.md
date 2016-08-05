# boggle-bot
Boggle playing bot for wordplays.com.

There are two components to the bot. The first is a multithreaded Boggle-solving engine written in C++14 and interfaced to
Python with Boost.Python. This engine can solve a 4x4 Boggle board in approximately 80 microseconds. The second component is a web-scraper written in Python using the `BeautifulSoup` and `requests` modules.

# Compiling
Compiling the boggle module requires 

1. `cmake` and `make`
2. the Boost libraries
3. either `clang` or `gcc`.

Inside the project directory, create a directory called `build`, enter it, and run `cmake ..`. You can optionally specify an alternative compiler by passing the `-DCMAKE_CXX_COMPILER=<your compiler>` option to `cmake`. Then run `make`. The Python module `boggle.so` should now appear in the directory `boggle-bot`.

# Running
To execute the bot, simply run the command `python3 boggle-bot`. You will be prompted for a username and password.

# Testing and benchmarking
If you would like to run unit tests, first enter into the `tests` directory and clone the `googletests` repository with the
command `git clone --depth=1 https://github.com/google/googletest`. Then when building the project with `cmake`, pass the
option `-DENABLE_TESTING=ON`. Unit tests can be found in the `tests` directory that will be created in your build directory.

If you would like to run benchmarks, first enter into the `benchmark` directory and clone the `google/benchmark` repository
with the command `git clone --depth=1 https://github.com/google/benchmark`. Then when building the project with `cmake`,
pass the option `-DENABLE_BENCHMARKS=ON`. Benchmarks will be cound in the `benchmark` directory that will be created in your build directory.
