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

namespace core {
namespace pose {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor, making an empty Pose.
/// @details Ensures that the molecules_ object always exists.
Pose::Pose() :
    base::MasalaObject(),
    molecules_( std::make_shared< core::chemistry::Molecules >() )
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

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the Pose class.
base::api::MasalaObjectAPIDefinitionCSP
Pose::get_api_definition() {
    using namespace base::api;

    MasalaObjectAPIDefinitionSP api_def(
        std::make_shared< MasalaObjectAPIDefinition >(
            class_name_static(),
            "The Pose class stores information about the geometry, chemical properties, annotations, "
            "and energies of a molecule or group of molecules, as well as any cached data for that "
            "molecule or group of molecules."
        )
    );

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

    api_def->add_work_function(
        std::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput< Pose, void > >(
            "make_independent",
            "Deep-copies all internal data, and ensures that data are not shared with any other "
            "Pose instance or any other class instance.",
            false,
            "None (void).",
            TODO
        )
    );

    return api_def;
}

} // namespace pose
} // namespace core
