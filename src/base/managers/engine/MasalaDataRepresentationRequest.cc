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

/// @file src/base/managers/plugin_module/MasalaDataRepresentationRequest.cc
/// @brief A class used to request data representations.
/// @details This class stores a list of criteria that a data representation must satisfy.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).


// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationRequest.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Every class can name itself.
/// @returns "MasalaDataRepresentationRequest".
std::string
MasalaDataRepresentationRequest::class_name() const {
    return class_name_static();
}

/// @brief Every class can provide its own namespace.
/// @returns "masala::base::managers::engine".
std::string
MasalaDataRepresentationRequest::class_namespace() const {
    return class_namespace_static();
}

/// @brief Every class can name itself.  Static version.
/// @returns "MasalaDataRepresentationRequest".
/*static*/
std::string
MasalaDataRepresentationRequest::class_name_static() {
    return "MasalaDataRepresentationRequest";
}

/// @brief Every class can provide its own namespace.  Static version.
/// @returns "masala::base::managers::engine".
/*static*/
std::string
MasalaDataRepresentationRequest::class_namespace_static() {
    return "masala::base::managers::engine";
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
