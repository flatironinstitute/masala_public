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

/// @file src/core/chemistry/atoms/data/PDBAtomData.cc
/// @brief A container class for data attached to an atom that was read from a PDB file.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/data/PDBAtomData.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:

namespace masala {
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
AtomDataSP
PDBAtomData::clone() const {
    return masala::make_shared< PDBAtomData >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
PDBAtomDataSP
PDBAtomData::deep_clone() const {
	PDBAtomDataSP pdbdata_copy( masala::make_shared< PDBAtomData >( *this ) );
    pdbdata_copy->make_independent();
    return pdbdata_copy;
}

/// @brief Returns "PDBAtomData".
std::string
PDBAtomData::class_name() const {
    return "PDBAtomData";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms::data".
std::string
PDBAtomData::class_namespace() const {
    return "masala::core::chemistry::atoms::data";
}

/// @brief Get the category or categories for this plugin class.
/// @details Must be implemented by derived classes.
/// @returns {{"AtomData", "PDBAtomData"}}
std::vector< std::vector< std::string > >
PDBAtomData::get_categories() const {
    std::vector< std::vector< std::string > > categories( AtomData::get_categories() );
    categories[0].push_back( "PDBAtomData" );
    categories[0].shrink_to_fit();
    categories.shrink_to_fit();
    return categories;
}

/// @brief Get the keywords for this plugin class.
/// @details Must be implemented by derived classes.
/// @returns {"atom_data", "pdb", "protein_data_bank"}
std::vector< std::string >
PDBAtomData::get_keywords() const {
    std::vector< std::string > keywords( AtomData::get_keywords() );
    keywords.push_back( "pdb" );
    keywords.push_back( "protein_data_bank" );
    keywords.shrink_to_fit();
    return keywords;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the atom name as listed in a PDB file.
std::string const &
PDBAtomData::pdb_atom_name() const {
	std::lock_guard< std::mutex > lock( mutex() );
    return pdb_atom_name_;
}

/// @brief Access the atom index as listed in a PDB file.
signed long
PDBAtomData::pdb_atom_index() const {
	std::lock_guard< std::mutex > lock( mutex() );
    return pdb_atom_index_;
}

/// @brief Access the element type as listed in a PDB file.
std::string const &
PDBAtomData::pdb_element_type() const {
	std::lock_guard< std::mutex > lock( mutex() );
    return pdb_element_type_;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Be sure to update this function whenever a private member is added!
void
PDBAtomData::protected_make_independent() {
	AtomData::protected_make_independent();
}

/// @brief Assign src to this.
/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
void
PDBAtomData::protected_assign( AtomData const & src ) {
	PDBAtomData const * src_ptr_cast( dynamic_cast< PDBAtomData const * >( &src ) );

	CHECK_OR_THROW_FOR_CLASS( src_ptr_cast != nullptr, "protected_assign", "Cannot assign an object of type " + src.class_name() + " to a PDBAtomData object." );
	
	pdb_atom_name_ = src_ptr_cast->pdb_atom_name_;
	pdb_atom_index_ = src_ptr_cast->pdb_atom_index_;
	pdb_element_type_ = src_ptr_cast->pdb_element_type_;

	AtomData::protected_assign( src );
}

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala