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

## @file cmake/generate_cmake_build.py
## @brief Used during the build process to generate the cmake files for all the stuff that
## has to be compiled in a given library.
## @details Recursively goes through directories and finds .cc files to compile.  Usage:
##          python3 generate_cmake_build.py <library name> <source dir> <output path and filename for cmake file>
## @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

from genericpath import isdir, isfile
from sys import argv
from os import path, listdir

errmsg = "Error in generate_cmake_build.py: "

def get_all_cc_files_in_dir_and_subdirs( dirname : str ) -> list :
    assert path.isdir( dirname ), errmsg + "Directory " + dirname + " doesn't exist."
    outlist = []
    for fname in listdir( dirname ) :
        concatname = dirname + "/" + fname
        if path.isfile( concatname ) :
            if fname.endswith( ".cc" ) :
                outlist.append( concatname )
        elif path.isdir( concatname ) :
            outlist.extend( get_all_cc_files_in_dir_and_subdirs( concatname ) )
    return outlist        

assert len(argv) == 4, errmsg + "Incorrect number of arguments.  Usage is python3 generate_cmake_build.py <library name> <source dir> <output path and filename for cmake file>."

lib_name = argv[1]
source_dir = argv[2]
output_file = argv[3]

cclist = get_all_cc_files_in_dir_and_subdirs( source_dir )
with open( output_file, 'w' ) as fhandle:
    if len(cclist) > 0 :
        fhandle.write( "ADD_LIBRARY(" + lib_name + " SHARED" )
    for entry in cclist:
        fhandle.write( "\n\t" + entry )
    if len(cclist) > 0 :
        fhandle.write( "\n)\n" )
        fhandle.write( "SET_TARGET_PROPERTIES(" + lib_name + " PROPERTIES VERSION ${PROJECT_VERSION})\n" )

print( "Wrote " + output_file + "." )
