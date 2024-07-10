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

/// @file src/base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.cc
/// @brief Implementations for a setter function annotation that indicates that a
/// function sets a type of object that is (a) wholly owned by the encapsulating object, and
/// (b) unique (i.e. an instance of the encapsulating object encapsulates only one instance
/// of the inner object).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.hh>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("OwnedSingleObjectSetterAnnotation").
std::string
OwnedSingleObjectSetterAnnotation::class_name() const {
	return "OwnedSingleObjectSetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
std::string
OwnedSingleObjectSetterAnnotation::class_namespace() const {
	return "masala::base::api::setter::setter_annotation";
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
