/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/core/chemistry/atoms/AtomInstance.cc
/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @note This stores element type, formal charge, partial charge,
/// hybridization state... everything EXCEPT atomic coordinates.
/// This class is not threadsafe.  Protocols ought not to have
/// multiple threads operating on the same atom (or should implement
/// suitable mutex locking to allow this).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/AtomInstance.hh>

// Core headers:
#include <core/chemistry/atoms/data/PDBAtomData.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ThreeInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_FourInput.tmpl.hh>
#include <base/managers/database/elements/ElementType.hh>
#include <base/managers/database/elements/MasalaElementDatabase.hh>
#include <base/managers/database/MasalaDatabaseManager.hh>
#include <base/enums/AtomHybridizationStateEnum.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

/// @brief Constructor from PDB atom.
AtomInstance::AtomInstance(
    std::string const & pdb_atom_name,
    signed long const pdb_atom_index,
    std::string const & pdb_element_name
) :
    masala::base::MasalaObject(),
    element_type_(
        masala::base::managers::database::MasalaDatabaseManager::get_instance()->element_database().element_type_from_ucase_abbreviation(pdb_element_name)
    ),
    additional_atom_data_{ masala::make_shared< data::PDBAtomData >( pdb_atom_name, pdb_atom_index, pdb_element_name ) }
{}

/// @brief Constructor from atom properties.
/// @param[in] element_type The element type, in standard representation (e.g. "C", "N", "Cu").
/// @param[in] hybridization_state The hybridization state ("sp3", "sp2", "sp", "s", etc.).
/// @param[in] formal_charge The atom's formal charge.
/// @param[in] partial_charge The atom's partial charge.
AtomInstance::AtomInstance(
	std::string const & element_type,
	std::string const & hybridization_state,
	signed long int const formal_charge,
	masala::base::Real const partial_charge
) :
	masala::base::MasalaObject(),
	element_type_(
        masala::base::managers::database::MasalaDatabaseManager::get_instance()->element_database().element_type_from_abbreviation( element_type )
	),
	hybridization_state_(
		masala::base::enums::enum_from_atom_hybridization_state_string( hybridization_state )
	),
	formal_charge_(formal_charge),
	partial_charge_(partial_charge)
{
	CHECK_OR_THROW( hybridization_state_ != AtomHybridizationState::INVALID_HYBRIDIZATION_STATE,
		class_namespace_static() + "::" + class_name_static(),
		"AtomInstance",
		"Error in atom constructor: the string \"" + hybridization_state + "\" could not be interpreted as a valid "
		"hybridization state.  Valid strings are: " + masala::base::enums::list_all_hybridization_states( ", ", true ) + "."
	)
}

/// @brief Constructor from atom property enums.
/// @param[in] element_type The element type, as an enum.
/// @param[in] hybridization_state The hybridization state, as an enum.
/// @param[in] formal_charge The atom's formal charge.
/// @param[in] partial_charge The atom's partial charge.
AtomInstance::AtomInstance(
	masala::base::managers::database::elements::ElementTypeEnum const element_type,
	AtomHybridizationState const hybridization_state,
	signed long int const formal_charge,
	masala::base::Real const partial_charge
) :
	masala::base::MasalaObject(),
	element_type_( masala::base::managers::database::MasalaDatabaseManager::get_instance()->element_database().element_type_from_enum( element_type ) ),
	hybridization_state_( hybridization_state ),
	formal_charge_(formal_charge),
	partial_charge_(partial_charge)
{
	CHECK_OR_THROW( hybridization_state_ != AtomHybridizationState::INVALID_HYBRIDIZATION_STATE,
		class_namespace_static() + "::" + class_name_static(),
		"AtomInstance",
		"Error in atom constructor: the hybridization state is invalid."
	)
}


/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
AtomInstanceSP
AtomInstance::clone() const {
    return masala::make_shared< AtomInstance >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
AtomInstanceSP
AtomInstance::deep_clone() const {
    AtomInstanceSP AtomInstance_copy( masala::make_shared< AtomInstance >( *this ) );
    AtomInstance_copy->make_independent();
    return AtomInstance_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Be sure to update this function whenever a private member is added!
void
AtomInstance::make_independent() {
    // Currently GNDN.
}

/// @brief Returns "AtomInstance".
std::string
AtomInstance::class_name() const {
    return class_name_static();
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
std::string
AtomInstance::class_namespace() const {
    return class_namespace_static();
}

/// @brief Returns "AtomInstance".
std::string
AtomInstance::class_name_static() {
    return "AtomInstance";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
std::string
AtomInstance::class_namespace_static() {
    return "masala::core::chemistry::atoms";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the formal charge for this atom instance.
signed long int
AtomInstance::formal_charge() const {
    return formal_charge_;
}

/// @brief Get the partial charge for this atom instance.
masala::base::Real
AtomInstance::partial_charge() const {
    return partial_charge_;
}

/// @brief Get the element type (enum) for this atom instance.
masala::base::managers::database::elements::ElementTypeEnum
AtomInstance::element_type_enum() const {
    return element_type_->element_type();
}

/// @brief Get the van der Waals radius for this element from the
/// element type database.
masala::base::Real
AtomInstance::van_der_waals_radius() const {
    return element_type_->van_der_waals_radius();
}

/// @brief Get the default colour for an element of this type.
std::array< masala::base::Real, 3 > const &
AtomInstance::element_default_rgb_colour() const {
    return element_type_->default_rgb_colour();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API FUNCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the API definition for an atom instance.
masala::base::api::MasalaObjectAPIDefinitionCWP
AtomInstance::get_api_definition() {
    using namespace base::api;
    using namespace base::api::constructor;
    using namespace base::api::getter;

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "An instance of an atom.",
                false, false
            )
        );

        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( AtomInstance, api_def );

		api_def->add_constructor(
			masala::make_shared< MasalaObjectAPIConstructorDefinition_ThreeInput< AtomInstance, std::string const &, signed long const, std::string const & > >(
				"AtomInstance", "Constructor from PDB atom.",
				"pdb_atom_name", "The name of the atom, as it appears in the PDB file.",
				"pdb_atom_index", "The index of the atom in the PDB file.",
				"pdb_element_name", "The element, as it appears in the PDB file."
			)
		);
		api_def->add_constructor(
			masala::make_shared<
				MasalaObjectAPIConstructorDefinition_FourInput<
					AtomInstance,
					std::string const &,
					std::string const &,
					signed long int const,
					masala::base::Real const
				>
			> (
				"AtomInstance", "Constructor from element type string, hybridization state string, formal charge, and partial charge.",
				"element_type", "The element type, in standard representation (e.g. 'C', 'N', 'Cu').",
				"hybridization_state", "The hybridization state.  Allowed states are: " + masala::base::enums::list_all_hybridization_states( ", ", true ) + ".",
				"formal_charge", "The atom's formal charge.",
				"partial_charge", "The atom's partial charge."
			)
		);
		api_def->add_constructor(
			masala::make_shared<
				MasalaObjectAPIConstructorDefinition_FourInput<
					AtomInstance,
					masala::base::managers::database::elements::ElementTypeEnum const,
					AtomHybridizationState const,
					signed long int const,
					masala::base::Real const
				>
			> (
				"AtomInstance", "Constructor from element type enum, hybridization state enum, formal charge, "
				"and partial charge.  More efficient than string version, since no strings have to be parsed.",
				"element_type", "The element type enum.",
				"hybridization_state", "The hybridization state enum.",
				"formal_charge", "The atom's formal charge.",
				"partial_charge", "The atom's partial charge."
			)
		);

        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < signed long int > >(
                "formal_charge", "Get the formal charge on this atom.  Formal charges are integer values.",
                "formal_charge", "The formal charge on this atom.", false, false,
                std::bind( &AtomInstance::formal_charge, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < base::Real > >(
                "partial_charge", "Get the partial charge on this atom.  Partial charges are real values.",
                "partial_charge", "The partial charge on this atom.", false, false, std::bind( &AtomInstance::partial_charge, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< masala::base::managers::database::elements::ElementTypeEnum > >(
                "element_type_enum", "Gets the element type for this atom instance, by enum (ElementTypeEnum).",
                "element_type_enum", "The element type, represented as an ElementTypeEnum.",
                false, false,
                std::bind( &AtomInstance::element_type_enum, *this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< masala::base::Real > >(
                "van_der_waals_radius", "Gets the van der Waals radius for this atom's element type.",
                "van_der_waals_radius", "The van der Waals radius, in Angstroms.", false, false,
                std::bind( &AtomInstance::van_der_waals_radius, *this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< std::array< masala::base::Real, 3 > const & > >(
                "element_default_rgb_colour", "Gets the default RGB colour for this atom's element type.  RGB colours are 3-arrays of values ranging from 0 to 1.",
                "element_default_rgb_colour", "The default RGB colour for elements of this type.", false, false,
                std::bind( &AtomInstance::element_default_rgb_colour, *this )
            )
        );

        api_definition_ = api_def; // Nonconst to const.
    }
    return api_definition_;
}


} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
