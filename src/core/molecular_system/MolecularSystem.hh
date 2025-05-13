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

/// @file src/core/molecular_system/MolecularSystem.hh
/// @brief A class representing a molecular structure.
/// @details MolecularSystems store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @note A MolecularSystem is equivalent to what is called a "Pose" in other molecular modelling
/// packages, such as Rosetta.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_molecular_system_MolecularSystem_hh
#define Masala_src_core_molecular_system_MolecularSystem_hh

// Forward declarations:
#include <core/molecular_system/MolecularSystem.fwd.hh>

// Core headers:
#include <core/chemistry/MolecularGeometry.fwd.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/MasalaObject.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace core {
namespace molecular_system {


/// @brief A class representing a molecular structure.
/// @details MolecularSystems store atom coordinates and bonds (in the form of a MolecularGeometry object),
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
    /// @details Ensures that the molecular_geometry_ object always exists.
    MolecularSystem();

    /// @brief Copy constructor (explicit due to mutex).
    /// @details Doesn't make this independent.  Use deep_clone() or make_independent() for that.
    MolecularSystem( MolecularSystem const & src );

	/// @brief An example of a deprecated constructor.  Does nothing.
	MolecularSystem( std::string const & dummy_setting_in, masala::base::Size const another_setting );

    /// @brief Default destructor.
    ~MolecularSystem() override = default;

    /// @brief Assignment operator (explicit due to mutex).
    MolecularSystem & operator=( MolecularSystem const & src );

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

    /// @brief Every class can provide its own namespace.  This returns "masala::core::molecular_system".
    /// @details Calls static version
    std::string
    class_namespace() const override;

    /// @brief Returns "masala::core::molecular_system".
    /// @details Called by non-static version.
    static
    std::string
    class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the MolecularGeometry object in this molecular system, by shared pointer.
    /// @details The MolecularGeometry object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A MolecularGeometry object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MolecularGeometryCSP
    molecular_geometry_shared_ptr() const;

    /// @brief Access the MolecularGeometry object in this molecular system, by weak pointer.
    /// @details The MolecularGeometry object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A MolecularGeometry object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MolecularGeometryCWP
    molecular_geometry_weak_ptr() const;

    /// @brief Access the MolecularGeometry object in this molecular system, by const reference.
    /// @details The MolecularGeometry object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A MolecularGeometry object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MolecularGeometry const &
    molecular_geometry() const;

	/// @brief An example of a deprecated API getter.
	bool
	deprecated_api_getter(
		masala::base::Size const input1
	);

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Add an atom to this molecular system.
    void
    add_atom(
        masala::core::chemistry::atoms::AtomInstanceSP const & new_atom,
        std::array< masala::base::Real, 3 > const & coords
    );

    /// @brief Add a bond to this molecule, with the bond type specified by string.
    void
    add_bond(
        masala::core::chemistry::atoms::AtomInstanceCSP const & first_atom,
        masala::core::chemistry::atoms::AtomInstanceCSP const & second_atom,
        std::string const & bond_type_string
    );

    /// @brief Add a bond to this molecule.
    void
    add_bond(
        masala::core::chemistry::atoms::AtomInstanceCSP const & first_atom,
        masala::core::chemistry::atoms::AtomInstanceCSP const & second_atom,
        masala::core::chemistry::bonds::ChemicalBondType const bond_type
    );

	/// @brief An example of a deprecated API setter.
	void
	deprecated_api_setter(
		masala::base::Size const input1
	);

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

    /// @brief A mutex for this object.
    mutable std::mutex mutex_;

    /// @brief The MolecularGeometry object in this MolecularSystem.
    /// @details The MolecularGeometry object contains the coordinates and properties of atoms
    /// and chemical bonds.
    /// @note A MolecularGeometry object may contain more than one molecule (i.e. its atoms may
    /// not all form one contiguously-bonded set).
    masala::core::chemistry::MolecularGeometrySP molecular_geometry_;

    /// @brief A description of this object's interface.
    /// @details Generated on first request.  Persists only as long as this instance
    /// persists.  Weak pointers are handed out.
    masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;


};

} // namespace molecular_system
} // namespace core
} // namespace masala

#endif // Masala_src_core_molecular_system_MolecularSystem_hh