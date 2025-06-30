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

/// @file src/core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.cc
/// @brief A class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @note This class is not intended to be instantiated outside of the API definition system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>

// Core headers
#include <core/chemistry/atoms/AtomInstance.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.  Explicit due to mutex.
AtomCoordinateRepresentation::AtomCoordinateRepresentation(
	AtomCoordinateRepresentation const & src
) :
	Parent(src)
{
	std::lock( src.data_representation_mutex(), data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock ); 
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
	protected_assign(src);
}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
AtomCoordinateRepresentationSP
AtomCoordinateRepresentation::clone() const {
	return masala::make_shared< AtomCoordinateRepresentation >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
AtomCoordinateRepresentationSP
AtomCoordinateRepresentation::deep_clone() const {
	AtomCoordinateRepresentationSP new_object( masala::make_shared< AtomCoordinateRepresentation >( *this ) );
	new_object->make_independent();
	return new_object;
}

/// @brief Returns "AtomCoordinateRepresentation".
std::string
AtomCoordinateRepresentation::class_name() const {
	return "AtomCoordinateRepresentation";
}

/// @brief Returns "masala::core::chemistry::atoms::coordinates".
std::string
AtomCoordinateRepresentation::class_namespace() const {
	return "masala::core::chemistry::atoms::coordinates";
}

/// @brief Make this object instance fully independent.
void
AtomCoordinateRepresentation::make_independent() {
	std::lock_guard< std::mutex > lock( data_representation_mutex() );
	
	protected_make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PLUGIN CLASS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the categories for this plugin.
/// @returns {{ "AtomCoordinateRepresentation" }}
std::vector< std::vector< std::string > >
AtomCoordinateRepresentation::get_categories() const {
	return std::vector< std::vector< std::string > > {{ "AtomCoordinateRepresentation" }};
}

/// @brief Get the keywords for this plugin.
/// @returns { "atom_coordinate_representation" }
std::vector< std::string >
AtomCoordinateRepresentation::get_keywords() const {
	return std::vector< std::string >{
		"atom_coordinate_representation"
	};
}

/// @brief Get the categories for this DataRepresentation.
/// @returns {{ "AtomCoordinateRepresentation" }}
std::vector< std::vector< std::string > >
AtomCoordinateRepresentation::get_data_representation_categories() const {
	return std::vector< std::vector< std::string > >{{ "AtomCoordinateRepresentation" }};
}

/// @brief Get the keywords that this data representation plugin has.
/// @details Categories are hierarchical, with the hierarchy represented as a vector of
/// strings.  One data representation category can be classified into multiple categories.
/// @returns { "atom_coordinate_representation" }
std::vector< std::string >
AtomCoordinateRepresentation::get_data_representation_keywords() const {
	return std::vector< std::string >{
		"atom_coordinate_representation"
	};
}

/// @brief Get the compatible engines for this data representation.
/// @returns Currently an empty list.  This may change in the future.
std::vector< std::string >
AtomCoordinateRepresentation::get_compatible_masala_engines() const {
	return std::vector< std::string >{};
}

/// @brief Get the properties of this data representation.
/// @returns { "atom_coordinate_representation" }
std::vector< std::string >
AtomCoordinateRepresentation::get_present_data_representation_properties() const {
	return std::vector< std::string >{
		"atom_coordinate_representation"
	};
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


/// @brief Replace an atom instance with a new one.
/// @details Used for deep cloning, since the AtomCoordinateRepresentation does not itself
/// implement a deep_clone() function.
/// @note Must be implemented by derived classes.
void
AtomCoordinateRepresentation::replace_atom_instance(
	AtomInstanceCSP const & ,//old_instance,
	AtomInstanceCSP const & //new_instance
) {
	MASALA_THROW( class_namespace() + "::" + class_name(), "replace_atom_instance",
		"This function must be implemented by plugin classes derived from AtomCoordinateRepresentation."
	);
}

/// @brief Add an atom.
/// @note Must be implemented by derived classes.
void
AtomCoordinateRepresentation::add_atom_instance(
	AtomInstanceCSP const & ,//new_atom,
	std::array< masala::base::Real, 3 > const & //new_atom_coordinates
) {
	MASALA_THROW( class_namespace() + "::" + class_name(), "add_atom_instance",
		"This function must be implemented by plugin classes derived from AtomCoordinateRepresentation."
	);
}

/// @brief Get the coordinates of an atom.
/// @note Must be implemented by derived classes.
std::array< masala::base::Real, 3 >
AtomCoordinateRepresentation::get_atom_coordinates(
	AtomInstanceCSP const & //atom
) const {
	MASALA_THROW( class_namespace() + "::" + class_name(), "get_atom_coordinates",
		"This function must be implemented by plugin classes derived from AtomCoordinateRepresentation."
	);
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API DEFINITION GETTER
////////////////////////////////////////////////////////////////////////////////

/// @brief Get an object describing the API for this object.
masala::base::api::MasalaObjectAPIDefinitionCWP
AtomCoordinateRepresentation::get_api_definition() {
	using namespace masala::base::api;

	std::lock_guard< std::mutex > lock( data_representation_mutex() );

	if( api_definition_ == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"The AtomCoordinateRepresentation class is a base class for the coordinates of a bunch of atoms.  It is not "
                "intended to be instantiated directly outside of the API definition system, and has protected constructors.",
				false, true
			)
		);

		// Constructors:
		ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( AtomCoordinateRepresentation, api_def );

		// Setters:
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< AtomInstanceCSP, AtomInstanceCSP > >(
				"replace_atom_instance", "Replace an atom instance with a new one.  Must be implemented by derived classes.  Base class implementation throws.",
				"old_instance", "The atom that we are replacing.",
				"new_instance", "The new atom that replaces the old.",
				false, false,
				std::bind( &AtomCoordinateRepresentation::replace_atom_instance, this, std::placeholders::_1, std::placeholders::_2 )
			)
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< AtomInstanceCSP, std::array< masala::base::Real, 3 > const & > >(
				"add_atom_instance", "Add an atom.  Must be implemented by derived classes.  Base class implementation throws.",
				"new_atom", "The atom that we are adding.",
				"new_coords", "The Cartesian coordinates of the atom that we're adding.",
				false, false,
				std::bind( &AtomCoordinateRepresentation::add_atom_instance, this, std::placeholders::_1, std::placeholders::_2 )
			)
		);

		// Getters:
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_OneInput< std::array< masala::base::Real, 3 >, AtomInstanceCSP const & > >(
				"get_atom_coordinates", "Get the coordinates of an atom.  Must be implemented by derived classes.  Base class implementation throws.",
				"atom", "The atom whose coordinates we're fetching.",
				"coords", "The coordinates of the atom.",
				false, false,
				std::bind( &AtomCoordinateRepresentation::get_atom_coordinates, this, std::placeholders::_1 )
			)
		);

		api_definition_ = api_def; //Make const.
	}

	return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
AtomCoordinateRepresentation::protected_empty() const { return true; }

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_clear() { /*GNDN.*/ }

/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_reset() { /*GNDN.*/ }

/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
/// by derived classses.  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_make_independent() { /*GNDN.*/ }

/// @brief Assign src to this.  Performs no mutex-locking.
void
AtomCoordinateRepresentation::protected_assign(
    masala::base::managers::engine::MasalaDataRepresentation const & src
) {
    CHECK_OR_THROW_FOR_CLASS( dynamic_cast< AtomCoordinateRepresentation const * >( &src ) != nullptr, "protected_assign",
        "Could not assign an object of type " + src.class_name() + " to an AtomCoordinateRepresentation."
    );
    masala::base::managers::engine::MasalaDataRepresentation::protected_assign( src );
}

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
