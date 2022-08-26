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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh
/// @brief A template class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for single-input constructors.  The type T1
/// defines the input type, and the type T0 defines the type for which we're defining
/// a constructor.
/// @note A constructor must take one or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_OneInput_tmpl_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_OneInput_tmpl_hh

// Base class.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>

// Forward declarations.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.fwd.hh>

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
/// @details This is a derived class for single-input constructors.  The type T1
/// defines the input type, and the type T0 defines the type for which we're defining
/// a constructor.
/// @note A constructor must take one or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0, typename T1 >
class MasalaObjectAPIConstructorDefinition_OneInput : public MasalaObjectAPIConstructorDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIConstructorDefinition_OneInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] constructor_name The name of the constructor that
	///			   we are describing here.
	/// @param[in] constructor_description The description of the constructor that
	///			   we are describing here.
	/// @param[in] input_parameter1_description The description of the input parameter.
	MasalaObjectAPIConstructorDefinition_OneInput(
		std::string const & constructor_name,
		std::string const & constructor_description,
		std::string const & input_parameter1_description
	) :
		MasalaObjectAPIConstructorDefinition( constructor_name, constructor_description ),
		input_parameter1_description_(input_parameter1_description)
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIConstructorDefinition_OneInput( MasalaObjectAPIConstructorDefinition_OneInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIConstructorDefinition_OneInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIConstructorDefinition_OneInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIConstructorDefinition_OneInput";
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
    	ss << "Setter:\tvoid " << constructor_name() << "( " << base::api::name_from_type< T1 >() << " ):" << std::endl;
		ss << constructor_description() << std::endl;
		ss << "Input 1:\t" << input_parameter1_description_ << std::endl;
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
	create_object( T1 const & input_parameter ) {
		return std::make_shared< T0 >( input_parameter );
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A description of input parameter 1.
	std::string const input_parameter1_description_;

}; // class MasalaObjectAPIConstructorDefinition_OneInput

} //namespace constructor
} //namespace api
} //namespace base

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_OneInput_tmpl_hh