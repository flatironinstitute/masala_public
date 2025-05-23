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

/// @file src/base/api/setter/MasalaObjectAPISetterDefinition_EightInput.fwd.hh
/// @brief Forward definitions for a class that stores the definition for a
/// setter function, as part of the API for an object.  Used to auto-generate
/// the public C++ headers, plus the bindings for Python or XML (or other
//// scripting languages).
/// @details This is a derived class for eight-input setters.  The types T1, T2, T3, T4, T5, T6, T7, and T8
/// define the input types.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_EightInput_fwd_hh
#define Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_EightInput_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace api {
namespace setter {

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,  typename T8 >
	class MasalaObjectAPISetterDefinition_EightInput;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,  typename T8 >
	using MasalaObjectAPISetterDefinition_EightInputSP = MASALA_SHARED_POINTER< MasalaObjectAPISetterDefinition_EightInput< T1, T2, T3, T4, T5, T6, T7, T8 > >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,  typename T8 >
	using MasalaObjectAPISetterDefinition_EightInputCSP = MASALA_SHARED_POINTER< MasalaObjectAPISetterDefinition_EightInput< T1, T2, T3, T4, T5, T6, T7, T8 > const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,  typename T8 >
	using MasalaObjectAPISetterDefinition_EightInputWP = MASALA_WEAK_POINTER< MasalaObjectAPISetterDefinition_EightInput< T1, T2, T3, T4, T5, T6, T7, T8 > >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,  typename T8 >
	using MasalaObjectAPISetterDefinition_EightInputCWP = MASALA_WEAK_POINTER< MasalaObjectAPISetterDefinition_EightInput< T1, T2, T3, T4, T5, T6, T7, T8 > const >;

} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_EightInput_fwd_hh