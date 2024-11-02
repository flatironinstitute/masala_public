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

/// @file src/base/utility/string/string_manipulation.cc
/// @brief Functions for conveniently manipulating strings.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <base/utility/string/string_manipulation.hh>

// Base headers
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>

// STL headers
#include <algorithm>
#include <sstream>

namespace masala {
namespace base {
namespace utility {
namespace string {

/// @brief Split a string by newline (\n or \r) characters.
std::vector< std::string >
split_by_newlines(
    std::string const & string_in
) {
    if( string_in.empty() ) {
        return std::vector< std::string >(); //Empty vector out if empty string in.
    }

    std::vector< std::string > outvec;

    signed long laststart(0), last_non_return(-1);
    bool in_returns(false);

    for( signed long i(0), imax(string_in.size()); i<imax; ++i ) {
        if( !in_returns ) {
            if( string_in[i] == '\n' || string_in[i] == '\r' ) {
                in_returns = true;
                last_non_return = i-1;
                continue;
            }
        } else {
            if( string_in[i] != '\n' && string_in[i] != '\r' ) {
                in_returns = false;
                if( !(laststart == 0 && last_non_return == -1) ) {
                    outvec.push_back( string_in.substr( laststart, last_non_return - laststart + 1 ) );
                }
                laststart = i;
                continue;
            }
        }
    }
    if( last_non_return >= laststart ) {
        outvec.push_back( string_in.substr( laststart, last_non_return - laststart + 1 ) );
    } else {
        outvec.push_back( string_in.substr( laststart ) );
    }
    return outvec;
}

/// @brief Split a string by a user-defined character.
std::vector< std::string >
split_by_character(
    std::string const & string_in,
    char const character_for_split
) {
    if( string_in.empty() ) {
        return std::vector< std::string >(); //Empty vector out if empty string in.
    }

    std::vector< std::string > outvec;

    signed long laststart(0), last_non_return(-1);
    bool in_specified_char(false);

    for( signed long i(0), imax(string_in.size()); i<imax; ++i ) {
        if( !in_specified_char ) {
            if( string_in[i] == character_for_split ) {
                in_specified_char = true;
                last_non_return = i-1;
                continue;
            }
        } else {
            if( string_in[i] != character_for_split ) {
                in_specified_char = false;
                if( !(laststart == 0 && last_non_return == -1) ) {
                    outvec.push_back( string_in.substr( laststart, last_non_return - laststart + 1 ) );
                }
                laststart = i;
                continue;
            }
        }
    }
    if( last_non_return >= laststart ) {
        outvec.push_back( string_in.substr( laststart, last_non_return - laststart + 1 ) );
    } else {
        outvec.push_back( string_in.substr( laststart ) );
    }
    return outvec;
}

/// @brief Split a string by a user-defined set of characters.
/// @details Any of the characters in the second string can indicate a split point.
std::vector< std::string >
split_by_characters(
    std::string const & string_in,
    std::string const & characters_for_split
) {
    if( string_in.empty() ) {
        return std::vector< std::string >(); //Empty vector out if empty string in.
    }

    std::vector< std::string > outvec;

    signed long laststart(0), last_non_return(-1);
    bool in_split_chars(false);

    for( signed long i(0), imax(string_in.size()); i<imax; ++i ) {
        if( !in_split_chars ) {
            if( characters_for_split.find( string_in[i] ) != std::string::npos  ) {
                in_split_chars = true;
                last_non_return = i-1;
                continue;
            }
        } else {
            if( characters_for_split.find( string_in[i] ) == std::string::npos ) {
                in_split_chars = false;
                if( !(laststart == 0 && last_non_return == -1) ) {
                    outvec.push_back( string_in.substr( laststart, last_non_return - laststart + 1 ) );
                }
                laststart = i;
                continue;
            }
        }
    }
    if( last_non_return >= laststart ) {
        outvec.push_back( string_in.substr( laststart, last_non_return - laststart + 1 ) );
    } else {
        outvec.push_back( string_in.substr( laststart ) );
    }
    return outvec;
}

/// @brief Convert a string to uppercase.
std::string
to_uppercase(
    std::string const & input
) {
    std::string strcopy( input );
    std::transform( strcopy.begin(), strcopy.end(), strcopy.begin(), ::toupper );
    return strcopy;
}

/// @brief Convert a string to lowercase.
std::string
to_lowercase(
    std::string const & input
) {
    std::string strcopy( input );
    std::transform( strcopy.begin(), strcopy.end(), strcopy.begin(), ::tolower );
    return strcopy;
}

/// @brief Trim whitespace from left.
std::string
ltrim(
    std::string const & input,
    std::string const & chars_to_trim//=" \t\n\r"
) {
    std::string output( input );
    output.erase(
        output.begin(),
        std::find_if(
            output.begin(), output.end(), [chars_to_trim](unsigned char curchar) {
                return chars_to_trim.find( curchar ) == chars_to_trim.npos;
            }
        )
    );
    return output;
}

/// @brief Trim whitespace from right.
std::string
rtrim(
    std::string const & input,
    std::string const & chars_to_trim//=" \t\n\r"
) {
    std::string output( input );
    output.erase(
        std::find_if(
            output.rbegin(), output.rend(), [chars_to_trim](unsigned char curchar) {
                return chars_to_trim.find( curchar ) == chars_to_trim.npos;
            }
        ).base(),
        output.end()
    );
    return output;
}

/// @brief Trim whitespace from both ends of a string.
std::string
trim(
    std::string const & input,
    std::string const & chars_to_trim//=" \t\n\r"
) {
    return rtrim(ltrim(input, chars_to_trim), chars_to_trim);
}

/// @brief Replace text pattern in string.
void
replace_all_instances_of_text(
    std::string & string_to_modify,
    std::string const & text_to_find,
    std::string const & replacement_text
) {
    CHECK_OR_THROW( replacement_text != text_to_find, "masala::base::utility::string", "replace_all_instances_of_text", "Text to find is identical to the replacement text! Please replace the text to find with something new." );
    size_t startloc( string_to_modify.find( text_to_find ) );
    while( startloc != std::string::npos ){
        string_to_modify.replace( startloc, text_to_find.size(), replacement_text );
        startloc = string_to_modify.find( text_to_find );
    }
}

/// @brief Take a string in camelcase (e.g. "SomethingLikeThis" ) and convert it to boxcar (e.g. "something_like_this").
std::string
camelcase_to_boxcar(
	std::string const & camelcase_string
) {
	using masala::base::Size;

	if( camelcase_string.empty() ) { return ""; }
	std::ostringstream boxcar_ss;
	boxcar_ss << std::tolower( camelcase_string[0] );
	if( camelcase_string.size() == 1 ) { return boxcar_ss.str(); }

	for( Size i(1); i<camelcase_string.size(); ++i ) {
		if(
			std::isupper( camelcase_string[i] ) &&
			( !std::isupper( camelcase_string[i-1] ) ) &&
			( camelcase_string[i-1] != '_' ) ) {
			boxcar_ss << "_";
		}
		boxcar_ss << std::tolower( camelcase_string[i] );
	}
	return boxcar_ss.str();
}

/// @brief Take a string in boxcar (e.g. "something_like_this") and convert it to camelcase (e.g. "SomethingLikeThis" ).
std::string
boxcar_to_camelcase(
	std::string const & boxcar_string
) {
	using masala::base::Size;

	if( boxcar_string.empty() ) { return ""; }

	std::ostringstream camelcase_ss;
	if( boxcar_string[0] != '_' ) {
		camelcase_ss << std::toupper( boxcar_string[0] );
	}
	if( boxcar_string.size() == 1 ) { return camelcase_ss.str(); }

	for( Size i(1); i<boxcar_string.size(); ++i ) {
		if( boxcar_string[i-1] == '_' ) {
			camelcase_ss << std::toupper( boxcar_string[i] );
		} else {
			if( boxcar_string[i] != '_' ) {
				camelcase_ss << std::tolower( boxcar_string[i] );
			}
		}
	}

	return camelcase_ss.str();
}

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala
