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

/// @file src/core_api/base_classes/chemistry/atoms/data/PluginAtomData.cc
/// @brief Implementations for a container for additional optional data that might be
/// attached to an atom.
/// @details Note that this is a pure virtual base class for plugin
/// atom data containers.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core_api/base_classes/chemistry/atoms/data/PluginAtomData.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

namespace masala {
namespace core_api {
namespace base_classes {
namespace chemistry {
namespace atoms {
namespace data {

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void
PluginAtomData::protected_make_independent() {
    Parent::protected_make_independent();
}

/// @brief Assign src to this.
/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
void
PluginAtomData::protected_assign(
    masala::core::chemistry::atoms::data::AtomData const & src
) {
    PluginAtomData const * src_ptr_cast( dynamic_cast< PluginAtomData const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_ptr_cast != nullptr, "protected_assign",  
        "Could not assign an object of type " + src.class_name() + " to an object of type PluginAtomData."
    );

    Parent::protected_assign( src );
}

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace base_classes
} // namespace core_api
} // namespace masala