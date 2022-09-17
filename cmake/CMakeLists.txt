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

# Build base library:
FILE(GLOB_RECURSE base_src CONFIGURE_DEPENDS "../src/base/*.hh" "../src/base/*.cc" )
ADD_LIBRARY(base SHARED ${base_src})
SET_TARGET_PROPERTIES(base PROPERTIES VERSION ${PROJECT_VERSION})

# Build numeric library:
# FILE(GLOB_RECURSE numeric_src CONFIGURE_DEPENDS "../src/numeric/*.hh" "../src/numeric/*.cc" )
# ADD_LIBRARY(numeric SHARED ${numeric_src})
# SET_TARGET_PROPERTIES(numeric PROPERTIES VERSION ${PROJECT_VERSION})
# TARGET_LINK_LIBRARIES(numeric
# 	PUBLIC base
# )

# Build core library:
FILE(GLOB_RECURSE core_src CONFIGURE_DEPENDS "../src/core/*.hh" "../src/core/*.cc" )
ADD_LIBRARY(core SHARED ${core_src})
SET_TARGET_PROPERTIES(core PROPERTIES VERSION ${PROJECT_VERSION})
TARGET_LINK_LIBRARIES(core
    #PUBLIC numeric
	PUBLIC base
)

ADD_EXECUTABLE( generate_core_api ../src/core/core_apps/generate_core_api.cc)
TARGET_LINK_LIBRARIES(generate_core_api
	PUBLIC base
	PUBLIC core
)

# Generate the JSON descriptions and C++ code for the APIs for the base, numeric, and core libraries:
# TODO TODO TODO base and numeric
add_custom_command(
    DEPENDS generate_core_api
    COMMAND echo "Generating JSON description of core API."
    COMMAND ./generate_core_api
    COMMAND echo "Auto-generating core API C++ code."
    COMMAND sh -c "cd .. && python3 code_templates/generate_library_api.py core build/core_api.json && cd build"
    #COMMAND python3 ../cmake/generate_cmake_build.py core_api ../src/core_api cmake_generated/core_api.cmake
    FILE(GLOB_RECURSE core_api_src CONFIGURE_DEPENDS "../src/core_api/*.hh" "../src/core_api/*.cc" )
    OUTPUT "../src/core_api/auto_generated_api/pose/Pose_API.cc"
    OUTPUT "../src/core_api/auto_generated_api/pose/Pose_API.fwd.hh"
    OUTPUT "../src/core_api/auto_generated_api/pose/Pose_API.hh"
    VERBATIM
)

# Build core_api library:
#FILE(GLOB_RECURSE core_api_src CONFIGURE_DEPENDS "../src/core_api/*.hh" "../src/core_api/*.cc" )
#ADD_LIBRARY(core_api SHARED ${core_api_src} )
ADD_LIBRARY(core_api SHARED
    "../src/core_api/auto_generated_api/pose/Pose_API.cc"
    "../src/core_api/auto_generated_api/pose/Pose_API.hh"
    "../src/core_api/auto_generated_api/pose/Pose_API.fwd.hh"
)
SET_TARGET_PROPERTIES(core_api PROPERTIES VERSION ${PROJECT_VERSION})
TARGET_LINK_LIBRARIES(core_api
    PUBLIC core
    #PUBLIC numeric
	PUBLIC base
)

#INCLUDE( ../build/cmake_generated/core_api.cmake )

# Compile the API for base, numeric, and core libraries:
# TODO TODO TODO

# Link the API for base, numeric, and core libraries:
# TODO TODO TODO
