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

/// @file src/core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.cc
/// @brief A container of atom coordinates, using the Eigen linear algebra library's data structures.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/utility/container/container_util.tmpl.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {
    

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.
EigenLinalgCartesianAtomCoordinateRepresentation::EigenLinalgCartesianAtomCoordinateRepresentation(
    EigenLinalgCartesianAtomCoordinateRepresentation const & src
) :
    AtomCoordinateRepresentation(src)
{
    std::lock( mutex_, src.mutex_ );
    std::lock_guard< std::mutex > lock1( mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lock2( src.mutex_, std::adopt_lock );
    atom_coordinates_ = src.atom_coordinates_;
    atom_instance_to_column_ = src.atom_instance_to_column_;
}

/// @brief Assignment operator.
EigenLinalgCartesianAtomCoordinateRepresentation &
EigenLinalgCartesianAtomCoordinateRepresentation::operator=(
    EigenLinalgCartesianAtomCoordinateRepresentation const & src
) {
    std::lock( mutex_, src.mutex_ );
    std::lock_guard< std::mutex > lock1( mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lock2( src.mutex_, std::adopt_lock );
    AtomCoordinateRepresentation::operator=( src );
    atom_coordinates_ = src.atom_coordinates_;
    atom_instance_to_column_ = src.atom_instance_to_column_;
    return *this;
}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
AtomCoordinateRepresentationSP
EigenLinalgCartesianAtomCoordinateRepresentation::clone() const {
    return masala::make_shared< EigenLinalgCartesianAtomCoordinateRepresentation >(*this);
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
EigenLinalgCartesianAtomCoordinateRepresentationSP
EigenLinalgCartesianAtomCoordinateRepresentation::deep_clone() const {
    EigenLinalgCartesianAtomCoordinateRepresentationSP new_object( masala::make_shared< EigenLinalgCartesianAtomCoordinateRepresentation >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Make this object instance fully independent.
void
EigenLinalgCartesianAtomCoordinateRepresentation::make_independent() {
    std::lock_guard< std::mutex > lock( mutex_ );
	using masala::core::chemistry::atoms::AtomInstanceCSP;
	using masala::base::Size;

	std::vector< AtomInstanceCSP > old_atom_instances;
	std::vector< AtomInstanceCSP > new_atom_instances;
	Size const n_atoms( atom_instance_to_column_.size() );
	old_atom_instances.reserve( n_atoms );
	new_atom_instances.reserve( n_atoms );
	for( auto const & entry : atom_instance_to_column_ ) {
		old_atom_instances.push_back( entry.first );
		new_atom_instances.push_back( entry.first->deep_clone() );
	}

	for( Size i(0); i<=n_atoms; ++i ) {
		replace_atom_instance_mutex_locked( old_atom_instances[i], new_atom_instances[i] );
	}

}

/// @brief Returns "EigenLinalgCartesianAtomCoordinateRepresentation".
std::string
EigenLinalgCartesianAtomCoordinateRepresentation::class_name() const {
    return "EigenLinalgCartesianAtomCoordinateRepresentation";
}

/// @brief Returns "masala::core::chemistry::atoms::coordinates".
std::string
EigenLinalgCartesianAtomCoordinateRepresentation::class_namespace() const {
    return "masala::core::chemistry::atoms::coordinates";
}

////////////////////////////////////////////////////////////////////////////////
// PLUGIN CLASS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the categories for this plugin.
/// @returns {{ "AtomCoordinateRepresentation", "CartesianAtomCoordinateRepresentation" }}
std::vector< std::vector< std::string > >
EigenLinalgCartesianAtomCoordinateRepresentation::get_categories() const {
    return std::vector< std::vector< std::string > > {{ "AtomCoordinateRepresentation", "CartesianAtomCoordinateRepresentation" }};
}

/// @brief Get the keywords for this plugin.
/// @returns { "atom_coordinate_representation", "cartesian", "linear_algebra", "Eigen" }
std::vector< std::string >
EigenLinalgCartesianAtomCoordinateRepresentation::get_keywords() const {
    return std::vector< std::string >{
        "atom_coordinate_representation",
        "cartesian",
        "linear_algebra",
        "Eigen"
    };
}

/// @brief Get the categories for this DataRepresentation.
/// @returns {{ "AtomCoordinateRepresentation", "CartesianAtomCoordinateRepresentation" }}
std::vector< std::vector< std::string > >
EigenLinalgCartesianAtomCoordinateRepresentation::get_data_representation_categories() const {
    return std::vector< std::vector< std::string > >{{ "AtomCoordinateRepresentation", "CartesianAtomCoordinateRepresentation" }};
}

/// @brief Get the compatible engines for this data representation.
/// @returns Currently an empty list.  This may change in the future.
std::vector< std::string >
EigenLinalgCartesianAtomCoordinateRepresentation::get_compatible_masala_engines() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties of this data representation.
/// @returns { "atom_coordinate_representation", "cartesian", "linear_algebra", "Eigen" }
std::vector< std::string >
EigenLinalgCartesianAtomCoordinateRepresentation::get_present_data_representation_properties() const {
    return std::vector< std::string >{
        "atom_coordinate_representation",
        "cartesian",
        "linear_algebra",
        "Eigen" 
    };
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


/// @brief Replace an atom instance with a new one.
/// @note Must be implemented by derived classes.
void
EigenLinalgCartesianAtomCoordinateRepresentation::replace_atom_instance(
    AtomInstanceCSP const & old_instance,
    AtomInstanceCSP const & new_instance
) {
    std::lock_guard< std::mutex > lock( mutex_ );
	replace_atom_instance_mutex_locked( old_instance, new_instance );
}

/// @brief Add an atom.
/// @note Must be implemented by derived classes.
void
EigenLinalgCartesianAtomCoordinateRepresentation::add_atom_instance(
    AtomInstanceCSP const & new_atom,
    std::array< masala::base::Real, 3 > const & new_atom_coordinates
) {
    std::lock_guard< std::mutex > lock( mutex_ );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count(new_atom) == 0, "add_atom_instance", "Atom has already been added!" );
    masala::base::Size const natoms_before( atom_coordinates_.cols() );
    atom_instance_to_column_[ new_atom ] = natoms_before;
    atom_coordinates_.conservativeResize( Eigen::NoChange, natoms_before + 1 );
    atom_coordinates_(0, natoms_before ) = new_atom_coordinates[0]; 
    atom_coordinates_(1, natoms_before ) = new_atom_coordinates[1];
    atom_coordinates_(2, natoms_before ) = new_atom_coordinates[2];
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_coordinates_.cols() >= 0, "add_atom_instance", "Somehow, the number of columns in the atom_coordinates_ matrix is negative.  This is a program error.  Please contact a developer." )
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( static_cast< masala::base::Size >( atom_coordinates_.cols() ) == atom_instance_to_column_.size(), "add_atom_instance", "Mismatch in map and matrix sizes!" );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the coordinates of an atom.
/// @note Must be implemented by derived classes.
std::array< masala::base::Real, 3 >
EigenLinalgCartesianAtomCoordinateRepresentation::get_atom_coordinates(
    AtomInstanceCSP const & atom
) const {
    std::lock_guard< std::mutex > lock( mutex_ );
    auto const it( atom_instance_to_column_.find( atom ) );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( it != atom_instance_to_column_.end(), "get_atom_coordinates", "Atom not found in molecular geometry object!" );
    masala::base::Size const column( it->second );
    return std::array< masala::base::Real, 3 >{ atom_coordinates_(0, column), atom_coordinates_(1, column), atom_coordinates_(2, column) };
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API DEFINITION GETTER
////////////////////////////////////////////////////////////////////////////////

/// @brief Get an object describing the API for this object.
masala::base::api::MasalaObjectAPIDefinitionCWP
EigenLinalgCartesianAtomCoordinateRepresentation::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The EigenLinalgCartesianAtomCoordinateRepresentation class is a data representation for "
                "efficiently representing the Cartesian coordinates of atoms.",
                false, false
            )
        );

        // Constructors:
        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( EigenLinalgCartesianAtomCoordinateRepresentation, api_def );

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< AtomInstanceCSP, AtomInstanceCSP > >(
                "replace_atom_instance", "Replace an atom instance with a new one.",
                "old_instance", "The atom that we are replacing.",
                "new_instance", "The new atom that replaces the old.",
                false, false,
                std::bind( &EigenLinalgCartesianAtomCoordinateRepresentation::replace_atom_instance, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< AtomInstanceCSP, std::array< masala::base::Real, 3 > const & > >(
                "add_atom_instance", "Add an atom.",
                "new_atom", "The atom that we are adding.",
                "new_coords", "The Cartesian coordinates of the atom that we're adding.",
                false, false,
                std::bind( &EigenLinalgCartesianAtomCoordinateRepresentation::add_atom_instance, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_OneInput< std::array< masala::base::Real, 3 >, AtomInstanceCSP const & > >(
                "get_atom_coordinates", "Get the coordinates of an atom.",
                "atom", "The atom whose coordinates we're fetching.",
                "coords", "The coordinates of the atom.",
                false, false,
                std::bind( &EigenLinalgCartesianAtomCoordinateRepresentation::get_atom_coordinates, this, std::placeholders::_1 )
            )
        );

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Replace an atom instance with a new one.  This version should be called only from
/// a mutex-locked context.
void
EigenLinalgCartesianAtomCoordinateRepresentation::replace_atom_instance_mutex_locked(
	AtomInstanceCSP const & old_instance,
	AtomInstanceCSP const & new_instance
) {
	DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count( old_instance ) == 1, "replace_atom_instance", "Could not replace atom.  Old atom is not present!" );
    masala::base::Size const col_index( atom_instance_to_column_.at(old_instance) );
    atom_instance_to_column_.erase(old_instance);
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( atom_instance_to_column_.count(new_instance) == 0, "replace_atom_instance", "Could not replace atom.  New atom is already present!" );
    atom_instance_to_column_[new_instance] = col_index;
}

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
