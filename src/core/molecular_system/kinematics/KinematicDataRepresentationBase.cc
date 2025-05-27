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

} // namespace kinematics
} // namespace molecular_system
} // namespace core
} // namespace masala
