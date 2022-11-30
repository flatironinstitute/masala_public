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

/// @file src/base/managers/threads/MasalaThreadManagerConfiguration.fwd.hh
/// @brief Forward declarations for a container of configuration settings for the
/// MasalaThreadManager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_fwd_hh
#define Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_fwd_hh

// STL headers
#include <base/managers/memory/util.hh>

namespace masala {
namespace base {
namespace managers {
namespace threads {

    class MasalaThreadManagerConfiguration;

    using MasalaThreadManagerConfigurationSP = MASALA_SHARED_POINTER< MasalaThreadManagerConfiguration >;
    using MasalaThreadManagerConfigurationCSP = MASALA_SHARED_POINTER< MasalaThreadManagerConfiguration const >;
    using MasalaThreadManagerConfigurationWP = MASALA_WEAK_POINTER< MasalaThreadManagerConfiguration >;
    using MasalaThreadManagerConfigurationCWP = MASALA_WEAK_POINTER< MasalaThreadManagerConfiguration const>;

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_fwd_hh
