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

/// @file src/core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.cc
/// @brief A container of atom coordinates, using the Eigen linear algebra library's data structures.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/utility/container/container_util.tmpl.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
AtomCoordinateRepresentationSP
EigenLinalgCartesianAtomCoordinateRepresentation::clone() const {
    return masala::make_shared< EigenLinalgCartesianAtomCoordinateRepresentation >(*this);
}

/// @brief Returns "EigenLinalgCartesianAtomCoordinateRepresentation".
std::string
EigenLinalgCartesianAtomCoordinateRepresentation::class_name() const {
    return "EigenLinalgCartesianAtomCoordinateRepresentation";
}

/// @brief Returns "masala::core::chemistry::atoms::coordinates".
std::string
EigenLinalgCartesianAtomCoordinateRepresentation::class_namespace() const {
    return "masala::core::chemistry::atoms::coordinates";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


/// @brief Replace an atom instance with a new one.
/// @details Used for deep cloning, since the AtomCoordinateRepresentation subclasses do not
/// implement a deep_clone() function.
/// @note Must be implemented by derived classes.
void
EigenLinalgCartesianAtomCoordinateRepresentation::replace_atom_instance(
    AtomInstanceCSP const & old_instance,
    AtomInstanceCSP const & new_instance
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count( old_instance ) == 1, "replace_atom_instance", "Could not replace atom.  Old atom is not present!" );
    masala::base::Size const col_index( atom_instance_to_column_.at(old_instance) );
    atom_instance_to_column_.erase(old_instance);
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count(new_instance) == 0, "replace_atom_instance", "Could not replace atom.  New atom is already present!" );
    atom_instance_to_column_[new_instance] = col_index;
}

/// @brief Add an atom.
/// @note Must be implemented by derived classes.
void
EigenLinalgCartesianAtomCoordinateRepresentation::add_atom_instance(
    AtomInstanceCSP const & new_atom,
    std::array< masala::base::Real, 3 > const & new_atom_coordinates
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count(new_atom) == 0, "add_atom_instance", "Atom has already been added!" );
    masala::base::Size const natoms_before( atom_coordinates_.cols() );
    atom_instance_to_column_[ new_atom ] = natoms_before;
    atom_coordinates_.conservativeResize( Eigen::NoChange, natoms_before + 1 );
    atom_coordinates_(0, natoms_before ) = new_atom_coordinates[0]; 
    atom_coordinates_(1, natoms_before ) = new_atom_coordinates[1];
    atom_coordinates_(2, natoms_before ) = new_atom_coordinates[2];
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_coordinates_.cols() >= 0, "add_atom_instance", "Somehow, the number of columns in the atom_coordinates_ matrix is negative.  This is a program error.  Please contact a developer." )
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( static_cast< masala::base::Size >( atom_coordinates_.cols() ) == atom_instance_to_column_.size(), "add_atom_instance", "Mismatch in map and matrix sizes!" );
}

/// @brief Get the coordinates of an atom.
/// @note Must be implemented by derived classes.
std::array< masala::base::Real, 3 > const
EigenLinalgCartesianAtomCoordinateRepresentation::get_atom_coordinates(
    AtomInstanceCSP const & atom
) const {
    auto const it( atom_instance_to_column_.find( atom ) );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( it != atom_instance_to_column_.end(), "get_atom_coordinates", "Atom not found in molecules object!" );
    masala::base::Size const column( it->second );
    return std::array< masala::base::Real, 3 >{ atom_coordinates_(0, column), atom_coordinates_(1, column), atom_coordinates_(2, column) };
}

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
