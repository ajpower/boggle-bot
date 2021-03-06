cmake_minimum_required(VERSION 3.0.2)

project(boggle-bot CXX)

option(ENABLE_BENCHMARKS "Enable bencharks" OFF)
option(ENABLE_TESTING "Enable testing" OFF)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)
		message(FATAL_ERROR "Clang version not supported.")
	endif ()

	add_compile_options(-std=c++14)

	add_compile_options(-Weverything)

	add_compile_options(-Wno-c++98-compat)
	add_compile_options(-Wno-c++98-compat-pedantic)
	add_compile_options(-Wno-exit-time-destructors)
	add_compile_options(-Wno-global-constructors)
	add_compile_options(-Wno-missing-braces)
	add_compile_options(-Wno-padded)

	add_compile_options(-fPIC)

	if (CMAKE_BUILD_TYPE STREQUAL Debug)
		add_compile_options(-g)
		add_compile_options(-fno-omit-frame-pointer)
		add_compile_options(-Werror)
	endif ()

	if (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
		add_compile_options(-O3)
		add_compile_options(-g)
		add_compile_options(-fno-omit-frame-pointer)
		add_compile_options(-Werror)
	endif ()

	if (CMAKE_BUILD_TYPE STREQUAL Release)
		add_compile_options(-O3)
		add_compile_options(-s)
		add_compile_options(-DNDEBUG)
	endif ()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5)
		message(FATAL_ERROR "GCC version not supported.")
	endif ()

	add_compile_options(-std=c++14)

	add_compile_options(-Wall)
	add_compile_options(-Wextra)
	add_compile_options(-pedantic)
	add_compile_options(-Wcast-align)
	add_compile_options(-Wcast-qual)
	add_compile_options(-Wctor-dtor-privacy)
	add_compile_options(-Wdisabled-optimization)
	add_compile_options(-Wformat=2)
	add_compile_options(-Wlogical-op)
	add_compile_options(-Wmissing-declarations)
	add_compile_options(-Wmissing-include-dirs)
	add_compile_options(-Wold-style-cast)
	add_compile_options(-Woverloaded-virtual)
	add_compile_options(-Wredundant-decls)
	add_compile_options(-Wshadow)
	add_compile_options(-Wsign-conversion)
	add_compile_options(-Wsign-promo)
	add_compile_options(-Wstrict-null-sentinel)
	add_compile_options(-Wswitch-default)
	add_compile_options(-Wundef)

	add_compile_options(-fPIC)

	if (CMAKE_BUILD_TYPE STREQUAL Debug)
		add_compile_options(-g)
		add_compile_options(-fno-omit-frame-pointer)
		add_compile_options(-Werror)
	endif ()

	if (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
		add_compile_options(-O3)
		add_compile_options(-g)
		add_compile_options(-fno-omit-frame-pointer)
		add_compile_options(-Werror)
	endif ()

	if (CMAKE_BUILD_TYPE STREQUAL Release)
		add_compile_options(-O3)
		add_compile_options(-s)
		add_compile_options(-DNDEBUG)
	endif ()

else ()
	message(FATAL_ERROR "Your compiler is not presently supported.")
endif ()

add_subdirectory(boggle-solver)

if (ENABLE_BENCHMARKS)
	add_subdirectory(benchmark)
endif ()

if (ENABLE_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif ()
