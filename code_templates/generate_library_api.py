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

## @file code_templates/generate_library_api.py
## @brief Used during the build process to produce the auto-generated API layer code.
## @details Usage:
##          python3 generate_library_api.py <source library name> <json api definition file>
## @note The source library name is something like "core".  This Python code would then
## produce code in "core_api/auto_generated_api/".  This file should be run from the Masala
## root directory.
## @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

from genericpath import isdir
import json
from re import split as regex_split
from sys import argv
import os
import shutil
import re
from masala_fxns import is_plugin_or_noapi_class, parent_class_file_from_class_name

VERBOSE_SCRIPT_OUTPUT = False
COLUMN_WIDTH = 120

INTACT = 0
DEPRECATION_WARNING = 1
DEPRECATED = 2

### @brief Determine whether an element is intact, soon to be deprecated, or deprecated.
def determine_deprecation_status( \
    element_properties : json, \
    project_maj_version : int, \
    project_min_version : int
    ) -> int :

    if "Will_Be_Deprecated" in element_properties :
        if element_properties["Will_Be_Deprecated"] == True :
            assert "Deprecation_Major_Version" in element_properties
            assert "Deprecation_Minor_Version" in element_properties
            dep_maj_vers = element_properties["Deprecation_Major_Version"]
            dep_min_vers = element_properties["Deprecation_Minor_Version"]
            if ( project_maj_version > dep_maj_vers ) or ( project_maj_version == dep_maj_vers and project_min_version >= dep_min_vers ) :
                return DEPRECATED
            if "Deprecation_Warning_Major_Version" in element_properties :
                assert "Deprecation_Warning_Minor_Version" in element_properties
                dep_warn_maj_vers = element_properties["Deprecation_Warning_Major_Version"]
                dep_warn_min_vers = element_properties["Deprecation_Warning_Minor_Version"]
                if ( project_maj_version > dep_warn_maj_vers ) or ( project_maj_version == dep_warn_maj_vers and project_min_version >= dep_warn_min_vers ) :
                    return DEPRECATION_WARNING
    return INTACT

### @brief Given a comment line, wrap it to fit an 80-character output, returning a series of new lines.
def wrap_comment_line( line : str ) -> [] :
    if len(line) <= COLUMN_WIDTH :
        return [line]
    
    initial_whitespace = ""
    for i in range(len(line)) :
        if line[i] == "/" :
            break
        initial_whitespace += line[i]

    effective_column_width = max( COLUMN_WIDTH - len(initial_whitespace) - 4, 1 )
    
    start = 0
    first = True
    breaknow = False
    newlines = []

    counter = 0

    while start < len(line) :
        for i in range(effective_column_width) :
            curpos = start + i
            if curpos == len(line) :
                breaknow = True
                break

            if line[curpos] == "\t" :
                counter += 4
            else :
                counter += 1
            if counter == effective_column_width :
                counter = curpos
                break
        
        if breaknow == True :
            if first == True :
                newlines.append( line[start:] )
                first = False
            else :
                # newlines.append( initial_whitespace + "/// " + line[start:] )
                startprime = start
                while( startprime < len(line) ) :
                    #print( line[startprime] )
                    if line[startprime] == "\t" or line[startprime] == " " :
                        startprime += 1
                    else :
                        break
                if startprime < len(line) :
                    newlines.append( initial_whitespace + "/// " + line[startprime:] )
            break
        else :
            found_space = False
            for i in range( counter, start + round(COLUMN_WIDTH/5), -1 ) :
                if( i == "\t" or i == " " ) :
                    counter = i
                    found_space = True
                    break
            
            if found_space == False:
                while( counter < len(line) ) :
                    if line[counter] == " " or line[counter] == "\t" :
                        break
                    counter += 1

            if first == True :
                newlines.append( line[start:counter] )
                first = False
            else :
                startprime = start
                while( startprime < len(line) ) :
                    if line[startprime] == "\t" or line[startprime] == " " :
                        startprime += 1
                    else :
                        break
                if startprime < len(line) :
                    if startprime < counter :
                        newlines.append( initial_whitespace + "/// " + line[startprime:counter])
                    else :
                        newlines.append( initial_whitespace + "/// " + line[startprime:])
                        break
                else :
                    break
            start = counter + 1
            counter = 0
    
    return newlines


### @brief Clean up the generated code.
### @details Currently, only wraps long comment lines.  Could do more in the future.
def clean_up_generated_code( filecontents : str ) -> str :
    filelines = filecontents.splitlines()
    fileconents_out = ""
    for line in filelines :
        linestripped = line.strip()
        if len(linestripped) > 3 and linestripped[0] == '/' and linestripped[1] == '/' and linestripped[2] == '/' :
            newlines = wrap_comment_line( line )
            #print( newlines )
            for newline in newlines :
                fileconents_out += newline + "\n"
        else :
            fileconents_out += line + "\n"
    return fileconents_out

## @brief Parse the commandline options.
## @returns Source library name, JSON API definition file.  Throws if
## these two options aren't provided.
def get_options() -> tuple :
    assert len(argv) == 6, "Invalid commandline flags.  Expected usage: python3 generate_library_api.py <project name> <project major version> <project minor version> <source library name> <json api definition file>"
    return (argv[1], int(argv[2]), int(argv[3]), argv[4], argv[5] )

## @brief Returns true if a class starts with "masala::" or with project_name + "::".
## Always returns false if this is an API class.
def is_masala_class( project_name : str, classname : str ) -> bool :
    classname_split = classname.replace("::", " ").split()
    if len( classname_split ) > 2 and classname_split[1].endswith( "_api" ) :
        return False
    if classname.startswith( "masala::" ) : return True
    if classname.startswith( project_name + "::" ) : return True
    return False

## @brief Determine whether a class derives from a masala plugin class base.
## @details Assumes that "const" has been trimmed from class_namespace_and_name.
def is_masala_plugin_class( \
    project_name : str, \
    library_name : str, \
    class_namespace_and_name : str, \
    jsonfile : json \
    ) -> bool :
    namesplit = class_namespace_and_name.split("::")
    if( namesplit[0] == project_name and namesplit[1] == library_name ) :
        if class_namespace_and_name in jsonfile["Elements"] :
            if jsonfile["Elements"][class_namespace_and_name]["Properties"]["Is_Plugin_Class"] == True :
                return True
            else :
                return False

    # Check the class inheritence:
    #print(namesplit) # DELETE ME
    if namesplit[0] != project_name :
        fname = "headers/" + namesplit[0] + "/headers/" + namesplit[1]
    else :
        fname = "src/" + namesplit[1]
    for i in range (2, len(namesplit)) :
        fname += "/" + namesplit[i]
    fname += ".hh"
    if VERBOSE_SCRIPT_OUTPUT == True :
        print( "\tLoading " + fname )
    fcontents = slurp_file_and_remove_comments( fname ).replace( "{", " { " ).replace( "}", " } " ).replace( "(", " ( " ).replace( ")", " ) " ).replace( "<", " < " ).replace( ">", " > " ).replace( ";", " ; " ).split()
    #print( fcontents ) # DELETE ME
    parentclass = None
    for i in range( len(fcontents) - 4 ) :
        if fcontents[i] == "class" and \
            fcontents[i+1] == namesplit[len(namesplit)-1] and \
            fcontents[i+2] == ":" and \
            fcontents[i+3] == "public" :
            parentclass = fcontents[i+4]
            break
    #print( parentclass ) # DELETE ME
    if parentclass == None : return False
    elif parentclass == "masala::base::managers::plugin_module::MasalaPlugin" : return True

    return is_masala_plugin_class( project_name, library_name, parentclass, jsonfile )

## @brief Returns true if a class is a masala API class (i.e. follows pattern
## "masala::*_api::" ).
def is_masala_api_class( classname : str ) -> bool :
    if classname.startswith( "masala::" ) == False :
        return False
    classname_split = classname.split()[0].replace("::", " ").split()
    if len(classname_split) > 2 and classname_split[1].endswith("_api") :
        return True
    return False

