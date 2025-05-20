/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh
/// @brief A template class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for single-input work functions.  The type T1
/// defines the input type and the type T0 defines the output type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_OneInput_tmpl_hh
#define Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_OneInput_tmpl_hh

// Base class.
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>

// Forward declarations.
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.fwd.hh>

// Base headers.
#include <base/api/names_from_types.tmpl.hh>

// External headers.
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers.
#include <sstream>
#include <functional>

namespace masala {
namespace base {
namespace api {
namespace work_function {

/// @brief A class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for single-input work functions.  The type T1
/// defines the input type and the type T0 defines the output type.
/// @note A work function can take zero or more inputs, and can return one non-void output.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0, typename T1 >
class MasalaObjectAPIWorkFunctionDefinition_OneInput : public MasalaObjectAPIWorkFunctionDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIWorkFunctionDefinition_OneInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] work_function_name The name of the work function that
	///			   we are describing here.
	/// @param[in] work_function_description The description of the work function that
	///			   we are describing here.
	/// @param[in] is_const Is this work function a const function?
	/// @param[in] returns_this_ref Does this function return reference (or const reference) to this?
	/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
	///            is NOT an override of a virtual function in a parent API class)?
	/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
	///            a function in a base API class?
	/// @param[in] input_parameter0_name The name for the input parameter.
	/// @param[in] input_parameter0_description The description of the input parameter.
	/// @param[in] output_parameter_name The name for what the work function returns.
	/// @param[in] output_parameter_description The description of what the work function returns.
	/// @param[in] work_function The actual work function.
	MasalaObjectAPIWorkFunctionDefinition_OneInput(
		std::string const & work_function_name,
		std::string const & work_function_description,
		bool const is_const,
		bool const returns_this_ref,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn,
		std::string const & input_parameter0_name,
		std::string const & input_parameter0_description,
		std::string const & output_parameter_name,
		std::string const & output_parameter_description,
		std::function< T0( T1 ) > const & work_function
	) :
		MasalaObjectAPIWorkFunctionDefinition(
			work_function_name, work_function_description,
			is_const, returns_this_ref,
			is_virtual_non_override_fxn, is_override_of_api_virtual_fxn
		),
		input_parameter0_name_(input_parameter0_name),
		input_parameter0_description_(input_parameter0_description),
		output_name_( output_parameter_name ),
		output_description_( output_parameter_description ),
		work_function_( work_function )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIWorkFunctionDefinition_OneInput( MasalaObjectAPIWorkFunctionDefinition_OneInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIWorkFunctionDefinition_OneInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIWorkFunctionDefinition_OneInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIWorkFunctionDefinition_OneInput";
	}

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api::work_function".
	std::string
	class_namespace() const override {
		return "masala::base::api::work_function";
	}

	/// @brief Run the function on an input.
	T0
	function(
		T1 input
	) const {
		return work_function_( input );
	}

	/// @brief Get a raw pointer to the function.
	std::function< T0(T1) > const * function_raw_ptr() const { return &work_function_; }

	/// @brief Get the number of input parameters.
	/// @details Must be implemented by derived classes.
	/// @returns Override returns 1.
	masala::base::Size num_input_parameters() const override { return 1; }

	/// @brief Set the function to throw a deprecation error if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_deprecated () override {
		std::function< T0(T1) > const work_function_copy( work_function_ );
		work_function_ = std::bind(
			static_cast< T0(MasalaObjectAPIWorkFunctionDefinition::*)(std::function< T0( T1 ) >, T1 ) >( &MasalaObjectAPIWorkFunctionDefinition::deprecated_function_to_bind ), this, work_function_copy,
			std::placeholders::_1
		);
	}

	/// @brief Set the function to give a deprecation warning if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_warning () override {
		std::function< T0(T1) > const work_function_copy( work_function_ );
		work_function_ = std::bind(
			static_cast< T0(MasalaObjectAPIWorkFunctionDefinition::*)(std::function< T0( T1 ) >, T1 ) >( &MasalaObjectAPIWorkFunctionDefinition::warning_function_to_bind ), this, work_function_copy,
			std::placeholders::_1
		);
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
    	ss << "WorkFunction:\t"
			<< (is_virtual_non_override_fxn() ? "virtual " : "" )
			<< masala::base::api::name_from_type( base::api::type<T0>() )
			<< " " << work_function_name() << "( " << masala::base::api::name_from_type( base::api::type<T1>() ) << " )"
			<< (is_const() ? " const" : "" )
			<< (is_override_of_api_virtual_fxn() ? " override" : "")
			<< ":" << std::endl;
		ss << work_function_description() << std::endl;
		if( always_returns_nullptr() ) {
			ss << "This version of this function always returns nullptr." << ( is_virtual_non_override_fxn() || is_override_of_api_virtual_fxn() ? "  This could be overridden by derived classes." : "" ) << std::endl;
		}
		if( returns_this_ref() ) {
			ss << "Note that this function returns a reference to the original object (*this)." << std::endl;
		}
		if( triggers_no_mutex_lock() ) {
			ss << ( returns_this_ref() ? "Also note " : "Note ") << "that this function triggers no mutex lock." << std::endl;
		}
		ss << "Input 0:\t" << input_parameter0_name_ << "\t" << input_parameter0_description_ << std::endl;
		ss << "Output: \t" << output_name_ << "\t" << output_description_ << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this work_function.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	nlohmann::json
	get_work_function_json_description() const override {
		nlohmann::json json_api;
		json_api["Work_Function_Name"] = work_function_name();
		json_api["Work_Function_Description"] = work_function_description();
		json_api["Is_Const"] = is_const();
		json_api["Returns_This_Ref"] = returns_this_ref();
		json_api["Is_Virtual_Not_Overriding_Base_API_Virtual_Function"] = is_virtual_non_override_fxn();
		json_api["Is_Override_Of_Base_API_Virtual_Function"] = is_override_of_api_virtual_fxn();

		// Optional properties:
		if( triggers_no_mutex_lock() ) {
			json_api["Triggers_No_Mutex_Lock"] = true;
		}
		if( always_returns_nullptr() ) {
			json_api["Always_Returns_Nullptr"] = true;
		}

		//Inputs:
		json_api["Work_Function_N_Inputs"] = 1;

		nlohmann::json json_input0;
		json_input0["Input_Index"] = 0;
		json_input0["Input_Type"] = masala::base::api::name_from_type( base::api::type<T1>() );
		json_input0["Input_Description"] = input_parameter0_description_;
		json_input0["Input_Name"] = input_parameter0_name_;

		nlohmann::json json_inputs;
		json_inputs["Input_0"] = json_input0;
		json_api["Inputs"] = json_inputs;

		// Outputs:
		nlohmann::json json_output;
		json_output[ "Output_Type" ] = masala::base::api::name_from_type( base::api::type<T0>() );
		json_output[ "Output_Description" ] = output_description_;
		json_output[ "Output_Name" ] = output_name_;
		json_api["Output"] = json_output;

		modify_json_description_with_annotators( json_api );

		return json_api;
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A name for input parameter 1.
	std::string const input_parameter0_name_;

	/// @brief A description of input parameter 1.
	std::string const input_parameter0_description_;

	/// @brief A name for what this work function returns.
	std::string const output_name_;

	/// @brief A description of what this work function returns.
	std::string const output_description_;

	/// @brief The function that we're binding to.
	std::function< T0(T1) > const work_function_;

}; // class MasalaObjectAPIWorkFunctionDefinition_OneInput

} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_OneInput_tmpl_hh