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

/// @file src/base/managers/plugin_module/MasalaPluginLibraryManager.cc
/// @brief A static singleton for managing plugin libaries for Masala.
/// @details This manages the .dll (Windows), .so (Linux), or .dylib (MacOS)
/// dyanmic-link libraries that are loaded, which contain plugin modules.
/// The MasalaPluginModuleManager in turn manages the plugins contained by
/// these libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/plugin_module/MasalaPluginLibraryManager.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>
#include <base/managers/disk/MasalaDiskManager.hh>

// STL headers:
#include <string>
#include <exception>
#include <dlfcn.h>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaPluginLibraryManagerHandle
MasalaPluginLibraryManager::get_instance() {
    static MasalaPluginLibraryManager plugin_manager;
    return &plugin_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaPluginLibraryManager".
std::string
MasalaPluginLibraryManager::class_name() const {
    return "MasalaPluginLibraryManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::plugin_module".
std::string
MasalaPluginLibraryManager::class_namespace() const {
    return "masala::base::managers::plugin_module";
}

/// @brief Completely reset the manager.
/// @details Unregisters all plugin libraries.
/// @note Calls reset() on the MasalaPluginModuleManager.
void
MasalaPluginLibraryManager::reset() {
    std::lock_guard< std::mutex > lock( plugin_libraries_mutex_ );
    MasalaPluginModuleManager::get_instance()->reset();
    for(
        std::map< std::string, void * >::iterator it( plugin_libraries_name_to_handle_map_.begin() );
        it != plugin_libraries_name_to_handle_map_.end();
        ++it
    ) {
        dlclose( it->second );
    }
    plugin_libraries_name_to_handle_map_.clear();
}

/// @brief Get the number of registered plugin libraries.
masala::base::Size
MasalaPluginLibraryManager::total_plugin_libraries() const {
    std::lock_guard< std::mutex > lock( plugin_libraries_mutex_ );
    return plugin_libraries_name_to_handle_map_.size();
}

/// @brief Load and register all the plugin modules in a Masala plugin library.
/// @details This calls the registration function for the library.  It is expected
/// that (a) the function is named with a C-style name (i.e. not C++ mangled by the
/// compiler), and (b) the registration function is "void register_library()".
/// @note The 'extern "C"' keyword can be used in a function declaration to direct
/// the compiler to make that function available with C-style naming in the compiled
/// binary.
void
MasalaPluginLibraryManager::load_and_register_plugin_library(
	std::string const & dynamic_link_library_path_and_filename,
	bool const throw_on_failure/*=false*/
) {
	std::string const abspath( disk::MasalaDiskManager::get_instance()->get_absolute_path( dynamic_link_library_path_and_filename ) );
	std::lock_guard< std::mutex > lock( plugin_libraries_mutex_ );

	void * handle; // A handle for the dynamic library.

	// Try to load the dynamic library, and handle errors:
	try {
		handle = dlopen( abspath.c_str(), RTLD_NOW );
		char * errormsg;
		CHECK_OR_THROW_FOR_CLASS( ( errormsg = dlerror() ) != NULL, "load_and_register_plugin_library", std::string( errormsg ) );
		CHECK_OR_THROW_FOR_CLASS( handle != nullptr, "load_and_register_plugin_library", "Pointer handle was null." );
	} catch( std::exception & except ) {
		if( throw_on_failure ) {
			MASALA_THROW(
				class_namespace_and_name(), "load_and_register_plugin_library",
				"Unable to load dynamic link library \"" + dynamic_link_library_path_and_filename + "\".  Error was:\n" + except.what()
			);
		} else {
			write_to_tracer( "Warning: unable to load dynamic link library \"" + dynamic_link_library_path_and_filename + "\".\n"
				"Error message was: " + except.what() + "\nRecovering and carrying on."
			);
			return;
		}
	}
	dlerror(); //Clear error message.

	// Try to register the dynamic library, and handle errors:
	void (*registration_fxn)();
	try {
		registration_fxn = dlsym( handle, "register_library" );
		char * errormsg;
		CHECK_OR_THROW_FOR_CLASS( ( errormsg = dlerror() ) != NULL, "load_and_register_plugin_library", std::string( errormsg ) );
		CHECK_OR_THROW_FOR_CLASS( registration_fxn != nullptr, "load_and_register_plugin_library", "Function pointer was null." );
	} catch( std::exception & except ) {
		if( throw_on_failure ) {
			MASALA_THROW(
				class_namespace_and_name(), "load_and_register_plugin_library",
				"Unable to find register_library() function in dynamic link library \"" + dynamic_link_library_path_and_filename + "\".  Error was:\n" + except.what()
			);
		} else {
			write_to_tracer( "Warning: unable to find register_library() function in dynamic link library \"" + dynamic_link_library_path_and_filename + "\".\n"
				"Error message was: " + except.what() + "\nRecovering and carrying on."
			);
			return;
		}
	}
	dlerror(); //Clear error message.

	*registration_fxn();
}

/// @brief Iterate through all sub-directories in a directory, and load all
/// plugins in each subdirectory.  (Not recursive.)
/// @details This also registers all plugin modules by calling the appropriate
/// registration function for each library.  It is expected that (a) the function
/// is named with a C-style name (i.e. not C++ mangled by the compiler), (b) the
/// registration function is implemented in libregistration_api.so, libregistration_api.dll,
/// or libregistration_api.dylib (depending on whether this is Windows, Linux, or MacOS,
/// respectively), and (c) the registration function is "void register_library()".
/// @note The 'extern "C"' keyword can be used in a function declaration to direct
/// the compiler to make that function available with C-style naming in the compiled
/// binary.
void
MasalaPluginLibraryManager::load_and_register_plugin_libraries_in_subdirectories(
    std::string const & path_to_plugin_directory,
	bool const throw_on_failure /*=false*/
) {
	using namespace base::managers::disk;

#ifdef _WIN32
	std::string const expected_libfile( "registration_api.dll" );
#elif __linux__
	std::string const expected_libfile( "libregistration_api.so" );
#elif __APPLE__
	std::string const expected_libfile( "libregistration_api.dylib" );
#endif

	MasalaDiskManagerHandle const diskmanager( MasalaDiskManager::get_instance() );
	std::vector< std::string > const subdirs( diskmanager->get_subdirectories( path_to_plugin_directory ) );
	for( std::string const & subdir : subdirs ) {
		std::vector< std::string > const files( diskmanager->get_files( subdir ) );
		for( std::string const & path_and_file : files ) {
			std::string const file( diskmanager->filename_from_path_and_filename( path_and_file ) );
			if( file == expected_libfile ) {
				load_and_register_plugin_library( path_and_file, throw_on_failure );
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala
