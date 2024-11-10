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

/// @file src/core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.hh
/// @brief A container of atom coordinates, using the Eigen linear algebra library's data structures.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_hh
#define Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_hh

// Parent headers:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>

// Forward declarations:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.fwd.hh>

// Core headers:
#include <base/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// External headers:
#include <external/eigen/Eigen/Core>

// STL headers:
#include <mutex>
#include <map>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {


/// @brief A container of atom coordinates, using the Eigen linear algebra library's data structures.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class EigenLinalgCartesianAtomCoordinateRepresentation : public masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentation {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    EigenLinalgCartesianAtomCoordinateRepresentation() = default;

    /// @brief Copy constructor.
    EigenLinalgCartesianAtomCoordinateRepresentation( EigenLinalgCartesianAtomCoordinateRepresentation const & src );

    // Destructor ommitted to keep class pure virtual.
    ~EigenLinalgCartesianAtomCoordinateRepresentation() override = default;

    /// @brief Assignment operator.
    EigenLinalgCartesianAtomCoordinateRepresentation &
    operator=( EigenLinalgCartesianAtomCoordinateRepresentation const & src );

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    AtomCoordinateRepresentationSP
    clone() const override;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    EigenLinalgCartesianAtomCoordinateRepresentationSP
    deep_clone() const;

	/// @brief Make this object instance fully independent.
	void
	make_independent();

    /// @brief Returns "EigenLinalgCartesianAtomCoordinateRepresentation".
    std::string
    class_name() const override;

    /// @brief Returns "masala::core::chemistry::atoms::coordinates".
    std::string
    class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PLUGIN CLASS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the categories for this plugin.
    /// @returns {{ "AtomCoordinateRepresentation", "CartesianAtomCoordinateRepresentation" }}
    std::vector< std::vector< std::string > >
    get_categories() const override;

    /// @brief Get the keywords for this plugin.
    /// @returns { "atom_coordinate_representation", "cartesian", "linear_algebra", "Eigen" }
    std::vector< std::string >
    get_keywords() const override;

    /// @brief Get the categories for this DataRepresentation.
    /// @returns {{ "AtomCoordinateRepresentation", "CartesianAtomCoordinateRepresentation" }}
    std::vector< std::vector< std::string > >
    get_data_representation_categories() const override;

	/// @brief Get the keywords that this data representation plugin has.
	/// @details Categories are hierarchical, with the hierarchy represented as a vector of
	/// strings.  One data representation category can be classified into multiple categories.
	/// @returns { "atom_coordinate_representation", "cartesian", "linear_algebra", "Eigen" }
	std::vector< std::string >
	get_data_representation_keywords() const override;

    /// @brief Get the compatible engines for this data representation.
    /// @returns Currently an empty list.  This may change in the future.
    std::vector< std::string >
    get_compatible_masala_engines() const override;

    /// @brief Get the properties of this data representation.
    /// @returns { "atom_coordinate_representation", "cartesian", "linear_algebra", "Eigen" }
    std::vector< std::string >
    get_present_data_representation_properties() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Replace an atom instance with a new one.
    /// @note Must be implemented by derived classes.
    void
    replace_atom_instance(
        AtomInstanceCSP const & old_instance,
        AtomInstanceCSP const & new_instance
    ) override;

    /// @brief Add an atom.
    /// @note Must be implemented by derived classes.
    void
    add_atom_instance(
        AtomInstanceCSP const & new_atom,
        std::array< masala::base::Real, 3 > const & new_atom_coordinates
    ) override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the coordinates of an atom.
    /// @note Must be implemented by derived classes.
    std::array< masala::base::Real, 3 >
    get_atom_coordinates(
        AtomInstanceCSP const & atom
    ) const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API DEFINITION GETTER
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get an object describing the API for this object.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Replace an atom instance with a new one.  This version should be called only from
	/// a mutex-locked context.
    void
    replace_atom_instance_mutex_locked(
        AtomInstanceCSP const & old_instance,
        AtomInstanceCSP const & new_instance
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for locking this object.
    mutable std::mutex mutex_;

    /// @brief The API definition for this object.
    masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

    /// @brief Data storage for atom coordinates.
    /// @details Rows are x, y, and z coordinates.  Columns are for atoms.
    Eigen::Matrix< masala::base::Real, 3, Eigen::Dynamic > atom_coordinates_;

    /// @brief Map of atom index to column index.
    std::map< masala::core::chemistry::atoms::AtomInstanceCSP, masala::base::Size > atom_instance_to_column_;

};

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_hh