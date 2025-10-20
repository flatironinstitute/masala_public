# Masala
# Copyright (C) 2025 Vikram K. Mulligan
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

## This file actually does the building.

CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )

# Set project attributes:
PROJECT( Masala VERSION 1.1 DESCRIPTION "The Masala molecular modelling suite, combining the best of physics-based simulations and machine-learning based methods." )

# Default build is release mode.  To build in debug mode (recommeded for development),
# change the nex tline to SET( MODE debug ).
SET( MODE release )
#SET( MODE debug )
IF( ${MODE} STREQUAL "release" )
	SET( CMAKE_BUILD_TYPE Release )
ELSEIF( ${MODE} STREQUAL "debug" )
	SET( CMAKE_BUILD_TYPE Debug )
ELSE()
	MESSAGE( FATAL_ERROR "The only allowed compilation modes are debug and release." )
ENDIF()

# Uncomment the following to enable compilation with support for AVX512 instructions on Linux or Windows systems.
# Note that this only has an effect in relase mode.
#SET( MASALA_SUPPORT_AVX512 TRUE )

# Uncomment the following to enable compilation with support for OpenBLAS, for more efficient matrix manipulations.
#SET( MASALA_USE_OPENBLAS TRUE )

# Uncomment the following to enable deprecated API functions.
#ADD_DEFINITIONS( -DMASALA_ENABLE_DEPRECATED_FUNCTIONS )

# Uncomment the following to disable deprecation warnings.
#ADD_DEFINITIONS( -DMASALA_DISABLE_DEPRECATION_WARNINGS )

# Ensure that version is set in only one place, in the PROJECT line at the top of this file:
ADD_DEFINITIONS( -DMASALA_MAJOR_VERSION=${CMAKE_PROJECT_VERSION_MAJOR} -DMASALA_MINOR_VERSION=${CMAKE_PROJECT_VERSION_MINOR} )

SET( LINK_TYPE SHARED )
SET( LINK_EXTERNAL_LIBS stdc++ )
SET( CMAKE_MACOSX_RPATH 0 )
SET( CMAKE_SKIP_BUILD_RPATH FALSE )
SET( CMAKE_BUILD_WITH_INSTALL_RPATH FALSE )
SET( THREADS_PREFER_PTHREAD_FLAG ON )
SET( Catch2_DIR ../catch2_build )
#SET(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra -pedantic-errors")
FIND_PACKAGE( Threads REQUIRED )

# Set header file locations:
INCLUDE_DIRECTORIES( SYSTEM ../ ../src/ )

# Compiler settings and compilation flags:
INCLUDE( compiler.cmake )

# Generate the build lists for base, numeric, and core libraries and their associated API libraries:
execute_process(
    COMMAND python3 ../code_templates/generate_cmake_build.py masala ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} base ../src/base cmake_generated/base.cmake NONE cmake_generated/base_tests.cmake
)
execute_process(
    COMMAND python3 ../code_templates/generate_cmake_build.py masala ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} numeric ../src/numeric cmake_generated/numeric.cmake cmake_generated/numeric_api.cmake cmake_generated/numeric_tests.cmake
)
execute_process(
    COMMAND python3 ../code_templates/generate_cmake_build.py masala ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} core ../src/core cmake_generated/core.cmake cmake_generated/core_api.cmake cmake_generated/core_tests.cmake
)

# Build the base, numeric, and core libraries:
INCLUDE( ../build/cmake_generated/base.cmake )
INCLUDE( ../build/cmake_generated/numeric.cmake )
INCLUDE( ../build/cmake_generated/core.cmake )

# Build the numeric and core APIs.
INCLUDE( ../build/cmake_generated/numeric_api.cmake )
INCLUDE( ../build/cmake_generated/core_api.cmake )

# Build tests for base, numeric, and core.
INCLUDE( ../build/cmake_generated/base_tests.cmake )
INCLUDE( ../build/cmake_generated/numeric_tests.cmake )
INCLUDE( ../build/cmake_generated/core_tests.cmake )
