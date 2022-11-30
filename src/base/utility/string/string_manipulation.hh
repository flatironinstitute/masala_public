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

/// @file src/base/utility/string/string_manipulation.hh
/// @brief Functions for conveniently manipulating strings.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_utility_string_string_manipulation_hh
#define Masala_src_base_utility_string_string_manipulation_hh

// STL headers
#include <vector>
#include <string>

namespace masala {
namespace base {
namespace utility {
namespace string {

    /// @brief Split a string by newline (\n or \r) characters.
    std::vector< std::string >
    split_by_newlines(
        std::string const & string_in
    );

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala

#endif //Masala_src_base_utility_string_string_manipulation_hh
