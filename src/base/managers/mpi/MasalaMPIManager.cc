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

static std::mutex initialization_mutex_;
static bool manager_is_initialized_ = false;

////////////////////////////////////////////////////////////////////////////////
// MasalaMPIManager PUBLIC STATIC INITIALIZATION AND ACCESS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Instantiate the static singleton, and configure it for externally-managed MPI processes.
/// @details Throws if the MPI manager has already been instantiated.  Must be called from ALL MPI ranks!
MasalaMPIManagerHandle
MasalaMPIManager::initialize_for_external_mpi(
	masala::base::Size const this_mpi_rank,
	masala::base::Size const n_mpi_ranks
) {
	using namespace masala::base::managers::tracer;
	MasalaMPIManagerHandle mpiman( MasalaMPIManager::get_instance( true ) );
	std::lock_guard< std::mutex > lock( mpiman->mpi_manager_mutex_, std::adopt_lock ); // The object should be locked.  This ensures that we ultimately unlock it.
	mpiman->this_mpi_rank_ = this_mpi_rank;
	mpiman->total_mpi_ranks_ = n_mpi_ranks;
	mpiman->mpi_mode_ = MasalaMPIMode::EXTERNALLY_MANAGED_MPI;
	{
		// Configure the tracer manager to report MPI rank.
		MasalaTracerManagerAccessKey access_key;
		MasalaTracerManagerHandle tracerman( MasalaTracerManager::get_instance() );
		tracerman->set_mpi_rank( this_mpi_rank, access_key );
	}
	return mpiman;
}

/// @brief Check whether the MasalaMPIManager has been initialized.
/*static*/
bool
MasalaMPIManager::manager_was_initialized() {
	std::lock_guard< std::mutex > lock( initialization_mutex_ );
	return manager_is_initialized_;
}

/// @brief Get a handle to the static singleton, instantiating it if it has not yet been instantiated.
/// @details If an initialization function isn't called first (in all processes), then this sets the MPI
/// manager up to report that MPI is NOT being used at all.
/// @note If throw_if_initialized is true, then we throw if we have already initialized the MPI manager,
/// and the MPI manager is returned with its internal mutex locked.  Calling code must release this mutex.
/// False by default, resulting in no check and the object returned with no mutex lock.
MasalaMPIManagerHandle
MasalaMPIManager::get_instance(
	bool const throw_if_initialized
) {
	std::lock_guard< std::mutex > lock( initialization_mutex_ );
	if( throw_if_initialized ) {
		CHECK_OR_THROW( !manager_is_initialized_, class_namespace_static() + "::" + class_name_static(),
			"get_instance", "The MasalaMPIManager has already been initialized."
		);
	}
	static MasalaMPIManager mpi_manager;
	manager_is_initialized_ = true;
	if( throw_if_initialized ) {
		mpi_manager.mpi_manager_mutex_.lock(); // Return object locked.
	} else {
		std::lock_guard< std::mutex > lock( mpi_manager.mpi_manager_mutex_ );  // Wait until it's possible to obtain a mutex lock, then unlock.
	}
	return &mpi_manager;
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
// MasalaMPIManager PUBLIC NAMING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaMPIManager".
std::string
MasalaMPIManager::class_name() const {
	return class_name_static();
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::mpi".
std::string
MasalaMPIManager::class_namespace() const {
	return class_namespace_static();
}

/// @brief Get the name of this object.  Static version.
/// @details Returns "MasalaMPIManager".
/*static*/
std::string
MasalaMPIManager::class_name_static() {
	return "MasalaMPIManager";
}

/// @brief Get the namespace of this object.  Static version.
/// @details Returns "masala::base::managers::mpi".
/*static*/
std::string
MasalaMPIManager::class_namespace_static() {
	return "masala::base::managers::mpi";
}

////////////////////////////////////////////////////////////////////////////////
// MasalaMPIManager PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Are we using MPI?
/// @returns True if the mode is anything but MasalaMPIMode::NO_MPI.
bool
MasalaMPIManager::using_mpi() const {
	std::lock_guard< std::mutex > lock( mpi_manager_mutex_ );
	return mpi_mode_ != MasalaMPIMode::NO_MPI;
}

/// @brief Get the current MPI process rank.
/// @details Throws if not using MPI.
masala::base::Size
MasalaMPIManager::mpi_process_rank() const {
	std::lock_guard< std::mutex > lock( mpi_manager_mutex_ );
	CHECK_OR_THROW_FOR_CLASS( mpi_mode_ != MasalaMPIMode::NO_MPI, "mpi_process_rank", "Program error: no MPI rank can be returned when MPI is not used!" );
	return this_mpi_rank_;
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
