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

/// @file src/core/chemistry/AtomCoordinateRepresentation.hh
/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_AtomCoordinateRepresentation_hh
#define Masala_src_core_chemistry_AtomCoordinateRepresentation_hh

// Forward declarations:
#include <core/chemistry/AtomCoordinateRepresentation.fwd.hh>

// Core headers:
#include <core/chemistry/AtomInstance.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <set>

namespace core {
namespace chemistry {



/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomCoordinateRepresentation : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    AtomCoordinateRepresentation() = default;

    /// @brief Copy constructor.
    AtomCoordinateRepresentation( AtomCoordinateRepresentation const & ) = default;

    // Destructor ommitted to keep class pure virtual.
    // ~AtomCoordinateRepresentation() override;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    AtomCoordinateRepresentationSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual
    AtomCoordinateRepresentationSP
    deep_clone(
        std::set< AtomInstanceCSP > const & new_atom_instance_set
    ) const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

};

} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_AtomCoordinateRepresentation_hh