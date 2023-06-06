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

## @file code_templates/copy_headers.py
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

assert len(argv) == 5, errmsg + "Incorrect number of arguments.   Usage: python3 copy_headers.py <project name> <library name> <source dir> <destination dir>."

project_name = argv[1]
lib_name = argv[2]
source_dir = argv[3]
dest_dir = argv[4]

assert path.isdir( source_dir ), source_dir + " is not a directory."
assert path.isdir( dest_dir ), dest_dir + " is not a directory."
assert path.isdir( source_dir + "/" + lib_name ), source_dir + "/" + lib_name + " is not a directory."

## @brief Determine whether an auto-generated API file defines a plugin creator.
def is_creator( filename : str ) -> bool :
    basename = path.basename( filename ).split(".")[0]
    if basename.endswith("Creator") == False :
        return False
    hhname = filename.replace(".fwd.hh", ".hh")
    with open( hhname, 'r' ) as filehandle:
        filelines = filehandle.readlines()
    is_creator = None
    for line in filelines :
        linesplit = line.strip().split()
        if len(linesplit) >= 6 and \
            linesplit[0] == "class" and \
            linesplit[2] == ":" and \
            linesplit[3] == "public" :
            assert is_creator == None, "Error in is_creator() function: More than one class definition found in file " + hhname + "."
            if linesplit[4] == "masala::base::managers::plugin_module::MasalaPluginCreator" :
                is_creator = True
            else :
                is_creator = False
    assert is_creator is not None, "Error in is_creator() function: Could not find class definition in file " + hhname + "."
    return is_creator

## @brief Determine whether an auto-generated API file defines an API for a lightweight,
## stack-allocated class (True) or for a heavyweight, heap-allocated class (False).
## @details Used to determine whether header files should be copied for the
## stack-allocated class.
def is_lightweight( filename : str ) -> bool :
    hhname = filename.replace(".fwd.hh", ".hh")
    with open( hhname, 'r' ) as filehandle:
        filelines = filehandle.readlines()
    is_lightweight = False
    for line in filelines:
        if line.strip() == "/// @note Note that this is a special case API object built for a lightweight" :
            is_lightweight = True
            break
    # if is_lightweight == True :
    #     print( filename + " IS LIGHTWEIGHT" )
    # else :
    #     print( filename + " IS NOT LIGHTWEIGHT")
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

## @brief Given file contents, purge comments and comment lines.
def purge_comments( file_contents : str ) -> str :
    # Get rid of //
    outstr = ""
    file_lines = file_contents.splitlines()
    for line in file_lines:
        pos = line.find("//")
        if pos == -1 :
            outstr += line + "\n"
        else :
            outstr += line[0:pos] + "\n"

    # Get rid of /*...*/
    outstr2 = ""
    recording = True
    for i in range(len(outstr)) :
        if i + 1 < len(outstr) and recording == True :
            if outstr[i:i+2] == "/*" :
                recording = False
                continue
        if i > 0 and recording == False :
            if outstr[i-1:i+1] == "*/" :
                recording = True
                continue
        if recording == True :
            outstr2 += outstr[i]
    return outstr2

