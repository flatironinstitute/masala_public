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

/// @file src/base/managers/configuration/ConfigurationBase.cc
/// @brief Pure virtual base class for containers that store configuration
/// settings for modules.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <base/managers/configuration/ConfigurationBase.hh>

namespace masala {
namespace base {
namespace managers {
namespace configuration {

/// @brief MasalaConfigurationManager-authorized constructor.
/// @details The MasalaConfigurationManagerAuthorization object is an object that only the
/// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
/// ConfigurationBase-derived object.
ConfigurationBase::ConfigurationBase(
    MasalaConfigurationManagerAuthorization const &
) : 
    masala::base::MasalaObject()
{}

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala
