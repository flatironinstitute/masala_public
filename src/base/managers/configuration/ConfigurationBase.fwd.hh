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

/// @file src/base/managers/configuration/ConfigurationBase.fwd.hh
/// @brief Forward declarations for pure virtual base class for containers
/// that store configuration settings for modules.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_configuration_ConfigurationBase_fwd_hh
#define Masala_src_base_managers_configuration_ConfigurationBase_fwd_hh

// STL headers
#include <base/managers/memory/util.hh>

namespace masala {
namespace base {
namespace managers {
namespace configuration {

    class ConfigurationBase;

    using ConfigurationBaseSP = MASALA_SHARED_POINTER< ConfigurationBase >;
    using ConfigurationBaseCSP = MASALA_SHARED_POINTER< ConfigurationBase const >;
    using ConfigurationBaseWP = MASALA_WEAK_POINTER< ConfigurationBase >;
    using ConfigurationBaseCWP = MASALA_WEAK_POINTER< ConfigurationBase const>;

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_configuration_ConfigurationBase_fwd_hh
