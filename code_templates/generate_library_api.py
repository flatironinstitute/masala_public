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
## produce code in "core_api/auto_generated_code/".  This file should be run from the Masala
## root directory.
## @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

import json
from sys import argv
from os import path, listdir

# Parse the commandline options.
def get_options() :
    assert len(argv) == 3, "Invalid commandline flags.  Expected usage: python3 generate_library_api.py <source library name> <json api definition file>"
    return (argv[1], argv[2])

################################################################################
## Program entry point
################################################################################

library_name, api_def_file = get_options()
print( "Generating API for library \"" + library_name + "\" from API definition file \"" + api_def_file + "\"." )