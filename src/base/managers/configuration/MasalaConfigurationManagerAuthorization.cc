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

/// @file src/base/managers/configuration/MasalaConfigurationManagerAuthorization.cc
/// @brief A "key" class with a private constructor, which can only be instantiated by
/// the MasalaConfigurationManager, used to ensure that only the configuration manager
/// can instantiate configuration objects.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Base headers
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.hh>

// STL headers
#include <string>

namespace masala {
namespace base{
namespace managers{
namespace configuration{


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("MasalaConfigurationManagerAuthorization").
std::string
MasalaConfigurationManagerAuthorization::class_name() const {
    return "MasalaConfigurationManagerAuthorization";
}

/// @brief Get the class namespace ("masala::base::managers::configuration").
std::string
MasalaConfigurationManagerAuthorization::class_namespace() const {
    return "bas::managers::configuration";
}

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala
