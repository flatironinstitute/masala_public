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

/// @file src/base/MasalaNoAPIObject.cc
/// @brief Implementations for a base class for all Masala derived classes that lack an API.
/// @details These might include lightweight classes used for caching data within a library, but which
/// are not intended to be configured by code outside that library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/MasalaNoAPIObject.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.hh>

// STL headers
#include <string>

namespace masala {
namespace base {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the namespace and name for this pure virtual base class.
/// @returns "masala::base::MasalaNoAPIObject"
/*static*/
std::string
MasalaNoAPIObject::class_namespace_and_name_static() {
	return "masala::base::MasalaNoAPIObject";
}

/// @brief Get an object describing the API for this object.
/// @details This and all derived classes return nullptr.
base::api::MasalaObjectAPIDefinitionCWP
MasalaNoAPIObject::get_api_definition() /*final*/ {
    return base::api::MasalaObjectAPIDefinitionCWP();
}

} // namespace base
} // namespace masala
