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

## @file code_templates/generate_cmake_build.py
## @brief Used during the build process to generate the cmake files for all the stuff that
## has to be compiled in a given library.  This also generates the cmake files for the
## associated API libraries.
## @details Recursively goes through directories and finds .cc files to compile.  Usage:
##          python3 generate_cmake_build.py <library name> <source dir> <output path and filename for cmake file> <output path and filename for cmake file for test, or NONE>
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

## @brief Given the name of a parent class, return the header file name (with .hh extension).
def parent_class_file_from_class_name( parent_class_name : str, libname : str ) -> str :
    if parent_class_name.startswith( libname + "::" ) :
        outstr = "../src/" + parent_class_name[ len(libname) + 2 : ].replace("::", "/") + ".hh"
    else :
        startpos = parent_class_name.find("::")
        assert startpos != -1
        outstr = "../headers/" + parent_class_name.split("::")[0] + "/headers/" + parent_class_name[ startpos + 2 : ].replace("::", "/") + ".hh"
    return outstr

## @brief Recursively scan a header file that defines a class to determine whether the class is
## a descendant of masala::base::managers::plugin_module::MasalaPlugin.
def is_plugin_class( headerfile : str, libname : str ) -> bool :
    #return False
    print( "\tChecking " + headerfile + " for plugin parent class." )
    assert headerfile.startswith( "../src/" ) or headerfile.startswith( "../headers/" )
    with open( headerfile, 'r' ) as fhandle:
        file_contents = fhandle.read()
    file_contents = ' '.join( purge_comments( file_contents ).split() ) #Put the file on a single line with all whitespace converted to spaces and comments removed.

    classname = path.basename( headerfile ).split('.')[0]

    class_declaration_position = file_contents.find( "class " + classname + " :" )
    if class_declaration_position == -1 :
        class_declaration_position = file_contents.find( "class " + classname + ":" )
        if class_declaration_position == -1 :
            assert file_contents.find( "class " + classname ) != -1, "Could not find class declaration for class \"" + classname + "\" in file " + headerfile + "!"
            print( "\t\tFound no plugin parent class.  Will NOT auto-generate Creator class." )
            return False # This class has no parent.
        else :
            parent_index = 3
    else :
        parent_index = 4
    
    parent_class_name = file_contents[class_declaration_position:].split()[parent_index]
    if parent_class_name == "masala::base::managers::plugin_module::MasalaPlugin" or parent_class_name == "base::managers::plugin_module::MasalaPlugin" :
        print( "\t\tFound plugin parent class!  Will auto-generate Creator class." )
        return True

    parent_class_file = parent_class_file_from_class_name( parent_class_name, libname )
    return is_plugin_class( parent_class_file, libname ) #Recursive call.

## @brief From a filename, generate the name of the corresponding api file
## or creator file.
## @details Omits extension.
def apiname_or_creatorname_from_filename( fname : str, do_creator : bool ) -> str :
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
            if do_creator == True :
                newname += "/" + entrysplit[0] + "Creator"
            else :
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
    else :
        if dirname.endswith( libname + "/auto_generated_api" ) or dirname.endswith( libname + "/auto_generated_api/" ) :
            return []
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
                    (concatname != "../src/base/MasalaObject.cc") :
                if has_api_definition(fname, concatname) :
                    apiname = apiname_or_creatorname_from_filename( concatname, False )
                    outlist_apis.append( apiname + ".cc" )
                    outlist_apis.append( apiname + ".hh" )
                    outlist_apis.append( apiname + ".fwd.hh" )
                    if is_plugin_class( concatname[:-3] + ".hh", libname ) :
                        creatorname = apiname_or_creatorname_from_filename( concatname, True )
                        outlist_apis.append( creatorname + ".cc" )
                        outlist_apis.append( creatorname + ".hh" )
                        outlist_apis.append( creatorname + ".fwd.hh" )
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

assert len(argv) == 7, errmsg + "Incorrect number of arguments.   python3 generate_cmake_build.py <project name> <library name> <source dir> <output path and filename for cmake file> <output path and filename for API cmake file or NONE> <output path and filename for cmake file for test, or NONE>."

