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

/// @file src/core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh
/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh
#define Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh

// Forward declarations:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.fwd.hh>

// Core headers:
#include <core/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>
#include <core/engine/MasalaDataRepresentationBase.hh>

// STL headers:
#include <set>
#include <array>

namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {


/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomCoordinateRepresentation : public core::engine::MasalaDataRepresentationBase {

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
        std::array< core::Real, 3 > const & new_atom_coordinates
    ) = 0;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

};

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh