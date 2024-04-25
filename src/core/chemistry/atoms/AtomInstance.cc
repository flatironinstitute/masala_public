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
#include <base/managers/database/elements/ElementType.hh>
#include <base/managers/database/elements/MasalaElementDatabase.hh>
#include <base/managers/database/MasalaDatabaseManager.hh>

// STL headers:
#include <string>
#include <sstream>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

/// @brief Utility function to get hybridization state string from hybridization state enum.
std::string
string_from_atom_hybridization_state_enum(
	AtomHybridizationState const hybstate
) {
	switch(hybstate) {
		case AtomHybridizationState::UNKNOWN_HYBRIDIZATION_STATE :
			return "unknown";
		case AtomHybridizationState::sp3 :
			return "sp3";
		case AtomHybridizationState::sp2 :
			return "sp2";
		case AtomHybridizationState::sp :
			return "sp";
		case AtomHybridizationState::s :
			return "s";
		case AtomHybridizationState::OTHER_HYBRIDIZATION_STATE :
			return "other";
		default:
			MASALA_THROW( "masala::core::chemistry::atoms", "string_from_atom_hybridization_state_enum",
				"Invalid hybridization state provided to this function!"
			);
	}
	return "";
}

/// @brief Utility function to get hybridization state enum from hybridization state string.
/// @details Returns INVALID_HYBRIDIZATION_STATE if string can't be parsed.
AtomHybridizationState
string_from_atom_hybridization_state_enum(
	std::string const & hybstate_string
) {
	using masala::base::Size;
	for( Size i(0); i<=static_cast<Size>(AtomHybridizationState::N_HYBRIDIZATION_STATES); ++i ) {
		if( string_from_atom_hybridization_state_enum( static_cast<AtomHybridizationState>(i) ) == hybstate_string ) {
			return static_cast<AtomHybridizationState>(i);
		}
	}
	return AtomHybridizationState::INVALID_HYBRIDIZATION_STATE;
}

/// @brief Get a list of all hybridization states, separated by a delimiter (e.g. ", ").
/// @details If include_and is true, the final entry is preceded by "and".
std::string
list_all_hybridization_states(
	std::string const & delimiter,
	bool const include_and
) {
	std::ostringstream ss;
	using masala::base::Size;
	for( Size i(0); i<=static_cast<Size>(AtomHybridizationState::N_HYBRIDIZATION_STATES); ++i ) {
		if( i>0 ) {
			ss << delimiter;
		}
		if( include_and && i == static_cast<Size>(AtomHybridizationState::N_HYBRIDIZATION_STATES) ) {
			ss << "and ";
		}
		ss << string_from_atom_hybridization_state_enum( static_cast<AtomHybridizationState>(i) );
	}
	return ss.str();
}

/// @brief Constructor from PDB atom.
AtomInstance::AtomInstance(
    std::string const & pdb_atom_name,
    signed long pdb_atom_index,
    std::string const & pdb_element_name
) :
    masala::base::MasalaObject(),
    element_type_(
        masala::base::managers::database::MasalaDatabaseManager::get_instance()->element_database().element_type_from_ucase_abbreviation(pdb_element_name)
    ),
    additional_atom_data_{ masala::make_shared< data::PDBAtomData >( pdb_atom_name, pdb_atom_index, pdb_element_name ) }
{}

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
    return "AtomInstance";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
std::string
AtomInstance::class_namespace() const {
    return "masala::core::chemistry::atoms";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the formal charge for this atom instance.
signed int
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
			masala::make_shared< MasalaObjectAPIConstructorDefinition_ThreeInput< AtomInstance, std::string const &, signed long, std::string const & > >(
				"AtomInstance", "Constructor from PDB atom.",
				"pdb_atom_name", "The name of the atom, as it appears in the PDB file.",
				"pdb_atom_index", "The index of the atom in the PDB file.",
				"pdb_element_name", "The element, as it appears in the PDB file."
			)
		);

        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < signed int > >(
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
                "element_type_enum", "Gets the element type for this atom instance, by enum (ElementTypeEneum).",
                "element_type_enum", "The element type, represented as an ElementTypeEnum.",
                "ElementTypeEnum", "masala::base::managers::database::elements", false, false,
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
