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
/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_hh
#define Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/api/setter/MasalaObjectAPISetterDefinition.fwd.hh>

// Base headers.

// STL headers.
#include <string>

namespace base {
namespace api {
namespace setter {

/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a pure virtual base class.  Derived classes are for
/// one-parameter, two-parameter, three-parameter, etc. setters.
/// @note A setter must take one or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPISetterDefinition : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPISetterDefinition() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] setter_function_name The name of the setter function that
	///			   we are describing here.
	/// @param[in] setter_function_description The description of the setter function that
	///			   we are describing here.
	MasalaObjectAPISetterDefinition(
		std::string const & setter_function_name,
		std::string const & setter_function_description
	);

	/// @brief Copy constructor.
	MasalaObjectAPISetterDefinition( MasalaObjectAPISetterDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPISetterDefinition() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this setter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	std::string
	get_setter_human_readable_description() const = 0;

	/// @brief Get a JSON description of this setter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	// virtual
	// json_return_type ???
	// get_setter_json_description() const = 0;
	// TODO TODO TODO

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of the setter function.
	std::string const & setter_function_name() const;

	/// @brief Get the setter function's description.
	std::string const & setter_function_description() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of the setter function.
	/// @details Must be set on construction.
	std::string const setter_function_name_;

	/// @brief The description of the setter function.
	/// @details Must be set on construction.
	std::string const setter_function_description_;

}; // class MasalaObjectAPISetterDefinition

} //namespace setter
} //namespace api
} //namespace base

#endif //Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_hh