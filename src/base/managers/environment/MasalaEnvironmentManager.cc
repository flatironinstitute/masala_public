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

/// @file src/base/managers/environment/MasalaEnvironmentManager.cc
/// @brief A static singleton for managing environment variables.
/// @details All environment variables are queried once and cached by this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/environment/MasalaEnvironmentManager.hh>

// Base headers:
#include <base/managers/environment/MasalaEnvironmentVariable.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace environment {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Instantiate the static singleton and get a handle to it.
MasalaEnvironmentManagerHandle
MasalaEnvironmentManager::get_instance() {
    static const MasalaEnvironmentManager disk_manager;
    return &disk_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Destructor.
MasalaEnvironmentManager::~MasalaEnvironmentManager() {
    reset();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object (i.e. delete all the owned MasalaEnvironmentVariables.)
void
MasalaEnvironmentManager::reset() {
    std::lock_guard< std::mutex > lock( environment_manager_mutex_ );
    for(
        std::map< std::string, MasalaEnvironmentVariable const * >::iterator it( environment_variables_.begin() );
        it != environment_variables_.end();
        ++it
    ) {
        delete (it->second);
    }
    environment_variables_.clear();
}

/// @brief Get the name of this object.
/// @details Returns "MasalaEnvironmentManager".
std::string
MasalaEnvironmentManager::class_name() const {
    return "MasalaEnvironmentManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::environment".
std::string
MasalaEnvironmentManager::class_namespace() const {
    return "masala::base::managers::environment";
}

/// @brief Get the value of an environment variable.
/// @details If the environment variable is set, then value_receiver is
/// populated with its value.  If not, then this function returns false,
/// and the value of value_receiver is not changed.
/// @note Triggers read from system environment the first time that a
/// value is accessed.
bool
MasalaEnvironmentManager::get_environment_variable(
    std::string const & environment_variable_name,
    std::string & value_receiver
) const {
    std::lock_guard< std::mutex > lock( environment_manager_mutex_ );
    std::map< std::string, MasalaEnvironmentVariable const * >::const_iterator it( environment_variables_.find( environment_variable_name ) );
    if( it == environment_variables_.end() ) {
        char * envvar_pointer( getenv( environment_variable_name.c_str() ) );
        if( envvar_pointer == nullptr ) {
            write_to_tracer( "Environment variable \"" + environment_variable_name + "\" was not set." );
            environment_variables_[environment_variable_name] = new MasalaEnvironmentVariable( false, "" );
            return false;
        } else {
            std::string const envvar_string( envvar_pointer );
            write_to_tracer( "Environment variable \"" + environment_variable_name + "\" was found with value \"" + envvar_string + "\"." );
            environment_variables_[environment_variable_name] = new MasalaEnvironmentVariable( true, envvar_string ); // Store for future reference.
            value_receiver = envvar_string;
            return true;
        }
    } else {
        if( it->second->env_var_was_set() ) {
            value_receiver = it->second->env_var_value();
            return true;
        } else {
            return false;
        }
    }
    return false; //Keep the compiler happy.
}

} // namespace environment
} // namespace managers
} // namespace base
} // namespace masala
