# Masala
# Copyright (C) 2022 Vikram K. Mulligan
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# This file sets compiler settings for compilation.

IF(APPLE)
    SET(COMPILER clang)
	ADD_DEFINITIONS(-DMASALA_MAC)
    SET( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -flat_namespace -march=native -mtune=native" )
    IF( ${MODE} STREQUAL "release" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native")
    ENDIF()
ELSEIF(UNIX)
    SET(COMPILER gcc)
	ADD_DEFINITIONS(-DMASALA_UNIX)
    IF( ${MODE} STREQUAL "debug" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffloat-store")
    ELSEIF( ${MODE} STREQUAL "release" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-limit=100000 -s")
    ENDIF()
ELSEIF(WIN32)
    SET(COMPILER gcc)
	ADD_DEFINITIONS(-DMASALA_WINDOWS)
    IF( ${MODE} STREQUAL "debug" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffloat-store")
    ELSEIF( ${MODE} STREQUAL "release" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-limit=100000 -s")
    ENDIF()
ELSE()
    MESSAGE( FATAL_ERROR "Only Macintosh, Linux/Unix, and Windows builds are supported at this time." )
ENDIF()

SET( CMAKE_CXX_STANDARD 17 )
SET( CMAKE_CXX_STANDARD_REQUIRED True )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -pipe -ftemplate-depth-512 -fPIC -I /usr/include -I src" )
SET( CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -rdynamic -frtti" )
SET( cxx -std=c++17 )
#SET( compile -pipe -ftemplate-depth-512 -fPIC -I /usr/include -I src -Wl --no-as-needed )
SET( warn -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing )
SET( link -Wl --no-as-needed )

IF( ${MODE} STREQUAL "debug" )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -ggdb -D_DEBUG")
    #LIST( APPEND compile -O0 )
    #LIST( APPEND mode -g -ggdb -ffloat-store )
    #LIST( APPEND defines -D_DEBUG )
ELSEIF( ${MODE} STREQUAL "release" )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -fno-finite-math-only -funroll-loops -finline-functions -DNDEBUG")
    #LIST( APPEND compile -O3 -ffast-math -fno-finite-math-only -funroll-loops -finline-functions -finline-limit=100000 -s )
    #LIST( APPEND defines -DNDEBUG )
ELSE()
    MESSAGE( FATAL_ERROR "The only allowed compilation modes are debug and release." )
ENDIF()

MESSAGE(STATUS "Compiler: ${COMPILER}")
