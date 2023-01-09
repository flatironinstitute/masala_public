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
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

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
template< class T >
bool
MasalaEnvironmentManager::get_environment_variable(
    std::string const & environment_variable_name,
    T & value_receiver
) const {
    TODO TODO TODO
}

} // namespace environment
} // namespace managers
} // namespace base
} // namespace masala
