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
#include <base/error/ErrorHandling.hh>

// STL headers:

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
    std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
	// TODO TODO TODO
    write_to_tracer( "Reset the MasalaFileInterpreterManager.  No file interpreters are registered." );
}

/// @brief Get the number of registered plugins.
masala::base::Size
MasalaFileInterpreterManager::total_file_interpreters() const {
    std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
    //return all_file_interpreter_map_.size();
	return 0; // TODO TODO TODO
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS FOR REGISTERING AND UNREGISTERING FILE INTERPRETERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add a file interpreter to the ones registered with this manager.
/// @details Throws if the file interpreter has already been added.
/// @param creator_in The creator for the new file interpreter plugin type.
void
MasalaFileInterpreterManager::register_file_interpreter(
	MasalaFileInterpreterCreatorCSP const & creator_in
) {
	std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
	protected_register_file_interpreter( creator_in );	
}

/// @brief Add some new file interpreters to the ones registered with this manager.
/// @details Throws if any of the file interpreters has already been added.
/// @param creators_in A vector of creators for the new file interpreter plugin types.
void
MasalaFileInterpreterManager::register_file_interpreters(
	std::vector< MasalaFileInterpreterCreatorCSP > const & creators_in
) {
	std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
	for( MasalaFileInterpreterCreatorCSP const & creator_in : creators_in ) {
		protected_register_file_interpreter( creator_in );
	}
}


} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala
