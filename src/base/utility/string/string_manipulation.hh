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

    /// @brief Split a string by a user-defined character.
    std::vector< std::string >
    split_by_character(
        std::string const & string_in,
        char const character_for_split
    );

    /// @brief Split a string by a user-defined set of characters.
    /// @details Any of the characters in the second string can indicate a split point.
    std::vector< std::string >
    split_by_characters(
        std::string const & string_in,
        std::string const & characters_for_split
    );

    /// @brief Convert a string to uppercase.
    std::string
    to_uppercase(
        std::string const & input
    );

    /// @brief Convert a string to lowercase.
    std::string
    to_lowercase(
        std::string const & input
    );

    /// @brief Trim whitespace from left.
    std::string
    ltrim(
        std::string const & input,
        std::string const & chars_to_trim=" \t\n\r"
    );

    /// @brief Trim whitespace from right.
    std::string
    rtrim(
        std::string const & input,
        std::string const & chars_to_trim=" \t\n\r"
    );

    /// @brief Trim whitespace from both ends of a string.
    std::string
    trim(
        std::string const & input,
        std::string const & chars_to_trim=" \t\n\r"
    );

    /// @brief Replace text pattern in string.
    void
    replace_all_instances_of_text(
        std::string & string_to_modify,
        std::string const & text_to_find,
        std::string const & replacement_text
    );

} // namespace string
} // namespace utility
} // namespace base
} // namespace masala

#endif //Masala_src_base_utility_string_string_manipulation_hh
