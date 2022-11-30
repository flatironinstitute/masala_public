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

/// @file src/base/managers/threads/MasalaThreadManager.fwd.hh
/// @brief Forward declarations for a static singleton for managing a thread
/// pool, and execution of code in parallel threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadManager_fwd_hh
#define Masala_src_base_managers_threads_MasalaThreadManager_fwd_hh

namespace masala {
namespace base {
namespace managers {
namespace threads {

    class MasalaThreadManagerAccessKey;
    class MasalaThreadManager;

    /// Note that singletons define no shared pointers or weak pointers.  Nonconst to allow
    /// lazy loading of data.
    using MasalaThreadManagerHandle = MasalaThreadManager *;

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_threads_MasalaThreadManager_fwd_hh