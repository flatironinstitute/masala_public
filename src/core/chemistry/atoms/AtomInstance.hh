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

/// @file src/core/chemistry/atoms/AtomInstance.hh
/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @note This stores element type, formal charge, partial charge,
/// hybridization state... everything EXCEPT atomic coordinates.
/// This class is not threadsafe.  Protocols ought not to have
/// multiple threads operating on the same atom (or should implement
/// suitable mutex locking to allow this).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_AtomInstance_hh
#define Masala_src_core_chemistry_atoms_AtomInstance_hh

// Forward declarations:
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// Core headers:
#include <base/types.hh>
#include <core/chemistry/atoms/data/AtomData.fwd.hh>

// Base headers:
#include <base/managers/database/elements/ElementType.fwd.hh>
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
/// This class is not threadsafe.  Protocols ought not to have
/// multiple threads operating on the same atom (or should implement
/// suitable mutex locking to allow this).
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
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the formal charge for this atom instance.
    signed int formal_charge() const;

    /// @brief Get the partial charge for this atom instance.
    masala::core::Real partial_charge() const;

    /// @brief Get the element type (enum) for this atom instance.
    masala::base::managers::database::elements::ElementTypeEnum element_type_enum() const;

    /// @brief Get the van der Waals radius for this element from the
    /// element type database.
    masala::core::Real van_der_waals_radius() const;

    /// @brief Get the default colour for an element of this type.
    std::array< masala::core::Real, 3 > const &
    element_default_rgb_colour() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API FUNCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the API definition for an atom instance.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The type of element that this atom is.
    masala::base::managers::database::elements::ElementTypeCSP element_type_;

    /// @brief This atom's hybridization state.
    AtomHybridizationState hybridization_state_ = AtomHybridizationState::sp3;

    /// @brief The formal charge on this atom.
    signed int formal_charge_ = 0;

    /// @brief The partial charge on this atom.
    masala::core::Real partial_charge_ = 0.0;

    /// @brief Optional additional data attached to this atom.
    /// @details Intended to store things like PDB name, PDB index, etc.
    std::set< data::AtomDataSP > additional_atom_data_;

    /// @brief An API definition for this object.
    masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

};

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_AtomInstance_hh