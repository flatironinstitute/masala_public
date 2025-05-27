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

/// @file src/core_api/base_classes/molecular_system/kinematics/PluginKinematicDataRepresentation.cc
/// @brief Implementations for a base class for plugin Masala kinematic data representations, which facilitate kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).  This class is pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <core_api/base_classes/molecular_system/kinematics/PluginKinematicDataRepresentation.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentation.hh>
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace molecular_system {
namespace kinematics {


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.  Explicit due to mutex.
PluginKinematicDataRepresentation::PluginKinematicDataRepresentation(
	PluginKinematicDataRepresentation const & src
) :
	Parent(src)
{
	std::lock( src.data_representation_mutex(), data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock ); 
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock ); 
	protected_assign( src );
}

/// @brief Assignment operator.  Explicit due to mutex.
PluginKinematicDataRepresentation &
PluginKinematicDataRepresentation::operator=(
	PluginKinematicDataRepresentation const & src
) {
	std::lock( src.data_representation_mutex(), data_representation_mutex() );
	std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock ); 
	std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock ); 
	protected_assign( src );
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
PluginKinematicDataRepresentation::protected_empty() const {
	return Parent::protected_empty();
}

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
PluginKinematicDataRepresentation::protected_clear() {
	Parent::protected_clear();
}

/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
void
PluginKinematicDataRepresentation::protected_reset() {
	Parent::protected_assign();
}

/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
/// by derived classses.  Performs no mutex-locking.
void
PluginKinematicDataRepresentation::protected_make_independent() {
	Parent::protected_make_independent();
}

/// @brief Called by the assignment operator and the copy constructor, this copies all data.  Must be implemented by
/// derived classes.  Performs no mutex locking.
/// @param src The object that we are copying from.
void
PluginKinematicDataRepresentation::protected_assign(
	masala::base::managers::engine::MasalaDataRepresentation const & src
) {
	PluginKinematicDataRepresentation const * src_ptr_cast( dynamic_cast< PluginKinematicDataRepresentation const * >( &src ) );
	CHECK_OR_THROW_FOR_CLASS( src_ptr_cast != nullptr, "protected_assign", "Could not assign an object of type " + src.class_name() +
		" to an object of type PluginKinematicDataRepresentation."
	);
	Parent::protected_assign( src );
}

} // namespace kinematics
} // namespace molecular_system
} // namespace base_classes
} // namespace core_api
} // namespace masala
