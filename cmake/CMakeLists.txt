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


## This file actually does the building.

CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )

# Set project attributes:
PROJECT( Masala VERSION 0.1 DESCRIPTION "The Masala molecular modelling suite, combining the best of physics-based simulations and machine-learning based methods." )
SET( MODE debug )
SET( LINK_TYPE SHARED )
SET( LINK_EXTERNAL_LIBS stdc++ )
SET( CMAKE_MACOSX_RPATH 1 )
SET( CMAKE_SKIP_BUILD_RPATH FALSE )
SET( CMAKE_BUILD_WITH_INSTALL_RPATH FALSE )

# Set header file locations:
INCLUDE_DIRECTORIES( SYSTEM ../ ../src/ )

# Compiler settings and compilation flags:
INCLUDE( compiler.cmake )

# Generate the build lists for base, numeric, and core libraries and their associated API libraries:
execute_process(
    COMMAND python3 ../cmake/generate_cmake_build.py base ../src/base cmake_generated/base.cmake cmake_generated/base_api.cmake
)
# execute_process(
#     COMMAND python3 ../cmake/generate_cmake_build.py numeric ../src/numeric cmake_generated/numeric.cmake cmake_generated/numeric_api.cmake
# )
execute_process(
    COMMAND python3 ../cmake/generate_cmake_build.py core ../src/core cmake_generated/core.cmake cmake_generated/core_api.cmake
)

# Build the base, numeric, and core libraries:
INCLUDE( ../build/cmake_generated/base.cmake )
#INCLUDE( ../build/cmake_generated/numeric.cmake )
INCLUDE( ../build/cmake_generated/core.cmake )

# Generate the JSON descriptions and C++ code for the APIs for the base, numeric, and core libraries:
# TODO TODO TODO base and numeric
# ADD_CUSTOM_COMMAND(
#     DEPENDS generate_core_api POST_BUILD
#     OUTPUT ../build/cmake_generated/core_api.cmake
#     COMMAND echo "Generating JSON description of core API."
#     COMMAND ./generate_core_api
#     COMMAND echo "Auto-generating core API C++ code."
#     COMMAND sh -c "cd .. && python3 code_templates/generate_library_api.py core build/core_api.json && cd build"
#     VERBATIM
# )

INCLUDE( ../build/cmake_generated/core_api.cmake )

# Compile the API for base, numeric, and core libraries:
# TODO TODO TODO

# Link the API for base, numeric, and core libraries:
# TODO TODO TODO
