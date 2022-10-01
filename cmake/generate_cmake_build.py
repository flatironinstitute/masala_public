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
## has to be compiled in a given library.  This also generates the cmake files for the
## associated API libraries.
## @details Recursively goes through directories and finds .cc files to compile.  Usage:
##          python3 generate_cmake_build.py <library name> <source dir> <output path and filename for cmake file>
## @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

from sys import argv
from os import path, listdir

errmsg = "Error in generate_cmake_build.py: "

## @brief Given a string for the contents of a .cc file, purge anything that is between braces
## that are not namespace braces.

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
    # print( "Original string:\n--------------------------------------------------------------------------------\n" )
    # print( file_contents + "\n" )
    # print( "--------------------------------------------------------------------------------\n" )
    # print( "Stripped of comments:\n--------------------------------------------------------------------------------\n" )
    # print( outstr2 + "\n" )
    # print("--------------------------------------------------------------------------------\n")
    return outstr2

## @brief Determine whether a given .cc file contains an API definition:
def has_api_definition( filename : str, concatname : str ) -> bool :
    with open( concatname, 'r' ) as fhandle:
        file_contents = fhandle.read()

    filename_base = filename.split('.')[0]

    # Initial check: if we don't have the string at all, we're done.
    if file_contents.find( filename_base + "::" + "get_api_definition" ) == -1 :
        return False

    # Second check: if the string is in the file, we need to make sure that it doesn't
    # occur inside a comment or in a context other than a function definition.
    file_contents = ' '.join( purge_comments( file_contents ).split() ) #Put the file on a single line with all whitespace converted to spaces and comments removed.
    if file_contents.find( filename_base + "::" + "get_api_definition" ) == -1 :
        return False

    return True

## @brief From a filename, generate the name of the corresponding api file.
## @details Omits extension.
def apiname_from_filename( fname: str) -> str :
    fname_entries = fname.split("/")
    assert len(fname_entries) > 3
    newname = ""
    for i in range( len(fname_entries) ):
        if i == 0 :
            newname += fname_entries[i]
        elif i == 2 :
            newname += "/" + fname_entries[i] + "_api/auto_generated_api"
        elif i == len(fname_entries) - 1 :
            entrysplit = fname_entries[i].split(".")
            assert len(entrysplit) == 2
            newname += "/" + entrysplit[0] + "_API"
        else :
            newname += "/" + fname_entries[i]
    return newname

## @brief Scan all directories and subdirectories in a path, and make a list of all .cc and .hh files.
## @details If skip_apps is true, we also check for .cc files that contain API definitions, and
## report those in a second list.  If skip_apps is false, we do not do this.
def get_all_cc_and_hh_files_in_dir_and_subdirs( libname:str, dirname : str, skip_apps : bool ) :
    assert path.isdir( dirname ), errmsg + "Directory " + dirname + " doesn't exist."
    if skip_apps == True :
        if dirname.endswith( libname + "_apps" ) or dirname.endswith( libname + "_apps/" ) :
            # Skip directories like core_apps.  Apps are compiled separately into executables.
            return [], []
    outlist = []
    if skip_apps == True :
        outlist_apis = []
    for fname in listdir( dirname ) :
        concatname = dirname + "/" + fname
        if path.isfile( concatname ) :
            if fname.endswith( ".cc" ) or fname.endswith( ".hh") :
                outlist.append( concatname )
            if (skip_apps == True) and \
                    fname.endswith( ".cc" ) and \
                    (concatname != "../src/base/MasalaObject.cc") and \
                    (has_api_definition(fname, concatname)) :
                apiname = apiname_from_filename( concatname )
                outlist_apis.append( apiname + ".cc" )
                outlist_apis.append( apiname + ".hh" )
                outlist_apis.append( apiname + ".fwd.hh" )
        elif path.isdir( concatname ) :
            if skip_apps == True :
                outlist2, outlist2_apis = get_all_cc_and_hh_files_in_dir_and_subdirs( libname, concatname, skip_apps )
                outlist.extend(outlist2)
                outlist_apis.extend(outlist2_apis)
            else :
                outlist.extend( get_all_cc_and_hh_files_in_dir_and_subdirs( libname, concatname, skip_apps ) )
    if skip_apps == True :
        return outlist, outlist_apis
    return outlist

