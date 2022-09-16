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

/// @file src/core/chemistry/atoms/AtomInstance.hh
/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_AtomInstance_hh
#define Masala_src_core_chemistry_atoms_AtomInstance_hh

// Forward declarations:
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// Core headers:
#include <core/types.hh>
#include <core/chemistry/atoms/ElementType.fwd.hh>
#include <core/chemistry/atoms/data/AtomData.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <set>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @note This stores element type, formal charge, partial charge,
/// hybridization state... everything EXCEPT atomic coordinates.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomInstance : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    AtomInstance() = default;

    /// @brief Constructor from PDB atom.
    AtomInstance(
        std::string const & pdb_atom_name,
        signed long pdb_atom_index,
        std::string const & pdb_element_name
    );

    /// @brief Copy constructor.
    AtomInstance( AtomInstance const & ) = default;

    /// @brief Default destructor.
    ~AtomInstance() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    AtomInstanceSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual
    AtomInstanceSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "AtomInstance".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The type of element that this atom is.
    ElementTypeCSP element_type_;

    /// @brief This atom's hybridization state.
    AtomHybridizationState hybridization_state_ = AtomHybridizationState::sp3;

    /// @brief The formal charge on this atom.
    signed int formal_charge_ = 0;

    /// @brief The partial charge on this atom.
    masala::core::Real partial_charge_ = 0.0;

    /// @brief Optional additional data attached to this atom.
    /// @details Intended to store things like PDB name, PDB index, etc.
    std::set< data::AtomDataSP > additional_atom_data_;

};

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_AtomInstance_hh