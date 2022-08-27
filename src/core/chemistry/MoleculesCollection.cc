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

/// @brief Every class can provide its own namespace.  This returns "core::chemistry".
std::string
MoleculesCollection::class_namespace() const {
    return "core::chemistry";
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