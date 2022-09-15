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
    return std::make_shared< EigenLinalgCartesianAtomCoordinateRepresentation >(*this);
}

/// @brief Returns "EigenLinalgCartesianAtomCoordinateRepresentation".
std::string
EigenLinalgCartesianAtomCoordinateRepresentation::class_name() const {
    return "EigenLinalgCartesianAtomCoordinateRepresentation";
}

/// @brief Returns "masla::core::chemistry::atoms::coordinates".
std::string
EigenLinalgCartesianAtomCoordinateRepresentation::class_namespace() const {
    return "masla::core::chemistry::atoms::coordinates";
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
    masala::core::Size const col_index( atom_instance_to_column_.at(old_instance) );
    atom_instance_to_column_.erase(old_instance);
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count(new_instance) == 0, "replace_atom_instance", "Could not replace atom.  New atom is already present!" );
    atom_instance_to_column_[new_instance] = col_index;
}

/// @brief Add an atom.
/// @note Must be implemented by derived classes.
void
EigenLinalgCartesianAtomCoordinateRepresentation::add_atom_instance(
    AtomInstanceCSP const & new_atom,
    std::array< masala::core::Real, 3 > const & new_atom_coordinates
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count(new_atom) == 0, "add_atom_instance", "Atom has already been added!" );
    masala::core::Size const natoms_before( atom_coordinates_.cols() );
    atom_instance_to_column_[ new_atom ] = natoms_before;
    atom_coordinates_.conservativeResize( Eigen::NoChange, natoms_before + 1 );
    atom_coordinates_(0, natoms_before ) = new_atom_coordinates[0]; 
    atom_coordinates_(1, natoms_before ) = new_atom_coordinates[1];
    atom_coordinates_(2, natoms_before ) = new_atom_coordinates[2];
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_coordinates_.cols() == atom_instance_to_column_.size(), "add_atom_instance", "Mismatch in map and matrix sizes!" );
}

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
