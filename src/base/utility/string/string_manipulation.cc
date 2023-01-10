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

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala
