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

/// @file src/core/chemistry/MolecularGeometry.hh
/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_MolecularGeometry_hh
#define Masala_src_core_chemistry_MolecularGeometry_hh

// Forward declarations:
#include <core/chemistry/MolecularGeometry.fwd.hh>

// Core headers:
#include <base/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>
#include <core/chemistry/atoms/AtomInstanceConstIterator.fwd.hh>
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.fwd.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.fwd.hh>
#include <core/chemistry/MolecularGeometryConfiguration.fwd.hh>
#include <base/types.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/configuration/ConfigurationBase.fwd.hh>

// STL headers:
#include <array>
#include <set>
#include <vector>
#include <map>
#include <mutex>

namespace masala {
namespace core {
namespace chemistry {

/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MolecularGeometry : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    /// @details Gets configuration from configuration manager, which may trigger load from disk.
    MolecularGeometry();

    /// @brief Copy constructor.
    /// @details Must be explicitly declared due to mutex.
    MolecularGeometry( MolecularGeometry const & src );

    /// @brief Default destructor.
    ~MolecularGeometry() override = default;

    /// @brief Assignment operator.
    /// @details Be sure to update this as data are added.
    MolecularGeometry &
    operator=(
        MolecularGeometry const & src
    );

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    MolecularGeometrySP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    /// @details Threadsafe.  Be sure to update this function whenever a private member is added!
    virtual
    MolecularGeometrySP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "MolecularGeometry".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry".
	std::string class_namespace() const override;

    /// @brief Get the API definition for this object.
    base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Add an atom to this molecule.
    void
    add_atom(
        masala::core::chemistry::atoms::AtomInstanceSP const & atom_in,
        std::array< masala::base::Real, 3 > const & coords
    );

    /// @brief Get the number of atoms in this molecule.
    base::Size total_atoms() const;

    /// @brief Begin const iterator for accessing atoms.
    atoms::AtomInstanceConstIterator
    atoms_begin() const;

    /// @brief End const iterator for accessing atoms.
    atoms::AtomInstanceConstIterator
    atoms_end() const;

    /// @brief Access the coordinates for an atom.
    std::array< masala::base::Real, 3 >
    get_atom_coordinates(
        atoms::AtomInstanceConstIterator const atom_iterator
    ) const;

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

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the master coordinate representation.
    /// @details Creates the representation from options if necessary.
    /// @note For nonconst access. Use with care!  Avoid:
    /// - Holding on to this owning pointer past a single manipulation or set of manipulations.
    /// - Calling this from multiple threads.  This function does not lock the object mutex!  It should
    /// only be called from locked contexts!
    masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP
    master_atom_coordinate_representation_mutex_locked();

	/// @brief Create a configuration object for this object.
	/// @details Can trigger read from disk.  Private since it intended to be called only the first time
	/// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
	/// implementation throws.  Must be implemented by derived classes that have configurations.
	/// @note Receives an instance of a MasalaConfigurationManagerAuthorization object.  Since this has a
	/// private constructor, it can only be instantiated by the MasalaConfigurationManager, its only friend
	/// class.  This version creates a MolecularGeometryConfiguration object.
	base::managers::configuration::ConfigurationBaseCSP
	load_configuration(
		base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
	) const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Check whether an atom exists in this object.
    /// @returns True if the atom exists, false otherwise.
    bool
    has_atom(
        masala::core::chemistry::atoms::AtomInstanceCSP const & atom
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Does a bond exist between two atoms?
	/// @details Intended to be called from a mutex-locked context.
	bool
	has_bond_mutex_locked(
		masala::core::chemistry::atoms::AtomInstanceCSP const & atom1,
		masala::core::chemistry::atoms::AtomInstanceCSP const & atom2
	) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for locking a whole molecular geometry object.
    mutable std::mutex whole_object_mutex_;

    /// @brief Configuration for this object.
    MolecularGeometryConfigurationCSP configuration_;

    /// @brief The representation of the atom coordinates.
    /// @details Different calculators might need atoms represented in different ways, internally (e.g.
    /// matrices of coordinates, etc.)  Different subclasses of the AtomCoordinateRepresentation class
    /// store the data differently, but all offer iterators to access atom coordinates.
    /// @note This is the MASTER representation.  All other representations either update this
    /// representation, or are updated by this representation.  Be sure to use master_atom_coordinate_representation()
    /// internally, since this does a check for whether it's necessary to create the master representation.
    masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP master_atom_coordinate_representation_;

    /// @brief Have the master coordinates changed?
    bool master_coordinates_have_changed_ = false;

    /// @brief Additional representations of atom coordinates.
    std::vector< masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP > additional_atom_coordinate_representations_;

    /// @brief The atoms themselves and their properties.
    /// @details The MolecularGeometry container is responsible for keeping these linked to the
    /// AtomCoordinateRepresentation.
    /// @note This is deliberately a set and not a vector to prevent an arbitrary index
    /// from being handed out or used for atoms.  Iterators are properly used to iterate
    /// over all atoms, and pointers to access a particular atom.  This also allows more
    /// efficient insertions and deletions of atoms.  AtomCoordinateRepresentations are
    /// responsible for keeping track of coordinates given atom smart pointers.
    std::set< masala::core::chemistry::atoms::AtomInstanceSP > atoms_;

    /// @brief A set of const shared pointers to the atoms, for convenience of iterating with
    /// iterators to AtomInstanceCSPs.
    std::set< masala::core::chemistry::atoms::AtomInstanceCSP > atoms_const_;

    /// @brief The bonds between atoms.
    /// @note This is deliberately a set and not a vector to prevent an arbitrary index
    /// from being handed out or used for bonds.  Iterators are properly used to iterate
    /// over all bonds, and pointers to access a particular bonds.  This also allows more
    /// efficient insertions and deletions of bonds.
    std::set< masala::core::chemistry::bonds::ChemicalBondInstanceSP > bonds_;

    /// @brief The API definition for this class.
    base::api::MasalaObjectAPIDefinitionCSP api_definition_;

}; // class MolecularGeometry

} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_MolecularGeometry_hh