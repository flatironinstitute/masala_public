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
class MasalaThreadPoolCreationKey : public base::MasalaObject {

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
class MasalaThreadPool : public base::MasalaObject {

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

	/// @brief Given a function, run it in up to the requested number of threads.
	/// @note The actual number of threads in which it runs might be less than
	/// the requested number.
	void
	execute_function_in_threads(
		std::function< void() > const & fxn,
		base::Size const threads_to_request,
		masala::base::managers::threads::MasalaThreadedWorkExecutionSummary & summary
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

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