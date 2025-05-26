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

/// @file src/core/chemistry/atoms/data/PDBAtomData.hh
/// @brief A container class for data attached to an atom that was read from a PDB file.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_data_PDBAtomData_hh
#define Masala_src_core_chemistry_atoms_data_PDBAtomData_hh

// Forward declarations:
#include <core/chemistry/atoms/data/PDBAtomData.fwd.hh>

// Parent header:
#include <core/chemistry/atoms/data/AtomData.hh>

// Core headers:
#include <base/types.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace data {

/// @brief A container class for data attached to an atom that was read from a PDB file.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PDBAtomData : public masala::core::chemistry::atoms::data::AtomData {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    PDBAtomData() = default;

    /// @brief Options constructor.
    /// @param[in] pdb_atom_name The atom name as specified in a PDB file.
    /// @param[in] pdb_atom_index The atom index as specified in a PDB file.
    /// @param[in] pdb_element_type The element type string, as specified in a PDB file.
    PDBAtomData(
        std::string const & pdb_atom_name,
        signed long pdb_atom_index,
        std::string const & pdb_element_type
    );

    /// @brief Copy constructor.
    PDBAtomData( PDBAtomData const & src ) = default;

    /// @brief Default destructor.
    ~PDBAtomData() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    PDBAtomDataSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    /// @details Threadsafe.  Be sure to update this function whenever a private member is added!
    virtual
    PDBAtomDataSP
    deep_clone() const;

	/// @brief Returns "PDBAtomData".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms::data".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the atom name as listed in a PDB file.
    std::string const & pdb_atom_name() const;

    /// @brief Access the atom index as listed in a PDB file.
    signed long pdb_atom_index() const;

    /// @brief Access the element type as listed in a PDB file.
    /// @note May not match the AtomInstance::element().  Use AtomInstance::element() for
    /// Masala protocols that depend on element types.
    std::string const & pdb_element_type() const;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Make this object independent by making a deep copy of all of its private members.
	/// @details Be sure to update this function whenever a private member is added!
	void
	protected_make_independent() override;

	/// @brief Assign src to this.
	/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
	/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
	void
	protected_assign(
		AtomData const & src
	) override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The atom name as listed in a PDB file.
    std::string pdb_atom_name_;

    /// @brief The atom index as listed in a PDB file.
    signed long pdb_atom_index_ = 0;

    /// @brief The element type as listed in a PDB file.
    std::string pdb_element_type_;


};

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_data_PDBAtomData_hh