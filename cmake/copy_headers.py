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

## @brief Determine whether an auto-generated API file defines an API for a lightweight,
## stack-allocated class (True) or for a heavyweight, heap-allocated class (False).
## @details Used to determine whether header files should be copied for the
## stack-allocated class.
def is_lightweight( filename : str ) -> bool :
    hhname = filename.replace(".fwd.hh", ".hh")
    with open( hhname, 'r' ) as filehandle:
        filelines = filehandle.readlines()
    is_lightweight = None
    for line in filelines:
        linestripped = line.strip()
        if linestripped.endswith( "inner_object_;" ) :
            linesplit = linestripped.split()
            assert len(linesplit) == 2
            if linesplit[0].endswith("SP") :
                is_lightweight = False
                break
            else :
                is_lightweight = True
                break
    assert is_lightweight is not None, "Error in parsing file " + hhname + " to determine whether this is a lightweight API."
    return is_lightweight

## @brief Get a list of all of the .fwd.hh files included by a header file.
def get_fwd_files( filename : str, source_dir : str ) -> list :
    returnlist = []
    with open( filename, 'r' ) as filehandle:
        filelines = filehandle.readlines()
    for line in filelines :
        linestripped = line.strip()
        if linestripped.startswith("#include"):
            linesplit = linestripped.replace("<", " ").replace(">", " ").split()
            assert len(linesplit) >= 2
            if linesplit[1].endswith(".fwd.hh") :
                returnlist.append( source_dir + "/"+ linesplit[1] )
    return returnlist


files = glob.glob( source_dir + "/" + lib_name + "/**/*.hh", recursive=True )
files.extend( glob.glob( source_dir + "/" + lib_name + "/*.hh", recursive=False ) )
print( "Copying Masala header files from " + source_dir + "/" + lib_name + "/ directory to " + dest_dir + "/ directory." )
for file in files :
    newfile = dest_dir + file[ len(source_dir) : ]
    newfile_path = path.dirname( newfile )
    if path.isdir( newfile_path ) == False :
        makedirs( newfile_path )
        print( "\tCreated directory " + newfile_path + "." )
    print( "\t" + file + " -> " + newfile )
    copyfile( file, newfile )
    
    if file[ len( source_dir + "/" + lib_name ) : ].startswith( "/auto_generated_api" ) :
        if file.endswith(".fwd.hh") :
            original_lib_name = lib_name[:-4] # If the library is "core_api", the original library is "core".
            path_and_file = file[ len( source_dir + "/" + lib_name + "/auto_generated_api/" ) : ]
            original_path = path.dirname( path_and_file )
            original_file = path.basename( path_and_file )[ : -11 ] + ".fwd.hh" # If the file is "Pose_API.fwd.hh", the original file is "Pose.fwd.hh".
            original_fwd_declaration = source_dir + "/" + original_lib_name + "/" + original_path + "/" + original_file
            if is_lightweight( file ) == True :
                original_hh_file = path.basename( path_and_file )[ : -11 ] + ".hh"
                original_hh_declaration = source_dir + "/" + original_lib_name + "/" + original_path + "/" + original_hh_file
                files_to_copy = get_fwd_files( original_hh_declaration, source_dir )
            else :
                original_hh_file = None
                original_hh_declaration = None
                files_to_copy = []

            files_to_copy.append( original_fwd_declaration )
            if original_hh_declaration is not None :
                files_to_copy.append( original_hh_declaration )

            for f2 in files_to_copy:
                new_original_file = dest_dir + f2[ len(source_dir) : ]
                new_original_file_path = path.dirname( new_original_file )
                if path.isdir( new_original_file_path ) == False :
                    makedirs( new_original_file_path )
                    print( "\tCreated directory " + new_original_file_path + "." )
                if path.exists( new_original_file ) == False :
                    print( "\t" + f2 + " -> " + new_original_file )
                    copyfile( f2, new_original_file )
        elif file.endswith( ".hh" ) :
            files_to_copy = get_fwd_files( file, source_dir )
            for f2 in files_to_copy :
                newfile = dest_dir + f2[ len(source_dir) : ]
                newfile_path = path.dirname( newfile )
                if path.isdir( newfile_path ) == False :
                    makedirs( newfile_path )
                    print( "\tCreated directory " + newfile_path + "." )
                if path.exists( newfile ) == False :
                    print( "\t" + f2 + " -> " + newfile )
                    copyfile( f2, newfile )
    