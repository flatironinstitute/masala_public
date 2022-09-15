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

/// @file src/base/utility/string/string_manipulation.cc
/// @brief Functions for conveniently manipulating strings.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <base/utility/string/string_manipulation.hh>

// Base headers
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>

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

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala
