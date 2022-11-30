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

/// @file src/base/managers/threads/thread_pool/MasalaThreadPool.fwd.hh
/// @brief Forward declarations for a container for a set of threads.  Controls
/// launching, destroying, or renumbering threads in a threadsafe way.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_fwd_hh
#define Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_fwd_hh

#include <memory> // For std::shared_ptr

namespace masala {
namespace base {
namespace managers {
namespace threads {
namespace thread_pool {

	class MasalaThreadPoolCreationKey;

	class MasalaThreadPool;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	using MasalaThreadPoolSP = std::shared_ptr< MasalaThreadPool >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	using MasalaThreadPoolCSP = std::shared_ptr< MasalaThreadPool const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	using MasalaThreadPoolWP = std::weak_ptr< MasalaThreadPool >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	using MasalaThreadPoolCWP = std::weak_ptr< MasalaThreadPool const >;

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namesapce masala

#endif //Masala_src_base_managers_threads_thread_pool_MasalaThreadPool_fwd_hh