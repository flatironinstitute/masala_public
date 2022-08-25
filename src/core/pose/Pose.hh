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

/// @file src/core/pose/Pose.hh
/// @brief A class representing a molecular structure.
/// @details Poses store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_pose_Pose_hh
#define Masala_src_core_pose_Pose_hh

// Forward declarations:
#include <core/pose/Pose.fwd.hh>

// Core headers:
#include <core/chemistry/Molecules.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace core {
namespace pose {


/// @brief A class representing a molecular structure.
/// @details Poses store atom coordinates and bonds (in the form of a Molecules object),
/// degree-of-freedom and kinematic relationships, annotations, and computed or measured
/// properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Pose : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor, making an empty Pose.
    /// @details Ensures that the molecules_ object always exists.
    Pose();

    /// @brief Copy constructor.
    Pose( Pose const & ) = default;

    /// @brief Default destructor.
    ~Pose() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual PoseSP clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual PoseSP deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

    /// @brief Returns "Pose".
    /// @details Calls static version.
    std::string
    class_name() const override;

    /// @brief Returns "Pose".
    /// @details Called by non-static version.
    static
    std::string
    class_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the Molecules object in this pose, by shared pointer.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    core::chemistry::MoleculesCSP
    molecules_shared_ptr() const;

    /// @brief Access the Molecules object in this pose, by weak pointer.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    core::chemistry::MoleculesCWP
    molecules_weak_ptr() const;

    /// @brief Access the Molecules object in this pose, by const reference.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    core::chemistry::Molecules const &
    molecules() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the Pose class.
    /// @details Non-static version calls static version.
    base::api::MasalaObjectAPIDefinitionCSP
    get_api_definition() const override;

    /// @brief Get a description of the API for the Pose class.
    /// @details Static version called by non-static version.
    static
    base::api::MasalaObjectAPIDefinitionCSP
    get_api_definition_static();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The Molecules object in this Pose.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    core::chemistry::MoleculesSP molecules_;

};

} // namespace pose
} // namespace core

#endif // Masala_src_core_pose_Pose_hh