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

/// @file src/core_api/utility/binary_in_ascii_util.cc
/// @brief Implementations of API utility functions for storing binary information safely in
/// ASCII files.  This uses the trick of using four bytes of ASCII information to store
/// three bytes of binary information, using only the 64 bitstrings corresponding to the
/// characters A-Z, a-z, 0-9, +, and /.  Note that this avoids whitespace and EOF characters.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <core_api/utility/binary_in_ascii_util.hh>

// Core headers:
#include <core/utility/binary_in_ascii_util.hh>

namespace masala {
namespace core_api {
namespace utility {

/// @brief Given a pointer to the first byte of a block of memory and a string, interpret every
/// four bytes of the string as three bytes of data and start filling the block of memory.
/// @details Fills up to max_bytes bytes, or until the string is exhausted, whichever comes first.
/// @returns The number of bytes filled.
masala::base::Size
decode_data_from_string(
	unsigned char * data,
	std::string const & datastring,
	masala::base::Size const max_bytes
) {
	return masala::core::utility::decode_data_from_string( data, datastring, max_bytes );
}

} // namespace utility
} // namespace core_api
} // namespace masala
