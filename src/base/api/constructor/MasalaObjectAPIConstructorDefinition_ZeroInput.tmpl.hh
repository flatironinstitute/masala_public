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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh
/// @brief A template class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for no-input constructors.  The type T0 defines
/// the type for which we're defining a constructor.
/// @note A constructor must take zero or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_tmpl_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_tmpl_hh

// Base class.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>

// Forward declarations.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.fwd.hh>

// Base headers.
#include <base/api/names_from_types.tmpl.hh>

// STL headers.
#include <sstream>
#include <functional>

namespace base {
namespace api {
namespace constructor {

/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for no-input constructors.  The type T0 defines
/// the type for which we're defining a constructor.
/// @note A constructor must take zero or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0 >
class MasalaObjectAPIConstructorDefinition_ZeroInput : public MasalaObjectAPIConstructorDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIConstructorDefinition_ZeroInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] constructor_name The name of the constructor that
	///			   we are describing here.  Should match the T0 class name.
	/// @param[in] constructor_description The description of the constructor that
	///			   we are describing here.
	MasalaObjectAPIConstructorDefinition_ZeroInput(
		std::string const & constructor_name,
		std::string const & constructor_description
	) :
		MasalaObjectAPIConstructorDefinition( constructor_name, constructor_description ),
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIConstructorDefinition_ZeroInput( MasalaObjectAPIConstructorDefinition_ZeroInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIConstructorDefinition_ZeroInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIConstructorDefinition_ZeroInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIConstructorDefinition_ZeroInput";
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this constructor.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	std::string
	get_constructor_human_readable_description() const override {
		std::ostringstream ss;
    	ss << "Constructor:\t" << constructor_name() << "():" << std::endl;
		ss << constructor_description() << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this constructor.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	// json_return_type ???
	// get_constructor_json_description() const override;
	// TODO TODO TODO

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Create an instance of this class using the constructor.
	std::shared_ptr< T0 >
	create_object() const {
		return std::make_shared< T0 >();
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

}; // class MasalaObjectAPIConstructorDefinition_ZeroInput

} //namespace constructor
} //namespace api
} //namespace base

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_tmpl_hh