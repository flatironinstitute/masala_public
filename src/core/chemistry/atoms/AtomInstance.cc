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
#include <core/chemistry/atoms/ElementType.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

/// @brief Constructor from PDB atom.
AtomInstance::AtomInstance(
    std::string const & pdb_atom_name,
    signed long pdb_atom_index,
    std::string const & pdb_element_name
) :
    masala::base::MasalaObject(),
    // TODO TODO TODO element_type_( ),
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
masala::core::Real
AtomInstance::partial_charge() const {
    return partial_charge_;
}

/// @brief Get the element type (enum) for this atom instance.
ElementTypeEnum
AtomInstance::element_type_enum() const {
    return element_type_->element_type();
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
                false
            )
        );
        api_def->add_constructor(
            masala::make_shared< MasalaObjectAPIConstructorDefinition_ZeroInput< AtomInstance > >(
                class_name(), "Construct an empty instance of an AtomIstance object, with no options."
            )
        );
        api_def->add_constructor(
            masala::make_shared< MasalaObjectAPIConstructorDefinition_OneInput< AtomInstance, AtomInstance const & > >(
                class_name(), "AtomInstance object copy constructor.",
                "src", "The input AtomInstance object to copy."
            )
        );

        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < signed int > >(
                "formal_charge", "Get the formal charge on this atom.  Formal charges are integer values.",
                "formal_charge", "The formal charge on this atom.", std::bind( &AtomInstance::formal_charge, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < core::Real > >(
                "partial_charge", "Get the partial charge on this atom.  Partial charges are real values.",
                "partial_charge", "The partial charge on this atom.", std::bind( &AtomInstance::partial_charge, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< ElementTypeEnum > >(
                "element_type_enum", "Gets the element type for this atom instance, by enum (ElementTypeEneum).",
                "element_type_enum", "The element type, represented as an ElementTypeEnum.",
                "ElementTypeEnum", "masala::core::chemistry::atoms",
                std::bind( &AtomInstance::element_type_enum, *this )
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
