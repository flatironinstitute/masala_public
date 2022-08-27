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

/// @file src/base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh
/// @brief A template class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for zero-input getters.  The type T0
/// defines the output type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_ZeroInput_tmpl_hh
#define Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_ZeroInput_tmpl_hh

// Base class.
#include <base/api/getter/MasalaObjectAPIGetterDefinition.hh>

// Forward declarations.
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.fwd.hh>

// Base headers.
#include <base/api/names_from_types.tmpl.hh>

// STL headers.
#include <sstream>

namespace base {
namespace api {
namespace getter {

/// @brief A class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for zero-input getters.  The type T0
/// defines the output type.
/// @note A getter can take zero or more inputs, and must return one non-void output.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0 >
class MasalaObjectAPIGetterDefinition_ZeroInput : public MasalaObjectAPIGetterDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIGetterDefinition_ZeroInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] getter_function_name The name of the getter function that
	///			   we are describing here.
	/// @param[in] getter_function_description The description of the getter function that
	///			   we are describing here.
	/// @param[in] output_parameter_description The description of what the getter returns.
	MasalaObjectAPIGetterDefinition_ZeroInput(
		std::string const & getter_function_name,
		std::string const & getter_function_description,
		std::string const & output_parameter_description
	) :
		MasalaObjectAPIGetterDefinition( getter_function_name, getter_function_description ),
		output_description_( output_parameter_description )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIGetterDefinition_ZeroInput( MasalaObjectAPIGetterDefinition_ZeroInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIGetterDefinition_ZeroInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIGetterDefinition_ZeroInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIGetterDefinition_ZeroInput";
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this getter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	std::string
	get_getter_human_readable_description() const override {
		std::ostringstream ss;
    	ss << "Getter:\t" << base::api::name_from_type< T0 >() << " " << getter_function_name() << "() const:" << std::endl;
		ss << getter_function_description() << std::endl;
		ss << "Output: \t" << output_description_ << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this getter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	// json_return_type ???
	// get_getter_json_description() const override;
	// TODO TODO TODO

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A description of what this getter returns.
	std::string const output_description_;

}; // class MasalaObjectAPIGetterDefinition_ZeroInput

} //namespace getter
} //namespace api
} //namespace base

#endif //Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_ZeroInput_tmpl_hh