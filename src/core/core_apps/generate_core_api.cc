/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/core/core_apps/generate_core_api.cc
/// @brief An application that generates a JSON file defining the API
/// for the Masala core library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Core headers
#include <core/api/generate_api_classes.hh>
#include <core/types.hh>

// Base headers
#include <base/MasalaObject.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>

// External headers
#include <nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers
#include <fstream> // TEMPORARY!  SWITCH THIS TO USE DISK I/O MANAGER INSTEAD!

// Program entry point:
int
main(
    int /*argc*/,
    char * /*argv[]*/
) {
    nlohmann::json api_definition;
    api_definition["FileType"] = "API_definition";
    api_definition["Module"] = "Core";
    nlohmann::json api_entries;
    std::vector< base::MasalaObjectSP > const api_objects( core::api::generate_api_classes() );
    for( core::Size i(0), imax(api_objects.size()); i<imax; ++i ) {
        base::api::MasalaObjectAPIDefinitionCSP api_def( api_objects[i]->get_api_definition() );
        api_entries[ "Element_" + std::to_string(i) ] = *api_def->get_json_description();
    }
    api_definition["Elements"] = api_entries;

    // TEMPORARY!  REPLACE THE FOLLOWING TO USE DISK I/O MANAGER INSTEAD!
    std::ofstream filehandle( "core_api.json" );
    filehandle << api_definition.dump() << "\n";
    filehandle.close();

    return 0;
}