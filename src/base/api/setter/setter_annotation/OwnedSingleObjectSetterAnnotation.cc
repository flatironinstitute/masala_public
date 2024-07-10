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

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>

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

/// @brief Get an object describing the API for this object.
masala::base::api::MasalaObjectAPIDefinitionCWP
OwnedSingleObjectSetterAnnotation::get_api_definition() {
	using namespace masala::base::api;

	std::lock_guard< std::mutex > lock( mutex() );

	if( api_definition() == nullptr ) {
		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this, "An annotation that can be attached to a setter function that indicates "
				"that the setter function sets and object that is wholly owned by this class "
				"instance, and which moreover is a unique instance owned by this instance.  This "
				"is intended for UIs and GUIs that may wish to make it easy for a user to configure "
				"the contained object inline with the outer container.", false, false
			)
		);

		ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( OwnedSingleObjectSetterAnnotation, api_def );

		api_definition() = api_def;
	}

	return api_definition();
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
