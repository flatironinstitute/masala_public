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

/// @file src/base/managers/tracer/MasalaTracerManager.hh
/// @brief A static singleton for managing output to the tracer (screen and/or logfile(s)).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_tracer_MasalaTracerManager_hh
#define Masala_src_base_managers_tracer_MasalaTracerManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/tracer/MasalaTracerManager.fwd.hh>
#include <base/managers/mpi/MasalaMPIManager.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <iostream>
#include <mutex>
#include <thread>

namespace masala {
namespace base {
namespace managers {
namespace tracer {

/// @brief A largely empty class with a private constructor and particlar
/// managers as its only friends, needed for accessing the
/// advanced API functions of the MasalaTracerManager.  This ensures
/// that only managers like the MasalaMPIManager can access these functions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaTracerManagerAccessKey : public masala::base::MasalaObject {

	// We make the MasalaMPIManager a friend so that it alone can instantiate
	// this private-constructor key class.
	friend class masala::base::managers::mpi::MasalaMPIManager;

private:

	/// @brief Default constructor, private.
	MasalaTracerManagerAccessKey() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Copy constructor, deleted.
	MasalaTracerManagerAccessKey( MasalaTracerManagerAccessKey const & ) = delete;

	/// @brief Assignment operator, deleted.
	MasalaTracerManagerAccessKey & operator=( MasalaTracerManagerAccessKey const & ) = delete;

	/// @brief Destructor.
	~MasalaTracerManagerAccessKey() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaTracerManagerAccessKey".
	std::string class_name() const override { return "MasalaTracerManagerAccessKey"; }

	/// @brief Returns "masala::base::managers::tracer".
	std::string class_namespace() const override { return "masala::base::managers::tracer"; }

}; // class MasalaTracerManagerAccessKey


/// @brief A static singleton for managing output to the tracer (screen and/or logfile(s)).
class MasalaTracerManager : public masala::base::MasalaObject {

public:

	/// @brief Instantiate the static singleton and get a handle to it.
	static MasalaTracerManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

	/// @brief Private constructor: object can only be instantiated with getInstance().
	MasalaTracerManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief No copy constructor.
	MasalaTracerManager( MasalaTracerManager const & ) = delete;

	/// @brief No assignment operator.
	void operator=( MasalaTracerManager const & ) = delete;

	/// @brief Default destructor.
	~MasalaTracerManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of this object.
	/// @details Returns "MasalaTracerManager".
	std::string
	class_name() const override;

	/// @brief Get the namespace of this object.
	/// @details Returns "masala::base::managers::tracer".
	std::string
	class_namespace() const override;

	/// @brief If we want to direct output to something other than std::cout, we can provide a pointer
	/// to a std::ostream object.
	/// @details WARNING!  It is the developer's responsibility to manage the lifetime of this object and to
	/// ensure that it persists throughout program execution!
	/// @param output_stream_pointer A pointer to a std::ostream object guaranteed to persist through program execution (
	/// or as long as we use this output stream).
	void
	set_redirect_tracers(
		std::ostream * const output_stream_pointer
	);

	/// @brief Reset the output to flow to std::cout instead of to any custom std::ostream provided previously.
	void
	reset_redirect_tracers();

	/// @brief Check whether a particular tracer is enabled.
	/// @details If the tracer is in the list of tracers specifically enabled or disabled, the
	/// tracer's status is returned.  Otherwise, the global default is returned.
	bool
	tracer_is_enabled(
		std::string const & tracer_name
	) const;

	/// @brief Set whether a particular tracer is explicitly enabled or disabled.  True means
	/// enabled, false means disabled.
	/// @details Can be undone with reset_tracer_state().
	void
	set_tracer_state(
		std::string const & tracer_name,
		bool const setting
	);

	/// @brief Remove the explicit specification for whether a particular tracer is enabled or
	/// disabled.  This reverts the tracer behaviour back to the global setting.
	void
	reset_tracer_state(
		std::string const & tracer_name
	);

	/// @brief Check whether the global default for unspecified tracers is enabled or disabled.
	bool global_tracer_default() const;

	/// @brief Set whether the global default for unspecified tracers is enabled or disabled.
	void set_global_tracer_default( bool const setting );

	/// @brief Write a message to a tracer.
	/// @param tracer_name The tracer to which we are writing.
	/// @param message The text that we are writing.  This gets split by lines, with each line preceded
	/// by the tracer name.
	/// @param skip_check If true, we don't bother to check whether the tracer is enabled.  If false, we
	/// check and skip writing if the tracer is disabled.  Default false.
	void
	write_to_tracer(
		std::string const & tracer_name,
		std::string const & message,
		bool const skip_check = false
	) const;

	/// @brief Get the string for the current thread's ID.
	std::string get_thread_id_string() const;

	/// @brief Register thread ID with the tracer manager.
	void register_thread_id( std::thread::id const system_thread_id, base::Size const masala_thread_id );

	/// @brief Unregister thread ID with the tracer manager.
	void unregister_thread_id( std::thread::id const system_thread_id );

public:

////////////////////////////////////////////////////////////////////////////////
// ADVANCED API PUBLIC MEMBER FUNCTIONS
// These require an instance of a MasalaTracerManagerAccessKey.  Since only
// certain managers can instantiate this class, this ensures that only these
// classes may call these functions.
////////////////////////////////////////////////////////////////////////////////

	/// @brief Indicate that we are using MPI, and set the current MPI rank.
	/// @details In addition to setting the MPI rank, this sets using_mpi_ to true.
	/// @note This requires an instance of a MasalaTracerManagerAccessKey.  Since only
	// certain managers can instantiate this class, this ensures that only these
	// classes may call these functions.
	void
	set_mpi_rank(
		masala::base::Size const rank_in,
		MasalaTracerManagerAccessKey const & access_key
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex to lock this object.
	mutable std::mutex masala_tracer_manager_mutex_;

	/// @brief The stream to which we direct output.  Defaults to std::cout.
	std::ostream * output_stream_ = &std::cout;

	/// @brief The default setting for tracers.
	/// @details Defaults to "on" ("true") for now.  Will be set from configuration file
	/// at a later time.
	bool global_tracer_default_ = true;

	/// @brief List of tracers that are either explicitly enabled or explicitly disabled.
	std::map< std::string, bool > explicitly_enabled_or_disabled_tracers_;

	/// @brief Are we using MPI?
	bool using_mpi_ = false;

	/// @brief If we are using MPI, what is the rank of the current process?
	masala::base::Size mpi_process_rank_ = 0;

	/// @brief A mutex for the list of threads that this object knows about.
	mutable std::mutex thread_map_mutex_;

	/// @brief List of threads that this object knows about.
	std::map< std::thread::id, base::Size > thread_map_;

};

} // namespace tracer
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_tracer_MasalaTracerManager_hh