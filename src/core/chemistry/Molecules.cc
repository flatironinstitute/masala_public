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

/// @file src/core/chemistry/Molecules.cc
/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/Molecules.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/chemistry/atoms/AtomCoordinateRepresentation.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.hh>

// STL headers:
#include <string>

namespace core {
namespace chemistry {

/// @brief Copy constructor.
/// @details Must be explicitly declared due to mutex.
Molecules::Molecules(
    Molecules const & src
) {
    std::lock_guard< std::mutex > mutexlock( src.whole_object_mutex_ );
    atom_coordinates_ = src.atom_coordinates_;
    atoms_ = src.atoms_;
    bonds_ = src.bonds_;
}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
MoleculesSP
Molecules::clone() const {
    return std::make_shared< Molecules >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
MoleculesSP
Molecules::deep_clone() const {
    MoleculesSP molecules_copy( std::make_shared< Molecules >( *this ) );
    molecules_copy->make_independent();
    return molecules_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void
Molecules::make_independent() {
    std::lock_guard< std::mutex > whole_object_lock( whole_object_mutex_ );

    core::chemistry::atoms::AtomCoordinateRepresentationCSP old_coordinates( atom_coordinates_ );
    atom_coordinates_ = old_coordinates->clone();
    std::set< core::chemistry::atoms::AtomInstanceSP > const old_atom_instances( atoms_ );
    atoms_.clear();
    for(
        std::set< core::chemistry::atoms::AtomInstanceSP >::const_iterator it( old_atom_instances.begin() );
        it != old_atom_instances.end();
        ++it
    ) {
        core::chemistry::atoms::AtomInstanceSP new_atom( (*it)->deep_clone() );
        atoms_.insert( new_atom );
        atom_coordinates_->replace_atom_instance( *it, new_atom );
    }

    std::set< core::chemistry::bonds::ChemicalBondInstanceSP > const old_bonds( bonds_ );
    bonds_.clear();
    for(
        std::set< core::chemistry::bonds::ChemicalBondInstanceSP >::const_iterator it( old_bonds.begin() );
        it != old_bonds.end();
        ++it
    ) {
        bonds_.insert( (*it)->deep_clone() );
    }

    //TODO TODO TODO -- need maps of atoms to bonds and bonds to atoms.
    //Need to clone these appropriately.
}

/// @brief Returns "Molecules".
std::string
Molecules::class_name() const {
    return "Molecules";
}

/// @brief Every class can provide its own namespace.  This returns "core::chemistry".
std::string
Molecules::class_namespace() const {
    return "core::chemistry";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add an atom to this molecule.
void
Molecules::add_atom(
    core::chemistry::atoms::AtomInstanceSP const & atom_in,
    std::array< core::Real, 3 > const & coords
) {
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );
    atoms_.insert(atom_in);
    atom_coordinates_->add_atom_instance( atom_in, coords );

    //TODO update anything that needs to be updated (observers, etc.) when an atom is added.
}

} // namespace chemistry
} // namespace core