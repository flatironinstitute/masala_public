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

/// @file src/base/utility/string/string_parsing.tmpl.hh
/// @brief Template functions for conveniently parsing strings.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_utility_string_string_parsing_tmpl_hh
#define Masala_src_base_utility_string_string_parsing_tmpl_hh

// STL headers
#include <sstream>

// Base headers
#include <base/api/names_from_types.tmpl.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace utility{
namespace string {

    /// @brief Parse a string and return an object of type T.
    /// @tparam T The type of the return value.
    /// @param string_in The string to parse.  The first whitespace-delimited thing in the
    /// string will be interpreted as a T and returned.
    /// @param eof_expected If true, this function throws if there's anything left in the
    /// string after the parse.  False by default.
    /// @returns The contents of the string, interpreted as type T.
    /// @note Throws if the string could not be interpreted as an object of type T.
    template< typename T >
    T
    parse_string(
        std::string const & string_in,
        bool const eof_expected=false
    ) {
        T returnval;
        std::istringstream ss( string_in );
        ss >> returnval;
        CHECK_OR_THROW( !( ss.fail() || ss.bad() ), "utility::string", "parse_string", "Could not interpret \"" + string_in + "\" as a value of type " + masala::base::api::name_from_type< T >(base::api::type<T>()) + "!" );
        if( eof_expected ) {
            CHECK_OR_THROW( ss.eof(), "utility::string", "parse_string", "Additional content found in string \"" + string_in + "\"." );
        }
        return returnval;
    }

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala

#endif //Masala_src_base_utility_string_string_parsing_tmpl_hh
