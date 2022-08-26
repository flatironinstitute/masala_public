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

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh
/// @brief A template class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for zero-input work functions.  The type T0
/// defines the output type.  The type P defines the class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_ZeroInput_tmpl_hh
#define Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_ZeroInput_tmpl_hh

// Base class.
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>

// Forward declarations.
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.fwd.hh>

// Base headers.
#include <base/api/names_from_types.tmpl.hh>

// STL headers.
#include <sstream>
#include <functional>

namespace base {
namespace api {
namespace work_function {

/// @brief A class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for zero-input work functions.  The type T0
/// defines the output type.  The type P defines the class.
/// @note A work function can take zero or more inputs, and can return one non-void output.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename P, typename T0 >
class MasalaObjectAPIWorkFunctionDefinition_ZeroInput : public MasalaObjectAPIWorkFunctionDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIWorkFunctionDefinition_ZeroInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] work_function_name The name of the work function that
	///			   we are describing here.
	/// @param[in] work_function_description The description of the work function that
	///			   we are describing here.
	/// @param[in] is_const Is this work function a const function?
	/// @param[in] output_parameter_description The description of what the work function returns.
	/// @param[in] work_function The actual work function.
	MasalaObjectAPIWorkFunctionDefinition_ZeroInput(
		std::string const & work_function_name,
		std::string const & work_function_description,
		bool const is_const,
		std::string const & output_parameter_description,
		std::function< T0() > & work_function
	) :
		MasalaObjectAPIWorkFunctionDefinition( work_function_name, work_function_description, is_const ),
		output_description_( output_parameter_description ),
		work_function_( work_function )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIWorkFunctionDefinition_ZeroInput( MasalaObjectAPIWorkFunctionDefinition_ZeroInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIWorkFunctionDefinition_ZeroInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIWorkFunctionDefinition_ZeroInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIWorkFunctionDefinition_ZeroInput";
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this work function.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	std::string
	get_work_function_human_readable_description() const override {
		std::ostringstream ss;
    	ss << "WorkFunction:\t" << base::api::name_from_type< T0 >() << " " << work_function_name() << "()" << (is_const ? " const" : "" ) << ":" << std::endl;
		ss << work_function_description() << std::endl;
		ss << "Output: \t" << output_description_ << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this work function.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	// json_return_type ???
	// get_work_function_json_description() const override;
	// TODO TODO TODO

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A description of what this work function returns.
	std::string const output_description_;

	/// @brief The function that we're binding to.
	std::function< T0() > work_function_;

}; // class MasalaObjectAPIWorkFunctionDefinition_ZeroInput

} //namespace work_function
} //namespace api
} //namespace base

#endif //Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_ZeroInput_tmpl_hh