## @brief Read a C++ file and remove comments, returning a string of file contents.
def slurp_file_and_remove_comments( filename : str ) -> str :
    with open( filename, 'r' ) as filehandle :
        filecontents = filehandle.read()
    
    # Remove anything between /* and */ or bewteen // and \n
    # (Shamelessly taken from stackexchange).
    comments = re.compile( r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"', re.DOTALL | re.MULTILINE )

    return comments.sub( ' ', filecontents )
    


## @brief Initialize the auto_generated_api directory, creating it if it does
## not exist and deleting anything in it if it does.
## @brief Puts a README.txt file in the directory indicating that it is auto-
## generated, and that no one should put anything in there manually.
def initialize_directory( library_name : str ) -> None :
    assert os.path.isdir( "src/" + library_name + "_api" ), "Error in generate_library_api.py: Could not find directory \"src/" + library_name + "\".  Note that this script must be run from the Masala root directory."
    apidir = "src/" + library_name + "_api/auto_generated_api/"
    if os.path.isdir( apidir ) :
        print( "\tFound directory \"" + apidir + "\".  Clearing contents." )
        shutil.rmtree( apidir )
    else :
        print( "\tCreating \"" + apidir + "\"." )
    os.makedirs( apidir )
    with open( apidir + "README.txt", 'w' ) as filehandle:
        filehandle.write( "Directory \"" + apidir + "\" is auto-generated by the build process.\n" )
        filehandle.write( "Do not put anything in this directory manually, since it is cleared and regenerated\n" )
        filehandle.write( "each time the build occurs.\n" )
    print( "\tWrote \"" + apidir + "README.txt.\"" )
    
## @brief Given a namespace for a class, create a directory in the auto-
## generated API directory with directory structure matching the
## namespace.  If the directory already exists, do nothing.
## @returns The directory name, for reuse later.
def prepare_directory( project_name : str, libname : str, namespace : list ) -> str :
    assert namespace[0] == project_name
    assert namespace[1] == libname
    dirname = "src/" + libname + "_api/auto_generated_api/"
    for i in range( 2, len(namespace) ) :
        dirname += namespace[i] + "/"
    if os.path.isdir( dirname ) == False :
        print( "\tCreating \"" + dirname + "\"." )
        os.makedirs( dirname )
    else :
        print( "\tDirectory \"" + dirname + "\" already exists.  Skipping creation." )
    return dirname

## @brief Given a namespace string of the form "XXXX::YYYY::ZZZZ", return a\
## list of [ "XXXX", "YYYY", "ZZZZ" ].
def separate_namespace( namespace_string ) -> list :
    return regex_split( "\:\:" , namespace_string )

## @brief Read a file and return its contents as a string.
def read_file( filename : str ) -> list :
    with open( filename, 'r' ) as filehandle :
        filecontents = filehandle.read()
    if VERBOSE_SCRIPT_OUTPUT == True :
        print( "\tRead contents of \"" + filename + "\" into memory." )
    return filecontents

## @brief Determine whether an object is an API type, and if so, access the
## class type inside.
def access_needed_object( project_name: str, classname : str, instancename : str, jsonfile : json ) -> str :
    #print( "*** Checking " + classname + " ***" ) # DELETE ME
    if is_masala_class( project_name, classname ) == False :
        #print( "*** " + classname + " is not a Masala class ***" ) # DELETE ME
        if classname.startswith( "MASALA_SHARED_POINTER" ) :
            firstchevron = classname.find( "<" )
            lastchevron = classname.rfind( ">" )
            innerclass = classname[firstchevron+1:lastchevron].strip()
            if is_masala_class( project_name, innerclass ) :
                return instancename + "->get_inner_object()"
        return instancename #Not an API class
    if is_known_masala_base_enum( classname ) :
        return instancename
    classtype = classname.split()[0]
    if classtype == "masala::base::MasalaAPI" :
        return instancename
    
    if is_plugin_or_noapi_class( parent_class_file_from_class_name( classtype, project_name, False ), project_name, False ) :
        #print( classtype + " IS a no-API Masala object." )
        return instancename
    #else :
    #    print( classtype + " is not a no-API Masala object." )

    assert classtype in jsonfile["Elements"], "Error!  Class " + classtype + " is not defined in the JSON file!"
    if jsonfile["Elements"][classtype]["Properties"]["Is_Lightweight"]:
        return instancename + ".get_inner_object()"
    return "*( " + instancename + ".get_inner_object() )"

## @brief Given a Masala type that may contain "const", drop the const.
def drop_const( classname: str )-> str :
    classname_split = classname.split()
    outstr = ""
    first = True
    for entry in classname_split :
        if entry != "const" :
            if first == False :
                outstr += " "
            else :
                first = False
            outstr += entry
    return outstr

## @brief Add a Masala header to the list of additional headers to include.
def add_base_class_include( project_name : str, inputclass : str , additional_includes: list ) -> None :
    if is_masala_class( project_name, inputclass ) == False :
        # Do nothing.
        return
    includefile = inputclass[ inputclass.find("::") + 2 : ].replace( "::", "/" )
    if includefile not in additional_includes :
        additional_includes.append(includefile)

## @brief Given a class namespace and name, get a directory name.
def directory_and_name_from_namespace_and_name( namespace_and_name : str ) :
    namesplit = namespace_and_name.replace("::", " ").split()
    dirname = ""
    assert len(namesplit) > 2
    assert namesplit[0] == "masala"
    for i in range( 1, len(namesplit) - 1 ) :
        dirname += namesplit[i]
        if i < len(namesplit) - 2 :
            dirname += "/"
    return dirname, namesplit[len(namesplit) -1]

# ## @brief Given an enum class, find the forward header that defines it.
# def find_enum_fwd_declarations( additional_includes : list, enum_namespace_and_name : str ) -> None :
#     enum_directory, enum_name = directory_and_name_from_namespace_and_name( enum_namespace_and_name )

#     if VERBOSE_SCRIPT_OUTPUT == True :
#         print( "Searching for forward declaration that defines " + enum_name + " enum class in directory " + enum_directory + "." )
#     found = False
#     for filename in os.listdir( "src/" + enum_directory ) :
#         if filename.endswith(".fwd.hh") == False :
#             continue
#         with open( "src/" + enum_directory + "/" + filename, 'r' ) as filehandle:
#             filelines = filehandle.readlines()
#         for line in filelines :
#             if line.find( "enum" ) != -1 :
#                 linesplit = line.split()
#                 if len(linesplit) < 3 :
#                     continue
#                 for i in range( len(linesplit)-2 ) :
#                     if linesplit[i] == "enum" :
#                         if linesplit[i+1] == "class" and linesplit[i+2] == enum_name :
#                             found = True
#                             fname_sans_end = enum_directory + "/" + filename[:-7]
#                             if fname_sans_end not in additional_includes :
#                                 additional_includes.append(fname_sans_end)
#                             break
#     assert found == True, "Could not find file that defines enum class " + enum_name + "."

## @brief Given an API class, figure out the file to include.
## @note Return value does not include extension.
def include_file_from_masala_api_class( inputclass : str ) -> str :
    assert inputclass.startswith( "masala::" ), "Expected " + inputclass + " to start with masala::, but it did not!"
    inputclass_split = inputclass.split()[0].replace("::", " ").split()
    assert len(inputclass_split) > 1
    outfile = ""
    for i in range(1,len(inputclass_split)) :
        if i > 1 :
            outfile += "/"
        outfile += inputclass_split[i]
    return outfile

## @brief Given the definition of an unordered map, find the first and last chevrons, and the (one or two) commas.
## @details If the second comma is not present, return -1 for its position.
def parse_unordered_map( inputclass : str ) -> tuple :
    inchevron = False
    inchevron2 = 0
    stringcopy = ""
    for i in range(0, len(inputclass) ) :
        if inchevron == False :
            if inputclass[i] == "<" :
                inchevron = True
                stringcopy += inputclass[i]
            else :
                stringcopy += "#"
        else :
            if inchevron2 == 0 :
                if inputclass[i] == "<" :
                    inchevron2 = True
                    stringcopy += "#"
                elif inputclass[i] == ">" :
                    inchevron = False
                    stringcopy += inputclass[i]
                else :
                    stringcopy += inputclass[i]
            else :
                if inputclass[i] == ">" :
                    inchevron2 -= 1
                    stringcopy += "#"
                elif inputclass[i] == "<" :
                    inchevron2 += 1
                    stringcopy += "#"
                else :
                    stringcopy += "#"
    firstchevron = stringcopy.find( "<" )
    lastchevron = stringcopy.rfind( ">" )
    firstcomma = stringcopy.find( "," )
    lastcomma = stringcopy.rfind( "," )
    if lastcomma == firstcomma :
        lastcomma = -1

    return firstchevron, lastchevron, firstcomma, lastcomma

## @brief Given a class name, construct the name of the API class (if it is a Masala class)
## or do nothing (if it is not a Masala class.)
## @details Has certain exceptions, like masala::base::api::MasalaObjectAPIDefinition.
## @note As a side-effect, this populates the additional_includes list with files to include
## for the additional API classes.  Each entry added is first checked so that it is not added
## multiple times.  The extension (.hh or .fwd.hh) is omitted.
def correct_masala_types( project_name: str, inputclass : str, additional_includes: list ) -> str :
    #print( inputclass )

    # Special case for MasalaObjectAPI
    if inputclass.startswith( "masala::base::MasalaObjectAPI" ):
        additional_includes.append( "<base/MasalaObjectAPI.hh>" )
        return inputclass
    
    # Special case for MasalaPluginAPI
    if inputclass.startswith( "masala::base::managers::plugin_module::MasalaPluginAPI" ):
        additional_includes.append( "<base/managers/plugin_module/MasalaPluginAPI.hh>" )
        return inputclass

    # Special case for MasalaEngineAPI
    if inputclass.startswith( "masala::base::managers::engine::MasalaEngineAPI" ):
        additional_includes.append( "<base/managers/engine/MasalaEngineAPI.hh>" )
        return inputclass
    
    # Special case for MasalaDataRepresentationAPI
    if inputclass.startswith( "masala::base::managers::engine::MasalaDataRepresentationAPI" ):
        additional_includes.append( "<base/managers/engine/MasalaDataRepresentationAPI.hh>" )
        return inputclass

    if is_masala_class( project_name, inputclass ) == False :
        if inputclass.startswith( "MASALA_SHARED_POINTER" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            return "MASALA_SHARED_POINTER< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : lastchevron].strip(), additional_includes ) + " " + inputclass[lastchevron:]
        elif inputclass.startswith( "Eigen::Matrix<" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            secondcomma = inputclass.rfind( ",", 0, lastchevron )
            firstcomma = inputclass.rfind( ",", 0, secondcomma )
            additional_includes.append("<external/eigen/Eigen/Dense>")
            return "Eigen::Matrix< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : firstcomma].strip(), additional_includes ) + inputclass[firstcomma:]
        elif inputclass.startswith( "Eigen::Vector<" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            secondcomma = inputclass.rfind( ",", 0, lastchevron )
            firstcomma = inputclass.rfind( ",", 0, secondcomma )
            additional_includes.append("<external/eigen/Eigen/Core>")
            return "Eigen::Vector< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : firstcomma].strip(), additional_includes ) + inputclass[firstcomma:]
        elif inputclass.startswith( "vector" ) or inputclass.startswith( "std::vector" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            additional_includes.append("<vector>")
            return "std::vector< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : lastchevron].strip(), additional_includes ) + " " + inputclass[lastchevron:]
        elif inputclass.startswith( "function" ) or inputclass.startswith( "std::function" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            additional_includes.append("<functional>")
            return "std::function< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : lastchevron].strip(), additional_includes ) + " " + inputclass[lastchevron:]
        elif inputclass.startswith( "pair" ) or inputclass.startswith( "std::pair" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            lastcomma = inputclass.rfind( ",", 0, lastchevron )
            if( "<utility>" not in additional_includes ) :
                additional_includes.append("<utility>")
            return "std::pair< " \
                + correct_masala_types( project_name, inputclass[firstchevron + 1 : lastcomma].strip(), additional_includes ) \
                + ", " \
                + correct_masala_types( project_name, inputclass[lastcomma + 1 : lastchevron].strip(), additional_includes ) \
                + inputclass[lastchevron:]
        elif inputclass.startswith( "set" ) or inputclass.startswith( "std::set" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            additional_includes.append("<set>")
            return "std::set< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : lastchevron].strip(), additional_includes ) + " " + inputclass[lastchevron:]
        elif inputclass.startswith( "list" ) or inputclass.startswith( "std::list" ) :
            firstchevron = inputclass.find( "<" )
            lastchevron = inputclass.rfind( ">" )
            additional_includes.append("<list>")
            return "std::list< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : lastchevron].strip(), additional_includes ) + " " + inputclass[lastchevron:]
        elif inputclass.startswith( "map" ) or inputclass.startswith( "std::map" ) :
            firstchevron, lastchevron, firstcomma, lastcomma = parse_unordered_map( inputclass )
            additional_includes.append("<map>")
            if( lastcomma == -1 ) :
                return "std::map< " \
                    + correct_masala_types( project_name, inputclass[firstchevron + 1 : firstcomma].strip(), additional_includes ) \
                    + ", " \
                    + correct_masala_types( project_name, inputclass[firstcomma + 1 : lastchevron].strip(), additional_includes ) \
                    + " >"
            else :
                return "std::map< " \
                    + correct_masala_types( project_name, inputclass[firstchevron + 1 : firstcomma].strip(), additional_includes ) \
                    + ", " \
                    + correct_masala_types( project_name, inputclass[firstcomma + 1 : lastcomma].strip(), additional_includes ) \
                    + ", " \
                    + correct_masala_types( project_name, inputclass[lastcomma + 1 : lastchevron].strip(), additional_includes ) \
                    + " >"
        elif inputclass.startswith( "unordered_map" ) or inputclass.startswith( "std::unordered_map" ) :
            firstchevron, lastchevron, firstcomma, lastcomma = parse_unordered_map( inputclass )
            additional_includes.append("<unordered_map>")
            if( lastcomma == -1 ) :
                return "std::unordered_map< " \
                    + correct_masala_types( project_name, inputclass[firstchevron + 1 : firstcomma].strip(), additional_includes ) \
                    + ", " \
                    + correct_masala_types( project_name, inputclass[firstcomma + 1 : lastchevron].strip(), additional_includes ) \
                    + " >"
            else :
                return "std::unordered_map< " \
                    + correct_masala_types( project_name, inputclass[firstchevron + 1 : firstcomma].strip(), additional_includes ) \
                    + ", " \
                    + correct_masala_types( project_name, inputclass[firstcomma + 1 : lastcomma].strip(), additional_includes ) \
                    + ", " \
                    + correct_masala_types( project_name, inputclass[lastcomma + 1 : lastchevron].strip(), additional_includes ) \
                    + " >"
        # elif inputclass.startswith( "std::MASALA_WEAK_POINTER" ) :
        #     firstchevron = inputclass.find( "<" )
        #     lastchevron = inputclass.rfind( ">" )
        #     return "std::MASALA_WEAK_POINTER< " + correct_masala_types( project_name, inputclass[firstchevron + 1 : lastchevron].strip(), additional_includes ) + " >"
        if is_masala_api_class( inputclass ) :
            additional_includes.append( include_file_from_masala_api_class( inputclass ) )
        return inputclass # Do nothing if ths isn't a masala class.

    # Special case for hashes:
    if inputclass.startswith( "size_pair_hash" ) or inputclass.startswith( "base::size_pair_hash" ) or inputclass.startswith( "masala::base::size_pair_hash" ) :
        additional_includes.append( "<base/hash_types.hh>" )
        return "masala::base::size_pair_hash"

    if is_known_masala_base_enum( inputclass ) :
        enum_filename = include_file_for_known_masala_base_enum( inputclass )
        if enum_filename not in additional_includes :
            additional_includes.append( enum_filename )
        return inputclass

    api_classname = ""
    api_filename = ""
    firstspace = inputclass.find(" ")
    if firstspace == -1 :
        inputclass_base = inputclass
        inputclass_extension = ""
    else :
        inputclass_base = inputclass[0:firstspace]
        inputclass_extension = inputclass[firstspace + 1:]
    inputclass_split = inputclass_base.split("::")
    assert len(inputclass_split) > 2
    inputclass_header = ""
    for i in range( len(inputclass_split) ) :
        if i == 0 :
            if inputclass_split[0] == project_name :
                inputclass_header_start = "./src/"
            else :
                assert inputclass_split[0] == "masala", "Expected input class \"masala\", but got \"" + inputclass_split[0] + "\"."
                inputclass_header_start = "./headers/masala/headers/"
            continue # Skip "masala" or library name
        inputclass_header += inputclass_split[i]
        if i < len(inputclass_split) - 1 :
            inputclass_header += "/"

    non_api_class = is_plugin_or_noapi_class( inputclass_header_start + inputclass_header + ".hh", project_name, False )
    if non_api_class == True :
        api_filename = inputclass_header

    for i in range(len(inputclass_split)) :
        curstring = inputclass_split[i]
        api_classname += curstring
        if i == 0 :
            api_classname += "::"
            continue # Skip "masala" or library name
        if non_api_class == False :
            api_filename += curstring
        if i == 1 and non_api_class == False :
            api_classname += "_api::auto_generated_api"
            api_filename += "_api/auto_generated_api"
        if i == len(inputclass_split) - 1 :
            if non_api_class == False :
                api_classname += "_API"
                api_filename += "_API"
        else :
            api_classname += "::"
            if non_api_class == False :
                api_filename += "/"
    if api_filename not in additional_includes :
        additional_includes.append( api_filename )
    if len(inputclass_extension) > 0 :
        return api_classname + " " + inputclass_extension
    return api_classname

    

## @brief Given the namespace as a list of strings, generate the C++ namespace lines.
## @details If opening_parentheses is true, we generate the parentheses that open the
## namespace.  Otherwise, we generate the parentheses that close the namespace.
def generate_cpp_namespace( namespace: list, opening_parentheses : bool ) -> str :
    outstr = ""
    for i in range( len(namespace) ) :
        if opening_parentheses == True :
            outstr += "namespace " + namespace[i]
            if i == 1 :
                outstr += "_api {\nnamespace auto_generated_api"
            outstr += " {"
        else :
            curindex = len(namespace) - i - 1
            outstr += "} // namespace " + namespace[curindex]
            if curindex == 1 :
                outstr += "_api\n} // namespace auto_generated_api"
        outstr += "\n"
    return outstr

## @brief Given the namespace as a list of strings, generate the C++ namespace for the API
## as a single line (separated by double colons):
def generate_cpp_namespace_singleline( namespace: list ) -> str :
    outstr = ""
    first = True
    for i in range( len( namespace ) ) :
        if first == True :
            first = False
        else :
            outstr += "::"
        outstr += namespace[i]
        if i == 1 :
            outstr += "_api::auto_generated_api"
    return outstr

## @brief Given a source class and namespace, generate the path and filename for a source file
## with a given extension.
def generate_source_class_filename( classname : str, namespace : list, extension : str ) -> str :
    assert len(namespace) >= 2
    outstr = ""
    for i in range( 1, len(namespace) ) :
        outstr += namespace[i]
        outstr += "/"
    outstr += classname + extension
    return outstr

## @brief Generate the prototypes for the constructors based on the JSON description of the API.
## @note The classname input should include namespace.
def generate_constructor_prototypes(project_name: str, classname: str, jsonfile: json, tabchar: str, additional_includes: list, proj_maj_vers : int, proj_min_vers : int) -> str :
    outstring = ""

    if jsonfile["Elements"][classname]["Properties"]["Has_Protected_Constructors"] == True :
        outstring += "protected:\n\n"
    else :
        outstring += "public:\n\n"

    first = True
    for constructor in jsonfile["Elements"][classname]["Constructors"]["Constructor_APIs"] :
        #print(constructor)
        if first :
            first = False
        else :
            outstring += "\n\n"
        outstring += tabchar + "/// @brief " + constructor["Constructor_Description"] + "\n"
        ninputs = constructor["Constructor_N_Inputs"]
        if ninputs > 0 :
            for i in range(ninputs) :
                outstring += tabchar + "/// @param[in] " + constructor["Inputs"]["Input_" + str(i)]["Input_Name"] + " " + constructor["Inputs"]["Input_" + str(i)]["Input_Description"] + "\n"
        outstring += tabchar + constructor["Constructor_Name"] + "_API("
        if ninputs > 0 :
            for i in range(ninputs) :
                if i > 0 :
                    outstring += ","
                outstring += "\n" + tabchar + tabchar + correct_masala_types( project_name, constructor["Inputs"]["Input_" + str(i)]["Input_Type"], additional_includes ) + " " + constructor["Inputs"]["Input_" + str(i)]["Input_Name"]
            outstring += "\n" + tabchar + ");"
        else :
            outstring += ");"
    return outstring

## @brief Generate the implementations for the constructors based on the JSON description of the API.
## @note The classname input should include namespace.
def generate_constructor_implementations(project_name: str, api_base_class : str, classname: str, jsonfile: json, tabchar: str, additional_includes: list, is_lightweight : bool,  is_derived : bool, is_plugin_class : bool, proj_maj_vers : int, proj_min_vers : int ) -> str :
    outstring = ""
    first = True

    for constructor in jsonfile["Elements"][classname]["Constructors"]["Constructor_APIs"] :
        #print(constructor)
        if first :
            first = False
        else :
            outstring += "\n\n"
        outstring += "/// @brief " + constructor["Constructor_Description"] + "\n"
        ninputs = constructor["Constructor_N_Inputs"]
        if ninputs > 0 :
            for i in range(ninputs) :
                outstring += "/// @param[in] " + constructor["Inputs"]["Input_" + str(i)]["Input_Name"] + " " + constructor["Inputs"]["Input_" + str(i)]["Input_Description"] + "\n"
        outstring += constructor["Constructor_Name"] + "_API::" + constructor["Constructor_Name"] + "_API("
        if ninputs > 0 :
            for i in range(ninputs) :
                if i > 0 :
                    outstring += ","
                outstring += "\n" + tabchar + correct_masala_types( project_name, constructor["Inputs"]["Input_" + str(i)]["Input_Type"], additional_includes ) + " " + constructor["Inputs"]["Input_" + str(i)]["Input_Name"]
            outstring += "\n" + ") :\n"
        else :
            outstring += ") :\n"
        
        # Initialization:
        if is_derived == True :
            outstring += tabchar + api_base_class + "( "
            if is_lightweight == True :
                outstring += classname + "("
            else:
                outstring += "masala::make_shared< " + classname + " >("
            if ninputs > 0 :
                for i in range(ninputs) :
                    outstring += " " + access_needed_object( project_name, constructor["Inputs"]["Input_" + str(i)]["Input_Type"], constructor["Inputs"]["Input_" + str(i)]["Input_Name"], jsonfile )
                    if i+1 < ninputs :
                        outstring += ","
                    else :
                        outstring += " "
            
            if is_lightweight == True :
                outstring +=")\n"
            else :
                outstring +=") )\n"
        else :
            outstring += tabchar + api_base_class + "(),\n"
            if is_lightweight == True :
                outstring += tabchar + "inner_object_("
            else:
                outstring += tabchar + "inner_object_( masala::make_shared< " + classname + " >("
            if ninputs > 0 :
                for i in range(ninputs) :
                    outstring += " " + access_needed_object( project_name, constructor["Inputs"]["Input_" + str(i)]["Input_Type"], constructor["Inputs"]["Input_" + str(i)]["Input_Name"], jsonfile )
                    if i+1 < ninputs :
                        outstring += ","
                    else :
                        outstring += " "
            
            if is_lightweight == True :
                outstring +=")\n"
            else :
                outstring +=") )\n"

        # Body:
        outstring += "{}"
    return outstring

## @brief Generate the prototypes for setters, getters, or work functions based on the JSON
## description of the API.
## @note The classname input should include namespace.  As a side-effect, this function appends to the
## additional_includes list.
def generate_function_prototypes( project_name: str, classname: str, jsonfile: json, tabchar: str, fxn_type: str, additional_includes: list, is_plugin_class : bool, is_engine_class : bool, is_data_representation_class : bool, is_file_interpreter_class : bool, proj_maj_vers : int, proj_min_vers : int ) -> str :
    outstring = ""
    first = True

    assert fxn_type == "SETTER" or fxn_type == "GETTER" or fxn_type == "WORKFXN"
    if fxn_type == "SETTER" :
        groupname = "Setters"
        namepattern = "Setter"
    elif fxn_type == "GETTER" :
        groupname = "Getters"
        namepattern = "Getter"
        if is_plugin_class :
            outstring += tabchar + "/// @brief Nonconst access to the inner plugin object.\n"
            outstring += tabchar + "masala::base::managers::plugin_module::MasalaPluginSP\n"
            outstring += tabchar + "get_inner_plugin_object_nonconst() override;\n\n"
            outstring += tabchar + "/// @brief Const access to the inner plugin object.\n"
            outstring += tabchar + "masala::base::managers::plugin_module::MasalaPluginCSP\n"
            outstring += tabchar + "get_inner_plugin_object() const override;\n\n"
    elif fxn_type == "WORKFXN" :
        groupname = "WorkFunctions"
        namepattern = "Work_Function"

    if fxn_type == "GETTER" :
        if is_data_representation_class == True :

            outstring += tabchar + "/// @brief Get the inner data representation object.\n"
            outstring += tabchar + "/// @note Use this function with care!  Holding a shared pointer to the inner\n"
            outstring += tabchar + "/// object can nullify the thread safety that the API object provides.\n"
            outstring += tabchar + "masala::base::managers::engine::MasalaDataRepresentationSP\n"
            outstring += tabchar + "get_inner_data_representation_object() override;\n"

            outstring += "\n"
            outstring += tabchar + "/// @brief Get the inner data representation object (const access).\n"
            outstring += tabchar + "/// @note Use this function with care!  Holding a const shared pointer to the inner\n"
            outstring += tabchar + "/// object can nullify the thread safety that the API object provides.\n"
            outstring += tabchar + "masala::base::managers::engine::MasalaDataRepresentationCSP\n"
            outstring += tabchar + "get_inner_data_representation_object_const() const override;\n"

            outstring += "\n"
            outstring += tabchar + "/// @brief Is the inner data representation object empty?\n"
            outstring += tabchar + "/// @returns True if the inner data representation object contains no data, false otherwise.\n"
            outstring += tabchar + "/// @note This does not report on whether the inner object has had configuration settings\n"
            outstring += tabchar + "/// set; only on whether it is devoid of data.\n"
            outstring += tabchar +  "bool\n"
            outstring += tabchar +  "inner_object_empty() const override;"

            first = False
        elif is_engine_class == True :
            outstring += tabchar + "/// @brief Get the inner engine object.\n"
            outstring += tabchar + "/// @note Use this function with care!  Holding a shared pointer to the inner\n"
            outstring += tabchar + "/// object can nullify the thread safety that the API object provides.\n"
            outstring += tabchar + "masala::base::managers::engine::MasalaEngineSP\n"
            outstring += tabchar + "get_inner_engine_object() override;\n"
            outstring += "\n"
            outstring += tabchar + "/// @brief Get the inner engine object (const access).\n"
            outstring += tabchar + "/// @note Use this function with care!  Holding a const shared pointer to the inner\n"
            outstring += tabchar + "/// object can nullify the thread safety that the API object provides.\n"
            outstring += tabchar + "masala::base::managers::engine::MasalaEngineCSP\n"
            outstring += tabchar + "get_inner_engine_object_const() const override;"
            first = False
        elif is_file_interpreter_class == True :
            outstring += tabchar + "/// @brief Get the inner file interpreter object.\n"
            outstring += tabchar + "/// @note Use this function with care!  Holding a shared pointer to the inner\n"
            outstring += tabchar + "/// object can nullify the thread safety that the API object provides.\n"
            outstring += tabchar + "masala::base::managers::file_interpreter::MasalaFileInterpreterSP\n"
            outstring += tabchar + "get_inner_file_interpreter_object() override;\n"
            outstring += "\n"
            outstring += tabchar + "/// @brief Get the inner file interpreter object (const access).\n"
            outstring += tabchar + "/// @note Use this function with care!  Holding a const shared pointer to the inner\n"
            outstring += tabchar + "/// object can nullify the thread safety that the API object provides.\n"
            outstring += tabchar + "masala::base::managers::file_interpreter::MasalaFileInterpreterCSP\n"
            outstring += tabchar + "get_inner_file_interpreter_object_const() const override;\n"
            outstring += "\n"
            outstring += tabchar + "/// @brief Get the descriptors for the file types that the file interpreter created by this creator manages.\n"
            outstring += tabchar + "/// @details Descriptors may be something like \"protein_data_bank_file\".  A given file interpreter may\n"
            outstring += tabchar + "/// manage more than one file type.\n"
            outstring += tabchar + "/// @note Must be implemented by derived classes.\n"
            outstring += tabchar + "std::vector< std::string >\n"
            outstring += tabchar + "get_file_interpreter_file_descriptors() const override;\n"
            outstring += "\n"
            outstring += tabchar + "/// @brief Get the extensions for the file types that the file interpreter created by this creator manages.\n"
            outstring += tabchar + "/// @details Extensions may be something like \"pdb\" (in lowercase).  A given file interpreter may\n"
            outstring += tabchar + "/// manage more than one file type extension.\n"
            outstring += tabchar + "/// @note Must be implemented by derived classes.\n"
            outstring += tabchar + "std::vector< std::string >\n"
            outstring += tabchar + "get_file_interpreter_file_extensions() const override;"
            first = False
    elif fxn_type == "SETTER" :
        if is_data_representation_class == True :

            outstring += "\n"
            outstring += tabchar + "/// @brief Delete all of the data from this data representation.\n"
            outstring += tabchar + "/// @note This only clears data, not configuration settings.\n"
            outstring += tabchar +  "void\n"
            outstring += tabchar +  "inner_object_clear() override;\n"

            outstring += "\n"
            outstring += tabchar + "/// @brief Delete all of the data and all of the configuration settings from this data representation.\n"
            outstring += tabchar + "/// @note This completely resets the object, clearing both data and configuration settings.\n"
            outstring += tabchar +  "void\n"
            outstring += tabchar +  "inner_object_reset() override;"

            first = False


    for fxn in jsonfile["Elements"][classname][groupname][namepattern+"_APIs"] :
        #print(fxn)
        if first :
            first = False
        else :
            outstring += "\n\n"

        deprecation_status = determine_deprecation_status( element_properties = fxn, project_maj_version=proj_maj_vers, project_min_version=proj_min_vers )
        if deprecation_status == DEPRECATED :
            outstring += "#ifndef MASALA_ENABLE_DEPRECATED_FUNCTIONS\n"

        if ( "Triggers_No_Mutex_Lock" in fxn ) and ( fxn["Triggers_No_Mutex_Lock"] == True ) :
            triggers_no_mutex_lock = True
        else :
            triggers_no_mutex_lock = False

        if ("Output" in fxn) and (fxn["Output"]["Output_Type"] != "void") :
            has_output = True
        else :
            has_output = False

        if ( "Always_Returns_Nullptr" in fxn ) and ( fxn["Always_Returns_Nullptr"] == True ) :
            assert has_output, "A function was found that was annotated to have no output but also to return nullptr."
            always_returns_nullptr = True
        else :
            always_returns_nullptr = False

        outstring += tabchar + "/// @brief " + fxn[namepattern+"_Description"] + "\n"
        ninputs = fxn[namepattern+"_N_Inputs"]

        if ninputs > 0 :
            for i in range(ninputs) :
                outstring += tabchar + "/// @param[in] " + fxn["Inputs"]["Input_" + str(i)]["Input_Name"] + " " + fxn["Inputs"]["Input_" + str(i)]["Input_Description"] + "\n"
        if has_output :
            outstring += tabchar + "/// @returns " + fxn["Output"]["Output_Description"] + "\n"
            if triggers_no_mutex_lock :
                outstring += tabchar + "/// @note This function triggers no mutex lock.  Calling it from multiple threads is only threadsafe in a read-only context."
                if always_returns_nullptr :
                    outstring += "  Also note that this version always returns nullptr."
                outstring += "\n"
            else :
                outstring += tabchar + "/// @note This version always returns nullptr.\n"
            if fxn["Is_Virtual_Not_Overriding_Base_API_Virtual_Function"] == True :
                outstring += tabchar + "virtual\n"
            outstring += tabchar + correct_masala_types( project_name, fxn["Output"]["Output_Type"], additional_includes ) + "\n"
        else :
            if triggers_no_mutex_lock :
                outstring += tabchar + "/// @note This function triggers no mutex lock.  Calling it from multiple threads is only threadsafe in a read-only context."
                if always_returns_nullptr :
                    outstring += "  Also note that this version always returns nullptr."
                outstring += "\n"
            else :
                outstring += tabchar + "/// @note This version always returns nullptr.\n"
            if fxn["Is_Virtual_Not_Overriding_Base_API_Virtual_Function"] == True :
                outstring += tabchar + "virtual\n"
            outstring += tabchar + "void\n"
        outstring += tabchar + fxn[namepattern + "_Name"] + "("

        if fxn["Is_Const"] == True :
            conststr = " const"
        else :
            conststr = ""

        if fxn["Is_Override_Of_Base_API_Virtual_Function"] == True :
            overridestr = " override"
        else :
            overridestr = ""

        if ninputs > 0 :
            #if( fxn_type == "SETTER" ) :
            #    print( "FXN: " + fxn["Setter_Name"] )
            for i in range(ninputs) :
                outstring += "\n" + tabchar + tabchar + correct_masala_types( project_name, fxn["Inputs"]["Input_" + str(i)]["Input_Type"], additional_includes ) + " " + fxn["Inputs"]["Input_" + str(i)]["Input_Name"]
                if i+1 < ninputs :
                    outstring += ","
            outstring += "\n" + tabchar + ")" + conststr + overridestr + ";"
        else :
            outstring += ")" + conststr + overridestr + ";"
        if deprecation_status == DEPRECATED :
            outstring += "\n#endif // MASALA_ENABLE_DEPRECATED_FUNCTIONS"
    return outstring

## @brief Generate the actual function call in a setter, getter, or work function.
def generate_function_call( \
        object_string : str, \
        accessor_string : str, \
        namepattern : str, \
        fxn : json, \
        ninputs : int, \
        project_name : str, \
        jsonfile : json \
    ) -> str :
    outstring = object_string + accessor_string + fxn[namepattern + "_Name"] + "("
    if ninputs > 0 :
        for i in range(ninputs) :
            curinputname = fxn["Inputs"]["Input_" + str(i)]["Input_Type"]

            input_is_masala_API_ptr = False
            input_is_masala_class = False
            input_is_known_enum = is_known_masala_base_enum( curinputname )
            input_is_noapi_class = False
            if curinputname.startswith( "MASALA_SHARED_POINTER" ) :
                firstchevron = curinputname.find("<")
                lastchevron = curinputname.rfind(">")
                curinput_inner = curinputname[firstchevron+1:lastchevron].strip()
                if( is_masala_class( project_name, curinput_inner )  ) :
                    input_is_masala_API_ptr = True
            elif is_masala_class( project_name, curinputname ) :
                curinput_inner = curinputname
                input_is_masala_class = True
                if input_is_known_enum == False :
                    if is_plugin_or_noapi_class( parent_class_file_from_class_name( curinputname.split()[0], project_name, False ), project_name, False ) :
                        input_is_noapi_class = True

            if ( input_is_masala_class == True and input_is_noapi_class == False ) or input_is_masala_API_ptr == True :
                if input_is_masala_API_ptr :
                    input_point_or_arrow = "->"
                else :
                    input_point_or_arrow = "."

                curinput_inner_split = curinput_inner.split()
                inputtype = curinput_inner_split[0]
                if inputtype in jsonfile["Elements"] and jsonfile["Elements"][inputtype]["Properties"]["Is_Lightweight"] == True :
                    outstring += fxn["Inputs"]["Input_" + str(i)]["Input_Name"] + input_point_or_arrow + "get_inner_object()"
                else :
                    if input_is_masala_class and input_is_known_enum == False and inputtype.endswith( "API" ) == False :
                        outstring += " *( "
                    else :
                        outstring += " "
                    outstring += fxn["Inputs"]["Input_" + str(i)]["Input_Name"]
                    if input_is_known_enum == False:
                        if inputtype.endswith( "API" ) == False :
                            outstring += input_point_or_arrow + "get_inner_object()"
                    if input_is_masala_class and input_is_known_enum == False and inputtype.endswith( "API" ) == False :
                        outstring += " )"
            else:

                outstring += " " + fxn["Inputs"]["Input_" + str(i)]["Input_Name"]
            if i+1 < ninputs :
                outstring += ","
            else :
                outstring += " "
    outstring += ")"
    return outstring

## @brief Return true if and only if (a) a class is defined in a JSON file, and (b) it has public constructors.
def class_exists_and_has_public_constructors( \
        namespace_and_name : str, \
        jsonfile : json \
    ) -> bool :
    if namespace_and_name in jsonfile["Elements"] :
        return ( jsonfile["Elements"][namespace_and_name]["Properties"]["Has_Protected_Constructors"] == False )
    return False

## @brief List known enums that can be taken or returned by functions, defined in masala::base.
def is_known_masala_base_enum( \
    objtype : str \
    ) -> bool :

    if objtype == "masala::base::managers::database::elements::ElementTypeEnum" :
        return True
    if objtype == "masala::base::managers::database::elements::ElementTypeEnum const" :
        return True
    elif objtype == "masala::base::enums::ChemicalBondType" :
        return True
    elif objtype == "masala::base::enums::ChemicalBondType const" :
        return True
    elif objtype == "masala::base::enums::AtomHybridizationState" :
        return True
    elif objtype == "masala::base::enums::AtomHybridizationState const" :
        return True
    
    return False

## @brief Given a known enum that can be taken or returned by functions, defined in masala::base,
## return the known header file to include that defines the enum.
def include_file_for_known_masala_base_enum( objtype : str ) -> str :
    if objtype == "masala::base::managers::database::elements::ElementTypeEnum" or objtype == "masala::base::managers::database::elements::ElementTypeEnum const" :
        return "<base/managers/database/elements/ElementType.fwd.hh>"
    elif objtype == "masala::base::enums::ChemicalBondType" or objtype == "masala::base::enums::ChemicalBondType const" :
        return "<base/enums/ChemicalBondTypeEnum.fwd.hh>"
    elif objtype == "masala::base::enums::AtomHybridizationState" or objtype == "masala::base::enums::AtomHybridizationState const" :
        return "<base/enums/AtomHybridizationStateEnum.fwd.hh>"

    assert False, "Error!  Do not know filename for enum type " + objtype + "!"

## @brief Generate the implementations for setters, getters, or work functions based on the JSON
## description of the API.
## @note The classname input should include namespace.  As a side-effect, this function appends to the
## additional_includes list.
def generate_function_implementations( \
    project_name: str, \
    library_name : str, \
    classname: str, \
    jsonfile: json, \
    tabchar: str, \
    fxn_type: str, \
    additional_includes: list, \
    is_lightweight: bool, \
    is_derived : bool, \
    is_plugin_class : bool, \
    is_engine_class : bool, \
    is_data_representation_class : bool, \
    proj_maj_vers : int, \
    proj_min_vers : int
    ) -> str :

    outstring = ""
    first = True

    apiclassname = jsonfile["Elements"][classname]["Module"] + "_API"

    assert fxn_type == "SETTER" or fxn_type == "GETTER" or fxn_type == "WORKFXN"
    if fxn_type == "SETTER" :
        groupname = "Setters"
        namepattern = "Setter"
    elif fxn_type == "GETTER" :
        groupname = "Getters"
        namepattern = "Getter"
        if is_plugin_class :
            outstring += "/// @brief Nonconst access to the inner plugin object.\n"
            outstring += "masala::base::managers::plugin_module::MasalaPluginSP\n"
            outstring += apiclassname + "::get_inner_plugin_object_nonconst() {\n"
            outstring += tabchar + "return get_inner_object();\n"
            outstring += "}\n\n"
            outstring += "/// @brief Const access to the inner plugin object.\n"
            outstring += "masala::base::managers::plugin_module::MasalaPluginCSP\n"
            outstring += apiclassname + "::get_inner_plugin_object() const {\n"
            outstring += tabchar + "return get_inner_object();\n"
            outstring += "}\n\n"
    elif fxn_type == "WORKFXN" :
        groupname = "WorkFunctions"
        namepattern = "Work_Function"

    if fxn_type == "GETTER" :
        if is_data_representation_class == True :
            outstring += "/// @brief Get the inner data representation object.\n"
            outstring += "/// @note Use this function with care!  Holding a shared pointer to the inner\n"
            outstring += "/// object can nullify the thread safety that the API object provides.\n"
            outstring += "masala::base::managers::engine::MasalaDataRepresentationSP\n"
            outstring += apiclassname + "::get_inner_data_representation_object() {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_;\n"
            outstring += "}\n"

            outstring += "\n"
            outstring += "/// @brief Get the inner data representation object (const access).\n"
            outstring += "/// @note Use this function with care!  Holding a const shared pointer to the inner\n"
            outstring += "/// object can nullify the thread safety that the API object provides.\n"
            outstring += "masala::base::managers::engine::MasalaDataRepresentationCSP\n"
            outstring += apiclassname + "::get_inner_data_representation_object_const() const {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_;\n"
            outstring += "}\n"

            outstring += "\n"
            outstring += "/// @brief Is the inner data representation object empty?\n"
            outstring += "/// @returns True if the inner data representation object contains no data, false otherwise.\n"
            outstring += "/// @note This does not report on whether the inner object has had configuration settings\n"
            outstring += "/// set; only on whether it is devoid of data.\n"
            outstring += "bool\n"
            outstring += apiclassname + "::inner_object_empty() const {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object()->empty();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_->empty();\n"
            outstring += "}"

            first = False
        elif is_engine_class == True :
            outstring += "/// @brief Get the inner engine object.\n"
            outstring += "/// @note Use this function with care!  Holding a shared pointer to the inner\n"
            outstring += "/// object can nullify the thread safety that the API object provides.\n"
            outstring += "masala::base::managers::engine::MasalaEngineSP\n"
            outstring += apiclassname + "::get_inner_engine_object() {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_;\n"
            outstring += "}\n"
            outstring += "\n"
            outstring += "/// @brief Get the inner engine object (const access).\n"
            outstring += "/// @note Use this function with care!  Holding a const shared pointer to the inner\n"
            outstring += "/// object can nullify the thread safety that the API object provides.\n"
            outstring += "masala::base::managers::engine::MasalaEngineCSP\n"
            outstring += apiclassname + "::get_inner_engine_object_const() const {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_;\n"
            outstring += "}"
            first = False
        elif is_file_interpreter_class == True :
            outstring += "/// @brief Get the inner file interpreter object.\n"
            outstring += "/// @note Use this function with care!  Holding a shared pointer to the inner\n"
            outstring += "/// object can nullify the thread safety that the API object provides.\n"
            outstring += "masala::base::managers::file_interpreter::MasalaFileInterpreterSP\n"
            outstring += apiclassname + "::get_inner_file_interpreter_object() {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_;\n"
            outstring += "}\n"
            outstring += "\n"
            outstring += "/// @brief Get the inner file interpreter object (const access).\n"
            outstring += "/// @note Use this function with care!  Holding a const shared pointer to the inner\n"
            outstring += "/// object can nullify the thread safety that the API object provides.\n"
            outstring += "masala::base::managers::file_interpreter::MasalaFileInterpreterCSP\n"
            outstring += apiclassname + "::get_inner_file_interpreter_object_const() const {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_;\n"
            outstring += "}"
            outstring += "\n\n"
            outstring += "/// @brief Get the descriptors for the file types that the file interpreter created by this creator manages.\n"
            outstring += "/// @details Descriptors may be something like \"protein_data_bank_file\".  A given file interpreter may\n"
            outstring += "/// manage more than one file type.\n"
            outstring += "/// @note Must be implemented by derived classes.\n"
            outstring += "std::vector< std::string >\n"
            outstring += apiclassname + "::get_file_interpreter_file_descriptors() const {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object()->get_file_descriptors();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_->get_file_descriptors();\n"
            outstring += "}\n\n"
            outstring += "/// @brief Get the extensions for the file types that the file interpreter created by this creator manages.\n"
            outstring += "/// @details Extensions may be something like \"pdb\" (in lowercase).  A given file interpreter may\n"
            outstring += "/// manage more than one file type extension.\n"
            outstring += "/// @note Must be implemented by derived classes.\n"
            outstring += "std::vector< std::string >\n"
            outstring += apiclassname + "::get_file_interpreter_file_extensions() const {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "return inner_object()->get_file_extensions();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "return inner_object_->get_file_extensions();\n"
            outstring += "}\n"
            first = False
    elif fxn_type == "SETTER" :
        if is_data_representation_class == True :

            outstring += "\n"
            outstring += "/// @brief Delete all of the data from this data representation.\n"
            outstring += "/// @note This only clears data, not configuration settings.\n"
            outstring += "void\n"
            outstring += apiclassname + "::inner_object_clear() {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "inner_object()->clear();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "inner_object_->clear();\n"
            outstring += "}\n"

            outstring += "\n"
            outstring += "/// @brief Delete all of the data and all of the configuration settings from this data representation.\n"
            outstring += "/// @note This completely resets the object, clearing both data and configuration settings.\n"
            outstring += "void\n"
            outstring += apiclassname + "::inner_object_reset() {\n"
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
                outstring += tabchar + "inner_object()->reset();\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
                outstring += tabchar + "inner_object_->reset();\n"
            outstring += "}\n"

            first = False

    for fxn in jsonfile["Elements"][classname][groupname][namepattern+"_APIs"] :
        #print(fxn)
        if first :
            first = False
        else :
            outstring += "\n\n"
        
        deprecation_status = determine_deprecation_status( element_properties = fxn, project_maj_version=proj_maj_vers, project_min_version=proj_min_vers )
        if deprecation_status == DEPRECATED :
            outstring += "#ifndef MASALA_ENABLE_DEPRECATED_FUNCTIONS\n"

        outstring += "/// @brief " + fxn[namepattern+"_Description"] + "\n"
        ninputs = fxn[namepattern+"_N_Inputs"]
        if ("Output" in fxn) :
            outtype = fxn["Output"]["Output_Type"]
            if outtype != "void" :
                has_output = True
            else :
                has_output = False
        else :
            outtype = "void"
            has_output = False

        outtype_base = outtype.split()[0]
        output_is_lightweight = False
        if is_masala_class( project_name, outtype_base )  :
            if is_known_masala_base_enum( outtype_base ) == False :
                assert (outtype_base in jsonfile["Elements"]), "ERROR: " + outtype_base + " not found in JSON Elements."
                if jsonfile["Elements"][outtype_base]["Properties"]["Is_Lightweight"] == True :
                    output_is_lightweight = True

        if ( "Returns_This_Ref" in fxn ) and ( fxn["Returns_This_Ref"] == True ) :
            returns_this_ref = True
        else :
            returns_this_ref = False
        if ( "Triggers_No_Mutex_Lock" in fxn ) and ( fxn["Triggers_No_Mutex_Lock"] == True ) :
            triggers_no_mutex_lock = True
        else :
            triggers_no_mutex_lock = False
        
        if ( "Always_Returns_Nullptr" in fxn ) and ( fxn["Always_Returns_Nullptr"] == True ) :
            assert has_output, "A function was found that was annotated to have no output but also to return nullptr."
            always_returns_nullptr = True
        else :
            always_returns_nullptr = False

        if ninputs > 0 :
            for i in range(ninputs) :
                outstring += "/// @param[in] " + fxn["Inputs"]["Input_" + str(i)]["Input_Name"] + " " + fxn["Inputs"]["Input_" + str(i)]["Input_Description"] + "\n"
        if has_output :
            outstring += "/// @returns " + fxn["Output"]["Output_Description"] + "\n"
            if triggers_no_mutex_lock :
                outstring += "/// @note This function triggers no mutex lock.  Calling it from multiple threads is only threadsafe in a read-only context."
                if always_returns_nullptr :
                    outstring += "  Also note that this version always returns nullptr."
                outstring += "\n"
            else :
                outstring += "/// @note This version always returns nullptr.\n"
            outstring += correct_masala_types( project_name, outtype, additional_includes ) + "\n"
        else :
            if triggers_no_mutex_lock :
                outstring += "/// @note This function triggers no mutex lock.  Calling it from multiple threads is only threadsafe in a read-only context."
                if always_returns_nullptr :
                    outstring += "  Also note that this version always returns nullptr."
                outstring += "\n"
            else :
                outstring += "/// @note This version always returns nullptr.\n"
            outstring += "void\n"
        outstring +=  apiclassname + "::" + fxn[namepattern + "_Name"] + "("

        if fxn["Is_Const"] == True :
            conststr = " const"
        else :
            conststr = ""

        if ninputs > 0 :
            for i in range(ninputs) :
                outstring += "\n" + tabchar + correct_masala_types( project_name, fxn["Inputs"]["Input_" + str(i)]["Input_Type"], additional_includes ) + " " + fxn["Inputs"]["Input_" + str(i)]["Input_Name"]
                if i+1 < ninputs :
                    outstring += ","
            outstring += "\n)" + conststr + " {"
        else :
            outstring += ")" + conststr + " {"

        # Body:

        if always_returns_nullptr :
            outstring += " return nullptr; }\n"
            if deprecation_status == DEPRECATED :
                outstring += "#endif // MASALA_ENABLE_DEPRECATED_FUNCTIONS\n"
            continue
        else :
            outstring += "\n"

        convert_to_masala_API_ptr = False
        is_masala_API_obj = False
        is_masala_plugin_ptr = False
        #is_masala_plugin_obj = False
        if outtype.startswith( "MASALA_SHARED_POINTER" ) :
            firstchevron = outtype.find("<")
            lastchevron = outtype.rfind(">")
            outtype_inner = outtype[firstchevron+1:lastchevron].strip()
            if( is_masala_class( project_name, outtype_inner ) and outtype_inner.split()[0].endswith("API") == False  ) :
                if is_plugin_or_noapi_class( parent_class_file_from_class_name( drop_const( outtype_inner ), project_name, False ), project_name, False ) == False :
                    convert_to_masala_API_ptr = True
                    if VERBOSE_SCRIPT_OUTPUT == True:
                        print( "\tChecking whether " + drop_const( outtype_inner ) + " is a Masala plugin class..." )
                    if( is_masala_plugin_class( project_name, library_name, drop_const( outtype_inner ), jsonfile ) ) :
                        is_masala_plugin_ptr = True
        elif is_masala_class( project_name, outtype ) and returns_this_ref == False and is_known_masala_base_enum( outtype ) == False :
            is_masala_API_obj = True
            # if( is_masala_plugin_class( project_name, library_name, drop_const( outtype_inner ), jsonfile ) ) :
            #     is_masala_plugin_obj = True
            assert( is_masala_plugin_class( project_name, library_name, drop_const( outtype ), jsonfile ) == False ), \
                "\n********************************************************************************\n" \
                + "Error in generating implementation for function " + apiclassname + "::" + fxn[namepattern + "_Name"] \
                + "():\nsupport for returning plugin classes by reference (and properly enclosing them in the correct\n" \
                + "type of API container) has not yet been added to the Masala build system.\n" \
                + "********************************************************************************"

        if is_lightweight == True :
            accessor_string = "."
            if is_derived == True :
                object_string = "static_cast< " + classname + conststr + " >( inner_object() )"
            else :
                object_string = "inner_object_"
        else :
            if is_derived == True :
                accessor_string = "."
                object_string = "static_cast< " + classname + conststr + " & >( inner_object_ref() )"
            else :
                accessor_string = "->"
                object_string = "inner_object_"

        if triggers_no_mutex_lock == False :
            if is_derived == True :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex() );\n"
            else :
                outstring += tabchar + "std::lock_guard< std::mutex > lock( api_mutex_ );\n"
        if (fxn_type == "GETTER" or fxn_type == "WORKFXN") and has_output == True and returns_this_ref == False :
            if convert_to_masala_API_ptr or is_masala_plugin_ptr :
                outstring += tabchar + "// In this function, note that std::const_pointer_cast is safe to use.  We might\n"
                outstring += tabchar + "// cast away the constness of the object, but if we do, we effectively restore it by\n"
                outstring += tabchar + "// encapsulating it in a const API object (in that case) that only allows const access.\n"
                outstring += tabchar + "// This is ONLY allowed in Masala code that is auto-generated in a manner that ensures\n"
                outstring += tabchar + "// that nothing unsafe is done with the nonconst object.\n" 

                if is_masala_plugin_ptr :
                    dummy = []
                    output_api_class_name = correct_masala_types( project_name, drop_const( outtype_inner ), dummy )
                    outstring += tabchar + "MASALA_SHARED_POINTER< " \
                        + outtype_inner \
                        + " > returnobj( " \
                        + generate_function_call( object_string, accessor_string, namepattern, fxn, ninputs, project_name, jsonfile ) \
                        + " );\n"
                    if( class_exists_and_has_public_constructors( drop_const( outtype_inner ), jsonfile ) == True ) :
                        outstring += tabchar + "if( returnobj->class_namespace_and_name() == \"" \
							+ drop_const( outtype_inner ) + "\" ) {\n"
                        outstring += tabchar + tabchar + "return masala::make_shared< " \
							+ output_api_class_name \
							+ " >( std::const_pointer_cast< " + drop_const( outtype_inner ) + " >( returnobj ) );\n"
                        outstring += tabchar + "}\n"
                    tempsplit = outtype_inner.strip().split()
                    outstring += tabchar + "return std::static_pointer_cast< " \
                        + output_api_class_name
                    if tempsplit[0] == "const" or tempsplit[len(tempsplit)-1] == "const" :
                        outstring += " const"
                    outstring += " >(\n" + tabchar + tabchar + \
                        "masala::base::managers::plugin_module::MasalaPluginModuleManager::get_instance()->"
                    if tempsplit[0] == "const" or tempsplit[len(tempsplit)-1] == "const" :
                        outstring += "encapsulate_const_plugin_object_instance( returnobj )\n"
                    else :
                        outstring += "encapsulate_plugin_object_instance( returnobj )\n"
                    outstring += tabchar + ");\n}\n"

                    if deprecation_status == DEPRECATED :
                        outstring += "#endif // MASALA_ENABLE_DEPRECATED_FUNCTIONS\n"
                    add_base_class_include( project_name, outtype, additional_includes )
                    add_base_class_include( project_name, drop_const( outtype_inner ), additional_includes )
                    additional_includes.append( "base/managers/plugin_module/MasalaPluginModuleManager" )
                    continue # Go on to next function.

            outstring += tabchar + "return "

            if convert_to_masala_API_ptr and returns_this_ref == False :
                dummy = []
                outstring += "masala::make_shared< " + correct_masala_types( project_name, drop_const( outtype_inner ), dummy ) + " >(\n"
                outstring += tabchar + tabchar + "std::const_pointer_cast< " + drop_const( outtype_inner ) + " >(\n"
                outstring += tabchar + tabchar + tabchar
            elif is_masala_API_obj :
                dummy = []
                outstring += correct_masala_types( project_name, outtype, dummy ) + "(\n"
                if output_is_lightweight :
                    outstring += tabchar + tabchar + outtype + "( "
                else :
                    outstring += tabchar + tabchar + "masala::make_shared< " + drop_const( outtype ) + " >( "
                add_base_class_include( project_name, outtype, additional_includes )
        else :
            outstring += tabchar

        outstring += generate_function_call( object_string, accessor_string, namepattern, fxn, ninputs, project_name, jsonfile )
        if convert_to_masala_API_ptr and returns_this_ref == False :
            outstring += "\n" + tabchar + tabchar + ")\n" + tabchar + ")"
        elif is_masala_API_obj and returns_this_ref == False :
            outstring += " )\n" + tabchar + ")"
        outstring += ";\n"
        if returns_this_ref == True :
            outstring += tabchar + "return *this;\n"
        outstring += "}"
        if deprecation_status == DEPRECATED :
            outstring += "\n#endif // MASALA_ENABLE_DEPRECATED_FUNCTIONS"
    return outstring

## @brief Given a list of additional files to include, generate a
## string of the inclusions.
def generate_additional_includes( additional_includes : list, generate_fwd_includes : bool, original_api_include: str ) -> str :
    outstr = ""
    added = []
    if generate_fwd_includes == True :
        fwdstr = ".fwd"
    else :
        fwdstr = ""
    first = True
    for entry in additional_includes :
        if entry != original_api_include :
            if entry.startswith("<") :
                assert entry.endswith(">")
                if(fwdstr=="") :
                    continue #Only include vector/list/set/map includes in header file.
                newentry = "#include " + entry
            else :
                newentry = "#include <" + entry + fwdstr + ".hh>"
            if newentry not in added :
                added.append(newentry)
                if first == True :
                    first = False
                else :
                    outstr += "\n"
                outstr += newentry
    return outstr

## @brief Generate the keywords for a data representation or engine class, from the JASON description.
def generate_dr_or_eng_keywords( \
    name_string : str, \
    namespace_string : str, \
    json_api : json, \
	is_dr_class : bool, \
	is_engine_class : bool
    ) -> str :
    outstr = ""
    if is_dr_class == True :
        assert is_engine_class == False, "Cannot be both a data representation and an engine!"
        keywords = json_api["Elements"][ namespace_string + "::" + name_string ]["Data_Representation_Keywords"]
    elif is_engine_class == True :
        keywords = json_api["Elements"][ namespace_string + "::" + name_string ]["Engine_Keywords"]
    else :
        assert False, "Expected an engine or data representation!"
        
    first = True
    outstr += "{ "
    for entry in keywords :
        if first == True :
            first = False
        else :
            outstr += ", "
        outstr += "\"" + entry + "\""
    outstr += " }"
    return outstr

## @brief Generate the categories for a data representation or engine class, from the JASON description.
def generate_dr_or_eng_categories( \
    name_string : str, \
    namespace_string : str, \
    json_api : json, \
	is_dr_class : bool, \
	is_engine_class : bool
    ) -> str :
    outstr = ""
    if is_dr_class == True :
        assert is_engine_class == False, "Cannot be both a data representation and an engine!"
        categories = json_api["Elements"][ namespace_string + "::" + name_string ]["Data_Representation_Categories"]
    elif is_engine_class == True :
        categories = json_api["Elements"][ namespace_string + "::" + name_string ]["Engine_Categories"]
    else :
        assert False, "Expected an engine or data representation!"
        
    firstcat = True
    for category in categories :
        if firstcat == True :
            firstcat = False
        else :
            outstr += ", "
        outstr += "{ "
        first = True
        for entry in category :
            if first == True :
                first = False
            else :
                outstr += ", "
            outstr += "\"" + entry + "\""
        outstr += " }"
    return outstr

## @brief Generate the compatible engines list for a data representation or file interpreter
## class, from the JSON description.
def generate_dr_or_fr_stringlist( \
    name_string : str, \
    namespace_string : str, \
    json_api : json, \
    json_category_string : str, \
    ) -> str :
    outstr = ""
    entries = json_api["Elements"][ namespace_string + "::" + name_string ][json_category_string]
    first = True
    for entry in entries :
        if first == True :
            first = False
        else :
            outstr += ", "
        outstr += "\"" + entry + "\""
    return outstr

## @brief Generate the categories for a plugin class, from the JSON description.
def generate_plugin_categories( \
    name_string : str, \
    namespace_string : str, \
    json_api : json \
    ) -> str :

    outstr = ""
    categories = json_api["Elements"][ namespace_string + "::" + name_string ]["Plugin_Categories"]
    firstcat = True
    for category in categories :
        if firstcat == True :
            firstcat = False
        else :
            outstr += ", "
        outstr += "{ "
        first = True
        for entry in category :
            if first == True :
                first = False
            else :
                outstr += ", "
            outstr += "\"" + entry + "\""
        outstr += " }"
    return outstr

## @brief Generate the keywords for a plugin class, from the JSON description.
def generate_plugin_keywords( \
    name_string : str, \
    namespace_string : str, \
    json_api : json
    ) -> str :

    outstr = ""
    keywords = json_api["Elements"][ namespace_string + "::" + name_string ]["Plugin_Keywords"]
    first = True
    for entry in keywords :
        if first == True :
            first = False
        else :
            outstr += ", "
        outstr += "\"" + entry + "\""
    return outstr

## @brief Auto-generate the forward declaration file (***Creator.fwd.hh) for the creator for a plugin class.
def prepare_creator_forward_declarations( \
    plugin_creator_fwdfile_template : str, \
    data_rep_creator_fwdfile_template : str, \
    engine_creator_fwdfile_template : str, \
    file_interpreter_creator_fwdfile_template : str, \
    licence : str, \
    creator_name : str, \
    creator_namespace : list, \
    creator_filename : str, \
    json_api : json, \
    name_string : str, \
    namespace : list, \
    library_name : str, \
    project_name : str, \
    is_data_representation_class : bool, \
    is_file_interpreter_class : bool \
    ) -> None :

    original_class_namespace_string = ""

    header_guard_string = capitalize_project_name(project_name) + "_" + library_name + "_api_auto_generated_api_"
    for i in range( len(namespace) ):
        original_class_namespace_string += namespace[i]
        if i+1<len(namespace) :
            original_class_namespace_string += "::"
        if i > 1 :
            header_guard_string += namespace[i] + "_"
    header_guard_string += creator_name + "_fwd_hh"

    if is_data_representation_class == True :
        plugin_creator_fwdfile = data_rep_creator_fwdfile_template
    elif is_file_interpreter_class == True :
        plugin_creator_fwdfile = file_interpreter_creator_fwdfile_template
    elif is_engine_class == True :
        plugin_creator_fwdfile = engine_creator_fwdfile_template
    else :
        plugin_creator_fwdfile = plugin_creator_fwdfile_template

    plugin_creator_fwdfile = \
        plugin_creator_fwdfile \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence + "\n*/\n" ) \
        .replace( "<__DOXYGEN_CREATOR_FILE_PATH_AND_FWD_FILE_NAME__>", "/// @file " + creator_filename[4:] + ".fwd.hh" ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE_AND_NAME__>", original_class_namespace_string + "::" + name_string ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__CPP_CREATOR_FWD_HEADER_GUARD__>", "#ifndef " + header_guard_string + "\n#define " + header_guard_string ) \
        .replace( "<__CPP_NAMESPACE__>", generate_cpp_namespace( namespace, True ) ) \
        .replace( "<__CPP_END_NAMESPACE__>", generate_cpp_namespace( namespace, False ) ) \
        .replace( "<__CREATOR_CLASS_API_NAME__>", creator_name ) \
        .replace( "<__CPP_END_FWD_HEADER_GUARD__>", "#endif //" + header_guard_string )

    plugin_creator_fwdfile = clean_up_generated_code( plugin_creator_fwdfile )

    with open( creator_filename + ".fwd.hh", 'w' ) as filehandle :
        filehandle.write( plugin_creator_fwdfile )
    print( "\tWrote \"" + creator_filename + ".fwd.hh\"." )

## @brief Auto-generate the header file (***Creator.hh) for the creator for a plugin class.
def prepare_creator_header_file( \
    plugin_creator_hhfile_template : str, \
    data_rep_creator_hhfile_template : str, \
    engine_creator_fwdfile_template : str, \
    file_interpreter_creator_hhfile_template : str, \
    licence_template : str, \
    creator_name : str, \
    creator_namespace : list, \
    creator_filename : str, \
    json_api : json, \
    name_string : str, \
    namespace : list, \
    library_name : str, \
    project_name : str, \
    is_engine : bool, \
    is_data_representation_class : bool, \
    is_file_interpreter_class : bool \
    ) -> None :

    original_class_namespace_string = ""
    creator_namespace_string = ""

    header_guard_string = capitalize_project_name(project_name) + "_" + library_name + "_api_auto_generated_api_"
    for i in range( len(namespace) ):
        original_class_namespace_string += namespace[i]
        if i+1<len(namespace) :
            original_class_namespace_string += "::"
        if i > 1 :
            header_guard_string += namespace[i] + "_"
    header_guard_string += creator_name + "_hh"

    first = True
    for entry in creator_namespace :
        if first == True :
            first = False
        else :
            creator_namespace_string += "::"
        creator_namespace_string += entry
    
    parent_api_include, parent_api_namespace_and_name, root_api_name, next_is_plugin = get_api_class_include_and_classname( project_name, library_name, name_string, namespace, True, is_engine, is_data_representation_class, is_file_interpreter_class )
    if parent_api_include.endswith( "_API.hh>" ) :
        base_include_file = parent_api_include[:-8] + "Creator.hh>"
    else :
        base_include_file = parent_api_include[:-7] + "Creator.hh>"
    if parent_api_namespace_and_name.endswith( "_API") :
        plugin_creator_base_class = parent_api_namespace_and_name[:-4] + "Creator"
    else :
        plugin_creator_base_class = parent_api_namespace_and_name[:-3] + "Creator"

    if is_data_representation_class == True :
        plugin_creator_hhfile = data_rep_creator_hhfile_template \
            .replace( "<__DATA_REPRESENTATION_CATEGORIES__>", generate_dr_or_eng_categories( name_string, original_class_namespace_string, json_api, True, False ) ) \
            .replace( "<__DATA_REPRESENTATION_KEYWORDS__>", generate_dr_or_eng_keywords( name_string, original_class_namespace_string, json_api, True, False ) ) \
            .replace( "<__DATA_REPRESENTATION_COMPATIBLE_ENGINES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Compatible_Engines" ) ) \
            .replace( "<__DATA_REPRESENTATION_INCOMPATIBLE_ENGINES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Incompatible_Engines" ) ) \
            .replace( "<__DATA_REPRESENTATION_PRESENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Present_Properties" ) ) \
            .replace( "<__DATA_REPRESENTATION_ABSENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Absent_Properties" ) ) \
            .replace( "<__DATA_REPRESENTATION_POSSIBLY_PRESENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Possibly_Present_Properties" ) ) \
            .replace( "<__DATA_REPRESENTATION_POSSIBLY_ABSENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Possibly_Absent_Properties" ) )
    elif is_engine_class == True :
        plugin_creator_hhfile = engine_creator_hhfile_template \
            .replace( "<__ENGINE_CATEGORIES__>", generate_dr_or_eng_categories( name_string, original_class_namespace_string, json_api, False, True ) ) \
            .replace( "<__ENGINE_KEYWORDS__>", generate_dr_or_eng_keywords( name_string, original_class_namespace_string, json_api, False, True ) )
    elif is_file_interpreter_class == True :
        plugin_creator_hhfile = file_interpreter_creator_hhfile_template \
			.replace( "<__FILE_INTERPRETER_FILE_DESCRIPTIONS__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "File_Interpreter_FileType_Descriptions" ) ) \
			.replace( "<__FILE_INTERPRETER_FILE_EXTENSIONS__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "File_Interpreter_FileType_Extensions" ) )
    else :
        plugin_creator_hhfile = plugin_creator_hhfile_template

    plugin_creator_hhfile = \
        plugin_creator_hhfile \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence_template + "\n*/\n" ) \
        .replace( "<__DOXYGEN_CREATOR_FILE_PATH_AND_HH_FILE_NAME__>", "/// @file " + creator_filename[4:] + ".hh" ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE_AND_NAME__>", original_class_namespace_string + "::" + name_string ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__CPP_CREATOR_HH_HEADER_GUARD__>", "#ifndef " + header_guard_string + "\n#define " + header_guard_string ) \
        .replace( "<__CREATOR_INCLUDE_FILE_PATH_AND_FWD_FILE_NAME__>", "#include <" + creator_filename[4:] + ".fwd.hh>  " ) \
        .replace( "<__PLUGIN_CATEGORIES__>", generate_plugin_categories( name_string, original_class_namespace_string, json_api ) ) \
        .replace( "<__PLUGIN_KEYWORDS__>", generate_plugin_keywords( name_string, original_class_namespace_string, json_api ) ) \
        .replace( "<__CPP_NAMESPACE__>", generate_cpp_namespace( namespace, True ) ) \
        .replace( "<__CPP_END_NAMESPACE__>", generate_cpp_namespace( namespace, False ) ) \
        .replace( "<__SOURCE_CLASS_NAME__>", name_string ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE__>", original_class_namespace_string ) \
        .replace( "<__CREATOR_CLASS_API_NAME__>", creator_name ) \
        .replace( "<__CREATOR_CLASS_API_NAMESPACE__>", creator_namespace_string ) \
        .replace( "<__CPP_END_HH_HEADER_GUARD__>", "#endif //" + header_guard_string ) \
        .replace( "<__PLUGIN_CREATOR_BASE_INCLUDE_FILE__>", base_include_file ) \
        .replace( "<__PLUGIN_CREATOR_BASE_CLASS__>", plugin_creator_base_class )

    plugin_creator_hhfile = clean_up_generated_code( plugin_creator_hhfile )

    with open( creator_filename + ".hh", 'w' ) as filehandle :
        filehandle.write( plugin_creator_hhfile )
    print( "\tWrote \"" + creator_filename + ".hh\"." )

## @brief Auto-generate the cc file (***Creator.cc) for the creator for a plugin class.
def prepare_creator_cc_file( \
    plugin_creator_ccfile_template : str, \
    data_rep_creator_ccfile_template : str, \
    engine_creator_fwdfile_template : str, \
    file_interpreter_creator_ccfile_template : str, \
    licence_template : str, \
    creator_name : str, \
    creator_namespace : list, \
    creator_filename : str, \
    json_api : json, \
    name_string : str, \
    namespace : list, \
    library_name : str, \
    project_name : str, \
    api_dirname : str, \
    is_data_representation_class : bool, \
    is_file_interpreter_class : bool, \
    has_protected_constructors : bool \
    ) -> None :

    original_class_namespace_string = ""
    creator_namespace_string = ""
    api_dirname_short = api_dirname[4:]

    for i in range( len(namespace) ):
        original_class_namespace_string += namespace[i]
        if i+1<len(namespace) :
            original_class_namespace_string += "::"

    first = True
    for entry in creator_namespace :
        if first == True :
            first = False
        else :
            creator_namespace_string += "::"
        creator_namespace_string += entry

    if has_protected_constructors == True :
        instantiable_string = "#define " + name_string + "_API_NOT_INSTANTIABLE"
        object_string = "/*object*/"
    else :
        instantiable_string = ""
        object_string = "object"

    if is_data_representation_class == True :
        plugin_creator_ccfile = data_rep_creator_ccfile_template \
            .replace( "<__DATA_REPRESENTATION_CATEGORIES__>", generate_dr_or_eng_categories( name_string, original_class_namespace_string, json_api, True, False ) ) \
            .replace( "<__DATA_REPRESENTATION_KEYWORDS__>", generate_dr_or_eng_keywords( name_string, original_class_namespace_string, json_api, True, False ) ) \
            .replace( "<__DATA_REPRESENTATION_COMPATIBLE_ENGINES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Compatible_Engines" ) ) \
            .replace( "<__DATA_REPRESENTATION_INCOMPATIBLE_ENGINES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Incompatible_Engines" ) ) \
            .replace( "<__DATA_REPRESENTATION_PRESENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Present_Properties" ) ) \
            .replace( "<__DATA_REPRESENTATION_ABSENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Absent_Properties" ) ) \
            .replace( "<__DATA_REPRESENTATION_POSSIBLY_PRESENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Possibly_Present_Properties" ) ) \
            .replace( "<__DATA_REPRESENTATION_POSSIBLY_ABSENT_PROPERTIES__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "Data_Representation_Possibly_Absent_Properties" ) )
    elif is_engine_class == True :
        plugin_creator_ccfile = engine_creator_ccfile_template \
            .replace( "<__ENGINE_CATEGORIES__>", generate_dr_or_eng_categories( name_string, original_class_namespace_string, json_api, False, True ) ) \
            .replace( "<__ENGINE_KEYWORDS__>", generate_dr_or_eng_keywords( name_string, original_class_namespace_string, json_api, False, True ) )
    elif is_file_interpreter_class == True :
        plugin_creator_ccfile = file_interpreter_creator_ccfile_template \
			.replace( "<__FILE_INTERPRETER_FILE_DESCRIPTIONS__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "File_Interpreter_FileType_Descriptions" ) ) \
			.replace( "<__FILE_INTERPRETER_FILE_EXTENSIONS__>", generate_dr_or_fr_stringlist( name_string, original_class_namespace_string, json_api, "File_Interpreter_FileType_Extensions" ) )
    else :
        plugin_creator_ccfile = plugin_creator_ccfile_template

    plugin_creator_ccfile = \
        plugin_creator_ccfile \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence_template + "\n*/\n" ) \
        .replace( "<__DOXYGEN_CREATOR_FILE_PATH_AND_CC_FILE_NAME__>", "/// @file " + creator_filename[4:] + ".cc" ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE_AND_NAME__>", original_class_namespace_string + "::" + name_string ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__CREATOR_INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>", "#include <" + creator_filename[4:] + ".hh>  " ) \
        .replace( "<__PLUGIN_CATEGORIES__>", generate_plugin_categories( name_string, original_class_namespace_string, json_api ) ) \
        .replace( "<__PLUGIN_KEYWORDS__>", generate_plugin_keywords( name_string, original_class_namespace_string, json_api ) ) \
        .replace( "<__CPP_NAMESPACE__>", generate_cpp_namespace( namespace, True ) ) \
        .replace( "<__CPP_END_NAMESPACE__>", generate_cpp_namespace( namespace, False ) ) \
        .replace( "<__SOURCE_CLASS_NAME__>", name_string ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE__>", original_class_namespace_string ) \
        .replace( "<__CREATOR_CLASS_API_NAME__>", creator_name ) \
        .replace( "<__CREATOR_CLASS_API_NAMESPACE__>", creator_namespace_string ) \
        .replace( "<__INCLUDE_SOURCE_FILE_PATH_AND_HH_FILE_NAME__>", "#include <" + generate_source_class_filename( name_string, namespace, ".hh" ) + ">" ) \
        .replace( "<__API_INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>", "#include <" + api_dirname_short + name_string + "_API.hh>" ) \
        .replace( "<__SOURCE_CLASS_API_NAME__>", name_string + "_API" ) \
        .replace( "<__IS_SOURCE_CLASS_API_NOT_INSTANTIABLE__>", instantiable_string ) \
        .replace( "<__OBJECT_OR_COMMENTED__>", object_string )
    
    plugin_creator_ccfile = clean_up_generated_code( plugin_creator_ccfile )

    with open( creator_filename + ".cc", 'w' ) as filehandle :
        filehandle.write( plugin_creator_ccfile )
    print( "\tWrote \"" + creator_filename + ".cc\"." )
    
## @brief Auto-generate the forward declaration file (***.fwd.hh) for the class.
def prepare_forward_declarations( libraryname : str, classname : str, namespace : list, dirname : str, fwdfile_template : str, licence : str ) :
    apiclassname = classname + "_API"
    original_class_namespace_string = ""
    header_guard_string = capitalize_project_name(project_name) + "_" + libraryname + "_api_auto_generated_api_"
    for i in range( len(namespace) ):
        original_class_namespace_string += namespace[i]
        if i+1<len(namespace) :
            original_class_namespace_string += "::"
        if i > 1 :
            header_guard_string += namespace[i] + "_"
    header_guard_string += apiclassname + "_fwd_hh"

    dirname_short = dirname.replace("src/", "")
    namespace_and_source_class = original_class_namespace_string + "::" + classname

    fwdfile = \
        fwdfile_template \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence + "\n*/\n" ) \
        .replace( "<__DOXYGEN_FILE_PATH_AND_FWD_FILE_NAME__>", "/// @file " + dirname_short + apiclassname + ".fwd.hh" ) \
        .replace( "<__DOXYGEN_FWD_BRIEF_DESCRIPTION__>", "/// @brief Forward declarations for auto-generated API for\n/// " + namespace_and_source_class + " class." ) \
        .replace( "<__DOXYGEN_DETAILED_DESCRIPTION__>", "/// @details This file was generated automatically.  Do not edit it, for changes\n/// will be lost on next rebuild." ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE_AND_NAME__>", namespace_and_source_class ) \
        .replace( "<__CPP_FWD_HEADER_GUARD__>", "#ifndef " + header_guard_string + "\n#define " + header_guard_string ) \
        .replace( "<__CPP_NAMESPACE__>", generate_cpp_namespace( namespace, True ) ) \
        .replace( "<__CPP_END_NAMESPACE__>", generate_cpp_namespace( namespace, False ) ) \
        .replace( "<__SOURCE_CLASS_API_NAME__>", apiclassname ) \
        .replace( "<__CPP_END_FWD_HEADER_GUARD__>", "#endif // " + header_guard_string )
    
    fwdfile = clean_up_generated_code( fwdfile )

    fname = dirname + apiclassname + ".fwd.hh"
    with open( fname, 'w' ) as filehandle :
        filehandle.write(fwdfile)
    print( "\tWrote \"" + fname + "\"."  )

## @brief Figure out the parent class for this API class, and the include file that defines the parent class.
## @details If the parent class of the inner object has an API, use the API class for that object as the parent.  Otherwise,
## use MasalaPluginAPI (if it is a plug-in class) or MasalaObjectAPI (if it is not).
## @returns A tuple of ( parent include file string, parent namespace and name string, root API class namespace and name string, boolean representing whether this is a class derived from another API class ).
def get_api_class_include_and_classname( project_name : str, libraryname : str, classname : str, namespace : list, is_plugin_class : bool, is_engine_class : bool, is_data_representation_class : bool, is_file_interpreter_class : bool ) -> tuple :
    #print( classname, namespace, flush=True )
    # First, find the parent class name.
    assert len(namespace) > 1
    if namespace[0] == project_name :
        fstring = "src/"
    else :
        fstring = "headers/" + namespace[0] + "/headers/"
    for i in range( 1, len(namespace) ) : #Deliberately starting at 1 (not 0) to omit project namespace.
        fstring += namespace[i]
        fstring += "/"
    fstring += classname + ".hh"
    lines = slurp_file_and_remove_comments(fstring).splitlines()
    #for line in lines : print(line)
    parent_namespace_and_name = None
    for line in lines :
        linesplit = line.strip().split()
        if len(linesplit) > 2 and linesplit[0] == "class" and (linesplit[1] == classname or linesplit[1] == classname + ":") :
            if linesplit[1] == classname + ":" :
                startentry = 2
            else :
                startentry = 3
            assert len(linesplit) > startentry + 1
            assert linesplit[startentry] == "public"
            parent_namespace_and_name = linesplit[startentry+1]
            if parent_namespace_and_name.endswith("{") :
                parent_namespace_and_name = parent_namespace_and_name[:-1]
            if VERBOSE_SCRIPT_OUTPUT == True :
                print("\t\tFound parent class of " + classname + ":\t" + parent_namespace_and_name + ".")
            break

    if( parent_namespace_and_name.endswith("base::MasalaObject") == False and \
        parent_namespace_and_name.endswith( "base::managers::plugin_module::MasalaPlugin" ) == False and \
        parent_namespace_and_name.endswith( "base::managers::engine::MasalaEngine" ) == False and \
        parent_namespace_and_name.endswith( "base::managers::engine::MasalaDataRepresentation" ) == False \
        ) :
        # Second, prepare the parent class .hh file.
        parentsplit = parent_namespace_and_name.split("::")
        assert len(parentsplit) > 0
        if parentsplit[0] == project_name :
            parent_hhfile = "src"
            parent_api_hhfile = "src"
        else :
            parent_hhfile = "headers/" + parentsplit[0] + "/headers"
            parent_api_hhfile = "headers/" + parentsplit[0] + "/headers"
        parent_api_namespace_and_name = parentsplit[0]
        assert len(parentsplit) > 2, "Could not properly parse parent namespace (" + parent_namespace_and_name + ") for class " + classname + "."
        for i in range( 1, len(parentsplit) ) :
            parent_hhfile += "/" + parentsplit[i]
            if i == 2 :
                parent_api_hhfile += "_api/auto_generated_api"
                parent_api_namespace_and_name += "_api::auto_generated_api"
            parent_api_hhfile += "/" + parentsplit[i]
            parent_api_namespace_and_name += "::" + parentsplit[i]
        parent_hhfile += ".hh"
        parent_api_hhfile += "_API.hh"
        parent_api_namespace_and_name += "_API"

        # Third, check the parent file for an API definition.
        parent_has_api = False
        #print( "****\t" + parent_hhfile, flush=True )
        lines = slurp_file_and_remove_comments(parent_hhfile).replace("(", " ( ").replace(")", " ) ").replace("=", " = ").replace("0", " 0 ").replace(";", " ; ").split() # Overwrite old lines; split by whitespace.
        #print(lines)
        for i in range( 0, len(lines) - 6 ) :
            if lines[i].endswith("MasalaObjectAPIDefinitionCWP") and \
                lines[i+1] == "get_api_definition" and \
                lines[i+2] == "(" and \
                lines[i+3] == ")" and \
                lines[i+4] == "override" and \
                lines[i+5] != "=" and \
                lines[i+6] != "0":

                parent_has_api = True
                if VERBOSE_SCRIPT_OUTPUT == True :
                    print( "\t\tParent class " + parent_namespace_and_name + " has an API definition." )
                break

        parent_classname = parentsplit[len(parentsplit) - 1]
        parent_namespace = []
        for j in range( len(parentsplit) - 1 ) :
            parent_namespace.append( parentsplit[j] )
        if parent_api_hhfile.startswith( "src/" ) :
            parent_api_hhfile = "#include <" + parent_api_hhfile[4:] + ">"
        else :
            parent_api_hhfile = "#include <" + parent_api_hhfile[17 + len(parentsplit[0]):] + ">"

        if parent_has_api == True :
            include2, parent2, root_api_namespace_and_name, next_is_plugin = get_api_class_include_and_classname( project_name, parentsplit[1], parent_classname, parent_namespace, is_plugin_class, is_engine_class, is_data_representation_class, is_file_interpreter_class )
            if root_api_namespace_and_name == "masala::base::managers::plugin_module::MasalaPluginAPI" or \
                root_api_namespace_and_name == "masala::base::managers::engine::MasalaEngineAPI" or \
                root_api_namespace_and_name == "masala::base::managers::engine::MasalaDataRepresentationAPI" or \
                root_api_namespace_and_name == "masala::base::managers::file_interpreter::MasalaFileInterpreterAPI" or \
                root_api_namespace_and_name == "masala::base::MasalaObjectAPI" :
                root_api_namespace_and_name = parent_api_namespace_and_name
            return( parent_api_hhfile, parent_api_namespace_and_name, root_api_namespace_and_name, True )
        else : # parent_has_api == False
            if VERBOSE_SCRIPT_OUTPUT == True :
                print( "\t\tParent class " + parent_namespace_and_name + " lacks an API definition.", flush=True )
            return get_api_class_include_and_classname( project_name, parentsplit[1], parent_classname, parent_namespace, is_plugin_class, is_engine_class, is_data_representation_class, is_file_interpreter_class )

    # If we reach here, there's no parent class with an API.
    if is_plugin_class == True :
        if is_engine_class == True :
            return ( "#include <base/managers/engine/MasalaEngineAPI.hh>", \
            "masala::base::managers::engine::MasalaEngineAPI", \
            "masala::base::managers::engine::MasalaEngineAPI", \
            False )
        elif is_data_representation_class == True :
            return ( "#include <base/managers/engine/MasalaDataRepresentationAPI.hh>", \
            "masala::base::managers::engine::MasalaDataRepresentationAPI", \
            "masala::base::managers::engine::MasalaDataRepresentationAPI", \
            False )
        elif is_file_interpreter_class == True :
            return ( "#include <base/managers/file_interpreter/MasalaFileInterpreterAPI.hh>", \
            "masala::base::managers::file_interpreter::MasalaFileInterpreterAPI", \
            "masala::base::managers::file_interpreter::MasalaFileInterpreterAPI", \
            False )
        return ( "#include <base/managers/plugin_module/MasalaPluginAPI.hh>", \
            "masala::base::managers::plugin_module::MasalaPluginAPI", \
            "masala::base::managers::plugin_module::MasalaPluginAPI", \
            False )
    else :
        return ( "#include <base/MasalaObjectAPI.hh>", \
            "masala::base::MasalaObjectAPI", \
            "masala::base::MasalaObjectAPI", \
            False )

## @brief Auto-generate the header file (***.hh) for the class.
def prepare_header_file( project_name: str, libraryname : str, classname : str, namespace : list, dirname : str, hhfile_template : str, derived_hhfile_template : str, licence : str, jsonfile : json, tabchar : str, is_plugin_class : bool, is_engine_class : bool, is_data_representation_class : bool, is_file_interpreter_class : bool, proj_maj_vers : int, proj_min_vers : int ) :
    apiclassname = classname + "_API"
    original_class_namespace_string = ""
    header_guard_string = capitalize_project_name(project_name) + "_" + libraryname + "_api_auto_generated_api_"
    for i in range( len(namespace) ):
        original_class_namespace_string += namespace[i]
        if i+1<len(namespace) :
            original_class_namespace_string += "::"
        if i > 1 :
            header_guard_string += namespace[i] + "_"
    header_guard_string += apiclassname + "_hh"

    api_base_class_include, api_base_class, api_root_base_class, is_derived = get_api_class_include_and_classname( project_name, libraryname, classname, namespace, is_plugin_class, is_engine_class, is_data_representation_class, is_file_interpreter_class )

    if is_derived == False :
        hhfile_template_to_use = hhfile_template
    else :
        hhfile_template_to_use = derived_hhfile_template

    dirname_short = dirname.replace("src/", "")
    namespace_and_source_class = original_class_namespace_string + "::" + classname

    if jsonfile["Elements"][namespace_and_source_class]["Properties"]["Has_Protected_Constructors"] == True :
        pure_virtuals_for_protected_constructor_classes = " = 0"
        protected_constructor_comment_start = "/*\n\t// (Commented out because this API class has protected constructors.)"
        protected_constructor_comment_end = "*/"
    else :
        pure_virtuals_for_protected_constructor_classes = ""
        protected_constructor_comment_start = ""
        protected_constructor_comment_end = ""

    additional_includes = []

    hhfile = \
        hhfile_template_to_use \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence + "\n*/\n" ) \
        .replace( "<__DOXYGEN_FILE_PATH_AND_HH_FILE_NAME__>", "/// @file " + dirname_short + apiclassname + ".hh" ) \
        .replace( "<__DOXYGEN_BRIEF_DESCRIPTION__>", "/// @brief Headers for auto-generated API for\n/// " + namespace_and_source_class + " class." ) \
        .replace( "<__DOXYGEN_DETAILED_DESCRIPTION__>", "/// @details This file was generated automatically.  Do not edit it, for changes\n/// will be lost on next rebuild." ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE_AND_NAME__>", namespace_and_source_class ) \
        .replace( "<__SOURCE_CLASS_NAME__>", classname ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE__>", original_class_namespace_string ) \
        .replace( "<__CPP_HH_HEADER_GUARD__>", "#ifndef " + header_guard_string + "\n#define " + header_guard_string ) \
        .replace( "<__CPP_NAMESPACE__>", generate_cpp_namespace( namespace, True ) ) \
        .replace( "<__CPP_END_NAMESPACE__>", generate_cpp_namespace( namespace, False ) ) \
        .replace( "<__SOURCE_CLASS_API_NAME__>", apiclassname ) \
        .replace( "<__SOURCE_CLASS_API_NAMESPACE__>", generate_cpp_namespace_singleline( namespace ) ) \
        .replace( "<__INCLUDE_FILE_PATH_AND_FWD_FILE_NAME__>", "#include <" + dirname_short + apiclassname + ".fwd.hh>" ) \
        .replace( "<__INCLUDE_SOURCE_FILE_PATH_AND_FWD_FILE_NAME__>", "#include <" + generate_source_class_filename( classname, namespace, ".fwd.hh" ) + ">" ) \
        .replace( "<__INCLUDE_SOURCE_FILE_PATH_AND_HH_FILE_NAME__>", "#include <" + generate_source_class_filename( classname, namespace, ".hh" ) + ">" ) \
        .replace( "<__CPP_CONSTRUCTOR_PROTOTYPES__>", generate_constructor_prototypes(project_name, namespace_and_source_class, jsonfile, tabchar, additional_includes, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_SETTER_PROTOTYPES__>", generate_function_prototypes(project_name, namespace_and_source_class, jsonfile, tabchar, "SETTER", additional_includes, is_plugin_class, is_engine_class, is_data_representation_class, is_file_interpreter_class, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_GETTER_PROTOTYPES__>", generate_function_prototypes(project_name, namespace_and_source_class, jsonfile, tabchar, "GETTER", additional_includes, is_plugin_class, is_engine_class, is_data_representation_class, is_file_interpreter_class, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_WORK_FUNCTION_PROTOTYPES__>", generate_function_prototypes(project_name, namespace_and_source_class, jsonfile, tabchar, "WORKFXN", additional_includes, is_plugin_class, is_engine_class, is_data_representation_class, is_file_interpreter_class, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_END_HH_HEADER_GUARD__>", "#endif // " + header_guard_string ) \
        .replace( "<__CPP_ADDITIONAL_FWD_INCLUDES__>", generate_additional_includes( additional_includes, True, dirname_short + apiclassname ) ) \
        .replace( "<__BASE_API_CLASS_NAMESPACE_AND_NAME__>", api_base_class ) \
        .replace( "<__ROOT_BASE_API_CLASS_NAMESPACE_AND_NAME__>", api_root_base_class ) \
        .replace( "<__INCLUDE_BASE_API_CLASS_HH_FILE__>", api_base_class_include ) \
        .replace( "<__PURE_VIRTUALS_FOR_PROTECTED_CONSTRUCTOR_CLASSES__>", pure_virtuals_for_protected_constructor_classes ) \
        .replace( "<__POSSIBLE_COMMENT_START_FOR_PROTECTED_CONSTRUCTOR_CLASSES__>", protected_constructor_comment_start ) \
        .replace( "<__POSSIBLE_COMMENT_END_FOR_PROTECTED_CONSTRUCTOR_CLASSES__>", protected_constructor_comment_end )

    hhfile = clean_up_generated_code( hhfile )

    fname = dirname + apiclassname + ".hh"
    with open( fname, 'w' ) as filehandle :
        filehandle.write(hhfile)
    print( "\tWrote \"" + fname + "\"."  )

## @brief Auto-generate the cc file (***.cc) for the class.
def prepare_cc_file( project_name: str, libraryname : str, classname : str, namespace : list, dirname : str, ccfile_template : str, derived_ccfile_template : str, licence : str, jsonfile : json, tabchar : str, is_lightweight : bool, is_plugin_class : bool, is_engine_class : bool, is_data_representation_class : bool, proj_maj_vers : int, proj_min_vers : int ) :
    apiclassname = classname + "_API"
    original_class_namespace_string = ""
    for i in range( len(namespace) ):
        original_class_namespace_string += namespace[i]
        if i+1<len(namespace) :
            original_class_namespace_string += "::"

    dirname_short = dirname.replace("src/", "")
    namespace_and_source_class = original_class_namespace_string + "::" + classname

    if jsonfile["Elements"][namespace_and_source_class]["Properties"]["Has_Protected_Constructors"] == True :
        protected_constructor_comment_start = "/*\n// (Commented out because this API class has protected constructors and these functions are pure virtual.)"
        protected_constructor_comment_end = "*/"
    else :
        protected_constructor_comment_start = ""
        protected_constructor_comment_end = ""

    api_base_class_include, api_base_class, api_root_base_class, is_derived = get_api_class_include_and_classname( project_name, libraryname, classname, namespace, is_plugin_class, is_engine_class, is_data_representation_class, is_file_interpreter_class )

    if is_derived == False :
        ccfile_template_to_use = ccfile_template
    else :
        ccfile_template_to_use = derived_ccfile_template

    additional_includes = []

    ccfile = \
        ccfile_template_to_use \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence + "\n*/\n" ) \
        .replace( "<__DOXYGEN_FILE_PATH_AND_CC_FILE_NAME__>", "/// @file " + dirname_short + apiclassname + ".cc" ) \
        .replace( "<__DOXYGEN_BRIEF_DESCRIPTION__>", "/// @brief Implementations for auto-generated API for\n/// " + namespace_and_source_class + " class." ) \
        .replace( "<__DOXYGEN_DETAILED_DESCRIPTION__>", "/// @details This file was generated automatically.  Do not edit it, for changes\n/// will be lost on next rebuild." ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE_AND_NAME__>", namespace_and_source_class ) \
        .replace( "<__SOURCE_CLASS_NAME__>", classname ) \
        .replace( "<__SOURCE_CLASS_NAMESPACE__>", original_class_namespace_string ) \
        .replace( "<__CPP_NAMESPACE__>", generate_cpp_namespace( namespace, True ) ) \
        .replace( "<__CPP_END_NAMESPACE__>", generate_cpp_namespace( namespace, False ) ) \
        .replace( "<__SOURCE_CLASS_API_NAME__>", apiclassname ) \
        .replace( "<__SOURCE_CLASS_API_NAMESPACE__>", generate_cpp_namespace_singleline( namespace ) ) \
        .replace( "<__INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>", "#include <" + dirname_short + apiclassname + ".hh>" ) \
        .replace( "<__INCLUDE_SOURCE_FILE_PATH_AND_HH_FILE_NAME__>", "#include <" + generate_source_class_filename( classname, namespace, ".hh" ) + ">" ) \
        .replace( "<__CPP_CONSTRUCTOR_IMPLEMENTATIONS__>", generate_constructor_implementations(project_name, api_base_class, namespace_and_source_class, jsonfile, tabchar, additional_includes, is_lightweight, is_derived, is_plugin_class=is_plugin_class, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_SETTER_IMPLEMENTATIONS__>", generate_function_implementations(project_name, libraryname, namespace_and_source_class, jsonfile, tabchar, "SETTER", additional_includes, is_lightweight, is_derived, is_plugin_class=is_plugin_class, is_engine_class=is_engine_class, is_data_representation_class=is_data_representation_class, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_GETTER_IMPLEMENTATIONS__>", generate_function_implementations(project_name, libraryname, namespace_and_source_class, jsonfile, tabchar, "GETTER", additional_includes, is_lightweight, is_derived, is_plugin_class=is_plugin_class, is_engine_class=is_engine_class, is_data_representation_class=is_data_representation_class, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_WORK_FUNCTION_IMPLEMENTATIONS__>", generate_function_implementations(project_name, libraryname, namespace_and_source_class, jsonfile, tabchar, "WORKFXN", additional_includes, is_lightweight, is_derived, is_plugin_class=is_plugin_class, is_engine_class=is_engine_class, is_data_representation_class=is_data_representation_class, proj_maj_vers=proj_maj_vers, proj_min_vers=proj_min_vers) ) \
        .replace( "<__CPP_ADDITIONAL_HH_INCLUDES__>", generate_additional_includes( additional_includes, False, dirname_short + apiclassname ) ) \
        .replace( "<__BASE_API_CLASS_NAMESPACE_AND_NAME__>", api_base_class ) \
        .replace( "<__ROOT_BASE_API_CLASS_NAMESPACE_AND_NAME__>", api_root_base_class ) \
        .replace( "<__POSSIBLE_COMMENT_START_FOR_PROTECTED_CONSTRUCTOR_CLASSES__>", protected_constructor_comment_start ) \
        .replace( "<__POSSIBLE_COMMENT_END_FOR_PROTECTED_CONSTRUCTOR_CLASSES__>", protected_constructor_comment_end )
    
    ccfile = clean_up_generated_code( ccfile )

    fname = dirname + apiclassname + ".cc"
    with open( fname, 'w' ) as filehandle :
        filehandle.write(ccfile)
    print( "\tWrote \"" + fname + "\"."  )

## @brief Given the project name, capitalize it.
def capitalize_project_name( project_name: str ) -> str :
    namesplit = project_name.replace("_", " ").split()
    outname = ""
    for word in namesplit :
        if outname != "" :
            outname += "_"
        if len(word) > 0 :
            outname += word[0].capitalize()
        if len(word) > 1 :
            outname += word[1:]
    return outname

## @brief Given library name, class name, class namespace, and project name, return the name of the
## creator class, the namespace of the creator class (as a list), and the filename (without extension) of the
## creator class source.
def determine_creator_name_namespace_filename( library_name : str, name_string : str, namespace : list, project_name : str ) -> tuple :
    creator_name = name_string + "Creator"
    creator_namespace = [ project_name, library_name + "_api", "auto_generated_api" ]
    creator_filename_no_extension = "src/" + library_name + "_api/auto_generated_api"
    assert len(namespace) >= 2
    for i in range( len(namespace) ) :
        if i == 0 :
            assert namespace[i] == project_name
        elif i == 1 :
            assert namespace[i] == library_name
        else :
            creator_namespace.append( namespace[i] )
            creator_filename_no_extension += "/" + namespace[i]
    creator_filename_no_extension += "/" + creator_name
    #print( creator_name, creator_namespace, creator_filename_no_extension )
    return creator_name, creator_namespace, creator_filename_no_extension


## @brief If we have plugins, copy the registration file templates and fill them in.
def do_generate_registration_function( \
    project_name : str, \
    library_name : str, \
    plugins_list : list, \
    plugin_registration_ccfile_template : str, \
    plugin_registration_hhfile_template : str, \
    licence : str \
    ) -> None :

    #Prepare the directory:
    registration_dirname = "src/" + library_name  + "_api/auto_generated_api/registration"
    if os.path.isdir( registration_dirname ) :
        print( "\tFound directory \"" + registration_dirname + "\".  Clearing contents." )
        shutil.rmtree( registration_dirname )
    else :
        print( "\tCreating \"" + registration_dirname + "\"." )
    os.makedirs( registration_dirname )

    #Prepare plugin .hh files list, plus
    #list of plugin creators for registration:
    first = True
    plugin_hh_files_includes = ""
    plugin_creators_for_registration = ""
    for entry in plugins_list :
        if first == True :
            first = False
        else :
            plugin_hh_files_includes += "\n"
            plugin_creators_for_registration += ",\n\t\t\t"
        plugin_hh_files_includes += "#include <" + entry[2][4:] + ".hh>"
        first2 = True
        creator_namespace = ""
        for entry2 in entry[1] :
            if first2 == True :
                first2 = False
            else :
                creator_namespace += "::"
            creator_namespace += entry2
        plugin_creators_for_registration += "masala::make_shared< " + creator_namespace + "::" + entry[0] + " >()"

    #Prepare namespace:
    namespace_open = "namespace " + project_name + " {\nnamespace " + library_name + "_api {\nnamespace auto_generated_api {\nnamespace registration {"
    namespace_close = "} // namespace registration\n} // namespace auto_generated_api\n} // namespace " + library_name + "_api\n} // namespace " + project_name

#   Prepare header guards:
    header_guard_string = capitalize_project_name(project_name) + "_" + library_name + "_api_auto_generated_api_registration_register_" + library_name + "_hh" 

    #Prepare hh file:
    hh_fname = registration_dirname + "/register_" + library_name + ".hh"

    hhfile = plugin_registration_hhfile_template \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence + "\n*/\n" ) \
        .replace( "<__DOXYGEN_FILE_PATH_AND_HH_FILE_NAME__>", "/// @file " + hh_fname ) \
        .replace( "<__DOXYGEN_BRIEF_DESCRIPTION__>", "/// @brief Headers for registration functions for the " + library_name + " library plugins." ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__CPP_NAMESPACE__>", namespace_open ) \
        .replace( "<__CPP_END_NAMESPACE__>", namespace_close ) \
        .replace( "<__LIBNAME__>", library_name ) \
        .replace( "<__CPP_HH_HEADER_GUARD__>", "#ifndef " + header_guard_string + "\n#define " + header_guard_string ) \
        .replace( "<__CPP_END_HH_HEADER_GUARD__>", "#endif // " + header_guard_string )
    
    hhfile = clean_up_generated_code( hhfile )

    with open( hh_fname, 'w' ) as filehandle :
        filehandle.write(hhfile)
    print( "\tWrote \"" + hh_fname + "\"."  )

    #Prepare cc file:
    cc_fname = registration_dirname + "/register_" + library_name + ".cc"

    ccfile = plugin_registration_ccfile_template \
        .replace( "<__COMMENTED_LICENCE__>", "/*\n" + licence + "\n*/\n" ) \
        .replace( "<__DOXYGEN_FILE_PATH_AND_CC_FILE_NAME__>", "/// @file " + cc_fname ) \
        .replace( "<__DOXYGEN_BRIEF_DESCRIPTION__>", "/// @brief Implementations of registration functions for the " + library_name + " library plugins." ) \
        .replace( "<__DOXYGEN_AUTHOR_AND_EMAIL__>", "/// @author None (auto-generated by script code_templates/generate_library_api.py)." ) \
        .replace( "<__PLUGIN_CREATOR_HH_FILES_INCLUDES__>", plugin_hh_files_includes ) \
        .replace( "<__CPP_NAMESPACE__>", namespace_open ) \
        .replace( "<__CPP_END_NAMESPACE__>", namespace_close ) \
        .replace( "<__LIBNAME__>", library_name ) \
        .replace( "<__PLUGIN_CREATORS_FOR_REGISTRATION__>", plugin_creators_for_registration ) \
        .replace( "<__REGISTER_PLUGINS_HH_FILE_INCLUDE_>", "#include <" + hh_fname[4:] + ">" )
    
    ccfile = clean_up_generated_code( ccfile )

    with open( cc_fname, 'w' ) as filehandle :
        filehandle.write(ccfile)
    print( "\tWrote \"" + cc_fname + "\"."  )


################################################################################
## Program entry point
################################################################################

# Get options
project_name, project_maj_version, project_min_version, library_name, api_def_file = get_options()
print( "\tGenerating API for project " + project_name + ", library \"" + library_name + "\" from API definition file \"" + api_def_file + "\"." )

# Read JSON
with open( api_def_file, 'r' ) as jfile :
    json_api = json.load( jfile )

initialize_directory( library_name )
ccfile_template = read_file( "code_templates/api_templates/MasalaClassAPI.cc" )
hhfile_template = read_file( "code_templates/api_templates/MasalaClassAPI.hh" )
fwdfile_template = read_file( "code_templates/api_templates/MasalaClassAPI.fwd.hh" )

derived_ccfile_template = read_file( "code_templates/api_templates/MasalaDerivedClassAPI.cc" )
derived_hhfile_template = read_file( "code_templates/api_templates/MasalaDerivedClassAPI.hh" )

lightweight_ccfile_template = read_file( "code_templates/api_templates/MasalaLightWeightClassAPI.cc" )
lightweight_hhfile_template = read_file( "code_templates/api_templates/MasalaLightWeightClassAPI.hh" )
lightweight_fwdfile_template = read_file( "code_templates/api_templates/MasalaLightWeightClassAPI.fwd.hh" )

plugin_creator_ccfile_template = read_file( "code_templates/api_templates/MasalaPluginCreator.cc" )
plugin_creator_hhfile_template = read_file( "code_templates/api_templates/MasalaPluginCreator.hh" )
plugin_creator_fwdfile_template = read_file( "code_templates/api_templates/MasalaPluginCreator.fwd.hh" )

data_rep_creator_ccfile_template = read_file( "code_templates/api_templates/MasalaDataRepresentationCreator.cc" )
data_rep_creator_hhfile_template = read_file( "code_templates/api_templates/MasalaDataRepresentationCreator.hh" )
data_rep_creator_fwdfile_template = read_file( "code_templates/api_templates/MasalaDataRepresentationCreator.fwd.hh" )

engine_creator_ccfile_template = read_file( "code_templates/api_templates/MasalaEngineCreator.cc" )
engine_creator_hhfile_template = read_file( "code_templates/api_templates/MasalaEngineCreator.hh" )
engine_creator_fwdfile_template = read_file( "code_templates/api_templates/MasalaEngineCreator.fwd.hh" )

file_interpreter_creator_ccfile_template = read_file( "code_templates/api_templates/MasalaFileInterpreterCreator.cc" )
file_interpreter_creator_hhfile_template = read_file( "code_templates/api_templates/MasalaFileInterpreterCreator.hh" )
file_interpreter_creator_fwdfile_template = read_file( "code_templates/api_templates/MasalaFileInterpreterCreator.fwd.hh" )

plugin_registration_ccfile_template = read_file( "code_templates/api_templates/register_plugins.cc" )
plugin_registration_hhfile_template = read_file( "code_templates/api_templates/register_plugins.hh" )

project_name_capitalized = capitalize_project_name( project_name ).replace( "_", " " )
licence_template = read_file( "code_templates/licences/AGPL3.template" ).replace( "<__PROJECT_NAME__>", project_name_capitalized ).replace( "<__YEAR__>", str(2024) ).replace( "<__COPYRIGHT_HOLDER__>", "Vikram K. Mulligan" )
tabchar = "    "

generate_registration_function = False
plugins_list = []

if json_api["Elements"] is not None :
    for element in json_api["Elements"] :
        #print( element )
        namespace_string = json_api["Elements"][element]["ModuleNamespace"]
        name_string = json_api["Elements"][element]["Module"]
        namespace = separate_namespace( namespace_string )
        #print( namespace_string, name_string )
        #print( namespace )
        assert len(namespace) > 2
        assert namespace[0] == project_name, "Error!  All Masla classes (with or without APIs) are expected to be in base namespace \"" + project_name + "\".  This doesn't seem to be so for " + namespace_string + "::" + name_string + "."
        assert namespace[1] == library_name, "Error!  All Masla classes in library " + library_name + " (with or without APIs) are expected to be in namespace \"" + project_name + "::" + library_name + "\".  This doesn't seem to be so for " + namespace_string + "::" + name_string + "."
        dirname = prepare_directory( project_name, library_name, namespace )

        is_plugin_class = json_api["Elements"][element]["Properties"]["Is_Plugin_Class"]

        if "Is_Engine_Class" in json_api["Elements"][element]["Properties"] :
            is_engine_class = json_api["Elements"][element]["Properties"]["Is_Engine_Class"]
        else :
            is_engine_class = False

        if "Is_Data_Representation_Class" in json_api["Elements"][element]["Properties"] :
            is_data_representation_class = json_api["Elements"][element]["Properties"]["Is_Data_Representation_Class"]
        else :
            is_data_representation_class = False

        if "Is_File_Interpreter_Class" in json_api[ "Elements" ][ element ][ "Properties" ]:
            is_file_interpreter_class = json_api["Elements"][element]["Properties"]["Is_File_Interpreter_Class"]
        else :
            is_file_interpreter_class = False

        if json_api["Elements"][element]["Properties"]["Is_Lightweight"] == False :
            prepare_forward_declarations( library_name, name_string, namespace, dirname, fwdfile_template, licence_template )
            prepare_header_file( project_name, library_name, name_string, namespace, dirname, hhfile_template, derived_hhfile_template, licence_template, json_api, tabchar, is_plugin_class=is_plugin_class, is_engine_class=is_engine_class, is_data_representation_class=is_data_representation_class, is_file_interpreter_class=is_file_interpreter_class, proj_maj_vers=project_maj_version, proj_min_vers=project_min_version )
            prepare_cc_file( project_name, library_name, name_string, namespace, dirname, ccfile_template, derived_ccfile_template, licence_template, json_api, tabchar, False, is_plugin_class=is_plugin_class, is_engine_class=is_engine_class, is_data_representation_class=is_data_representation_class, proj_maj_vers=project_maj_version, proj_min_vers=project_min_version )
        else :
            prepare_forward_declarations( library_name, name_string, namespace, dirname, lightweight_fwdfile_template, licence_template )
            prepare_header_file( project_name, library_name, name_string, namespace, dirname, lightweight_hhfile_template, derived_hhfile_template, licence_template, json_api, tabchar, is_plugin_class=is_plugin_class, is_engine_class=is_engine_class, is_data_representation_class=is_data_representation_class, is_file_interpreter_class=is_file_interpreter_class, proj_maj_vers=project_maj_version, proj_min_vers=project_min_version )
            prepare_cc_file( project_name, library_name, name_string, namespace, dirname, lightweight_ccfile_template, derived_ccfile_template, licence_template, json_api, tabchar, True, is_plugin_class=is_plugin_class, is_engine_class=is_engine_class, is_data_representation_class=is_data_representation_class, proj_maj_vers=project_maj_version, proj_min_vers=project_min_version )
        
        if is_plugin_class == True :
            creator_name,creator_namespace,creator_filename = determine_creator_name_namespace_filename( library_name, name_string, namespace, project_name )
            if json_api["Elements"][element]["Properties"]["Has_Protected_Constructors"] == False :
                has_protected_constructors = False
                generate_registration_function = True
                plugins_list.append( [creator_name,creator_namespace,creator_filename] )
            else :
                has_protected_constructors = True
            prepare_creator_forward_declarations( plugin_creator_fwdfile_template, data_rep_creator_fwdfile_template, engine_creator_fwdfile_template, file_interpreter_creator_fwdfile_template, licence_template, creator_name, creator_namespace, creator_filename, json_api, name_string, namespace, library_name, project_name, is_data_representation_class=is_data_representation_class, is_file_interpreter_class=is_file_interpreter_class  )
            prepare_creator_header_file( plugin_creator_hhfile_template, data_rep_creator_hhfile_template, engine_creator_hhfile_template, file_interpreter_creator_hhfile_template, licence_template, creator_name, creator_namespace, creator_filename, json_api, name_string, namespace, library_name, project_name, is_engine=is_engine_class, is_data_representation_class=is_data_representation_class, is_file_interpreter_class=is_file_interpreter_class  )
            prepare_creator_cc_file( plugin_creator_ccfile_template, data_rep_creator_ccfile_template, engine_creator_ccfile_template, file_interpreter_creator_ccfile_template, licence_template, creator_name, creator_namespace, creator_filename, json_api, name_string, namespace, library_name, project_name, dirname, is_data_representation_class=is_data_representation_class, is_file_interpreter_class=is_file_interpreter_class, has_protected_constructors=has_protected_constructors  )
    
    if generate_registration_function == True :
        do_generate_registration_function( project_name, library_name, plugins_list, plugin_registration_ccfile_template, plugin_registration_hhfile_template, licence_template )

print( "\tFinished generating API for library \"" + library_name + "\" from API definition file \"" + api_def_file + "\"." )

