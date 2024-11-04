/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/base/managers/plugin_module/MasalaPluginAPI.cc
/// @brief Implementations for a base class for all Masala derived API classes for plugins.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <base/managers/plugin_module/MasalaPluginAPI.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief Get the namespace and name for this pure virtual base class.
/// @returns "masala::base::managers::plugin_module::MasalaPluginAPI"
/*static*/
std::string
MasalaPluginAPI::class_namespace_and_name_static() {
	return "masala::base::managers::plugin_module::MasalaPluginAPI";
}

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace masala
