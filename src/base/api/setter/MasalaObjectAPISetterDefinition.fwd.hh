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

/// @file src/base/api/MasalaObjectAPISetterDefinition.hh
/// @brief Forward definitions for a class that stores the definition for a
/// setter function, as part of the API for an object.  Used to auto-generate
/// the public C++ headers, plus the bindings for Python or XML (or other
//// scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaObjectAPISetterDefinition_fwd_hh
#define Masala_src_base_api_MasalaObjectAPISetterDefinition_fwd_hh

#include <memory> // For std::shared_ptr

namespace base {
namespace api {
namespace setter {

	class MasalaObjectAPISetterDefinition;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	using MasalaObjectAPISetterDefinitionSP = std::shared_ptr< MasalaObjectAPISetterDefinition >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	using MasalaObjectAPISetterDefinitionCSP = std::shared_ptr< MasalaObjectAPISetterDefinition const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	using MasalaObjectAPISetterDefinitionWP = std::weak_ptr< MasalaObjectAPISetterDefinition >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	using MasalaObjectAPISetterDefinitionCWP = std::weak_ptr< MasalaObjectAPISetterDefinition const >;

} // namespace setter
} // namespace api
} // namespace base

#endif //Masala_src_base_api_MasalaObjectAPISetterDefinition_fwd_hh