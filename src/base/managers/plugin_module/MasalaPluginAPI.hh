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

/// @file src/base/managers/plugin_module/MasalaPluginAPI.hh
/// @brief A base class for all Masala derived API classes for plugins.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_plugin_module_MasalaPluginAPI_hh
#define Masala_src_base_managers_plugin_module_MasalaPluginAPI_hh

// Forward declarations:
#include <base/MasalaPluginAPI.fwd.hh>

// Base headers:
#include <base/MasalaObjectAPI.hh>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief A base class for Masala API derived classes for plugins.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaPluginAPI : public base::MasalaObjectAPI {

public:

	/// @brief Default constructor.
	MasalaPluginAPI() = default;

	/// @brief Copy constructor.
	MasalaPluginAPI( MasalaPluginAPI const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~MasalaPluginAPI() = default;

}; // class MasalaPluginAPI

} // namespace plugin_module
} // namespace managers
} // namespace base
} // namesapce masala

#endif //Masala_src_base_managers_plugin_module_MasalaPluginAPI_hh