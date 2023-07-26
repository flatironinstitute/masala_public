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

/// @file src/base/managers/engine/MasalaDataRepresentation.cc
/// @brief A pure virtual base class class for particular representations
/// of data that can be requested by engines for efficient manipulation of
/// those data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/MasalaDataRepresentation.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {


////////////////////////////////////////////////////////////////////////////////
// DATA REPRESENTATION CATEGORIES, COMPATIBILITY, AND PROPERTIES FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the properties that this MasalaDataRepresentation has.  (Note that this can be
/// a non-exhaustive list.  If one data representation says it has the property
/// "linearly-scaling", another could also be linearly scaling despite not listing this.)
/// @note Can be overridden by derived classes.  The base implementation lists
/// no properties.
std::vector< std::string >
MasalaDataRepresentation::get_present_data_representation_properties() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties that this MasalaDataRepresentation DEFINITELY lacks.
/// Note that this is inevitably a non-exhaustive list.
/// @note Can be overridden by derived classes.  The base implementation lists
/// no properties.
std::vector< std::string >
MasalaDataRepresentation::get_absent_data_representation_properties() const {
    return std::vector< std::string >{};
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
