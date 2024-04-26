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

/// @brief Utility function to get hybridization state string from hybridization state enum.
std::string
string_from_atom_hybridization_state_enum(
	AtomHybridizationState const hybstate
);

/// @brief Utility function to get hybridization state enum from hybridization state string.
/// @details Returns INVALID_HYBRIDIZATION_STATE if string can't be parsed.
AtomHybridizationState
enum_from_atom_hybridization_state_string(
	std::string const & hybstate_string
);

/// @brief Get a list of all hybridization states, separated by a delimiter (e.g. ", ").
/// @details If include_and is true, the final entry is preceded by "and".
std::string
list_all_hybridization_states(
	std::string const & delimiter,
	bool const include_and
);

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
	/// @param[in] pdb_atom_name The atom name as it appears in the PDB file.
	/// @param[in] pdb_atom_index Atom index in the PDB file.
	/// @param[in] pdb_element_name The element type, in uppercase representation (e.g. "C", "N", "CU").
    AtomInstance(
        std::string const & pdb_atom_name,
        signed long const pdb_atom_index,
        std::string const & pdb_element_name
    );

	/// @brief Constructor from atom properties.
	/// @param[in] element_type The element type, in standard representation (e.g. "C", "N", "Cu").
	/// @param[in] hybridization_state The hybridization state ("sp3", "sp2", "sp", "s", etc.).
	/// @param[in] formal_charge The atom's formal charge.
	/// @param[in] partial_charge The atom's partial charge.
	AtomInstance(
		std::string const & element_type,
		std::string const & hybridization_state,
		signed long int const formal_charge,
		masala::base::Real const partial_charge
	);

	/// @brief Constructor from atom property enums.
	/// @param[in] element_type The element type, as an enum.
	/// @param[in] hybridization_state The hybridization state, as an enum.
	/// @param[in] formal_charge The atom's formal charge.
	/// @param[in] partial_charge The atom's partial charge.
	AtomInstance(
		masala::base::managers::database::elements::ElementTypeEnum const element_type,
		AtomHybridizationState const hybridization_state,
		signed long int const formal_charge,
		masala::base::Real const partial_charge
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

	/// @brief Returns "AtomInstance".
	static
	std::string
	class_name_static();

	/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
	static
	std::string
	class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the formal charge for this atom instance.
    signed long int formal_charge() const;

    /// @brief Get the partial charge for this atom instance.
    masala::base::Real partial_charge() const;

    /// @brief Get the element type (enum) for this atom instance.
    masala::base::managers::database::elements::ElementTypeEnum element_type_enum() const;

    /// @brief Get the van der Waals radius for this element from the
    /// element type database.
    masala::base::Real van_der_waals_radius() const;

    /// @brief Get the default colour for an element of this type.
    std::array< masala::base::Real, 3 > const &
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
    signed long int formal_charge_ = 0;

    /// @brief The partial charge on this atom.
    masala::base::Real partial_charge_ = 0.0;

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