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

/// @file src/core/chemistry/atoms/data/AtomData.cc
/// @brief A container data for additional optional data that might be
/// attached to an atom.
/// @details Note that this is a pure virtual base class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/data/AtomData.hh>

// Core headers:

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace data {

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void AtomData::make_independent() {}

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala