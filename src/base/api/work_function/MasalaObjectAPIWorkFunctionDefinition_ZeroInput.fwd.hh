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

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.hh
/// @brief Forward definitions for a class that stores the definition for a
/// work function, as part of the API for an object.  Used to auto-generate
/// the public C++ headers, plus the bindings for Python or XML (or other
//// scripting languages).
/// @details This is a derived class for zero-input work functions.  The type T0
/// defines the output type.  The type P defines the class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_ZeroInput_fwd_hh
#define Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_ZeroInput_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace api {
namespace work_function {

	template< typename T0 >
	class MasalaObjectAPIWorkFunctionDefinition_ZeroInput;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	template< typename T0 >
	using MasalaObjectAPIWorkFunctionDefinition_ZeroInputSP = MASALA_SHARED_POINTER< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< T0 > >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	template< typename T0 >
	using MasalaObjectAPIWorkFunctionDefinition_ZeroInputCSP = MASALA_SHARED_POINTER< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< T0 > const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	template< typename T0 >
	using MasalaObjectAPIWorkFunctionDefinition_ZeroInputWP = MASALA_WEAK_POINTER< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< T0 > >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	template< typename T0 >
	using MasalaObjectAPIWorkFunctionDefinition_ZeroInputCWP = MASALA_WEAK_POINTER< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< T0 > const >;

} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_ZeroInput_fwd_hh