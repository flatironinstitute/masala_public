/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/// @file src/numeric/numeric_apps/generate_numeric_api.cc
/// @brief An application that generates a JSON file defining the API
/// for the Masala numeric library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Numeric headers
#include <numeric/api/generate_api_classes.hh>
#include <base/types.hh>

// Base headers
#include <base/MasalaObject.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/managers/disk/MasalaDiskManager.hh>

// External headers
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers
#include <sstream>

// Program entry point:
int
main(
    // int argc,
    // char * argv[]
    int, char**
) {
    nlohmann::json api_definition;
    api_definition["FileType"] = "API_definition";
    api_definition["Module"] = "Numeric";
    nlohmann::json api_entries;
    std::vector< masala::base::MasalaObjectSP > const api_objects( masala::numeric::api::generate_api_classes() );
    for( masala::base::Size i(0), imax(api_objects.size()); i<imax; ++i ) {
        masala::base::api::MasalaObjectAPIDefinitionCSP api_def( api_objects[i]->get_api_definition() );
        api_entries[ api_objects[i]->class_namespace() + "::" + api_objects[i]->class_name() ] = *api_def->get_json_description();
    }
    api_definition["Elements"] = api_entries;

    std::ostringstream ss;
    ss << api_definition.dump( 1, '\t' ) << "\n";
    masala::base::managers::disk::MasalaDiskManager::get_instance()->write_ascii_file( "numeric_api.json", ss.str() );

    return 0;
}