project_name = argv[1]
lib_name = argv[2]
source_dir = argv[3]
output_file = argv[4]
output_file_api = argv[5]
if output_file_api == "NONE" :
    output_file_api = None
output_file_tests = argv[6]
if output_file_tests == "NONE" :
    output_file_tests = None

cclist, api_cclist = get_all_cc_and_hh_files_in_dir_and_subdirs( lib_name, source_dir, True )
if output_file_api is not None :
    api_cclist.extend( get_all_cc_and_hh_files_in_dir_and_subdirs( lib_name + "_api", source_dir + "_api", False ) )
depend_list = get_library_dependencies( source_dir )

appsdir = source_dir + "/" + lib_name + "_apps"
if path.isdir( appsdir ) :
    print( "\tChecking " + appsdir + " for apps." )
    appslist = get_all_cc_and_hh_files_in_dir_and_subdirs( lib_name, appsdir, False )
else :
    appslist = []

testsdir = "../tests/unit/" + lib_name
testlibname = lib_name + "_tests"
if output_file_tests != None :
    assert path.isdir( testsdir )
    print( "\tChecking " + testsdir + " for tests." )
    testslist = get_all_cc_and_hh_files_in_dir_and_subdirs( testlibname, testsdir, False )
    test_depend_list = get_library_dependencies( testsdir )
else :
    testslist = []

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

if len(api_cclist) > 0 and output_file_api != None :
    with open( output_file_api, 'w' ) as fhandle :
        fhandle.write( "ADD_CUSTOM_COMMAND(\n" )
        fhandle.write( "\tDEPENDS generate_" + lib_name + "_api POST_BUILD\n" )
        fhandle.write( "\tOUTPUT\n" )
        for entry in api_cclist :
            fhandle.write( "\t\t" + entry + "\n" )
        fhandle.write( "\tCOMMAND echo \"Generating JSON description of " + lib_name + " API.\"\n" )
        fhandle.write( "\tCOMMAND ./generate_" + lib_name + "_api\n" )
        fhandle.write( "\tCOMMAND echo \"Auto-generating " + lib_name + " API C++ code.\"\n" )
        fhandle.write( "\tCOMMAND sh -c \"cd .. && python3 code_templates/generate_library_api.py " + project_name + " "  + lib_name + " build/" + lib_name + "_api.json && cd build\"\n")
        fhandle.write( "\tVERBATIM\n)\n\n" )

        fhandle.write( "ADD_LIBRARY(" + lib_name + "_api SHARED" )
        for entry in api_cclist :
            fhandle.write( "\n\t" + entry )
        fhandle.write( "\n)\n" )
        fhandle.write( "SET_TARGET_PROPERTIES(" + lib_name + "_api PROPERTIES VERSION ${PROJECT_VERSION})\n" )
        fhandle.write( "TARGET_LINK_LIBRARIES(" + lib_name + "_api" )
        fhandle.write( "\n\tPUBLIC " + lib_name )
        if len(depend_list) > 0 :
            for dentry in depend_list :
                fhandle.write( "\n\tPUBLIC " + dentry )
        fhandle.write( "\n\tPRIVATE Threads::Threads" )
        fhandle.write("\n)\n")


if len(testslist) > 0 :
    assert output_file_tests != None
    with open( output_file_tests, 'w' ) as fhandle:
        if len(testslist) > 0 :
            fhandle.write( "ADD_EXECUTABLE(" + testlibname + " " )
            for entry in testslist:
                fhandle.write( "\n\t" + entry )
            fhandle.write( "\n)\n" )
            fhandle.write( "SET_TARGET_PROPERTIES(" + testlibname + " PROPERTIES VERSION ${PROJECT_VERSION})\n" )

            fhandle.write( "TARGET_LINK_LIBRARIES(" + testlibname )
            fhandle.write( "\n\tPUBLIC " + lib_name )
            for dentry in test_depend_list :
                fhandle.write( "\n\tPUBLIC " + dentry )
            fhandle.write( "\n\tPRIVATE Threads::Threads" )
            fhandle.write("\n)\n")


print( "Wrote " + output_file + "." )
