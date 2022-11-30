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

/// @file src/base/api/setter/MasalaObjectAPISetterDefinition_OneInput.fwd.hh
/// @brief Forward definitions for a class that stores the definition for a
/// setter function, as part of the API for an object.  Used to auto-generate
/// the public C++ headers, plus the bindings for Python or XML (or other
//// scripting languages).
/// @details This is a derived class for single-input setters.  The type T1
/// defines the input type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_OneInput_fwd_hh
#define Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_OneInput_fwd_hh

#include <memory> // For std::shared_ptr

namespace masala {
namespace base {
namespace api {
namespace setter {

	template< typename T1 >
	class MasalaObjectAPISetterDefinition_OneInput;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	template< typename T1 >
	using MasalaObjectAPISetterDefinition_OneInputSP = std::shared_ptr< MasalaObjectAPISetterDefinition_OneInput< T1 > >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	template< typename T1 >
	using MasalaObjectAPISetterDefinition_OneInputCSP = std::shared_ptr< MasalaObjectAPISetterDefinition_OneInput< T1 > const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	template< typename T1 >
	using MasalaObjectAPISetterDefinition_OneInputWP = std::weak_ptr< MasalaObjectAPISetterDefinition_OneInput< T1 > >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	template< typename T1 >
	using MasalaObjectAPISetterDefinition_OneInputCWP = std::weak_ptr< MasalaObjectAPISetterDefinition_OneInput< T1 > const >;

} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_OneInput_fwd_hh