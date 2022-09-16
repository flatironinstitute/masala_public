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
    molecules_( std::make_shared< masala::core::chemistry::Molecules >() )
{}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
PoseSP
Pose::clone() const {
    return std::make_shared< Pose >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
PoseSP
Pose::deep_clone() const {
    PoseSP newpose( std::make_shared< Pose >( *this ) );
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

/// @brief Every class can provide its own namespace.  This returns "masla::core::pose".
std::string
Pose::class_namespace() const {
    return class_namespace_static();
}

/// @brief Returns "masla::core::pose".
/// @details Called by non-static version.
std::string
Pose::class_namespace_static() {
    return "masla::core::pose";
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
            std::make_shared< MasalaObjectAPIDefinition >(
                class_name_static(),
                class_namespace_static(),
                "The Pose class stores information about the geometry, chemical properties, annotations, "
                "and energies of a molecule or group of molecules, as well as any cached data for that "
                "molecule or group of molecules."
            )
        );

        // Constructors:
        api_def->add_constructor(
            std::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < Pose > > (
                class_name_static(),
                "Creates an empty Pose, initializing it only with an empty Molecules object."
            )
        );
        api_def->add_constructor(
            std::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < Pose, Pose const & > > (
                class_name_static(),
                "Copy constructor: copies an input Pose.  Note that this does not make a unique Pose unless "
                "make_independent() is subsequently called.",
                "The input Pose to copy.  Unaltered by this operation."
            )
        );

        // Work functions:
        api_def->add_work_function(
            std::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput< void > >(
                "make_independent",
                "Deep-copies all internal data, and ensures that data are not shared with any other "
                "Pose instance or any other class instance.",
                false,
                "None (void).",
                std::bind( &Pose::make_independent, this )
            )
        );

        // Getters:
        api_def->add_getter(
            std::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::MoleculesCSP > >(
                "molecules_shared_ptr",
                "Access the Molecules object within the Pose, by shared pointer.",
                "A const shared pointer to the Molecules object, which stores atoms, atomic geometry, "
                "and chemical connectivity.",
                std::bind( &Pose::molecules_shared_ptr, this )
            )
        );
        api_def->add_getter(
            std::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::MoleculesCWP > >(
                "molecules_weak_ptr",
                "Access the Molecules object within the Pose, by weak pointer.",
                "A const weak pointer to the Molecules object, which stores atoms, atomic geometry, "
                "and chemical connectivity.  Must be converted to a shared pointer before use.",
                std::bind( &Pose::molecules_weak_ptr, this )
            )
        );
        api_def->add_getter(
            std::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::Molecules const & > >(
                "molecules",
                "Access the Molecules object within the Pose.",
                "A const reference to the Molecules object, which stores atoms, atomic geometry, "
                "and chemical connectivity.",
                std::bind( &Pose::molecules, this )
            )
        );

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
}

} // namespace pose
} // namespace core
} // namespace masala
