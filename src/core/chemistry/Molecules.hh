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

/// @file src/core/chemistry/Molecules.hh
/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_Molecules_hh
#define Masala_src_core_chemistry_Molecules_hh

// Forward declarations:
#include <core/chemistry/Molecules.fwd.hh>

// Core headers:
#include <core/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.fwd.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <array>
#include <set>
#include <vector>
#include <map>
#include <mutex>

namespace core {
namespace chemistry {



/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Molecules : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    Molecules() = default;

    /// @brief Copy constructor.
    /// @details Must be explicitly declared due to mutex.
    Molecules( Molecules const & src );

    /// @brief Default destructor.
    ~Molecules() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    MoleculesSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    /// @details Threadsafe.  Be sure to update this function whenever a private member is added!
    virtual
    MoleculesSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "Molecules".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "core::chemistry".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Add an atom to this molecule.
    void
    add_atom(
        core::chemistry::atoms::AtomInstanceSP const & atom_in,
        std::array< core::Real, 3 > const & coords
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for locking a whole molecules object.
    mutable std::mutex whole_object_mutex_;

    /// @brief The representation of the atom coordinates.
    /// @details Different calculators might need atoms represented in different ways, internally (e.g.
    /// matrices of coordinates, etc.)  Different subclasses of the AtomCoordinateRepresentation class
    /// store the data differently, but all offer iterators to access atom coordinates.
    /// @note This is the MASTER representation.  All other representations either update this
    /// representation, or are updated by this representation.
    core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP master_atom_coordinate_representation_;

    /// @brief Additional representations of atom coordinates.
    std::vector< core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP > additional_atom_coordinate_representations_;

    /// @brief The atoms themselves and their properties.
    /// @details The Molecules container is responsible for keeping these linked to the
    /// AtomCoordinateRepresentation.
    /// @note This is deliberately a set and not a vector to prevent an arbitrary index
    /// from being handed out or used for atoms.  Iterators are properly used to iterate
    /// over all atoms, and pointers to access a particular atom.  This also allows more
    /// efficient insertions and deletions of atoms.  AtomCoordinateRepresentations are
    /// responsible for keeping track of coordinates given atom smart pointers.
    std::set< core::chemistry::atoms::AtomInstanceSP > atoms_;

    /// @brief The bonds between atoms.
    /// @note This is deliberately a set and not a vector to prevent an arbitrary index
    /// from being handed out or used for bonds.  Iterators are properly used to iterate
    /// over all bonds, and pointers to access a particular bonds.  This also allows more
    /// efficient insertions and deletions of bonds.
    std::set< core::chemistry::bonds::ChemicalBondInstanceSP > bonds_;

};

} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_Molecules_hh