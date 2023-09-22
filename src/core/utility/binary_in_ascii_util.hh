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

/// @file src/core/utility/binary_in_ascii_util.hh
/// @brief Prototypes of utility functions for storing binary information safely in
/// ASCII files.  This uses the trick of using four bytes of ASCII information to store
/// three bytes of binary information, using only the 64 bitstrings corresponding to the
/// characters A-Z, a-z, 0-9, +, and /.  Note that this avoids whitespace and EOF characters.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_utility_binary_in_ascii_util_hh
#define Masala_src_core_utility_binary_in_ascii_util_hh

// Masala base headers:
#include <base/types.hh>

namespace masala {
namespace core {
namespace utility {

	/// @brief Convert the characters A-Z,a-z,0-9,+ to integers from 0 to 63.
	/// @returns An integer, from 0 to 63.
	masala::base::Size
	decode_size_from_char(
		char const character
	);

} // namespace utility
} // namespace core
} // namespace masala

#endif // Masala_src_core_utility_binary_in_ascii_util_hh
