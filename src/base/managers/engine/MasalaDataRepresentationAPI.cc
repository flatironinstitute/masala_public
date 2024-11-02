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

/// @file src/base/managers/plugin_module/MasalaDataRepresentationAPI.cc
/// @brief Implementations for a base class for all Masala derived API classes for MasalaDataRepresentations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).


// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationAPI.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief Get the namespace and name for this pure virtual base class.
/// @returns "masala::base::managers::engine::MasalaDataRepresentationAPI"
/*static*/
std::string
MasalaDataRepresentationAPI::class_namespace_and_name_static() {
    return "masala::base::managers::engine::MasalaDataRepresentationAPI";
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
