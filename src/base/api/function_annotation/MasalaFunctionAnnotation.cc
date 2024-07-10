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

/// @file src/base/api/function_annotation/MasalaFunctionAnnotation.cc
/// @brief Implementations for a pure virtual base class for function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <base/api/function_annotation/MasalaFunctionAnnotation.hh>

namespace masala {
namespace base {
namespace api {
namespace function_annotation {

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Allow derived classes to access the mutex.
std::mutex &
MasalaFunctionAnnotation::mutex() const {
	return mutex_;
}

/// @brief Allow derived classes to access the API defintion.
masala::base::api::MasalaObjectAPIDefinitionCSP &
MasalaFunctionAnnotation::api_definition() {
	return api_definition_;
}

} // namespace function_annotation
} // namespace api
} // namespace base
} // namespace masala
