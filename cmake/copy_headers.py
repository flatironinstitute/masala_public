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
from os import path, listdir
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
#print(files)
for file in files :
    newfile = dest_dir + file[ len(source_dir) : ]
    print( "\t" + file + " -> " + newfile )