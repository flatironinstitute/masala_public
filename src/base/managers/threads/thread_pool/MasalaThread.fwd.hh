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

/// @file src/base/managers/threads/thread_pool/MasalaThread.fwd.hh
/// @brief Forward declarations for a container for a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_thread_pool_MasalaThread_fwd_hh
#define Masala_src_base_managers_threads_thread_pool_MasalaThread_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace managers {
namespace threads {
namespace thread_pool {

	class MasalaThreadCreationKey;

	class MasalaThread;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using MasalaThreadSP = MASALA_SHARED_POINTER< MasalaThread >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using MasalaThreadCSP = MASALA_SHARED_POINTER< MasalaThread const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using MasalaThreadWP = MASALA_WEAK_POINTER< MasalaThread >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using MasalaThreadCWP = MASALA_WEAK_POINTER< MasalaThread const >;

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_thread_pool_MasalaThread_fwd_hh