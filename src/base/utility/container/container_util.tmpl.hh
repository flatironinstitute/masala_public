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