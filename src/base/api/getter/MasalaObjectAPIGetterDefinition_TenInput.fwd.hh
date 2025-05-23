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

/// @file src/base/api/getter/MasalaObjectAPIGetterDefinition_TenInput.hh
/// @brief Forward definitions for a class that stores the definition for a
/// getter function, as part of the API for an object.  Used to auto-generate
/// the public C++ headers, plus the bindings for Python or XML (or other
//// scripting languages).
/// @details This is a derived class for ten-input getters.  The types T1, T2, T3, T4, T5, T6, T7, T8, T9, and T10
/// define the input type and the type T0 defines the output type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_TenInput_fwd_hh
#define Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_TenInput_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace api {
namespace getter {

	template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
	class MasalaObjectAPIGetterDefinition_TenInput;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
	using MasalaObjectAPIGetterDefinition_TenInputSP = MASALA_SHARED_POINTER< MasalaObjectAPIGetterDefinition_TenInput< T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
	using MasalaObjectAPIGetterDefinition_TenInputCSP = MASALA_SHARED_POINTER< MasalaObjectAPIGetterDefinition_TenInput< T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
	using MasalaObjectAPIGetterDefinition_TenInputWP = MASALA_WEAK_POINTER< MasalaObjectAPIGetterDefinition_TenInput< T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
	using MasalaObjectAPIGetterDefinition_TenInputCWP = MASALA_WEAK_POINTER< MasalaObjectAPIGetterDefinition_TenInput< T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 > const >;

} // namespace getter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_TenInput_fwd_hh