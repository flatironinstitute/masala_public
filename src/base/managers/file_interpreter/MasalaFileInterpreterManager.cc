/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreterManager.cc
/// @brief A static singleton for managing modules responsible for reading and writing particular
/// file formats, and converting these to and from particular data representations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/file_interpreter/MasalaFileInterpreterManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/file_interpreter/MasalaPluginCreator.hh>
#include <base/managers/file_interpreter/MasalaPlugin.hh>
#include <base/error/ErrorHandling.hh>
#include <base/utility/container/container_util.tmpl.hh>
#include <base/managers/engine/MasalaEngineCreator.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.hh>
#include <base/managers/engine/MasalaEngineManager.hh>
#include <base/managers/engine/MasalaDataRepresentationManager.hh>

// STL headers:
#include <string>
#include <sstream>
//#include <iomanip> // DELETE ME

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaFileInterpreterManagerHandle
MasalaFileInterpreterManager::get_instance() {
    static MasalaFileInterpreterManager plugin_manager;
    return &plugin_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaFileInterpreterManager".
std::string
MasalaFileInterpreterManager::class_name() const {
    return "MasalaFileInterpreterManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::file_interpreter".
std::string
MasalaFileInterpreterManager::class_namespace() const {
    return "masala::base::managers::file_interpreter";
}

/// @brief Completely reset the manager.
/// @details Unregisters all file interpreters.
void
MasalaFileInterpreterManager::reset() {
    using namespace masala::base::managers::engine;

    std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
	// TODO TODO TODO
    write_to_tracer( "Reset the MasalaFileInterpreterManager.  No file interpreters are registered." );
}

/// @brief Get the number of registered plugins.
base::Size
MasalaFileInterpreterManager::total_file_interpreters() const {
    std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
    //return all_file_interpreter_map_.size();
	return 0; // TODO TODO TODO
}


} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala
