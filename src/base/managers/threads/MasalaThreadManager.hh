/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
class MasalaThreadManagerAccessKey : public base::MasalaObject {

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
    /// @details Returns "masala::base::managers::thread".
    std::string
    class_namespace() const override;

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
    /// @returns A summary of what work was done, the number of threads
    /// in which it was actually executed, and how long it took.
    MasalaThreadedWorkExecutionSummary
    do_work_in_threads(
        MasalaThreadedWorkRequest & request
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

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Given a request containing a vector of work, this function
    /// can be executed in parallel in order to actually do the work.
    void
    threaded_execution_function(
        MasalaThreadedWorkRequest & request,
        MasalaThreadedWorkExecutionSummary const & summary
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief Lock the thread manager (e.g. for resizing thread pools).
    mutable std::mutex thread_manager_mutex_;

    /// @brief The total number of threads to launch.
    base::Size total_threads_ = 1;

    /// @brief The thread pool.  These are created on instantiation of the thread
    /// manager.  Threads are launched internally on first request, and are kept
    /// idling until work is assigned.
    base::managers::threads::thread_pool::MasalaThreadPoolSP thread_pool_;

    /// @brief The system ID of the master thread for this process.  Set on construction.
    std::thread::id const master_thread_id_;

};

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_threads_MasalaThreadManager_hh