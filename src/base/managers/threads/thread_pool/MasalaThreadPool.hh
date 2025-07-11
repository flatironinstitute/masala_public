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

/// @file src/base/managers/threads/thread_pool/MasalaThreadPool.hh
/// @brief A container for a set of threads.  Controls launching, destroying,
/// or renumbering threads in a threadsafe way.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_hh
#define Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_hh

// Forward declarations:
#include <base/managers/threads/thread_pool/MasalaThreadPool.fwd.hh>

// Base headers:
#include <base/managers/threads/MasalaThreadManager.fwd.hh>
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.fwd.hh>
#include <base/managers/threads/thread_pool/MasalaThread.fwd.hh>
#include <base/MasalaObject.hh>
#include <base/types.hh>

// STL headers:
#include <mutex>
#include <vector>
#include <functional>
#include <thread>

namespace masala {
namespace base {
namespace managers {
namespace threads {
namespace thread_pool {

/// @brief An enum class for the states of the thread pool.
enum class MasalaThreadPoolState {
	INVALID_STATE = 0, // Keep this first.
	THREADS_NOT_LAUNCHED,
	THREADS_READY,
	SOME_THREADS_SPINNING_DOWN,
	ALL_THREADS_SPINNING_DOWN, // Keep this second-to-last.
	NUM_STATES = ALL_THREADS_SPINNING_DOWN // Keep this last.
};

/// @brief A largely empty class with a private constructor and the
/// MasalaThreadManager as its only friend, needed for construction
/// of a MasalaThreadPool.  This ensures that only the thread manager
/// can create a thread pool.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadPoolCreationKey : public masala::base::MasalaObject {

	// We make the MasalaThreadManager a friend so that it alone can instantiate
	// this private-constructor key class.
	friend class base::managers::threads::MasalaThreadManager;

private:
	/// @brief Default constructor, private.
	MasalaThreadPoolCreationKey() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Copy constructor, deleted.
	MasalaThreadPoolCreationKey( MasalaThreadPoolCreationKey const & ) = delete;

	/// @brief Assignment operator, deleted.
	MasalaThreadPoolCreationKey & operator=( MasalaThreadPoolCreationKey const & ) = delete;

	/// @brief Destructor.
	~MasalaThreadPoolCreationKey() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadPoolCreationKey".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads::thread_pool".
	std::string class_namespace() const override;

}; // class MasalaThreadPoolCreationKey

/// @brief A container for a set of threads.  Controls launching, destroying,
/// or renumbering threads in a threadsafe way.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadPool : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor, deleted.
	MasalaThreadPool() = delete;

	/// @brief Keyed constructor.
	/// @details The MasalaThreadPoolCreationKey class has a private constructor,
	/// and has the MasalaThreadManager as its only friend.  This ensures that only
	/// the thread manager can create thread pools (or can control what other classes
	/// can create thread pools).
	MasalaThreadPool( MasalaThreadPoolCreationKey const & key );

	/// @brief Copy constructor, deleted.
	MasalaThreadPool( MasalaThreadPool const & ) = delete;

	/// @brief Assignment operator, deleted.
	MasalaThreadPool &
	operator=(
		MasalaThreadPool const &
	) = delete;

	/// @brief Destructor.
	/// @details Safely terminates each thread.
	~MasalaThreadPool() override;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadPool".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads::thread_pool".
	std::string class_namespace() const override;

	/// @brief Check whether threads need to be launched, and launch
	/// them if necessary.
	/// @details Obtains a lock of the thread pool mutex as needed.  If desired
	/// thread count is greater than number launched, we launch more.  If it is
	/// less than number launched, we annotate threads for pruning and prune them
	/// when they become idle.
	void launch_threads_if_needed( base::Size const desired_thread_count );

	/// @brief Get the number of threads actually running.
	/// @details Includes any threads that have received spindown signals but
	/// which have not yet spun down.
	base::Size actual_threads_running() const;

	/// @brief Given a function, run it in up to the requested number of threads.
	/// @note The actual number of threads in which it runs might be less than
	/// the requested number.
	void
	execute_function_in_threads(
		std::function< void() > const & fxn,
		base::Size const threads_to_request,
		masala::base::managers::threads::MasalaThreadedWorkExecutionSummary & summary
	);

	/// @brief Clean up threads (i.e. terminate) marked for deletion.
	void
	clean_up_threads_spinning_down();

	/// @brief Given a system thread ID, return whether a thread with that
	/// system ID exists in the thread pool.
	bool
	has_system_thread_id(
		std::thread::id const system_thread_id
	) const;

	/// @brief Given a system thread ID, return the index of the stored thread with that
	/// system ID.  Throws if no such thread exists in the thread pool.
	masala::base::Size
	get_thread_manager_thread_id_from_system_thread_id(
		std::thread::id const system_thread_id
	) const;

	/// @brief Get the IDs of all threads currently running.
	std::vector< masala::base::Size >
	get_thread_manager_thread_ids() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a system thread ID, return the index of the stored thread with that
	/// system ID.  Throws if no such thread exists in the thread pool.
	/// @details This version performs no mutex locking.
	base::Size
	get_thread_manager_thread_id_from_system_thread_id_mutexlocked(
		std::thread::id const system_thread_id
	) const;

	/// @brief Increase the number of threads in the threadpool by N.
	/// @details The thread_pool_mutex_ must be locked before calling this function!
	void launch_threads_mutexlocked( base::Size const n_threads_to_launch );

	/// @brief Mark additional threads as inactive.
	/// @details The thread_pool_mutex_ must be locked before calling this function!
	void increment_inactive_threads_mutexlocked( base::Size n_new_inactive_threads );

	/// @brief Unmark some threads as inactive.
	/// @details The thread_pool_mutex_ must be locked before calling this function!
	void decrement_inactive_threads_mutexlocked( base::Size n_threads_to_reactivate );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Lock the thread pool when altering state.
	mutable std::mutex thread_pool_mutex_;

	/// @brief The state of the object.
	MasalaThreadPoolState thread_pool_state_ = MasalaThreadPoolState::THREADS_NOT_LAUNCHED;

	/// @brief The threads in this thread pool.
	std::vector< MasalaThreadSP > threads_;

	/// @brief The number of threads that are active (accepting work).
	base::Size num_active_threads_ = 0;

	/// @brief The number of threads that are spinning down (not accepting work).
	base::Size num_inactive_threads_ = 0;

	/// @brief The next thread index that has not yet been assigned to a thread.
	/// @note Thread numbering starts at 1.  Thread zero is the master thread.
	/// Also note that these numbers are (a) local to this thread pool (so that
	/// if ever there were multiple thread pools, you could have the same index
	/// in the different thread pools), and (b) not recycled (so if thread 5 is
	/// spun down and then a new thread is created, it will be given a higher
	/// number, and "5" will be retired).
	base::Size next_thread_index_ = 1;

}; // class MasalaThreadPool

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_hh