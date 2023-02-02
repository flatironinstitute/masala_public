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

/// @file src/core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh
/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh
#define Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh

// Forward declarations:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.fwd.hh>

// Core headers:
#include <base/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationBase.hh>

// STL headers:
#include <set>
#include <array>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {


/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomCoordinateRepresentation : public masala::base::managers::engine::MasalaDataRepresentationBase {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    AtomCoordinateRepresentation() = default;

    /// @brief Copy constructor.
    AtomCoordinateRepresentation( AtomCoordinateRepresentation const & ) = default;

    // Destructor.
    ~AtomCoordinateRepresentation() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    AtomCoordinateRepresentationSP
    clone() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


    /// @brief Replace an atom instance with a new one.
    /// @details Used for deep cloning, since the AtomCoordinateRepresentation does not itself
    /// implement a deep_clone() function.
    /// @note Must be implemented by derived classes.
    virtual
    void
    replace_atom_instance(
        AtomInstanceCSP const & old_instance,
        AtomInstanceCSP const & new_instance
    ) = 0;

    /// @brief Add an atom.
    /// @note Must be implemented by derived classes.
    virtual
    void
    add_atom_instance(
        AtomInstanceCSP const & new_atom,
        std::array< masala::core::Real, 3 > const & new_atom_coordinates
    ) = 0;

    /// @brief Get the coordinates of an atom.
    /// @note Must be implemented by derived classes.
    virtual
    std::array< masala::core::Real, 3 > const
    get_atom_coordinates(
        AtomInstanceCSP const & atom
    ) const = 0;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

};

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh