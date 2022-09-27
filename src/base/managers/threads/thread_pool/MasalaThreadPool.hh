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
#include <base/MasalaObject.hh>
#include <base/types.hh>

namespace masala {
namespace base {
namespace managers {
namespace threads {
namespace thread_pool {

/// @brief A container for a set of threads.  Controls launching, destroying,
/// or renumbering threads in a threadsafe way.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadPool : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaThreadPool() = default;

	/// @brief Copy constructor, deleted.
	MasalaThreadPool( MasalaThreadPool const & ) = delete;

	/// @brief Assignment operator, deleted.
	MasalaThreadPool &
	operator=(
		MasalaThreadPool const &
	) = delete;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaThreadPool() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadPool".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads".
	std::string class_namespace() const override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

}; // class MasalaThreadPool

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_hh