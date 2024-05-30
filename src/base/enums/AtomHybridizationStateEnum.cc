/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/base/enums/AtomHybridizationStateEnum.cc
/// @brief Implementations for utility functions for the enum for chemical bond type.
/// @details Needs to be declared in masala::base to be accessible to API definitions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#include <base/enums/AtomHybridizationStateEnum.hh>

// Base headers
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace base {
namespace enums {

/// @brief Utility function to get hybridization state string from hybridization state enum.
std::string
string_from_atom_hybridization_state_enum(
	AtomHybridizationState const hybstate
) {
	switch(hybstate) {
		case AtomHybridizationState::UNKNOWN_HYBRIDIZATION_STATE :
			return "unknown";
		case AtomHybridizationState::sp3 :
			return "sp3";
		case AtomHybridizationState::sp2 :
			return "sp2";
		case AtomHybridizationState::sp :
			return "sp";
		case AtomHybridizationState::s :
			return "s";
		case AtomHybridizationState::OTHER_HYBRIDIZATION_STATE :
			return "other";
		default:
			MASALA_THROW( "masala::base::enums", "string_from_atom_hybridization_state_enum",
				"Invalid hybridization state provided to this function!"
			);
	}
	return "";
}

/// @brief Utility function to get hybridization state enum from hybridization state string.
/// @details Returns INVALID_HYBRIDIZATION_STATE if string can't be parsed.
AtomHybridizationState
enum_from_atom_hybridization_state_string(
	std::string const & hybstate_string
) {
	using masala::base::Size;
	for( Size i(0); i<=static_cast<Size>(AtomHybridizationState::N_HYBRIDIZATION_STATES); ++i ) {
		if( string_from_atom_hybridization_state_enum( static_cast<AtomHybridizationState>(i) ) == hybstate_string ) {
			return static_cast<AtomHybridizationState>(i);
		}
	}
	return AtomHybridizationState::INVALID_HYBRIDIZATION_STATE;
}

/// @brief Get a list of all hybridization states, separated by a delimiter (e.g. ", ").
/// @details If include_and is true, the final entry is preceded by "and".
std::string
list_all_hybridization_states(
	std::string const & delimiter,
	bool const include_and
) {
	std::ostringstream ss;
	using masala::base::Size;
	for( Size i(0); i<=static_cast<Size>(AtomHybridizationState::N_HYBRIDIZATION_STATES); ++i ) {
		if( i>0 ) {
			ss << delimiter;
		}
		if( include_and && i == static_cast<Size>(AtomHybridizationState::N_HYBRIDIZATION_STATES) ) {
			ss << "and ";
		}
		ss << string_from_atom_hybridization_state_enum( static_cast<AtomHybridizationState>(i) );
	}
	return ss.str();
}

} // namespace enums
} // namespace base
} // namespace masala