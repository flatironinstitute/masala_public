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

/// @file src/base/managers/version/MasalaVersionManager.fwd.hh
/// @brief Forward declarations for a static singleton for managing the version
/// of Masala's core library and of plugin libraries, along with any inter-library
/// version dependencies.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_version_MasalaVersionManager_fwd_hh
#define Masala_src_base_managers_version_MasalaVersionManager_fwd_hh

namespace masala {
namespace base {
namespace managers {
namespace version {

    class MasalaVersionManager;

    /// Note that singletons define no shared pointers or weak pointers.  Nonconst to allow
    /// registration of plugin modules.
    using MasalaVersionManagerHandle = MasalaVersionManager *;

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_version_MasalaVersionManager_fwd_hh