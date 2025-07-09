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

/// @file src/base/managers/mpi/MasalaMPIManager.hh
/// @brief Headers for a static singleton for managing Masala behaviour in an MPI context.
/// @details This will ultimately handle two cases:
/// - External code is using MPI, and is calling Masala.
/// - Masala has launched MPI processes, and is handling MPI calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_mpi_MasalaMPIManager_hh
#define Masala_src_base_managers_mpi_MasalaMPIManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/mpi/MasalaMPIManager.fwd.hh>
//#include <base/managers/mpi/MasalaMPIManagerConfiguration.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <functional>
#include <mutex>
#include <atomic>
#include <thread>

namespace masala {
namespace base {
namespace managers {
namespace mpi {

/// @brief Modes for MPI in Masala.
/// @details Currently, no MPI or externally-managed MPI are supported.  Ultimately, internally-managed MPI will
/// also be suppported, but this has not yet been added.
enum class MasalaMPIMode {
	INVALID_MODE = 0, // KEEP THIS FIRST
	NO_MPI,
	EXTERNALLY_MANAGED_MPI,
	INTERNALLY_MANAGED_MPI, // Keep this second-to-last.
	N_MPI_MODES=MasalaMPIMode::INTERNALLY_MANAGED_MPI // Keep this last.
};

/// @brief A static singleton for managing Masala behaviour in an MPI context.
/// @details This will ultimately handle two cases:
/// - External code is using MPI, and is calling Masala.
/// - Masala has launched MPI processes, and is handling MPI calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaMPIManager : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC INITIALIZATION AND ACCESS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Instantiate the static singleton, and configure it for externally-managed MPI processes.
	/// @details Throws if the MPI manager has already been instantiated.  Must be called from ALL MPI ranks!
	static
	MasalaMPIManagerHandle
	initialize_for_external_mpi(
		masala::base::Size const this_mpi_rank,
		masala::base::Size const n_mpi_ranks
	);

	/// @brief Check whether the MasalaMPIManager has been initialized.
	static bool manager_was_initialized();

	/// @brief Get a handle to the static singleton, instantiating it if it has not yet been instantiated.
	/// @details If an initialization function isn't called first (in all processes), then this sets the MPI
	/// manager up to report that MPI is NOT being used at all.
	/// @note If throw_if_initialized is true, then we throw if we have already initialized the MPI manager,
	/// and the MPI manager is returned with its internal mutex locked.  Calling code must release this mutex.
	/// False by default, resulting in no check and the object returned with no mutex lock.
	static MasalaMPIManagerHandle get_instance( bool throw_if_initialized = false );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

	/// @brief Private constructor: object can only be instantiated with getInstance().
	MasalaMPIManager();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief No copy constructor.
	MasalaMPIManager( MasalaMPIManager const & ) = delete;

	/// @brief No assignment operator.
	void operator=( MasalaMPIManager const & ) = delete;

	/// @brief Default destructor.
	~MasalaMPIManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC NAMING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of this object.
	/// @details Returns "MasalaMPIManager".
	std::string
	class_name() const override;

	/// @brief Get the namespace of this object.
	/// @details Returns "masala::base::managers::mpi".
	std::string
	class_namespace() const override;

	/// @brief Get the name of this object.  Static version.
	/// @details Returns "MasalaMPIManager".
	static
	std::string
	class_name_static();

	/// @brief Get the namespace of this object.  Static version.
	/// @details Returns "masala::base::managers::mpi".
	static
	std::string
	class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Are we using MPI?
	/// @returns True if the mode is anything but MasalaMPIMode::NO_MPI.
	bool using_mpi() const;

	/// @brief Get the current MPI process rank.
	/// @details Throws if not using MPI.
	masala::base::Size mpi_process_rank() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	// @brief Create a configuration object for this object.
	// @details Can trigger read from disk.  Private since it intended to be called only the first time
	// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
	// implementation throws.  Must be implemented by derived classes that have configurations.
	// @note Receives an instance of a MasalaConfigurationManagerAuthorization object.  Since this has a
	// private constructor, it can only be instantiated by the MasalaConfigurationManager, its only friend
	// class.  This version creates a MasalaMPIManagerConfiguration object.
	// base::managers::configuration::ConfigurationBaseCSP
	// load_configuration(
	//     masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
	// ) const override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief Lock the mpi manager.
	mutable std::mutex mpi_manager_mutex_;

	/// @brief The MPI mode: no MPI, externally-managed MPI, or internally-managed MPI (not yet implemented).
	MasalaMPIMode mpi_mode_ = MasalaMPIMode::NO_MPI;

	/// @brief The rank of this MPI process.
	masala::base::Size this_mpi_rank_ = 0;

	/// @brief The total number of MPI processes.
	masala::base::Size total_mpi_ranks_ = 0;

};

} // namespace mpi
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_mpi_MasalaMPIManager_hh