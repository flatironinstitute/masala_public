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
#include <base/utility/string/string_manipulation.hh>

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

/// @brief Determinew whether two Masala class names match.
/// @details Names match if:
/// - They both contain namespace and name, and match fully.
/// - They both only name, and the name matches.
/// - One contains namespace and name, and the other contains only name, and the name matches.
bool
masala_class_names_match(
	std::string const & name1,
	std::string const & name2
) {
	if( name1 == name2 ) {
		return true;
	}
	std::vector< std::string > const namesplit1( split_by_characters( name1, ":" ) );
	std::vector< std::string > const namesplit2( split_by_characters( name2, ":" ) );
	if( (namesplit1.size() > 1 && namesplit2.size() == 1) || (namesplit1.size() == 1 && namesplit2.size() > 1) ) {
		return namesplit1[ namesplit1.size() - 1 ] == namesplit2[ namesplit2.size() - 1 ];
	}
	return false;
}

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala
