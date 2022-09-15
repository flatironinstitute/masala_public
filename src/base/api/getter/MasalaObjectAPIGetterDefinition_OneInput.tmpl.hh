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

/// @file src/base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh
/// @brief A template class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for single-input getters.  The type T1
/// defines the input type and the type T0 defines the output type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_OneInput_tmpl_hh
#define Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_OneInput_tmpl_hh

// Base class.
#include <base/api/getter/MasalaObjectAPIGetterDefinition.hh>

// Forward declarations.
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.fwd.hh>

// Base headers.
#include <base/api/names_from_types.tmpl.hh>

// External headers
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers.
#include <sstream>
#include <functional>

namespace masala {
namespace base {
namespace api {
namespace getter {

/// @brief A class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for single-input getters.  The type T1
/// defines the input type and the type T0 defines the output type.
/// @note A getter can take zero or more inputs, and must return one non-void output.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0, typename T1 >
class MasalaObjectAPIGetterDefinition_OneInput : public MasalaObjectAPIGetterDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIGetterDefinition_OneInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] getter_function_name The name of the getter function that
	///			   we are describing here.
	/// @param[in] getter_function_description The description of the getter function that
	///			   we are describing here.
	/// @param[in] input_parameter1_description The description of the input parameter.
	/// @param[in] output_parameter_description The description of what the getter returns.
	/// @param[in] getter_function The actual getter function.
	MasalaObjectAPIGetterDefinition_OneInput(
		std::string const & getter_function_name,
		std::string const & getter_function_description,
		std::string const & input_parameter1_description,
		std::string const & output_parameter_description,
		std::function< T0( T1 ) > const & getter_function
	) :
		MasalaObjectAPIGetterDefinition( getter_function_name, getter_function_description ),
		output_description_( output_parameter_description ),
		input_parameter1_description_(input_parameter1_description),
		getter_function_( getter_function )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIGetterDefinition_OneInput( MasalaObjectAPIGetterDefinition_OneInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIGetterDefinition_OneInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIGetterDefinition_OneInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIGetterDefinition_OneInput";
	}

	/// @brief Every class can provide its own namespace.  This returns "base::api::getter".
	std::string
	class_namespace() const override {
		return "base::api::getter";
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
    	ss << "Getter:\t" << masala::base::api::name_from_type< T0 >() << " " << getter_function_name() << "( " << masala::base::api::name_from_type< T1 >() << " ) const:" << std::endl;
		ss << getter_function_description() << std::endl;
		ss << "Input 1:\t" << input_parameter1_description_ << std::endl;
		ss << "Output: \t" << output_description_ << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this getter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	nlohmann::json
	get_getter_json_description() const override {
		nlohmann::json json_api;
		json_api["Getter_Name"] = getter_function_name();
		json_api["Getter_Description"] = getter_function_description();
		json_api["Is_Const"] = true;

		//Inputs:
		json_api["Getter_N_Inputs"] = 1;

		nlohmann::json json_input1;
		json_input1["Input_Index"] = 1;
		json_input1["Input_Type"] = masala::base::api::name_from_type< T1 >();
		json_input1["Input_Description"] = input_parameter1_description_;

		json_api["Input_1"] = json_input1;

		// Outputs:
		nlohmann::json json_output;
		json_output[ "Output_Type" ] = masala::base::api::name_from_type< T0 >();
		json_output[ "Output_Description" ] = output_description_;
		json_api["Output"] = json_output;

		return json_api;
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A description of what this getter returns.
	std::string const output_description_;

	/// @brief A description of input parameter 1.
	std::string const input_parameter1_description_;

	/// @brief The function that we're binding to.
	std::function< T0(T1) > const getter_function_;

}; // class MasalaObjectAPIGetterDefinition_OneInput

} // namespace getter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_OneInput_tmpl_hh