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

/// @file src/core/pose/MolecularSystem.hh
/// @brief A class representing a molecular structure.
/// @details MolecularSystems store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @note A MolecularSystem is equivalent to what is called a "Pose" in other molecular modelling
/// packages, such as Rosetta.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_pose_MolecularSystem_hh
#define Masala_src_core_pose_MolecularSystem_hh

// Forward declarations:
#include <core/pose/MolecularSystem.fwd.hh>

// Core headers:
#include <core/chemistry/Molecules.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace masala {
namespace core {
namespace pose {


/// @brief A class representing a molecular structure.
/// @details MolecularSystems store atom coordinates and bonds (in the form of a Molecules object),
/// degree-of-freedom and kinematic relationships, annotations, and computed or measured
/// properties.
/// @note A MolecularSystem is equivalent to what is called a "Pose" in other molecular modelling
/// packages, such as Rosetta.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MolecularSystem : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor, making an empty MolecularSystem.
    /// @details Ensures that the molecules_ object always exists.
    MolecularSystem();

    /// @brief Copy constructor.
    MolecularSystem( MolecularSystem const & ) = default;

    /// @brief Default destructor.
    ~MolecularSystem() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual MolecularSystemSP clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual MolecularSystemSP deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

    /// @brief Returns "MolecularSystem".
    /// @details Calls static version.
    std::string
    class_name() const override;

    /// @brief Returns "MolecularSystem".
    /// @details Called by non-static version.
    static
    std::string
    class_name_static();

    /// @brief Every class can provide its own namespace.  This returns "masala::core::pose".
    /// @details Calls static version
    std::string
    class_namespace() const override;

    /// @brief Returns "masala::core::pose".
    /// @details Called by non-static version.
    static
    std::string
    class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the Molecules object in this pose, by shared pointer.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MoleculesCSP
    molecules_shared_ptr() const;

    /// @brief Access the Molecules object in this pose, by weak pointer.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MoleculesCWP
    molecules_weak_ptr() const;

    /// @brief Access the Molecules object in this pose, by const reference.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::Molecules const &
    molecules() const;

    /// @brief Access the Molecules object in this pose, by nonconst shared pointer.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.  We will use an observer system to ensure that direct updates
    /// to the Molecules object also appropriately update any MolecularSystem containing it, so direct
    /// access is safe.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MoleculesSP
    molecules_shared_ptr_nonconst();

    /// @brief Access the Molecules object in this pose, by nonconst weak pointer.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.  We will use an observer system to ensure that direct updates
    /// to the Molecules object also appropriately update any MolecularSystem containing it, so direct
    /// access is safe.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MoleculesWP
    molecules_weak_ptr_nonconst();

    /// @brief Access the Molecules object in this pose, by nonconst reference.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.  We will use an observer system to ensure that direct updates
    /// to the Molecules object also appropriately update any MolecularSystem containing it, so direct
    /// access is safe.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::Molecules &
    molecules_nonconst();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the MolecularSystem class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The Molecules object in this MolecularSystem.
    /// @details The Molecules object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A Molecules object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MoleculesSP molecules_;

    /// @brief A description of this object's interface.
    /// @details Generated on first request.  Persists only as long as this instance
    /// persists.  Weak pointers are handed out.
    masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;


};

} // namespace pose
} // namespace core
} // namespace masala

#endif // Masala_src_core_pose_MolecularSystem_hh