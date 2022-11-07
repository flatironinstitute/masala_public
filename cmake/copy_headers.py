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

## @file cmake/copy_headers.py
## @brief Used during the build process to copy the headers to a directory for redistribution.
##        Only headers that are exposed to outside code should be copied.
## @details Recursively goes through directories and finds .hh files to copy.  Usage:
##          python3 <directory to copy> <src directory> <headers directory>
## @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

from sys import argv
from os import path, makedirs
from shutil import copyfile
import glob

errmsg = "Error in copy_headers.py: "

assert len(argv) == 4, errmsg + "Incorrect number of arguments.   Usage: python3 copy_headers.py <library name> <source dir> <destination dir>."

lib_name = argv[1]
source_dir = argv[2]
dest_dir = argv[3]

assert path.isdir( source_dir )
assert path.isdir( dest_dir )
assert path.isdir( source_dir + "/" + lib_name )

files = glob.glob( source_dir + "/" + lib_name + "/**/*.hh", recursive=True )
print( "Copying Masala header files from " + source_dir + "/" + lib_name + "/ directory to " + dest_dir + "/ directory." )
for file in files :
    newfile = dest_dir + file[ len(source_dir) : ]
    newfile_path = path.dirname( newfile )
    if path.isdir( newfile_path ) == False :
        makedirs( newfile_path )
        print( "\tCreated directory " + newfile_path + "." )
    print( "\t" + file + " -> " + newfile )
    copyfile( file, newfile )

    if file.endswith(".fwd.hh") and file[ len( source_dir + "/" + lib_name ) : ].startswith( "/auto_generated_api" ) :
        original_lib_name = lib_name[:-4] # If the library is "core_api", the original library is "core".
        path_and_file = file[ len( source_dir + "/" + lib_name + "/auto_generated_api/" ) : ]
        original_path = path.dirname( path_and_file )
        original_file = path.basename( path_and_file )[ : -11 ] + ".fwd.hh" # If the file is "Pose_API.fwd.hh", the original file is "Pose.fwd.hh".
        original_fwd_declaration = source_dir + "/" + original_lib_name + "/" + original_path + "/" + original_file
        #print( "NEED " + original_fwd_declaration )

        new_original_file = dest_dir + original_fwd_declaration[ len(source_dir) : ]
        new_original_file_path = path.dirname( new_original_file )
        if path.isdir( new_original_file_path ) == False :
            makedirs( new_original_file_path )
            print( "\tCreated directory " + new_original_file_path + "." )
        print( "\t" + original_fwd_declaration + " -> " + new_original_file )
        copyfile( original_fwd_declaration, new_original_file )
    