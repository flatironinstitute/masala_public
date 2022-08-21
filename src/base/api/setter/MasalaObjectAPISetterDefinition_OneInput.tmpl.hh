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

/// @file src/base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh
/// @brief A template class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for single-input setters.  The type T1
/// defines the input type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_OneInput_tmpl_hh
#define Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_OneInput_tmpl_hh

// Base class.
#include <base/api/setter/MasalaObjectAPISetterDefinition.hh>

// Forward declarations.
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.fwd.hh>

// Base headers.
#include <base/api/names_from_types.tmpl.hh>

// STL headers.
#include <sstream>
#include <functional>

namespace base {
namespace api {
namespace setter {

/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for single-input setters.  The type T1
/// defines the input type.
/// @note A setter must take one or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T1 >
class MasalaObjectAPISetterDefinition_OneInput : public MasalaObjectAPISetterDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPISetterDefinition_OneInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] setter_function_name The name of the setter function that
	///			   we are describing here.
	/// @param[in] setter_function_description The description of the setter function that
	///			   we are describing here.
	/// @param[in] input_parameter1_description The description of the input parameter.
	MasalaObjectAPISetterDefinition_OneInput(
		std::string const & setter_function_name,
		std::string const & setter_function_description,
		std::string const & input_parameter1_description,
		std::function< void( T1 ) > const & setter_function
	) :
		MasalaObjectAPISetterDefinition( setter_function_name, setter_function_description ),
		input_parameter1_description_(input_parameter1_description),
		setter_function_( setter_function )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPISetterDefinition_OneInput( MasalaObjectAPISetterDefinition_OneInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPISetterDefinition_OneInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPISetterDefinition_OneInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPISetterDefinition_OneInput";
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this setter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	std::string
	get_setter_human_readable_description() const override {
		std::ostringstream ss;
    	ss << "Setter:\tvoid " << setter_function_name() << "( " << base::api::name_from_type< T1 >() << " ):" << std::endl;
		ss << setter_function_description() << std::endl;
		ss << "Input 1:\t" << input_parameter1_description_ << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this setter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	// json_return_type ???
	// get_setter_json_description() const override;
	// TODO TODO TODO

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A description of input parameter 1.
	std::string const input_parameter1_description_;

	/// @brief The function that we're binding to.
	std::function< void(T1) > const setter_function_;

}; // class MasalaObjectAPISetterDefinition_OneInput

} //namespace setter
} //namespace api
} //namespace base

#endif //Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_OneInput_tmpl_hh