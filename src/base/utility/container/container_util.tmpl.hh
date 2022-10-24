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

/// @file src/base/utility/container/container_util.tmpl.hh
/// @brief Utility functions for dealing with STL containers.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_utility_container_container_util_tmpl_hh
#define Masala_src_base_utility_container_container_util_tmpl_hh

// STL headers
#include <algorithm>
#include <sstream>

namespace masala {
namespace base {
namespace utility {
namespace container {

    /// @brief Check whether an element exists in a container.
    template< class C, class T >
    bool
    has_value( C const & container, T const & value ) {
        return std::find( container.begin(), container.end(), value ) != container.end();
    }

    /// @brief Convert a vector to a string separated by a delimiter.
    template< class C >
    std::string
    container_to_string( C const & container, std::string const & delimiter ) {
        std::ostringstream ss;
        bool first(true);
        for( auto const & entry : container ) {
            if( first ) { first = false; }
            else { ss << delimiter; }
            ss << entry;
        }
        return ss.str();
    }

} // namespace container
} // namespace utility
} // namsespace base
} // namespace masala

#endif //Masala_src_base_utility_container_container_util_tmpl_hh