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

/// @file src/base/managers/plugin_module/MasalaPlugin.fwd.hh
/// @brief Forward declarations for a pure virtual base class for plugin modules.
/// @details This allows plugins to be defined in other libraries and
/// registered at runtime with the central manager class, without the code
/// in this library having to know about the particular plugins available.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_plugin_module_MasalaPlugin_fwd_hh
#define Masala_src_base_managers_plugin_module_MasalaPlugin_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

	class MasalaPlugin;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using MasalaPluginSP = MASALA_SHARED_POINTER< MasalaPlugin >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using MasalaPluginCSP = MASALA_SHARED_POINTER< MasalaPlugin const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using MasalaPluginWP = MASALA_WEAK_POINTER< MasalaPlugin >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using MasalaPluginCWP = MASALA_WEAK_POINTER< MasalaPlugin const >;

} // namespace plugin_module	
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_plugin_module_MasalaPlugin_fwd_hh