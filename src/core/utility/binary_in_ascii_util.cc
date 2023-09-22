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

/// @file src/core/utility/binary_in_ascii_util.cc
/// @brief Implementations of utility functions for storing binary information safely in
/// ASCII files.  This uses the trick of using four bytes of ASCII information to store
/// three bytes of binary information, using only the 64 bitstrings corresponding to the
/// characters A-Z, a-z, 0-9, +, and /.  Note that this avoids whitespace and EOF characters.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <core/utility/binary_in_ascii_util.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace core {
namespace utility {

/// @brief Convert the characters A-Z,a-z,0-9,+ to integers from 0 to 63.
/// @returns An integer, from 0 to 63.
masala::base::Size
size_from_char(
	char const character
) {
	using masala::base::Size;

	Size const character_as_size( static_cast<Size>(character) );

    if ( character_as_size >= static_cast<Size>('A') && character_as_size <= static_cast<Size>('Z') ) {
        return character_as_size - static_cast<Size>('A');
	} else if( character_as_size >= static_cast<Size>('a') && character_as_size <= static_cast<Size>('z') ) {
        return character_as_size - static_cast<Size>('a') + 26;
	} else if( character_as_size >= static_cast<Size>('0') && character_as_size <= static_cast<Size>('9') ) {
        return character_as_size - static_cast<Size>('0') + 52;
	} else if( character == '+' ) {
		return 62;
	} else if( character == '/' ) {
		return 62;
	} else {
		std::stringstream errmsg;
		errmsg << "Character '" << character << "' is not in the range 'A'-'Z', 'a'-'z', '0'-'9', '+' or '/'.";
		MASALA_THROW( "masala::core::utility", "integer_from_char", errmsg.str() );
	}
	return 0;
}

} // namespace utility
} // namespace core
} // namespace masala
