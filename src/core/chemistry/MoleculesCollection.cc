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

/// @file src/core/chemistry/MoleculesCollection.cc
/// @brief A class contiaining a collection of molecules.
/// @details Each Molecules object contains atoms and bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/MoleculesCollection.hh>

// Core headers:
#include <core/chemistry/Molecules.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
MoleculesCollectionSP
MoleculesCollection::clone() const {
    return std::make_shared< MoleculesCollection >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
MoleculesCollectionSP
MoleculesCollection::deep_clone() const {
    MoleculesCollectionSP molecules_copy( std::make_shared< MoleculesCollection >( *this ) );
    molecules_copy->make_independent();
    return molecules_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Be sure to update this function whenever a private member is added!
void
MoleculesCollection::make_independent() {
    // Deep-clone the molecules:
    std::set< MoleculesSP > molecule_set_copy_( molecule_set_ );
    molecule_set_.clear();
    for(
        std::set< MoleculesSP>::const_iterator it( molecule_set_copy_.cbegin() );
        it != molecule_set_copy_.cend();
        ++it
    ) {
        molecule_set_.insert( (*it)->deep_clone() );
    }
}

/// @brief Returns "Molecule".
std::string
MoleculesCollection::class_name() const {
    return "MoleculesCollection";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry".
std::string
MoleculesCollection::class_namespace() const {
    return "masala::core::chemistry";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the number of molecules in this MoleculesCollection container.
core::Size
MoleculesCollection::size() const {
    return molecule_set_.size();
}

/// @brief Get an iterator to the first Molecules object stored in this MoleculesCollection
/// container.
std::set< MoleculesSP >::const_iterator
MoleculesCollection::molecules_set_begin() const {
    return molecule_set_.cbegin();
}

/// @brief Get an iterator to the end of the set of Molecules objects stored in
/// this MoleculesCollection container.
std::set< MoleculesSP >::const_iterator
MoleculesCollection::molecules_set_end() const {
    return molecule_set_.cend();
}

} // namespace chemistry
} // namespace core
} // namespace masala
