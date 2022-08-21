# MIT License
#
# Copyright (c) 2022 Vikram K. Mulligan
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


# This file sets compiler settings for compilation.

IF(APPLE)
    SET(COMPILER clang)
	ADD_DEFINITIONS(-DMASALA_MAC)
ELSEIF(UNIX)
    SET(COMPILER gcc)
	ADD_DEFINITIONS(-DMASALA_UNIX)
ELSEIF(WIN32)
    SET(COMPILER gcc)
	ADD_DEFINITIONS(-DMASALA_WINDOWS)
ELSE()
    MESSAGE( FATAL_ERROR "Only Macintosh, Linux/Unix, and Windows builds are supported at this time." )
ENDIF()

SET( CMAKE_CXX_STANDARD 14 )
SET( CMAKE_CXX_STANDARD_REQUIRED True )
SET( cxx -std=c++14 )
SET( compile -pipe -ftemplate-depth-512 -fPIC -I /usr/include -I src -Wl --no-as-needed )
SET( warn -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing )
SET( link -Wl --no-as-needed )

IF( ${MODE} STREQUAL "debug" )
    LIST( APPEND compile -O0 )
    LIST( APPEND mode -g -ggdb -ffloat-store )
    LIST( APPEND defines -D_DEBUG )
ELSEIF( ${MODE} STREQUAL "release" )
    LIST( APPEND compile -O3 -ffast-math -fno-finite-math-only -funroll-loops -finline-functions -finline-limit=100000 -s )
    LIST( APPEND defines -DNDEBUG )
ELSE()
    MESSAGE( FATAL_ERROR "The only allowed compilation modes are debug and release." )
ENDIF()

MESSAGE(STATUS "Compiler: ${COMPILER}")
