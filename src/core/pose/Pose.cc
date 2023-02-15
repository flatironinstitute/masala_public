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

/// @file src/core/pose/Pose.cc
/// @brief A class representing a molecular structure.
/// @details Poses store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core/pose/Pose.hh>

// Core headers:
#include <core/chemistry/Molecules.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>

namespace masala {
namespace core {
namespace pose {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor, making an empty Pose.
/// @details Ensures that the molecules_ object always exists.
Pose::Pose() :
    masala::base::MasalaObject(),
    molecules_( masala::make_shared< masala::core::chemistry::Molecules >() )
{}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
PoseSP
Pose::clone() const {
    return masala::make_shared< Pose >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
PoseSP
Pose::deep_clone() const {
    PoseSP newpose( masala::make_shared< Pose >( *this ) );
    newpose->make_independent();
    return newpose;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Be sure to update this function whenever a private member is added!
void
Pose::make_independent() {
    molecules_ = molecules_->deep_clone();
}

/// @brief Returns "Pose".
std::string
Pose::class_name() const {
    return class_name_static();
}

/// @brief Returns "Pose".
/// @details Called by non-static version.
std::string
Pose::class_name_static() {
    return "Pose";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::pose".
std::string
Pose::class_namespace() const {
    return class_namespace_static();
}

/// @brief Returns "masala::core::pose".
/// @details Called by non-static version.
std::string
Pose::class_namespace_static() {
    return "masala::core::pose";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the Molecules object in this pose, by shared pointer.
/// @details The Molecules object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A Molecules object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MoleculesCSP
Pose::molecules_shared_ptr() const {
    return molecules_;
}

/// @brief Access the Molecules object in this pose, by weak pointer.
/// @details The Molecules object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A Molecules object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MoleculesCWP
Pose::molecules_weak_ptr() const {
    return molecules_;
}

/// @brief Access the Molecules object in this pose, by const reference.
/// @details The Molecules object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A Molecules object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::Molecules const &
Pose::molecules() const {
    return *molecules_;
}

/// @brief Access the Molecules object in this pose, by nonconst shared pointer.
/// @details The Molecules object contains the coordinates and properties of atoms
/// and chemical bonds.  We will use an observer system to ensure that direct updates
/// to the Molecules object also appropriately update any Pose containing it, so direct
/// access is safe.
/// @note A Molecules object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MoleculesSP
Pose::molecules_shared_ptr_nonconst() {
    return molecules_;
}

/// @brief Access the Molecules object in this pose, by nonconst weak pointer.
/// @details The Molecules object contains the coordinates and properties of atoms
/// and chemical bonds.  We will use an observer system to ensure that direct updates
/// to the Molecules object also appropriately update any Pose containing it, so direct
/// access is safe.
/// @note A Molecules object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MoleculesWP
Pose::molecules_weak_ptr_nonconst() {
    return molecules_;
}

/// @brief Access the Molecules object in this pose, by nonconst reference.
/// @details The Molecules object contains the coordinates and properties of atoms
/// and chemical bonds.  We will use an observer system to ensure that direct updates
/// to the Molecules object also appropriately update any Pose containing it, so direct
/// access is safe.
/// @note A Molecules object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::Molecules &
Pose::molecules_nonconst() {
    return *molecules_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the Pose class.
base::api::MasalaObjectAPIDefinitionCWP
Pose::get_api_definition() {
    using namespace masala::base::api;

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The Pose class stores information about the geometry, chemical properties, annotations, "
                "and energies of a molecule or group of molecules, as well as any cached data for that "
                "molecule or group of molecules.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < Pose > > (
                class_name_static(),
                "Creates an empty Pose, initializing it only with an empty Molecules object."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < Pose, Pose const & > > (
                class_name_static(),
                "Copy constructor: copies an input Pose.  Note that this does not make a unique Pose unless "
                "make_independent() is subsequently called.",
                "src", "The input Pose to copy.  Unaltered by this operation."
            )
        );

        // Work functions:


        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::MoleculesCSP > >(
                "molecules_shared_ptr",
                "Access the Molecules object within the Pose, by shared pointer.",
                "molecules", "A const shared pointer to the Molecules object, which stores atoms, atomic geometry, "
                "and chemical connectivity.", false, false,
                std::bind( &Pose::molecules_shared_ptr, this )
            )
        );
        // api_def->add_getter(
        //     masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::MoleculesCWP > >(
        //         "molecules_weak_ptr",
        //         "Access the Molecules object within the Pose, by weak pointer.",
        //         "molecules", "A const weak pointer to the Molecules object, which stores atoms, atomic geometry, "
        //         "and chemical connectivity.  Must be converted to a shared pointer before use.", false, false,
        //         std::bind( &Pose::molecules_weak_ptr, this )
        //     )
        // );
        // api_def->add_getter(
        //     masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::Molecules const & > >(
        //         "molecules",
        //         "Access the Molecules object within the Pose.",
        //         "molecules", "A const reference to the Molecules object, which stores atoms, atomic geometry, "
        //         "and chemical connectivity.", false, false,
        //         std::bind( &Pose::molecules, this )
        //     )
        // );

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
}

} // namespace pose
} // namespace core
} // namespace masala
