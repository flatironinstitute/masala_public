/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/base/api/MasalaObjectAPIGetterDefinition_OneInput.hh
/// @brief Forward definitions for a class that stores the definition for a
/// getter function, as part of the API for an object.  Used to auto-generate
/// the public C++ headers, plus the bindings for Python or XML (or other
//// scripting languages).
/// @details This is a derived class for single-input getters.  The type T1
/// defines the input type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaObjectAPIGetterDefinition_OneInput_fwd_hh
#define Masala_src_base_api_MasalaObjectAPIGetterDefinition_OneInput_fwd_hh

#include <memory> // For std::shared_ptr

namespace base {
namespace api {
namespace getter {

	template< typename T0, typename T1 >
	class MasalaObjectAPIGetterDefinition_OneInput;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	template< typename T0, typename T1 >
	using MasalaObjectAPIGetterDefinition_OneInputSP = std::shared_ptr< MasalaObjectAPIGetterDefinition_OneInput< T0, T1 > >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	template< typename T0, typename T1 >
	using MasalaObjectAPIGetterDefinition_OneInputCSP = std::shared_ptr< MasalaObjectAPIGetterDefinition_OneInput< T0, T1 > const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	template< typename T0, typename T1 >
	using MasalaObjectAPIGetterDefinition_OneInputWP = std::weak_ptr< MasalaObjectAPIGetterDefinition_OneInput< T0, T1 > >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	template< typename T0, typename T1 >
	using MasalaObjectAPIGetterDefinition_OneInputCWP = std::weak_ptr< MasalaObjectAPIGetterDefinition_OneInput< T0, T1 > const >;

} // namespace getter
} // namespace api
} // namespace base

#endif //Masala_src_base_api_MasalaObjectAPIGetterDefinition_OneInput_fwd_hh