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

/// @file src/base/managers/environment/MasalaEnvironmentManager.fwd.hh
/// @brief Forward declarations for a static singleton for managing environment variables.
/// @details All environment variables are queried once and cached by this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_environment_MasalaEnvironmentManager_fwd_hh
#define Masala_src_base_managers_environment_MasalaEnvironmentManager_fwd_hh

namespace masala {
namespace base {
namespace managers {
namespace environment {

    class MasalaEnvironmentManager;

    /// Note that singletons define no shared pointers or weak pointers.
    using MasalaEnvironmentManagerHandle = MasalaEnvironmentManager const *;

} // namespace environment
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_environment_MasalaEnvironmentManager_fwd_hh