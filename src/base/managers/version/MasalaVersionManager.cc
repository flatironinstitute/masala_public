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

/// @file src/base/managers/version/MasalaVersionManager.cc
/// @brief A static singleton for managing the version of Masala's core library and
/// of plugin libraries, along with any inter-library version dependencies.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/version/MasalaVersionManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/version/masala_version.hh>
#include <base/managers/version/MasalaModuleVersionInfo.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:

namespace masala {
namespace base {
namespace managers {
namespace version {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaVersionManagerHandle
MasalaVersionManager::get_instance() {
    static MasalaVersionManager version_manager;
    return &version_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
MasalaVersionManager::MasalaVersionManager() :
    masala::base::MasalaObject()
{
    std::lock_guard< std::mutex > lock( masala_version_manager_mutex_ );
    module_version_infos_[ "Masala" ] = masala::make_shared< MasalaModuleVersionInfo >( "Masala", masala_version() );
}


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaVersionManager".
std::string
MasalaVersionManager::class_name() const {
    return "MasalaVersionManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::version".
std::string
MasalaVersionManager::class_namespace() const {
    return "masala::base::managers::version";
}

/// @brief Add information for a new library.
/// @details Stores the input directly, without cloning.
void
MasalaVersionManager::add_library_information(
    MasalaModuleVersionInfoCSP const & module_version_info
) {
    std::string const & libname( module_version_info->library_name() );
    std::lock_guard< std::mutex > lock( masala_version_manager_mutex_ );
    std::unordered_map< std::string, MasalaModuleVersionInfoCSP >::const_iterator it( module_version_infos_.find( libname ) );
    CHECK_OR_THROW_FOR_CLASS( it == module_version_infos_.end(), "add_library_information", "The library \""
        + libname + "\" has already been added to the version manager!"
    );
    module_version_infos_[libname] = module_version_info;
    write_to_tracer( "Added version information for library \"" + libname + "\" version " + module_version_info->version_string() + "." );
}

/// @brief Remove information for a library.
/// @details Throws if library name not registered.
void
MasalaVersionManager::remove_library_information(
    std::string const & library_name
) {
    std::lock_guard< std::mutex > lock( masala_version_manager_mutex_ );
    std::unordered_map< std::string, MasalaModuleVersionInfoCSP >::iterator it( module_version_infos_.find( library_name ) );
    CHECK_OR_THROW_FOR_CLASS( it != module_version_infos_.end(), "remove_library_information", "No library named \""
        + library_name + "\" was registered with the Masala version manager."
    );
    module_version_infos_.erase(it);
    write_to_tracer( "Removed version information for library \"" + library_name + "\"." );
}

/// @brief Check whether version requirements are satisfied.
/// @returns True if satisfied, false otherwise.  If false, the messages
/// string is populated with information about unsatisfied modules.
bool
MasalaVersionManager::check_version_requirements_satisfied(
    std::string & messages
) const {
    std::string messages_out;
    bool satisfied(true);
    std::lock_guard< std::mutex > lock( masala_version_manager_mutex_ );
    for(
        std::unordered_map< std::string, MasalaModuleVersionInfoCSP >::const_iterator it( module_version_infos_.begin() );
        it != module_version_infos_.end();
        ++it
    ) {
        MasalaModuleVersionInfo const & module_version_info( *(it->second) );
        satisfied &= module_version_info.check_version_requirements_satisfied( module_version_infos_, messages_out );
    }
    if(!satisfied) {
        messages = messages_out;
    }
    return satisfied;
}

/// @brief Get the number of versioned modules that have been registered
/// with this manager.
masala::base::Size
MasalaVersionManager::n_modules_registered() const {
    std::lock_guard< std::mutex > lock( masala_version_manager_mutex_ );
    return module_version_infos_.size();
}

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala
