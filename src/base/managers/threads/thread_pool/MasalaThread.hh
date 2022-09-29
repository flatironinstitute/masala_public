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
#include <mutex>

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
	~MasalaThread() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThread".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads::thread_pool".
	std::string class_namespace() const override;

	/// @brief Get the index of this thread.
	base::Size thread_index() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this thread.
	mutable std::mutex thread_mutex_;

	/// @brief The index of this thread in the thread pool.
	/// @details Must be set on creation.
	base::Size const thread_index_ = 0;

}; // class MasalaThread

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_thread_pool_MasalaThread_hh