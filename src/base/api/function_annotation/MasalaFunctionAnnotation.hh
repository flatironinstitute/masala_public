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

/// @file src/base/api/function_annotation/MasalaFunctionAnnotation.hh
/// @brief Headers for a pure virtual base class for function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_function_annotation_MasalaFunctionAnnotation_hh
#define Masala_src_base_api_function_annotation_MasalaFunctionAnnotation_hh

// Forward declarations:
#include <base/api/function_annotation/MasalaFunctionAnnotation.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/api/MasalaObjectAPIDefinition.fwd.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace base {
namespace api {
namespace function_annotation {

/// @brief A pure virtual base class for function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaFunctionAnnotation : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaFunctionAnnotation() = default;

	/// @brief Copy constructor.
	MasalaFunctionAnnotation( MasalaFunctionAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~MasalaFunctionAnnotation() = default; 

}; // class MasalaFunctionAnnotation

} // namespace function_annotation
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_function_annotation_MasalaFunctionAnnotation_hh