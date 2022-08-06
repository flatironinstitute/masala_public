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
#include <core/chemistry/MoleculesCollection.hh>

namespace core {
namespace pose {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the MoleculesCollection object in this pose, by shared pointer.
/// @details The MoleculesCollection object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A MoleculesCollection object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MoleculesCollectionCSP
Pose::molecules_shared_ptr() const {
    return molecules_;
}

/// @brief Access the MoleculesCollection object in this pose, by weak pointer.
/// @details The MoleculesCollection object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A MoleculesCollection object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MoleculesCollectionCWP
Pose::molecules_weak_ptr() const {
    return molecules_;
}

/// @brief Access the MoleculesCollection object in this pose, by const reference.
/// @details The MoleculesCollection object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A MoleculesCollection object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MoleculesCollection const &
Pose::molecules() const {
    return *molecules_;
}

} // namespace pose
} // namespace core
