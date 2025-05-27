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

/// @file src/core/molecular_system/kinematics/KinematicDataRepresentationBase.cc
/// @brief Implementations for a base class for Masala kinematic data representations, which facilitate kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).  This class is not intended
/// to be instantiated outside of the API system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <core/molecular_system/kinematics/KinematicDataRepresentationBase.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentation.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace core {
namespace molecular_system {
namespace kinematics {


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.  Explicit due to mutex.
KinematicDataRepresentationBase::KinematicDataRepresentationBase(
	KinematicDataRepresentationBase const & src
) :
	Parent(src)
{
	std::lock( src.data_representation_mutex(), data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock ); 
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock ); 
	protected_assign( src );
}

/// @brief Assignment operator.  Explicit due to mutex.
KinematicDataRepresentationBase &
KinematicDataRepresentationBase::operator=(
	KinematicDataRepresentationBase const & src
) {
	std::lock( src.data_representation_mutex(), data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock ); 
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock ); 
	protected_assign( src );
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name.  Returns "KinematicDataRepresentationBase".
std::string
KinematicDataRepresentationBase::class_name() const {
	return "KinematicDataRepresentationBase";
}

/// @brief Get the class namespace.  Returns "masala::core::molecular_system::kinematics".
std::string
KinematicDataRepresentationBase::class_namespace() const {
	return "masala::core::molecular_system::kinematics";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS FOR PLUGINS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.
/// @returns {{ "KinematicDataRepresentation" }}.
std::vector< std::vector< std::string > >
KinematicDataRepresentationBase::get_categories() const {
	return std::vector< std::vector< std::string > >{ { "KinematicDataRepresentation" } };
}

/// @brief Get the keywords for this plugin class.
/// @returns Returns { "kinematic_data_representation" }.
std::vector< std::string >
KinematicDataRepresentationBase::get_keywords() const {
	return std::vector< std::string >{ "kinematic_data_representation" };
}

////////////////////////////////////////////////////////////////////////////////
// DATA REPRESENTATION CATEGORIES, COMPATIBILITY, AND PROPERTIES FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the categories that this data representation plugin falls into.
/// @returns {{ "KinematicDataRepresentation" }}.
std::vector< std::vector< std::string > >
KinematicDataRepresentationBase::get_data_representation_categories() const {
	return std::vector< std::vector< std::string > >{ { "KinematicDataRepresentation" } };
}

/// @brief Get the keywords that this data representation plugin has.
/// @returns Returns { "kinematic_data_representation" }.
std::vector< std::string >
KinematicDataRepresentationBase::get_data_representation_keywords() const {
	return std::vector< std::string >{ "kinematic_data_representation" };
}

/// @brief Get the MasalaEngines that with which this data representation plugin
/// is DEFINITELY compatible.  (There may be other engines with which it is also
/// compatible, so this is not necessarily an exhaustive list.)
/// @returns An empty list right now.  May change later.
std::vector< std::string >
KinematicDataRepresentationBase::get_compatible_masala_engines() const {
	return std::vector< std::string >{};
}

/// @brief Get the MasalaEngines that with which this data representation plugin
/// is DEFINITELY NOT compatible.  (There may be other engines with which it is also
/// not compatible, so this is not necessarily an exhaustive list.)
/// @returns An empty list right now.
std::vector< std::string >
KinematicDataRepresentationBase::get_incompatible_masala_engines() const {
	return std::vector< std::string >{};
}

/// @brief Get the properties that this MasalaDataRepresentation has.  (Note that this can be
/// a non-exhaustive list.  If one data representation says it has the property
/// "linearly-scaling", another could also be linearly scaling despite not listing this.)
/// @returns { "kinematic_data_representation" }.
std::vector< std::string >
KinematicDataRepresentationBase::get_present_data_representation_properties() const {
	return std::vector< std::string >{ "kinematic_data_representation" };
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
KinematicDataRepresentationBase::protected_empty() const {
	return true;
}

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
KinematicDataRepresentationBase::protected_clear() {
	// GNDN
}

/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
void
KinematicDataRepresentationBase::protected_reset() {
	// GNDN
}

/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
/// by derived classses.  Performs no mutex-locking.
void
KinematicDataRepresentationBase::protected_make_independent() {
	// GNDN
}

/// @brief Called by the assignment operator and the copy constructor, this copies all data.  Must be implemented by
/// derived classes.  Performs no mutex locking.
/// @param src The object that we are copying from.
void
KinematicDataRepresentationBase::protected_assign(
	masala::base::managers::engine::MasalaDataRepresentation const & src
) {
	KinematicDataRepresentationBase const * src_ptr_cast( dynamic_cast< KinematicDataRepresentationBase const * >( &src ) );
	CHECK_OR_THROW_FOR_CLASS( src_ptr_cast != nullptr, "protected_assign", "Could not assign an object of type " + src.class_name() +
		" to an object of type KinematicDataRepresentationBase."
	);
	Parent::protected_assign( src );
}

} // namespace kinematics
} // namespace molecular_system
} // namespace core
} // namespace masala
