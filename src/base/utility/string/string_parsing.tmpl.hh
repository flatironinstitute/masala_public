/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
