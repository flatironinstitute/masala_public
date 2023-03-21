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

/// @file src/base/utility/string/string_comparison.cc
/// @brief Functions for conveniently manipulating strings.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <base/utility/string/string_comparison.hh>

// Base headers
#include <base/types.hh>

// STL headers

namespace masala {
namespace base {
namespace utility {
namespace string {

/// @brief Determine whether a string starts with another string.
/// @details Always returns false if expected_start is longer than input_string.
bool
string_starts_with(
	std::string const & input_string,
	std::string const & expected_start
) {
	using masala::base::Size;
	Size const input_len( input_string.size() );
	Size const expected_len( expected_start.size() );
	if( expected_len > input_len ) return false;
	return( input_string.substr( 0, expected_len ) == expected_start );
}

/// @brief Determine whether a string ends with another string.
/// @details Always returns false if expected_ending is longer than input_string.
bool
string_ends_with(
	std::string const & input_string,
	std::string const & expected_ending
) {
	using masala::base::Size;
	Size const input_len( input_string.size() );
	Size const expected_len( expected_ending.size() );
	if( expected_len > input_len ) return false;
	return( input_string.substr( input_len - expected_len, expected_len ) == expected_ending );
}

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala
