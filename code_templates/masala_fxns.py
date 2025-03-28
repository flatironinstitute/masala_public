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

## @file code_templates/masala_fxns.py
## @brief Utility functions used by generate_cmake_build.py and generate_library_api.py.
## @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

from os import path

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

## @brief Given the name of a parent class, return the header file name (with .hh extension).
def parent_class_file_from_class_name( parent_class_name : str, project_name : str, seek_plugin : bool) -> str :
    #print( project_name + " *********")
    if parent_class_name.startswith( project_name + "::" ) :
        if seek_plugin == True :
            outstr = "../src/" + parent_class_name[ len(project_name) + 2 : ].replace("::", "/") + ".hh"
        else :
            outstr = "./src/" + parent_class_name[ len(project_name) + 2 : ].replace("::", "/") + ".hh"
    else :
        startpos = parent_class_name.find("::")
        assert startpos != -1
        if seek_plugin == True:
            outstr = "../headers/" + parent_class_name.split("::")[0] + "/headers/" + parent_class_name[ startpos + 2 : ].replace("::", "/") + ".hh"
        else :
            outstr = "./headers/" + parent_class_name.split("::")[0] + "/headers/" + parent_class_name[ startpos + 2 : ].replace("::", "/") + ".hh"
    return outstr

## @brief Recursively scan a header file that defines a class to determine whether the class is
## a descendant of masala::base::managers::plugin_module::MasalaPlugin (if seek_plugin is True)
## or masala::base::MasalaNoAPIObject (if seek_plugin is False).
def is_plugin_or_noapi_class( headerfile : str, project_name : str, seek_plugin : bool ) -> bool :
    if seek_plugin == True :
        print( "\tChecking " + headerfile + " for plugin parent class." )
        assert headerfile.startswith( "../src/" ) or headerfile.startswith( "../headers/" )
    else :
        print( "\tChecking " + headerfile + " for MasalaNoAPIObject parent class." )
        assert headerfile.startswith( "./src/" ) or headerfile.startswith( "./headers/" )
    with open( headerfile, 'r' ) as fhandle:
        file_contents = fhandle.read()
    file_contents = ' '.join( purge_comments( file_contents ).split() ) #Put the file on a single line with all whitespace converted to spaces and comments removed.

    classname = path.basename( headerfile ).split('.')[0]

    class_declaration_position = file_contents.find( "class " + classname + " :" )
    if class_declaration_position == -1 :
        class_declaration_position = file_contents.find( "class " + classname + ":" )
        if class_declaration_position == -1 :
            assert file_contents.find( "class " + classname ) != -1, "Could not find class declaration for class \"" + classname + "\" in file " + headerfile + "!"
            if seek_plugin == True :
                print( "\t\tFound no plugin parent class.  Will NOT auto-generate Creator class." )
            else :
                print( "\t\tFound no MasalaNoAPIObject parent class.  Object is NOT a non-API object." )
            return False # This class has no parent or is not derived from MasalaNoAPIObject.
        else :
            parent_index = 3
    else :
        parent_index = 4
    
    parent_class_name = file_contents[class_declaration_position:].split()[parent_index]
    if seek_plugin == True :
        if parent_class_name == "masala::base::managers::plugin_module::MasalaPlugin" or parent_class_name == "base::managers::plugin_module::MasalaPlugin" :
            print( "\t\tFound plugin parent class!  Will auto-generate Creator class." )
            return True
    else :
        if parent_class_name == "masala::base::MasalaNoAPIObject" or parent_class_name == "base::MasalaNoAPIObject" :
            print( "\t\tClass is derived from MasalaNoAPIObject." )
            return True

    parent_class_file = parent_class_file_from_class_name( parent_class_name, project_name, seek_plugin )
    return is_plugin_or_noapi_class( parent_class_file, project_name, seek_plugin ) #Recursive call.