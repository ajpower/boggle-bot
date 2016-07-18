cmake_minimum_required(VERSION 3.0.2)

# Project details.
project(boggle-bot CXX)
set(TARGET boggle)

set(SRC_DIR boggle-solver)
set(DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/boggle-bot)

# Detect compiler and set options. Exit if compiler or version are not supported.
if (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.3)
		message(FATAL_ERROR "Clang version not supported.")
	endif ()

	add_compile_options(-std=c++11)
	add_compile_options(-O3)

	add_compile_options(-Weverything)

	add_compile_options(-Wno-c++98-compat)
	add_compile_options(-Wno-c++98-compat-pedantic)
	add_compile_options(-Wno-padded)

	if (CMAKE_BUILD_TYPE STREQUAL Debug)
		add_compile_options(-g)
		#add_compile_options(-Werror)
	endif ()

	if (CMAKE_BUILD_TYPE STREQUAL Release)
		add_compile_options(-s)
		add_compile_options(-DNDEBUG)
	endif ()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
	if (CMAKE_CXX_COMPILER_VERSION STREQUAL 4.8.1)
		message(FATAL_ERROR "GCC version not supported.")
	endif ()

	add_compile_options(-std=c++11)
	add_compile_options(-O3)

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

	if (CMAKE_BUILD_TYPE STREQUAL Debug)
		add_compile_options(-g)
		#add_compile_options(-Werror)
	endif ()

	if (CMAKE_BUILD_TYPE STREQUAL Release)
		add_compile_options(-s)
		add_compile_options(-DNDEBUG)
	endif ()

else ()
	message(FATAL_ERROR "Your compiler is not presently supported.")
endif ()

# Set source files.
set(SOURCE_FILES ${SRC_DIR}/boggle.cpp)

# Create shared object.
add_library(${TARGET} SHARED ${SOURCE_FILES})
set_target_properties(${TARGET} PROPERTIES
                      PREFIX ""
                      LIBRARY_OUTPUT_DIRECTORY ${DESTINATION})

# Include and link libraries.
include_directories(/usr/include/python3.5)
target_link_libraries(${TARGET} boost_python-py35)