def get_library_dependencies( dirname : str ) -> list :
    assert path.isdir( dirname ), errmsg + "Directory " + dirname + " doesn't exist."
    liblistfile = dirname + "/link_dependencies.txt"
    if path.isfile( liblistfile ) :
        with open( liblistfile, 'r' ) as fread :
            dlist = fread.read().split()
        for entry in dlist :
            if entry[0] == "#" :
                dlist.remove(entry)
        return dlist
    return []

assert len(argv) == 5, errmsg + "Incorrect number of arguments.  Usage is python3 generate_cmake_build.py <library name> <source dir> <output path and filename for cmake file> <output path and filename for API cmake file>."

lib_name = argv[1]
source_dir = argv[2]
output_file = argv[3]
output_file_api = argv[4]

cclist, api_cclist = get_all_cc_and_hh_files_in_dir_and_subdirs( lib_name, source_dir, True )
depend_list = get_library_dependencies( source_dir )

appsdir = source_dir + "/" + lib_name + "_apps"
if path.isdir( appsdir ) :
    print( "\tChecking " + appsdir + " for apps." )
    appslist = get_all_cc_and_hh_files_in_dir_and_subdirs( lib_name, appsdir, False )
else :
    appslist = []

with open( output_file, 'w' ) as fhandle:
    if len(cclist) > 0 :
        fhandle.write( "ADD_LIBRARY(" + lib_name + " SHARED" )
        for entry in cclist:
            fhandle.write( "\n\t" + entry )
        fhandle.write( "\n)\n" )
        fhandle.write( "SET_TARGET_PROPERTIES(" + lib_name + " PROPERTIES VERSION ${PROJECT_VERSION})\n" )
        if len(depend_list) > 0 :
            fhandle.write( "TARGET_LINK_LIBRARIES(" + lib_name )
            for dentry in depend_list :
                fhandle.write( "\n\tPUBLIC " + dentry )
            fhandle.write( "\n\tPRIVATE Threads::Threads" )
            fhandle.write("\n)\n")
    if len( appslist ) > 0 :
        for app in appslist :
            appname = path.basename( app ).split(".")[0]
            fhandle.write("\nADD_EXECUTABLE( " + appname + " " + app + ")\n" )
            fhandle.write("TARGET_LINK_LIBRARIES(" + appname )
            for dentry in depend_list :
                fhandle.write( "\n\tPUBLIC " + dentry )
            fhandle.write( "\n\tPRIVATE Threads::Threads" )
            fhandle.write("\n\tPUBLIC " + lib_name + "\n)\n")

if len(api_cclist) > 0 :
    with open( output_file_api, 'w' ) as fhandle :
        fhandle.write( "ADD_CUSTOM_COMMAND(\n" )
        fhandle.write( "\tDEPENDS generate_" + lib_name + "_api POST_BUILD\n" )
        fhandle.write( "\tOUTPUT\n" )
        for entry in api_cclist :
            fhandle.write( "\t\t" + entry + "\n" )
        fhandle.write( "\tCOMMAND echo \"Generating JSON description of core API.\"\n" )
        fhandle.write( "\tCOMMAND ./generate_" + lib_name + "_api\n" )
        fhandle.write( "\tCOMMAND echo \"Auto-generating core API C++ code.\"\n" )
        fhandle.write( "\tCOMMAND sh -c \"cd .. && python3 code_templates/generate_library_api.py core build/core_api.json && cd build\"\n")
        fhandle.write( "\tVERBATIM\n)\n\n" )

        fhandle.write( "ADD_LIBRARY(" + lib_name + "_api SHARED" )
        for entry in api_cclist :
            fhandle.write( "\n\t" + entry )
        fhandle.write( "\n)\n" )
        fhandle.write( "SET_TARGET_PROPERTIES(" + lib_name + "_api PROPERTIES VERSION ${PROJECT_VERSION})\n" )
        fhandle.write( "TARGET_LINK_LIBRARIES(" + lib_name + "_api" )
        if len(depend_list) > 0 :
            for dentry in depend_list :
                fhandle.write( "\n\tPUBLIC " + dentry )
        fhandle.write( "\n\tPUBLIC " + lib_name )
        fhandle.write( "\n\tPRIVATE Threads::Threads" )
        fhandle.write("\n)\n")

print( "Wrote " + output_file + "." )
