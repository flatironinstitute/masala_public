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

## @file code_templates/generate_library_api.py
## @brief Used during the build process to produce the auto-generated API layer code.
## @details Usage:
##          python3 generate_library_api.py <source library name> <json api definition file>
## @note The source library name is something like "core".  This Python code would then
## produce code in "core_api/auto_generated_api/".  This file should be run from the Masala
## root directory.
## @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

from dbm.ndbm import library
import json
from re import split as regex_split
from sys import argv
import os

## @brief Parse the commandline options.
## @returns Source library name, JSON API definition file.  Throws if
## these two options aren't provided.
def get_options() -> tuple :
    assert len(argv) == 3, "Invalid commandline flags.  Expected usage: python3 generate_library_api.py <source library name> <json api definition file>"
    return (argv[1], argv[2])

## @brief Initialize the auto_generated_api directory, creating it if it does
## not exist and deleting anything in it if it does.
def initialize_directory( library_name : str ) -> None :
    assert os.path.isdir( "src/" + library_name + "_api" ), "Error in generate_library_api.py: Could not find directory \"src/" + library_name + "\".  Note that this script must be run from the Masala root directory."
    apidir = "src/" + library_name + "_api/auto_generated_api/"
    if os.path.isdir( apidir ) :
        print( "Found directory \"" + apidir + "\".  Clearing contents." )
        os.removedirs( apidir )
    else :
        print( "Creating \"" + apidir + "\"." )
    os.makedirs( apidir )
    
        

## @brief Given a namespace string of the form "XXXX::YYYY::ZZZZ", return a\
## list of [ "XXXX", "YYYY", "ZZZZ" ].
def separate_namespace( namespace_string ) -> list :
    return regex_split( "\:\:" , namespace_string )

################################################################################
## Program entry point
################################################################################

# Get options
library_name, api_def_file = get_options()
print( "Generating API for library \"" + library_name + "\" from API definition file \"" + api_def_file + "\"." )

# Read JSON
with open( api_def_file, 'r' ) as jfile :
    json_api = json.load( jfile )

initialize_directory( library_name )

for element in json_api["Elements"] :
    #print( element )
    namespace_string = json_api["Elements"][element]["ModuleNamespace"]
    name_string = json_api["Elements"][element]["Module"]
    namespace = separate_namespace( namespace_string )
    #print( namespace_string, name_string )
    #print( namespace )
    assert len(namespace) > 2
    assert namespace[0] == "masala", "Error!  All Masla classes (with or without APIs) are expected to be in base namespace \"masala\".  This doesn't seem to be so for " + namespace_string + "::" + name_string + "."
    assert namespace[1] == library_name, "Error!  All Masla classes in library " + library_name + " (with or without APIs) are expected to be in namespace \"masala::" + library_name + "\".  This doesn't seem to be so for " + namespace_string + "::" + name_string + "."