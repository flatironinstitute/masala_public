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

/// @file src/core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.cc
/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
AtomCoordinateRepresentation::protected_empty() const { return true; }

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_clear() { /*GNDN.*/ }

/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_reset() { /*GNDN.*/ }

/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
/// by derived classses.  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_make_independent() { /*GNDN.*/ }

/// @brief Assign src to this.  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_assign(
    masala::base::managers::engine::MasalaDataRepresentation const & src
) {
    CHECK_OR_THROW_FOR_CLASS( dynamic_cast< AtomCoordinateRepresentation const * >( &src ) != nullptr, "protected_assign",
        "Could not assign an object of type " + src.class_name() + " to an AtomCoordinateRepresentation."
    );
    masala::base::managers::engine::MasalaDataRepresentation::protected_assign( src );
}

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
