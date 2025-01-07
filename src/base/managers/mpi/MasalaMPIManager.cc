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

/// @file src/base/managers/mpi/MasalaMPIManager.cc
/// @brief Implementation of a static singleton for managing Masala behaviour in an MPI context.
/// @details This will ultimately handle two cases:
/// - External code is using MPI, and is calling Masala.
/// - Masala has launched MPI processes, and is handling MPI calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/mpi/MasalaMPIManager.hh>

// Base headers:
//#include <base/managers/mpi/MasalaMPIManagerConfiguration.hh>
#include <base/error/ErrorHandling.hh>
//#include <base/managers/configuration/MasalaConfigurationManager.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace mpi {


/// @brief Instantiate the static singleton and get a handle to it.
MasalaMPIManagerHandle
MasalaMPIManager::get_instance() {
	static MasalaMPIManager thread_manager;
	return &thread_manager;
}

////////////////////////////////////////////////////////////////////////////////
// MasalaMPIManager PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
MasalaMPIManager::MasalaMPIManager() :
	base::MasalaObject()
{
	//std::lock_guard< std::mutex > lock( mpi_manager_mutex_ );
}

////////////////////////////////////////////////////////////////////////////////
// MasalaMPIManager PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaMPIManager".
std::string
MasalaMPIManager::class_name() const {
	return "MasalaMPIManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::mpi".
std::string
MasalaMPIManager::class_namespace() const {
	return "masala::base::managers::mpi";
}

////////////////////////////////////////////////////////////////////////////////
// MasalaMPIManager PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// @brief Create a configuration object for this object.
// @details Can trigger read from disk.  Private since it intended to be called only the first time
// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
// implementation throws.  Must be implemented by derived classes that have configurations.
// @note Receives an instance of a MasalaConfigurationManagerAuthorization object.  Since this has a
// private constructor, it can only be instantiated by the MasalaConfigurationManager, its only friend
// class.  This version creates a MasalaMPIManagerConfiguration object.
// base::managers::configuration::ConfigurationBaseCSP
// MasalaMPIManager::load_configuration(
// 	masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
// ) const {

// 	write_to_tracer( "Loading default MasalaMPIManager configuration." );

// 	return masala::make_shared< MasalaMPIManagerConfiguration >( passkey );
// }

} // namespace mpi
} // namespace managers
} // namespace base
} // namespace masala
