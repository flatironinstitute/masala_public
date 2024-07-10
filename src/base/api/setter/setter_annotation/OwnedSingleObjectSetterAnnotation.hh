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

/// @file src/base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.hh
/// @brief Headers for a setter function annotation that indicates that a
/// function sets a type of object that is (a) wholly owned by the encapsulating object, and
/// (b) unique (i.e. an instance of the encapsulating object encapsulates only one instance
/// of the inner object).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_setter_annotation_OwnedSingleObjectSetterAnnotation_hh
#define Masala_src_base_api_setter_setter_annotation_OwnedSingleObjectSetterAnnotation_hh

// Forward declarations:
#include <base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.fwd.hh>

// Base headers:
#include <base/api/setter/setter_annotation/MasalaSetterFunctionAnnotation.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

/// @brief A setter function annotation that indicates that a
/// function sets a type of object that is (a) wholly owned by the encapsulating object, and
/// (b) unique (i.e. an instance of the encapsulating object encapsulates only one instance
/// of the inner object).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class OwnedSingleObjectSetterAnnotation : masala::base::api::setter::setter_annotation::MasalaSetterFunctionAnnotation {

public:

	/// @brief Default constructor.
	OwnedSingleObjectSetterAnnotation() = default;

	/// @brief Copy constructor.
	OwnedSingleObjectSetterAnnotation( OwnedSingleObjectSetterAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~OwnedSingleObjectSetterAnnotation() = default; 

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the class name ("OwnedSingleObjectSetterAnnotation").
	std::string class_name() const override;

	/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
	std::string class_namespace() const override;

}; // class OwnedSingleObjectSetterAnnotation

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_setter_annotation_OwnedSingleObjectSetterAnnotation_hh