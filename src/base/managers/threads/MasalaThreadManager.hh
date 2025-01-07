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

/// @file src/base/managers/threads/MasalaThreadManager.hh
/// @brief A static singleton for managing a thread pool, and execution of code
/// in parallel threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadManager_hh
#define Masala_src_base_managers_threads_MasalaThreadManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/threads/MasalaThreadManager.fwd.hh>
#include <base/managers/threads/MasalaThreadManagerConfiguration.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.fwd.hh>
#include <base/managers/threads/MasalaThreadedWorkRequest.fwd.hh>
#include <base/managers/threads/thread_pool/MasalaThreadPool.fwd.hh>

// STL headers:
#include <functional>
#include <mutex>
#include <atomic>
#include <thread>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief A largely empty class with a private constructor and the
/// MasalaThreadManager as its only friend, needed for accessing the
/// advanced API functions of the MasalaThreadManager.  This ensures
/// that the MasalaThreadManager can control what can access these
/// functions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadManagerAccessKey : public masala::base::MasalaObject {

	// We make the MasalaThreadManager a friend so that it alone can instantiate
	// this private-constructor key class.
	friend class MasalaThreadManager;

private:

	/// @brief Default constructor, private.
	MasalaThreadManagerAccessKey() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Copy constructor, deleted.
	MasalaThreadManagerAccessKey( MasalaThreadManagerAccessKey const & ) = delete;

	/// @brief Assignment operator, deleted.
	MasalaThreadManagerAccessKey & operator=( MasalaThreadManagerAccessKey const & ) = delete;

	/// @brief Destructor.
	~MasalaThreadManagerAccessKey() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadManagerAccessKey".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads".
	std::string class_namespace() const override;

}; // class MasalaThreadManagerAccessKey


/// @brief A static singleton for managing a thread pool, and execution of code
/// in parallel threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaThreadManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    /// @details Creates the thread pool object, but that does not launch threads until
    /// work is first assigned to threads (lazy thread launching).
    MasalaThreadManager();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaThreadManager( MasalaThreadManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaThreadManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaThreadManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaThreadManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::threads".
    std::string
    class_namespace() const override;

    /// @brief Get the number of hardware threads available on this node.
    /// @details May return 0 if std::thread::hardware_concurrency() does not
    /// work for some reason on this hardware.
    masala::base::Size hardware_threads() const;

    /// @brief Return the whether the current thread is known to the thread manager.
    bool this_thread_is_a_masala_thread() const;

    /// @brief Get the ID of the current thread.
    /// @details Throws if the thread is not known to or managed by the thread
    /// manager.  Use this_thread_is_a_masala_thread() to check whether the current
    /// thread is known to or managed by the thread manager.
	masala::base::Size get_thread_manager_thread_id() const;

	/// @brief Get the IDs of all threads currently running.
	std::vector< masala::base::Size > get_thread_manager_thread_ids() const;

	/// @brief Get the master thread's system ID.
	inline std::thread::id get_system_thread_id_of_master_thread() const { return master_thread_id_; }

    /// @brief Given the system ID of a thread, return the whether this thread is
    /// known to the thread manager.
    bool
    has_system_thread_id(
        std::thread::id const system_thread_id
    ) const;

    /// @brief Given the system ID of a thread, return the index of the thread as
    /// known to the thread manager.
    /// @details Throws if the thread is not known to or managed by the thread
    /// manager.  Use has_system_thread_id() to check whether a system thread
    /// is known to or managed by the thread manager.
    base::Size
    get_thread_manager_thread_id_from_system_thread_id(
        std::thread::id const system_thread_id
    ) const;

    /// @brief Do a vector of work in threads, without a reservation.
    /// @param[inout] request An object describing the work to be done and the
    /// number of requested threads in which to do it.  All the work in the
    /// request will be marked as completed as each job executes.
    /// @param[in] throw_on_error If true (the default), an exception in the
    /// threaded work results in a throw.  If false, we simply return a work
    /// summary indicating error status.
    /// @returns A summary of what work was done, the number of threads
    /// in which it was actually executed, and how long it took.
    MasalaThreadedWorkExecutionSummary
    do_work_in_threads(
        MasalaThreadedWorkRequest & request,
        bool const throw_on_error = true
    ) const;

    /// @brief Given a function, run it in a given number of threads.
    /// @note Calling this function requires a MasalaThreadManagerAccessKey.
    /// This is an (empty) class with a private constructor, and the
    /// MasalaThreadManager is its only friend.  This is a means by which
    /// access to this advanced API is restricted to avoid unsafe thread
    /// practices.  For most purposes, you want to create a MasalaThreadedWorkRequest
    /// containing a vector of work to do, and pass it to the do_work_in_threads()
    /// function.
    void
    execute_function_in_threads(
        std::function< void() > const & fxn,
        base::Size const threads_to_request,
        MasalaThreadManagerAccessKey const & access_key,
        MasalaThreadedWorkExecutionSummary & summary
    ) const;

    /// @brief Get the total number of threads that the thread pool is set
    /// to run.  (May not have been launched yet.)
    base::Size
    total_threads() const;

    /// @brief Get the total number of threads that are actually running.
    /// @details Includes the parent thread (i.e. one more than the number
    /// in the thread pool).
    base::Size
    actual_threads_running() const;
    
    /// @brief Set the number of threads in the thread pool.
    /// @details Does nothing if this matches the number running.  Launches
    /// threads if this is greater than the number running.  Signals that
    /// threads should spin down if this is less than the number running (in
    /// which case they finish their work before spinning down).
    /// @note A value of 0 means launch one thread for each hardware thread on
    /// the node.
    void set_total_threads( base::Size const desired_threadcount );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Create a configuration object for this object.
    /// @details Can trigger read from disk.  Private since it intended to be called only the first time
    /// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
    /// implementation throws.  Must be implemented by derived classes that have configurations.
    /// @note Receives an instance of a MasalaConfigurationManagerAuthorization object.  Since this has a
    /// private constructor, it can only be instantiated by the MasalaConfigurationManager, its only friend
    /// class.  This version creates a MasalaThreadManagerConfiguration object.
    base::managers::configuration::ConfigurationBaseCSP
    load_configuration(
        masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
    ) const override;

    /// @brief Given a request containing a vector of work, this function
    /// can be executed in parallel in order to actually do the work.
    void
    threaded_execution_function(
        MasalaThreadedWorkRequest & request,
        MasalaThreadedWorkExecutionSummary & summary
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief Lock the thread manager (e.g. for resizing thread pools).
    mutable std::mutex thread_manager_mutex_;

    /// @brief The number of hardware threads available on this node, set
    /// on object construction.
    masala::base::Size const hardware_threads_ = 1;

    /// @brief The default configuration for the thread manager.
    MasalaThreadManagerConfigurationCSP configuration_;

    /// @brief The total number of threads to launch.
    masala::base::Size total_threads_ = 1;

    /// @brief The thread pool.  These are created on instantiation of the thread
    /// manager.  Threads are launched internally on first request, and are kept
    /// idling until work is assigned.
    masala::base::managers::threads::thread_pool::MasalaThreadPoolSP thread_pool_;

    /// @brief The system ID of the master thread for this process.  Set on construction.
    std::thread::id const master_thread_id_;

};

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_threads_MasalaThreadManager_hh