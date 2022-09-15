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

/// @file src/core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.hh
/// @brief A container of atom coordinates, using the Eigen linear algebra library's data structures.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_hh
#define Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_hh

// Parent headers:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>

// Forward declarations:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.fwd.hh>

// Core headers:
#include <core/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// External headers:
#include <external/eigen/Eigen/Core>

// STL headers:
#include <map>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {


/// @brief A container of atom coordinates, using the Eigen linear algebra library's data structures.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class EigenLinalgCartesianAtomCoordinateRepresentation : public AtomCoordinateRepresentation {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    EigenLinalgCartesianAtomCoordinateRepresentation() = default;

    /// @brief Copy constructor.
    EigenLinalgCartesianAtomCoordinateRepresentation( EigenLinalgCartesianAtomCoordinateRepresentation const & ) = default;

    // Destructor ommitted to keep class pure virtual.
    ~EigenLinalgCartesianAtomCoordinateRepresentation() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    AtomCoordinateRepresentationSP
    clone() const override;

    /// @brief Returns "EigenLinalgCartesianAtomCoordinateRepresentation".
    std::string
    class_name() const override;

    /// @brief Returns "core::chemistry::atoms::coordinates".
    std::string
    class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


    /// @brief Replace an atom instance with a new one.
    /// @details Used for deep cloning, since the AtomCoordinateRepresentation subclasses do not
    /// implement a deep_clone() function.
    /// @note Must be implemented by derived classes.
    void
    replace_atom_instance(
        AtomInstanceCSP const & old_instance,
        AtomInstanceCSP const & new_instance
    ) override;

    /// @brief Add an atom.
    /// @note Must be implemented by derived classes.
    void
    add_atom_instance(
        AtomInstanceCSP const & new_atom,
        std::array< masala::core::Real, 3 > const & new_atom_coordinates
    ) override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief Data storage for atom coordinates.
    /// @details Rows are x, y, and z coordinates.  Columns are for atoms.
    Eigen::Matrix< masala::core::Real, 3, Eigen::Dynamic > atom_coordinates_;

    /// @brief Map of atom index to column index.
    std::map< masala::core::chemistry::atoms::AtomInstanceCSP, masala::core::Size > atom_instance_to_column_;

};

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_hh