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

/// @file src/base/enums/AtomHybridizationStateEnum.hh
/// @brief Headers for utility functions for the enum for chemical bond type.
/// @details Needs to be declared in masala::base to be accessible to API definitions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_enums_AtomHybridizationStateEnum_hh
#define Masala_src_base_enums_AtomHybridizationStateEnum_hh

#include <base/enums/AtomHybridizationStateEnum.fwd.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace enums {

/// @brief Utility function to get hybridization state string from hybridization state enum.
std::string
string_from_atom_hybridization_state_enum(
	AtomHybridizationState const hybstate
);

/// @brief Utility function to get hybridization state enum from hybridization state string.
/// @details Returns INVALID_HYBRIDIZATION_STATE if string can't be parsed.
AtomHybridizationState
enum_from_atom_hybridization_state_string(
	std::string const & hybstate_string
);

/// @brief Get a list of all hybridization states, separated by a delimiter (e.g. ", ").
/// @details If include_and is true, the final entry is preceded by "and".
std::string
list_all_hybridization_states(
	std::string const & delimiter,
	bool const include_and
);

} // namespace enums
} // namespace base
} // namespace masala

#endif //Masala_src_base_enums_AtomHybridizationStateEnum_hh