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

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {

////////////////////////////////////////////////////////////////////////////////
// DATA REPRESENTATION CATEGORIES, COMPATIBILITY, AND PROPERTIES FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the MasalaEngines that with which this data representation plugin
/// is DEFINITELY NOT compatible.  (There may be other engines with which it is also
/// not compatible, so this is not necessarily an exhaustive list.)
/// @details The default implementation returns an empty list.
/// @note Can be implemented by derived classes.  The list is by full name (i.e.
/// namespace + name), so for instance
/// "specialized_masala_plugins::optimizers::SpecializedChargeOptimizer".
std::vector< std::string >
MasalaDataRepresentation::get_incompatible_masala_engines() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties that this MasalaDataRepresentation has.  (Note that this can be
/// a non-exhaustive list.  If one data representation says it has the property
/// "linearly-scaling", another could also be linearly scaling despite not listing this.)
/// @note Can be overridden by derived classes.  The base implementation lists
/// no properties.
std::vector< std::string >
MasalaDataRepresentation::get_present_data_representation_properties() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation that might possibly be present.
/// @details Obviously, this is a non-exhuastive list.
/// @returns The base class returns an empty list.  Overrides could return other lists.
std::vector< std::string >
MasalaDataRepresentation::get_possibly_present_data_representation_properties() const {
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

/// @brief Get the properties of this MasalaDataRepresentation that might possibly be absent.
/// @details Obviously, this is a non-exhuastive list.
/// @returns The base class returns an empty list.  Overrides could return other lists.
std::vector< std::string >
get_possibly_absent_data_representation_properties() const {
    return std::vector< std::string >{};
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
