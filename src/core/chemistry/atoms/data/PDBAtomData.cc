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

/// @file src/core/chemistry/atoms/data/PDBAtomData.cc
/// @brief A container class for data attached to an atom that was read from a PDB file.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/data/PDBAtomData.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/chemistry/atoms/AtomCoordinateRepresentation.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.hh>

// STL headers:

namespace core {
namespace chemistry {
namespace atoms {
namespace data {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor.
/// @param[in] pdb_atom_name The atom name as specified in a PDB file.
/// @param[in] pdb_atom_index The atom index as specified in a PDB file.
/// @param[in] pdb_element_type The element type string, as specified in a PDB file.
PDBAtomData::PDBAtomData(
    std::string const & pdb_atom_name,
    signed long pdb_atom_index,
    std::string const & pdb_element_type
) :
    AtomData(),
    pdb_atom_name_(pdb_atom_name),
    pdb_atom_index_(pdb_atom_index),
    pdb_element_type_(pdb_element_type)
{}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
PDBAtomDataSP
PDBAtomData::clone() const {
    return std::make_shared< PDBAtomData >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
PDBAtomDataSP
PDBAtomData::deep_clone() const {
    PDBAtomDataSP pdbdata_copy( std::make_shared< PDBAtomData >( *this ) );
    pdbdata_copy->make_independent();
    return pdbdata_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void
PDBAtomData::make_independent() {
}

/// @brief Returns "PDBAtomData".
std::string
PDBAtomData::class_name() const {
    return "PDBAtomData";
}

/// @brief Every class can provide its own namespace.  This returns "core::chemistry::atoms::data".
std::string
PDBAtomData::class_namespace() const {
    return "core::chemistry::atoms::data";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the atom name as listed in a PDB file.
std::string const &
PDBAtomData::pdb_atom_name() const {
    return pdb_atom_name_;
}

/// @brief Access the atom index as listed in a PDB file.
signed long
PDBAtomData::pdb_atom_index() const {
    return pdb_atom_index_;
}

/// @brief Access the element type as listed in a PDB file.
std::string const &
PDBAtomData::pdb_element_type() const {
    return pdb_element_type_;
}

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace core