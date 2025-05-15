/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/base/api/setter/MasalaObjectAPISetterDefinition_SevenInput.tmpl.hh
/// @brief A template class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for seven-input setters.  The types T1, T2, T3, T4, T5, T6, and T7
/// define the input types.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_SevenInput_tmpl_hh
#define Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_SevenInput_tmpl_hh

// Base class.
#include <base/api/setter/MasalaObjectAPISetterDefinition.hh>

// Forward declarations.
#include <base/api/setter/MasalaObjectAPISetterDefinition_SevenInput.fwd.hh>

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
namespace setter {

/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for seven-input setters.  The types T1, T2, T3, T4, T5, T6, and T7
/// define the input types.
/// @note A setter must take one or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
class MasalaObjectAPISetterDefinition_SevenInput : public MasalaObjectAPISetterDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPISetterDefinition_SevenInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] setter_function_name The name of the setter function that
	///			   we are describing here.
	/// @param[in] setter_function_description The description of the setter function that
	///			   we are describing here.
	/// @param[in] input_parameter0_name The name of the input 1 parameter.
	/// @param[in] input_parameter0_description The description of the input 1 parameter.
	/// @param[in] input_parameter1_name The name of the input 2 parameter.
	/// @param[in] input_parameter1_description The description of the input 2 parameter.
	/// @param[in] input_parameter2_name The name of the input 3 parameter.
	/// @param[in] input_parameter2_description The description of the input 3 parameter.
	/// @param[in] input_parameter3_name The name of the input 4 parameter.
	/// @param[in] input_parameter3_description The description of the input 4 parameter.
	/// @param[in] input_parameter4_name The name of the input 5 parameter.
	/// @param[in] input_parameter4_description The description of the input 5 parameter.
	/// @param[in] input_parameter5_name The name of the input 6 parameter.
	/// @param[in] input_parameter5_description The description of the input 6 parameter.
	/// @param[in] input_parameter6_name The name of the input 7 parameter.
	/// @param[in] input_parameter6_description The description of the input 7 parameter.
	/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
	///            is NOT an override of a virtual function in a parent API class)?
	/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
	///            a function in a base API class?
	/// @param[in] setter_function The setter function, bound with std::bind with std::placeholders.
	MasalaObjectAPISetterDefinition_SevenInput(
		std::string const & setter_function_name,
		std::string const & setter_function_description,
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
		std::string const & input_parameter6_name,
		std::string const & input_parameter6_description,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn,
		std::function< void( T1, T2, T3, T4, T5, T6, T7 ) > const & setter_function
	) :
		MasalaObjectAPISetterDefinition(
			setter_function_name,
			setter_function_description,
			is_virtual_non_override_fxn,
			is_override_of_api_virtual_fxn
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
		input_parameter6_name_(input_parameter6_name),
		input_parameter6_description_(input_parameter6_description),
		setter_function_( setter_function )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPISetterDefinition_SevenInput( MasalaObjectAPISetterDefinition_SevenInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPISetterDefinition_SevenInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPISetterDefinition_SevenInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPISetterDefinition_SevenInput";
	}

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api::setter".
	std::string
	class_namespace() const override {
		return "masala::base::api::setter";
	}

	/// @brief Provide an input to the function.
	void
	function(
		T1 input1,
		T2 input2,
		T3 input3,
		T4 input4,
		T5 input5,
		T6 input6,
		T7 input7
	) const {
		setter_function_(input1, input2, input3, input4, input5, input6, input7);
	}

	/// @brief Get a raw pointer to the function.
	std::function< void(T1, T2, T3, T4, T5, T6, T7) > const * function_raw_ptr() const { return &setter_function_; }

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
    	ss << "Setter:\t" << (is_virtual_non_override_fxn() ? "virtual " : "" ) << "void " << setter_function_name() << "( "
			<< masala::base::api::name_from_type( base::api::type<T1>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T2>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T3>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T4>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T5>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T6>() ) << ", "
			<< masala::base::api::name_from_type( base::api::type<T7>() ) << " ) "
			<< (is_override_of_api_virtual_fxn() ? " override" : "") << ":"
			<< std::endl;
		ss << setter_function_description() << std::endl;
		ss << "Input 0:\t" << input_parameter0_name_ << "\t" << input_parameter0_description_ << std::endl;
		ss << "Input 1:\t" << input_parameter1_name_ << "\t" << input_parameter1_description_ << std::endl;
		ss << "Input 2:\t" << input_parameter2_name_ << "\t" << input_parameter2_description_ << std::endl;
		ss << "Input 3:\t" << input_parameter3_name_ << "\t" << input_parameter3_description_ << std::endl;
		ss << "Input 4:\t" << input_parameter4_name_ << "\t" << input_parameter4_description_ << std::endl;
		ss << "Input 5:\t" << input_parameter5_name_ << "\t" << input_parameter5_description_ << std::endl;
		ss << "Input 6:\t" << input_parameter6_name_ << "\t" << input_parameter6_description_ << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this setter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	nlohmann::json
	get_setter_json_description() const override {
		nlohmann::json json_api;
		json_api["Setter_Name"] = setter_function_name();
		json_api["Setter_Description"] = setter_function_description();
		json_api["Is_Const"] = false;
		json_api["Is_Virtual_Not_Overriding_Base_API_Virtual_Function"] = is_virtual_non_override_fxn();
		json_api["Is_Override_Of_Base_API_Virtual_Function"] = is_override_of_api_virtual_fxn();

		//Inputs:
		json_api["Setter_N_Inputs"] = 7;

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

		nlohmann::json json_input6;
		json_input6["Input_Index"] = 6;
		json_input6["Input_Type"] = masala::base::api::name_from_type( base::api::type<T7>() );
		json_input6["Input_Description"] = input_parameter6_description_;
		json_input6["Input_Name"] = input_parameter6_name_;

		nlohmann::json json_inputs;
		json_inputs["Input_0"] = json_input0;
		json_inputs["Input_1"] = json_input1;
		json_inputs["Input_2"] = json_input2;
		json_inputs["Input_3"] = json_input3;
		json_inputs["Input_4"] = json_input4;
		json_inputs["Input_5"] = json_input5;
		json_inputs["Input_6"] = json_input6;
		json_api["Inputs"] = json_inputs;

		modify_json_description_with_annotators( json_api );

		return json_api;
	}

	/// @brief Get the number of input parameters for this setter.
	/// @details Returns 7.
	masala::base::Size num_input_parameters() const override { return 7; }

	/// @brief Set the function to throw a deprecation error if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_deprecated () override {
		setter_function_ = std::bind(
			&MasalaObjectAPISetterDefinition::deprecated_function_to_bind<T1, T2, T3, T4, T5, T6, T7>, this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4,
			std::placeholders::_5,
			std::placeholders::_6,
			std::placeholders::_7
		);
	}

	/// @brief Set the function to give a deprecation warning if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_warning () override {
		std::function< void(T1, T2, T3, T4, T5, T6, T7) > const setter_function_copy( setter_function_ );
		setter_function_ = std::bind(
			&MasalaObjectAPISetterDefinition::warning_function_to_bind<T1, T2, T3, T4, T5, T6, T7>, this, setter_function_copy,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4,
			std::placeholders::_5,
			std::placeholders::_6,
			std::placeholders::_7
		);
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

	/// @brief A name for input parameter 7.
	std::string const input_parameter6_name_;

	/// @brief A description of input parameter 7.
	std::string const input_parameter6_description_;

	/// @brief The function that we're binding to.
	std::function< void(T1,T2,T3,T4,T5,T6,T7) > setter_function_;

}; // class MasalaObjectAPISetterDefinition_SevenInput

} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_SevenInput_tmpl_hh