## @brief Given an .hh file defining a class, a source directory (e.g. ""../src" ), and a
## library name for an api library (e.g. "numeric_api"), determine whether the class is a
## derived class with a parent in the parent library (e.g. "numeric" if this is "numeric_api").
## If it is, return the path and filename of the parent header (.hh file).  If it is not,
## simply return None.
def parent_library_base_filename( file : str, source_dir : str, lib_name : str, project_name : str, recursive=True ) -> list :
    if lib_name.endswith("_api") == False :
        return None
    with open( file, 'r' ) as filehandle:
        hh_filecontents = filehandle.read()
    hh_filecontents = purge_comments( hh_filecontents ).replace("(", " ( ").replace(")", " ) ").replace("<", " < ").replace(">", " > ").replace("{", " { ").replace("}", " } ").replace(";", " ; ").split()

    classdef_found = False

    for i in range( len( hh_filecontents ) - 5 ) :
        if hh_filecontents[i] == "class" :
            increment = 3
            if hh_filecontents[i+2] == ":" :
                increment +=  1
            if hh_filecontents[i+increment-1] == "public" :
                parent_class = hh_filecontents[i+increment]
                classdef_found = True
                break
    if classdef_found == False:
        return None

    #print( "*****\tParent in header " + file + " is " + parent_class + "." )
    parentsplit = parent_class.replace(":", " ").split()

    parent_lib_name = lib_name[:-4] # "numeric" if this is "numeric_api"

    if parentsplit[0] == project_name and parentsplit[1] == parent_lib_name :
        has_parent_class_to_copy = True
    elif parentsplit[0] == parent_lib_name :
        has_parent_class_to_copy = True
        parent_class = project_name + "::" + parent_class
        parentsplit = parent_class.replace(":", " ").split()
    else :
        has_parent_class_to_copy = False
    
    if has_parent_class_to_copy == False :
        return None

    parent_header = [ source_dir ]
    for j in range( 1, len(parentsplit) ) :
        parent_header[0] += "/" + parentsplit[j]
    parent_header[0] += ".hh"
    print( "\t\tFound parent class " + parent_class + " in header file " + file + ".  Will copy " + parent_header[0] + "." )
    if recursive == True :
        additional = parent_library_base_filename( parent_header[0], source_dir, lib_name, project_name, recursive=recursive )
        if additional is not None :
            parent_header.extend( additional )
    return parent_header

## @brief Copy all the files in a list.
def copy_files_in_list( files_to_copy : list, source_dir : str ) :
    for f2 in files_to_copy:
        new_original_file = dest_dir + f2[ len(source_dir) : ]
        new_original_file_path = path.dirname( new_original_file )
        if path.exists( f2 ) == False :
            if f2.startswith( "src/" ) :
                f2short = f2[4:]
            else :
                f2short = f2
            candidates = glob.glob( "headers/*/headers/" + f2short )
            assert len( candidates ) > 0, "Error in copy_files_in_list: no source found for " + f2 + "!"
            print("\tSkipping " + f2 + " since the following headers were found from other libraries:")
            for candidate in candidates:
                print( "\t\t" + candidate )
            continue
        if path.isdir( new_original_file_path ) == False :
            makedirs( new_original_file_path )
            print( "\tCreated directory " + new_original_file_path + "." )
        if path.exists( new_original_file ) == False :
            print( "\t" + f2 + " -> " + new_original_file )
            copyfile( f2, new_original_file )


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
    
    if file.endswith(".fwd.hh") :
        if file[ len( source_dir + "/" + lib_name ) : ].startswith( "/auto_generated_api" ) :
            original_lib_name = lib_name[:-4] # If the library is "core_api", the original library is "core".
            path_and_file = file[ len( source_dir + "/" + lib_name + "/auto_generated_api/" ) : ]
            original_path = path.dirname( path_and_file )
            original_file = path.basename( path_and_file )[ : -11 ] + ".fwd.hh" # If the file is "MolecularSystem_API.fwd.hh", the original file is "MolecularSystem.fwd.hh".
            original_fwd_declaration = source_dir + "/" + original_lib_name + "/" + original_path + "/" + original_file
            iscreator = is_creator( file )
            if iscreator == False and is_lightweight( file ) == True :
                original_hh_file = path.basename( path_and_file )[ : -11 ] + ".hh"
                original_hh_declaration = source_dir + "/" + original_lib_name + "/" + original_path + "/" + original_hh_file
                files_to_copy = get_fwd_files( original_hh_declaration, source_dir )
            else :
                original_hh_file = None
                original_hh_declaration = None
                files_to_copy = []

            if iscreator == False :
                files_to_copy.append( original_fwd_declaration )
                if original_hh_declaration is not None :
                    files_to_copy.append( original_hh_declaration )

            copy_files_in_list( files_to_copy, source_dir )

    elif file.endswith( ".hh" ) :
        iscreator = is_creator( file )
        if iscreator == True :
            files_to_copy = []
        else :
            files_to_copy = get_fwd_files( file, source_dir )
            parent_hh_files = parent_library_base_filename( file, source_dir, lib_name, project_name, recursive=True )
            if lib_name.endswith( "_api" ) and parent_hh_files != None :
                files_to_copy.extend( parent_hh_files )

        copy_files_in_list( files_to_copy, source_dir )
    