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

/// @file src/base/api/MasalaObjectAPIDefinition.hh
/// @brief A class that stores the definition for the API for an object.  Used
/// to auto-generate the public C++ headers, plus the bindings for Python
/// or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaObjectAPIDefinition_hh
#define Masala_src_base_api_MasalaObjectAPIDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/api/MasalaObjectAPIDefinition.fwd.hh>

namespace base {
namespace api {

/// @brief A class that stores the definition for the API for an object.  Used
/// to auto-generate the public C++ headers, plus the bindings for Python
/// or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPIDefinition : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIDefinition() = default;

	/// @brief Copy constructor.
	MasalaObjectAPIDefinition( MasalaObjectAPIDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPIDefinition() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".
	std::string class_name() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////


}; // class MasalaObjectAPIDefinition

} //namespace api
} //namespace base

#endif //Masala_src_base_api_MasalaObjectAPIDefinition_hh