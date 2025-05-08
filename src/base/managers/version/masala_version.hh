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

/// @file src/base/managers/version/masala_version.hh
/// @brief Contains only a single function that returns the minor and major version of Masala's core libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

/// Base headers:
#include <base/types.hh>

/// STL headers:
#include <utility> // For std::pair

#define MASALA_MAJOR_VERSION 0
#define MASALA_MINOR_VERSION 10

namespace masala {
namespace base {
namespace managers {
namespace version {

    /// @brief Returns the major and minor version of Masala's core libraries.
    inline
    std::pair< masala::base::Size, masala::base::Size >
    masala_version() {
        return std::make_pair( MASALA_MAJOR_VERSION, MASALA_MINOR_VERSION );
    }

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala