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
#include <core/types.hh>

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
class PDBAtomData : public AtomData {

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

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "PDBAtomData".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "core::chemistry::atoms::data".
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