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
#include <base/MasalaObject.hh>
#include <base/types.hh>

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
	THREADS_SPINNING_DOWN, // Keep this second-to-last.
	NUM_STATES = THREADS_SPINNING_DOWN // Keep this last.
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
	~MasalaThreadPool() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadPool".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads::thread_pool".
	std::string class_namespace() const override;

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

}; // class MasalaThreadPool

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_hh