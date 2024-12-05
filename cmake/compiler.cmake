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
    IF( ${MODE} STREQUAL "debug" )
	    ADD_DEFINITIONS(-D_GLIBCXX_DEBUG)
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing")
    ELSEIF( ${MODE} STREQUAL "release" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native -W -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing")
    ENDIF()
ELSEIF(UNIX)
    SET(COMPILER gcc)
	ADD_DEFINITIONS(-DMASALA_UNIX)
    SET( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lstdc++fs" )
    IF( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 9.5 )
        MESSAGE( "GCC version " ${CMAKE_CXX_COMPILER_VERSION} " detected.  Adding definitions for STL parallel execution policies." )
        ADD_DEFINITIONS(-DMASALA_USE_STL_PARALLEL)
    else()
        MESSAGE( "GCC version " ${CMAKE_CXX_COMPILER_VERSION} " detected.  Skipping definitions for STL parallel execution policies." )
    ENDIF()
    IF( ${MODE} STREQUAL "debug" )
	    #ADD_DEFINITIONS(-D_GLIBCXX_DEBUG)
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffloat-store -W -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing")
    ELSEIF( ${MODE} STREQUAL "release" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-limit=100000 -s -W -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing")
    ENDIF()
ELSEIF(WIN32)
    SET(COMPILER gcc)
	ADD_DEFINITIONS(-DMASALA_WINDOWS)
    IF( ${MODE} STREQUAL "debug" )
	    #ADD_DEFINITIONS(-D_GLIBCXX_DEBUG)
	    ADD_DEFINITIONS(-DMASALA_USE_STL_PARALLEL)
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffloat-store -W -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing")
    ELSEIF( ${MODE} STREQUAL "release" )
        SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-limit=100000 -s -W -Wall -Wextra -pedantic -Werror -Wno-long-long -Wno-strict-aliasing")
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
