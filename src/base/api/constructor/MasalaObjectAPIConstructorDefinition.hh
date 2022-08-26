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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition.hh
/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.fwd.hh>

// Base headers.

// STL headers.
#include <string>

namespace base {
namespace api {
namespace constructor {

/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a pure virtual base class.  Derived classes are for
/// one-parameter, two-parameter, three-parameter, etc. constructors.
/// @note A constructor must take one or more inputs, and must have no return value.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPIConstructorDefinition : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIConstructorDefinition() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] constructor_name The name of the constructor that
	///			   we are describing here.  Should match the T0 class name.
	/// @param[in] constructor_description The description of the constructor that
	///			   we are describing here.
	MasalaObjectAPIConstructorDefinition(
		std::string const & constructor_name,
		std::string const & constructor_description
	);

	/// @brief Copy constructor.
	MasalaObjectAPIConstructorDefinition( MasalaObjectAPIConstructorDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPIConstructorDefinition() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this constructor.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	std::string
	get_constructor_human_readable_description() const = 0;

	/// @brief Get a JSON description of this constructor.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	// virtual
	// json_return_type ???
	// get_constructor_json_description() const = 0;
	// TODO TODO TODO

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of the constructor.  Should match the T0 class name.
	std::string const & constructor_name() const;

	/// @brief Get the constructor's description.
	std::string const & constructor_description() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of the constructor.
	/// @details Must be set on construction.  Should match the T0 class name.
	std::string const constructor_name_;

	/// @brief The description of the constructor.
	/// @details Must be set on construction.
	std::string const constructor_description_;

}; // class MasalaObjectAPIConstructorDefinition

} //namespace constructor
} //namespace api
} //namespace base

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_hh