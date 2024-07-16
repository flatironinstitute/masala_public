/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_SixInput.tmpl.hh
/// @brief A template class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for six-input work functions.  The types T1 through T6
/// define the input types and the type T0 defines the output type.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_SixInput_tmpl_hh
#define Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_SixInput_tmpl_hh

// Base class.
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>

// Forward declarations.
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_SixInput.fwd.hh>

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
/// @details This is a derived class for six-input work functions.  The types T1 through T6
/// define the input types and the type T0 defines the output type.
/// @note A work function can take zero or more inputs, and can return one non-void output.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
class MasalaObjectAPIWorkFunctionDefinition_SixInput : public MasalaObjectAPIWorkFunctionDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIWorkFunctionDefinition_SixInput() = delete;

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
	/// @param[in] input_parameter0_name The name for the input parameter 1.
	/// @param[in] input_parameter0_description The description of the input parameter 1.
	/// @param[in] input_parameter1_name The name for the input parameter 2.
	/// @param[in] input_parameter1_description The description of the input parameter 2.
	/// @param[in] input_parameter2_name The name for the input parameter 3.
	/// @param[in] input_parameter2_description The description of the input parameter 3.
	/// @param[in] input_parameter3_name The name for the input parameter 4.
	/// @param[in] input_parameter3_description The description of the input parameter 4.
	/// @param[in] output_parameter_name The name for what the work function returns.
	/// @param[in] output_parameter_description The description of what the work function returns.
	/// @param[in] work_function The actual work function.
	MasalaObjectAPIWorkFunctionDefinition_SixInput(
		std::string const & work_function_name,
		std::string const & work_function_description,
		bool const is_const,
		bool const returns_this_ref,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn,
		std::string const & input_parameter0_name,
		std::string const & input_parameter0_description,
		std::string const & input_parameter1_name,
		std::string const & input_parameter1_description,
		std::string const & input_parameter2_name,
		std::string const & input_parameter2_description,
		std::string const & input_parameter3_name,
		std::string const & input_parameter3_description,
		std::string const & input_parameter4_name,
		std::string const & input_parameter4_description,
		std::string const & input_parameter5_name,
		std::string const & input_parameter5_description,
		std::string const & output_parameter_name,
		std::string const & output_parameter_description,
		std::function< T0( T1, T2, T3, T4, T5, T6 ) > const & work_function
	) :
		MasalaObjectAPIWorkFunctionDefinition(
			work_function_name, work_function_description,
			is_const, returns_this_ref,
			is_virtual_non_override_fxn, is_override_of_api_virtual_fxn
		),
		input_parameter0_name_(input_parameter0_name),
		input_parameter0_description_(input_parameter0_description),
		input_parameter1_name_(input_parameter1_name),
		input_parameter1_description_(input_parameter1_description),
		input_parameter2_name_(input_parameter2_name),
		input_parameter2_description_(input_parameter2_description),
		input_parameter3_name_(input_parameter3_name),
		input_parameter3_description_(input_parameter3_description),
		input_parameter4_name_(input_parameter4_name),
		input_parameter4_description_(input_parameter4_description),
		input_parameter5_name_(input_parameter5_name),
		input_parameter5_description_(input_parameter5_description),
		output_name_( output_parameter_name ),
		output_description_( output_parameter_description ),
		work_function_( work_function )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIWorkFunctionDefinition_SixInput( MasalaObjectAPIWorkFunctionDefinition_SixInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIWorkFunctionDefinition_SixInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIWorkFunctionDefinition_SixInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIWorkFunctionDefinition_SixInput";
	}

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api::work_function".
	std::string
	class_namespace() const override {
		return "masala::base::api::work_function";
	}

	/// @brief Run the function on an input.
	T0
	function(
		T1 input1,
		T2 input2,
		T3 input3,
		T4 input4,
		T5 input5,
		T6 input6
	) const {
		return work_function_( input1, input2, input3, input4, input5, input6 );
	}

	/// @brief Get a raw pointer to the function.
	std::function< T0(T1, T2, T3, T4, T5, T6) > const * function_raw_ptr() const { return &work_function_; }

	/// @brief Get the number of input parameters.
	/// @details Must be implemented by derived classes.
	/// @returns Override returns 6.
	masala::base::Size num_input_parameters() const override { return 6; }

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
			<< " " << work_function_name() << "( "
			<< masala::base::api::name_from_type( base::api::type<T1>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T2>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T3>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T4>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T5>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T6>() )
			<< " )"
			<< (is_const() ? " const" : "" )
			<< (is_override_of_api_virtual_fxn() ? " override" : "")
			<< ":" << std::endl;
		ss << work_function_description() << std::endl;
		if( returns_this_ref() ) {
			ss << "Note that this function returns a reference to the original object (*this)." << std::endl;
		}
		if( triggers_no_mutex_lock() ) {
			ss << ( returns_this_ref() ? "Also note " : "Note ") << "that this function triggers no mutex lock." << std::endl;
		}
		ss << "Input 0:\t" << input_parameter0_name_ << "\t" << input_parameter0_description_ << std::endl;
		ss << "Input 1:\t" << input_parameter1_name_ << "\t" << input_parameter1_description_ << std::endl;
		ss << "Input 2:\t" << input_parameter2_name_ << "\t" << input_parameter2_description_ << std::endl;
		ss << "Input 3:\t" << input_parameter3_name_ << "\t" << input_parameter3_description_ << std::endl;
		ss << "Input 4:\t" << input_parameter4_name_ << "\t" << input_parameter4_description_ << std::endl;
		ss << "Input 5:\t" << input_parameter5_name_ << "\t" << input_parameter5_description_ << std::endl;
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

		//Inputs:
		json_api["Work_Function_N_Inputs"] = 6;

		nlohmann::json json_input0;
		json_input0["Input_Index"] = 0;
		json_input0["Input_Type"] = masala::base::api::name_from_type( base::api::type<T1>() );
		json_input0["Input_Description"] = input_parameter0_description_;
		json_input0["Input_Name"] = input_parameter0_name_;

		nlohmann::json json_input1;
		json_input1["Input_Index"] = 1;
		json_input1["Input_Type"] = masala::base::api::name_from_type( base::api::type<T2>() );
		json_input1["Input_Description"] = input_parameter1_description_;
		json_input1["Input_Name"] = input_parameter1_name_;

		nlohmann::json json_input2;
		json_input2["Input_Index"] = 2;
		json_input2["Input_Type"] = masala::base::api::name_from_type( base::api::type<T3>() );
		json_input2["Input_Description"] = input_parameter2_description_;
		json_input2["Input_Name"] = input_parameter2_name_;

		nlohmann::json json_input3;
		json_input3["Input_Index"] = 3;
		json_input3["Input_Type"] = masala::base::api::name_from_type( base::api::type<T4>() );
		json_input3["Input_Description"] = input_parameter3_description_;
		json_input3["Input_Name"] = input_parameter3_name_;

		nlohmann::json json_input4;
		json_input4["Input_Index"] = 4;
		json_input4["Input_Type"] = masala::base::api::name_from_type( base::api::type<T5>() );
		json_input4["Input_Description"] = input_parameter4_description_;
		json_input4["Input_Name"] = input_parameter4_name_;

		nlohmann::json json_input5;
		json_input5["Input_Index"] = 5;
		json_input5["Input_Type"] = masala::base::api::name_from_type( base::api::type<T6>() );
		json_input5["Input_Description"] = input_parameter5_description_;
		json_input5["Input_Name"] = input_parameter5_name_;

		nlohmann::json json_inputs;
		json_inputs["Input_0"] = json_input0;
		json_inputs["Input_1"] = json_input1;
		json_inputs["Input_2"] = json_input2;
		json_inputs["Input_3"] = json_input3;
		json_inputs["Input_4"] = json_input4;
		json_inputs["Input_5"] = json_input5;
		json_api["Inputs"] = json_inputs;

		// Outputs:
		nlohmann::json json_output;
		json_output[ "Output_Type" ] = masala::base::api::name_from_type( base::api::type<T0>() );
		json_output[ "Output_Description" ] = output_description_;
		json_output[ "Output_Name" ] = output_name_;
		json_api["Output"] = json_output;

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

	/// @brief A name for input parameter 2.
	std::string const input_parameter1_name_;

	/// @brief A description of input parameter 2.
	std::string const input_parameter1_description_;

	/// @brief A name for input parameter 3.
	std::string const input_parameter2_name_;

	/// @brief A description of input parameter 3.
	std::string const input_parameter2_description_;

	/// @brief A name for input parameter 4.
	std::string const input_parameter3_name_;

	/// @brief A description of input parameter 4.
	std::string const input_parameter3_description_;

	/// @brief A name for input parameter 5.
	std::string const input_parameter4_name_;

	/// @brief A description of input parameter 5.
	std::string const input_parameter4_description_;

	/// @brief A name for input parameter 6.
	std::string const input_parameter5_name_;

	/// @brief A description of input parameter 6.
	std::string const input_parameter5_description_;

	/// @brief A name for what this work function returns.
	std::string const output_name_;

	/// @brief A description of what this work function returns.
	std::string const output_description_;

	/// @brief The function that we're binding to.
	std::function< T0( T1, T2, T3, T4, T5, T6 ) > const work_function_;

}; // class MasalaObjectAPIWorkFunctionDefinition_SixInput

} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_SixInput_tmpl_hh