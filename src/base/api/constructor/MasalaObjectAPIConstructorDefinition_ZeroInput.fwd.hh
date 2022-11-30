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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.fwd.hh
/// @brief Forward definitions for a class that stores the definition for a
/// constructor, as part of the API for an object.  Used to auto-generate
/// the public C++ headers, plus the bindings for Python or XML (or other
//// scripting languages).
/// @details This is a derived class for no-input constructors.  The type T0 defines
/// the type for which we're defining a constructor.
/// @note A constructor must take zero or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_fwd_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_fwd_hh

#include <memory> // For std::shared_ptr

namespace masala {
namespace base {
namespace api {
namespace constructor {

	template< typename T0 >
	class MasalaObjectAPIConstructorDefinition_ZeroInput;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	template< typename T0 >
	using MasalaObjectAPIConstructorDefinition_ZeroInputSP = std::shared_ptr< MasalaObjectAPIConstructorDefinition_ZeroInput< T0 > >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	template< typename T0 >
	using MasalaObjectAPIConstructorDefinition_ZeroInputCSP = std::shared_ptr< MasalaObjectAPIConstructorDefinition_ZeroInput< T0 > const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	template< typename T0 >
	using MasalaObjectAPIConstructorDefinition_ZeroInputWP = std::weak_ptr< MasalaObjectAPIConstructorDefinition_ZeroInput< T0 > >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	template< typename T0 >
	using MasalaObjectAPIConstructorDefinition_ZeroInputCWP = std::weak_ptr< MasalaObjectAPIConstructorDefinition_ZeroInput< T0 > const >;

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_fwd_hh