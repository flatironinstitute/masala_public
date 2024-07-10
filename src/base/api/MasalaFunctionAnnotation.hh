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

/// @file src/base/MasalaFunctionAnnotation.hh
/// @brief A base class for all Masala derived classes.  This allows the possibility of having a
/// generic MasalaFunctionAnnotation pointer or shared pointer.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaFunctionAnnotation_hh
#define Masala_src_base_api_MasalaFunctionAnnotation_hh

// Forward declarations:
#include <base/api/MasalaFunctionAnnotation.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/api/MasalaObjectAPIDefinition.fwd.hh>

// STL headers:
#include <vector>

namespace masala {
namespace base {
namespace api {

/// @brief A pure virtual base class for function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaFunctionAnnotation : masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaFunctionAnnotation() = default;

	/// @brief Copy constructor.
	MasalaFunctionAnnotation( MasalaFunctionAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~MasalaFunctionAnnotation() = default; 

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get an object describing the API for this object.
	/// @details Default implementation returns nullptr.  May be overridden by
	/// derived objects.
	/// @note This is a weak pointer rather than a shared pointer since the
	/// original object is expected to hold on to its API definition (which includes
	/// function pointers to the functions of the instance).  Querying whether the
	/// weak pointer can be converted to a shared pointer serves on a check as to
	/// whether it is safe to use the function pointers.  Not ideal, but better than
	/// nothing.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override = 0;

}; // class MasalaFunctionAnnotation

} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_MasalaFunctionAnnotation_hh