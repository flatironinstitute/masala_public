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

/// @file src/base/managers/threads/thread_pool/MasalaThread.hh
/// @brief A container for a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_thread_pool_MasalaThread_hh
#define Masala_src_base_managers_threads_thread_pool_MasalaThread_hh

// Forward declarations:
#include <base/managers/threads/thread_pool/MasalaThread.fwd.hh>

// Base headers:
#include <base/managers/threads/thread_pool/MasalaThreadPool.fwd.hh>
#include <base/MasalaObject.hh>
#include <base/types.hh>

// STL headers:
#include <condition_variable>
#include <mutex>
#include <thread>
#include <functional>
#include <atomic>

namespace masala {
namespace base {
namespace managers {
namespace threads {
namespace thread_pool {

/// @brief A largely empty class with a private constructor and the
/// MasalaThreadPool as its only friend, needed for construction
/// of a MasalaThread.  This ensures that only the thread pool
/// can create a thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadCreationKey : public base::MasalaObject {

	// We make the MasalaThreadPool a friend so that it alone can instantiate
	// this private-constructor key class.
	friend class base::managers::threads::thread_pool::MasalaThreadPool;

private:
	/// @brief Default constructor, private.
	MasalaThreadCreationKey() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Copy constructor, deleted.
	MasalaThreadCreationKey( MasalaThreadCreationKey const & ) = delete;

	/// @brief Assignment operator, deleted.
	MasalaThreadCreationKey & operator=( MasalaThreadCreationKey const & ) = delete;

	/// @brief Destructor.
	~MasalaThreadCreationKey() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadCreationKey".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads::thread_pool".
	std::string class_namespace() const override;

}; // class MasalaThreadCreationKey

/// @brief A container for a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThread : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor, deleted.
	MasalaThread() = delete;

	/// @brief Keyed constructor.
	/// @details The MasalaThreadCreationKey class has a private constructor,
	/// and has the MasalaThreadPool as its only friend.  This ensures that only
	/// the thread pool can launch threads.
	MasalaThread( base::Size const thread_index, MasalaThreadCreationKey const & key );

	/// @brief Copy constructor, deleted.
	MasalaThread( MasalaThread const & ) = delete;

	/// @brief Assignment operator, deleted.
	MasalaThread &
	operator=(
		MasalaThread const &
	) = delete;

	/// @brief Destructor.
	/// @details Calls terminate_thread().  Destruction should only occur in a
	/// context in which the mutex is unlocked, but in which it is guaranteed
	/// that this thread has no work (preferably in the forced_idle state).
	~MasalaThread() override;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThread".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads::thread_pool".
	std::string class_namespace() const override;

	/// @brief Get the index of this thread.
	/// @details This is the internal index used by the thread pool.  Numbering
	/// starts at 1, since thread 0 is the master thread for the process.  Thread
	/// indices are retired after use, so if you have a 4-thread thread pool, delete
	/// thread 2, and then launch a new thread, the new thread's index is 5.
	base::Size thread_index() const;

	/// @brief Get the thread ID used by the system for the contained thread.
	std::thread::id system_thread_id() const;

	/// @brief Access the mutex for this thread.
	std::mutex & thread_mutex() const;

	/// @brief Is this thread idle?
	/// @note Be sure to lock the thread mutex before calling this function!
	/// @details Idle is defined as having nullptr for the function to execute.
	inline bool is_idle() const { return function_ == nullptr; }

	/// @brief Is this thread being forced to idle?
	/// @note Be sure to lock the thread mutex before calling this function!
	inline bool forced_idle() const { return forced_idle_.load(); }

	/// @brief Set whether this thread is forced to idle.
	/// @note Be sure to lock the thread mutex before calling this function!
	void set_forced_idle( bool const setting );

	/// @brief Set the function that this thread will execute.
	/// @details Must be in the forced idle state to set this.
	/// @note Be sure to lock the thread mutex before calling this function!
	void
	set_function(
		std::function< void() > const & function,
		std::condition_variable & job_completion_cond_var,
		std::atomic_ulong & num_jobs_completed,
		std::mutex & num_jobs_completed_mutex
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief The function that the thread actually executes, which wraps
	/// whatever function is passed in.
	void
	wrapper_function_executed_in_thread();

	/// @brief Spins down the std::thread object contained (i.e. prevents it from
	/// accepting new work).
	/// @details Should only be called by this object's destructor, and with the mutex unlocked.
	void terminate_thread();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this thread.
	mutable std::mutex thread_mutex_;

	/// @brief The thread that this object contains.
	std::thread contained_thread_;

	/// @brief The system ID of the thread that this object contains, set on construction.
	std::thread::id system_thread_id_;

	/// @brief Are we locked in idle mode?
	std::atomic_bool forced_idle_;

	/// @brief Is it time to force termination of all threads?
	/// @details When termination is forced, it prevents a thread from accepting new work.
	std::atomic_bool forced_termination_;

	/// @brief The index of this thread in the thread pool.
	/// @details Must be set on creation.
	base::Size const thread_index_ = 0;

	/// @brief A (raw) pointer to the function to execute in this thread.
	/// @details Can be nullptr.
	std::function< void() > const * function_ = nullptr;

	/// @brief A condition var used to wake this thread to do work.
	std::condition_variable cv_for_wakeup_;

    /// @brief Pointer to mutex used for indicating that the work assigned to
    /// this thread has been completed.
    std::condition_variable * job_completion_cond_var_ = nullptr;

    /// @brief Pointer to counter used for indicating that the work assigned to
    /// this thread has been completed.
    std::atomic_ulong * num_jobs_completed_ = nullptr;

	/// @brief A mutex for the number of jobs completed.
	std::mutex * num_jobs_completed_mutex_ = nullptr;

}; // class MasalaThread

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_thread_pool_MasalaThread_hh