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
#include <base/managers/file_interpreter/MasalaFileInterpreterCreator.hh>
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
	masala::base::Size const n_interpreters( file_interpreters_by_name_.size() );
	file_interpreters_by_name_.clear();
	file_interpreters_by_file_type_descriptor_.clear();
	file_interpreters_by_file_type_extension_.clear();
    write_to_tracer( "Reset the MasalaFileInterpreterManager, removing " + std::to_string( n_interpreters )
		+ " file interpreters.  No file interpreters are now registered."
	);
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
	private_register_file_interpreter( creator_in );	
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
		private_register_file_interpreter( creator_in );
	}
}

/// @brief Remove a file interpreter from the ones registered with this manager.
/// @details Throws if the file interpreter has not already been added.
/// @param creator_to_remove A creator for the file interpreter plugin type
/// to remove.
void
MasalaFileInterpreterManager::unregister_file_interpreter(
	MasalaFileInterpreterCreatorCSP const & creator_to_remove
) {
	std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
	private_unregister_file_interpreter( creator_to_remove );	
}

/// @brief Remove some file interpreters from the ones registered with this manager.
/// @details Throws if any of the file interpreters have not already been added.
/// @param creators_to_remove A vector of creators for the file interpreter plugin types
/// to remove.
void
MasalaFileInterpreterManager::unregister_file_interpreters(
	std::vector< MasalaFileInterpreterCreatorCSP > const & creators_to_remove
) {
	std::lock_guard< std::mutex > lock( file_interpreter_manager_mutex_ );
	for( MasalaFileInterpreterCreatorCSP const & creator_to_remove : creators_to_remove ) {
		private_unregister_file_interpreter( creator_to_remove );
	}
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Register a file interpreter creator.
/// @details To be called from a mutex-locked context (i.e. does not lock the mutex itself).
/// Throws if the file interpreter has already been added.
void
MasalaFileInterpreterManager::private_register_file_interpreter(
	MasalaFileInterpreterCreatorCSP const & creator_in
) {
	// Register by name:
	std::string const fi_name( creator_in->get_plugin_object_namespace_and_name() );
	CHECK_OR_THROW_FOR_CLASS( file_interpreters_by_name_.count( fi_name ) == 0,
		"private_register_file_interpreter",  "The " + fi_name + " file interpreter has already been "
		"registered with the MasalaFileInterpreterManager!"
	);
	file_interpreters_by_name_[fi_name] = creator_in;

	// Register by file descriptor:
	std::vector< std::string > const descriptors( creator_in->get_file_interpreter_file_descriptors() );
	for( std::string const & descriptor : descriptors ) {
		std::map< std::string, std::vector< MasalaFileInterpreterCreatorCSP > >::iterator it_desc(
			file_interpreters_by_file_type_descriptor_.find( descriptor )
		);
		if( it_desc != file_interpreters_by_file_type_descriptor_.end() ) {
			it_desc->second.push_back( creator_in );
		} else {
			file_interpreters_by_file_type_descriptor_[ descriptor ] = { creator_in };
		}
	}

	// Register by file extension:
	std::vector< std::string > const extensions( creator_in->get_file_interpreter_file_extensions() );
	for( std::string const & extension : extensions ) {
		std::map< std::string, std::vector< MasalaFileInterpreterCreatorCSP > >::iterator it_ext(
			file_interpreters_by_file_type_extension_.find( extension )
		);
		if( it_ext != file_interpreters_by_file_type_extension_.end() ) {
			it_ext->second.push_back( creator_in );
		} else {
			file_interpreters_by_file_type_extension_[ extension ] = { creator_in };
		}
	}

	write_to_tracer( "Registering " + fi_name + " with the MasalaFileInterpreterManager." );
}

/// @brief Unregister a file interpreter creator.
/// @details To be called from a mutex-locked context (i.e. does not lock the mutex itself).
/// Throws if the file interpreter has not been added.
void
MasalaFileInterpreterManager::private_unregister_file_interpreter(
	MasalaFileInterpreterCreatorCSP const & creator_to_remove
) {
	// Unregister by name:
	std::string const fi_name( creator_to_remove->get_plugin_object_namespace_and_name() );
	std::map< std::string, MasalaFileInterpreterCreatorCSP >::iterator it_name(
		file_interpreters_by_name_.find( fi_name )
	);
	CHECK_OR_THROW_FOR_CLASS( it_name != file_interpreters_by_name_.end(),
		"private_unregister_file_interpreter",  "The " + fi_name + " file interpreter has not been "
		"registered with the MasalaFileInterpreterManager!"
	);
	file_interpreters_by_name_.erase( it_name );

	// Unregister by file descriptor:
	std::vector< std::string > const descriptors( creator_to_remove->get_file_interpreter_file_descriptors() );
	for( std::string const & descriptor : descriptors ) {
		std::map< std::string, std::vector< MasalaFileInterpreterCreatorCSP > >::iterator it_desc(
			file_interpreters_by_file_type_descriptor_.find( descriptor )
		);
		CHECK_OR_THROW_FOR_CLASS( it_desc != file_interpreters_by_file_type_descriptor_.end(),
			"private_unregister_file_interpreter",  "The \"" + descriptor + "\" file format descriptor has not been "
			"registered with the MasalaFileInterpreterManager!  This is a program error.  It ought not to happen."
			"  Please consult a developer."
		);
		Size counter(0);
		std::vector< MasalaFileInterpreterCreatorCSP > & vec( it_desc->second );
		for( std::vector< MasalaFileInterpreterCreatorCSP >::iterator itvec( vec.begin() ); itvec != vec.end(); ) {
			if( (*itvec)->get_plugin_object_namespace_and_name() == fi_name ) {
				vec.erase(itvec);
				++counter;
			} else {
				++itvec;
			}
		}
		if( vec.empty() ) {
			file_interpreters_by_file_type_descriptor_.erase( it_desc );
		}
		CHECK_OR_THROW_FOR_CLASS( counter > 0, "private_unregister_file_interpreter", "Could not find a creator "
			"for " + fi_name + " file interpreters in the list of creators for files of descriptor \"" +
			descriptor + ".  This is a program error; it ought not to happen.  Please consult a developer."
		);
	}

	// Register by file extension:
	std::vector< std::string > const extensions( creator_to_remove->get_file_interpreter_file_extensions() );
	for( std::string const & extension : extensions ) {
		std::map< std::string, std::vector< MasalaFileInterpreterCreatorCSP > >::iterator it_ext(
			file_interpreters_by_file_type_extension_.find( extension )
		);
		CHECK_OR_THROW_FOR_CLASS( it_ext != file_interpreters_by_file_type_extension_.end(),
			"private_unregister_file_interpreter",  "The \"" + extension + "\" file format extension has not been "
			"registered with the MasalaFileInterpreterManager!  This is a program error.  It ought not to happen."
			"  Please consult a developer."
		);
		Size counter(0);
		std::vector< MasalaFileInterpreterCreatorCSP > & vec( it_ext->second );
		for( std::vector< MasalaFileInterpreterCreatorCSP >::iterator itvec( vec.begin() ); itvec != vec.end(); ) {
			if( (*itvec)->get_plugin_object_namespace_and_name() == fi_name ) {
				vec.erase(itvec);
				++counter;
			} else {
				++itvec;
			}
		}
		if( vec.empty() ) {
			file_interpreters_by_file_type_extension_.erase( it_ext );
		}
		CHECK_OR_THROW_FOR_CLASS( counter > 0, "private_unregister_file_interpreter", "Could not find a creator "
			"for " + fi_name + " file interpreters in the list of creators for files of extension \"" +
			extension + ".  This is a program error; it ought not to happen.  Please consult a developer."
		);
	}

	write_to_tracer( "Unregistering " + fi_name + " from the MasalaFileInterpreterManager." );
}



} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala
