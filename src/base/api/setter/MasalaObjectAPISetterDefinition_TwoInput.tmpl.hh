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

/// @file src/base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh
/// @brief A template class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for two-input setters.  The types T1 and T2
/// define the input types.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_TwoInput_tmpl_hh
#define Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_TwoInput_tmpl_hh

// Base class.
#include <base/api/setter/MasalaObjectAPISetterDefinition.hh>

// Forward declarations.
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.fwd.hh>

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
/// @details This is a derived class for two-input setters.  The types T1 and T2
/// define the input types.
/// @note A setter must take one or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T1, typename T2 >
class MasalaObjectAPISetterDefinition_TwoInput : public MasalaObjectAPISetterDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPISetterDefinition_TwoInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] setter_function_name The name of the setter function that
	///			   we are describing here.
	/// @param[in] setter_function_description The description of the setter function that
	///			   we are describing here.
	/// @param[in] input_parameter0_name The name of the input 1 parameter.
	/// @param[in] input_parameter0_description The description of the input 1 parameter.
	/// @param[in] input_parameter1_name The name of the input 2 parameter.
	/// @param[in] input_parameter1_description The description of the input 2 parameter.
	/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
	///            is NOT an override of a virtual function in a parent API class)?
	/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
	///            a function in a base API class?
	/// @param[in] setter_function The setter function, bound with std::bind with std::placeholders.
	MasalaObjectAPISetterDefinition_TwoInput(
		std::string const & setter_function_name,
		std::string const & setter_function_description,
		std::string const & input_parameter0_name,
		std::string const & input_parameter0_description,
		std::string const & input_parameter1_name,
		std::string const & input_parameter1_description,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn,
		std::function< void( T1, T2 ) > const & setter_function
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
		setter_function_( setter_function )
	{}

	/// @brief Copy constructor.
	MasalaObjectAPISetterDefinition_TwoInput( MasalaObjectAPISetterDefinition_TwoInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPISetterDefinition_TwoInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPISetterDefinition_TwoInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPISetterDefinition_TwoInput";
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
		T2 input2
	) const {
		setter_function_(input1, input2);
	}

	/// @brief Get a raw pointer to the function.
	std::function< void(T1, T2) > const * function_raw_ptr() const { return &setter_function_; }

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
    	ss << "Setter:\t" << (is_virtual_non_override_fxn() ? "virtual " : "" ) << "void " << setter_function_name() << "( " << masala::base::api::name_from_type( base::api::type<T1>() ) << ", " << masala::base::api::name_from_type( base::api::type<T2>() ) << " ) " << (is_override_of_api_virtual_fxn() ? " override" : "") << ":" << std::endl;
		ss << setter_function_description() << std::endl;
		ss << "Input 0:\t" << input_parameter0_name_ << "\t" << input_parameter0_description_ << std::endl;
		ss << "Input 1:\t" << input_parameter1_name_ << "\t" << input_parameter1_description_ << std::endl;
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
		json_api["Setter_N_Inputs"] = 2;

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

		nlohmann::json json_inputs;
		json_inputs["Input_0"] = json_input0;
		json_inputs["Input_1"] = json_input1;
		json_api["Inputs"] = json_inputs;

		modify_json_description_with_annotators( json_api );

		return json_api;
	}

	/// @brief Get the number of input parameters for this setter.
	/// @details Returns 2.
	masala::base::Size num_input_parameters() const override { return 2; }

	/// @brief Set the function to throw a deprecation error if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_deprecated () override {
		setter_function_ = std::bind(
			static_cast< void(MasalaObjectAPISetterDefinition::*)(T1,T2) >( &MasalaObjectAPISetterDefinition::deprecated_function_to_bind ), this,
			std::placeholders::_1,
			std::placeholders::_2
		);
	}

	/// @brief Set the function to give a deprecation warning if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_warning () override {
		std::function< void(T1, T2) > const setter_function_copy( setter_function_ );
		setter_function_ = std::bind(
			&MasalaObjectAPISetterDefinition::warning_function_to_bind<T1, T2>, this, setter_function_copy,
			std::placeholders::_1,
			std::placeholders::_2
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

	/// @brief The function that we're binding to.
	std::function< void(T1,T2) > setter_function_;

}; // class MasalaObjectAPISetterDefinition_TwoInput

} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_TwoInput_tmpl_hh