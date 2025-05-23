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

/// @file src/base/api/constructor/constructor_annotation/DeprecatedConstructorAnnotation.fwd.hh
/// @brief Forward declarations for a constructor annotation that indicates that a particular constructor has
/// been deprecated or will be deprecated in a future version of this library.  If the Masala library
/// version is greater than or equal to that indicated in this constructor, then the constructor is excluded from
/// the API definition.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_constructor_annotation_DeprecatedConstructorAnnotation_fwd_hh
#define Masala_src_base_api_constructor_constructor_annotation_DeprecatedConstructorAnnotation_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace api {
namespace constructor {
namespace constructor_annotation {

	class DeprecatedConstructorAnnotation;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using DeprecatedConstructorAnnotationSP = MASALA_SHARED_POINTER< DeprecatedConstructorAnnotation >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using DeprecatedConstructorAnnotationCSP = MASALA_SHARED_POINTER< DeprecatedConstructorAnnotation const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using DeprecatedConstructorAnnotationWP = MASALA_WEAK_POINTER< DeprecatedConstructorAnnotation >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using DeprecatedConstructorAnnotationCWP = MASALA_WEAK_POINTER< DeprecatedConstructorAnnotation const >;

} // namespace constructor_annotation
} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_constructor_constructor_annotation_DeprecatedConstructorAnnotation_fwd_hh