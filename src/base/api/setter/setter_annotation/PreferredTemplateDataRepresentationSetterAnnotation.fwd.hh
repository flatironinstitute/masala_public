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

/// @file src/base/api/setter/setter_annotation/PreferredTemplateDataRepresentationSetterAnnotation.fwd.hh
/// @brief Forward declarations for a setter function annotation that indicates that a
/// function accepts an empty but configured MasalaDataRepresentation object to use as a
/// template for code requesting empty containers for data.  The set object will be deep-cloned
/// and handed out to requesting code by a corresponding getter function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_setter_annotation_PreferredTemplateDataRepresentationSetterAnnotation_fwd_hh
#define Masala_src_base_api_setter_setter_annotation_PreferredTemplateDataRepresentationSetterAnnotation_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

	class PreferredTemplateDataRepresentationSetterAnnotation;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using PreferredTemplateDataRepresentationSetterAnnotationSP = MASALA_SHARED_POINTER< PreferredTemplateDataRepresentationSetterAnnotation >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using PreferredTemplateDataRepresentationSetterAnnotationCSP = MASALA_SHARED_POINTER< PreferredTemplateDataRepresentationSetterAnnotation const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using PreferredTemplateDataRepresentationSetterAnnotationWP = MASALA_WEAK_POINTER< PreferredTemplateDataRepresentationSetterAnnotation >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using PreferredTemplateDataRepresentationSetterAnnotationCWP = MASALA_WEAK_POINTER< PreferredTemplateDataRepresentationSetterAnnotation const >;

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_setter_annotation_PreferredTemplateDataRepresentationSetterAnnotation_fwd_hh