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

	/// @brief Options constructor.
	/// @param[in] getter_function_name The name of the getter function that
	///			   we are describing here.
	/// @param[in] getter_function_description The description of the getter function that
	///			   we are describing here.
	/// @param[in] input_parameter0_description The name of the input parameter.
	/// @param[in] input_parameter0_description The description of the input parameter.
	/// @param[in] output_parameter_name A name for what the getter returns.  (Not used in the
	///            C++ code; could be used elsewhere.)
	/// @param[in] output_parameter_description The description of what the getter returns.
	/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
	///            is NOT an override of a virtual function in a parent API class)?
	/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
	///            a function in a base API class?
	/// @param[in] getter_function The actual getter function.
	MasalaObjectAPIGetterDefinition_OneInput(
		std::string const & getter_function_name,
		std::string const & getter_function_description,
		std::string const & input_parameter0_name,
		std::string const & input_parameter0_description,
		std::string const & output_parameter_name,
		std::string const & output_parameter_description,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn,
		std::function< T0( T1 ) > const & getter_function
	) :
		MasalaObjectAPIGetterDefinition(
			getter_function_name, getter_function_description,
			is_virtual_non_override_fxn, is_override_of_api_virtual_fxn
		),
		input_parameter0_name_(input_parameter0_name),
		input_parameter0_description_(input_parameter0_description),
		output_name_(output_parameter_name),
		output_description_( output_parameter_description ),
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

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api::getter".
	std::string
	class_namespace() const override {
		return "masala::base::api::getter";
	}

	/// @brief Provide an input to the function.
	T0
	function(
		T1 input
	) const {
		return getter_function_(input);
	}

	/// @brief Get a raw pointer to the function.
	std::function< T0(T1) > const * function_raw_ptr() const { return &getter_function_; }

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
    	ss << "Getter:\t" << (is_virtual_non_override_fxn() ? "virtual " : "" )
			<< masala::base::api::name_from_type(base::api::type<T0>())
			<< " " << getter_function_name()
			<< "( " << masala::base::api::name_from_type( base::api::type<T1>() ) << " ) const"
			<< ( is_override_of_api_virtual_fxn() ? " override" : "" )
			<< ":" << std::endl;
		ss << getter_function_description() << std::endl;
		ss << "Input 0:\t" << input_parameter0_name_ << "\t" << input_parameter0_description_ << std::endl;
		ss << "Output: \t" << output_name_ << "\t" << output_description_ << std::endl;
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
		json_api["Is_Virtual_Not_Overriding_Base_API_Virtual_Function"] = is_virtual_non_override_fxn();
		json_api["Is_Override_Of_Base_API_Virtual_Function"] = is_override_of_api_virtual_fxn();

		//Inputs:
		json_api["Getter_N_Inputs"] = 1;

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
		json_output[ "Output_Type" ] = masala::base::api::name_from_type(base::api::type<T0>());
		json_output[ "Output_Description" ] = output_description_;
		json_output[ "Output_Name" ] = output_name_;
		json_api["Output"] = json_output;

		modify_json_description_with_annotators( json_api );

		return json_api;
	}

	/// @brief Get the number of input parameters for this getter.
	/// @details Returns 1.
	masala::base::Size num_input_parameters() const override { return 1; }

	/// @brief Set the function to throw a deprecation error if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_deprecated () override {
		std::function< T0(T1) > const getter_function_copy( getter_function_ );
		getter_function_ = std::bind(
			static_cast< T0(MasalaObjectAPIGetterDefinition::*)(std::function< T0( T1 ) >, T1 ) >( &MasalaObjectAPIGetterDefinition::deprecated_function_to_bind ), this, getter_function_copy,
			std::placeholders::_1
		);
	}

	/// @brief Set the function to give a deprecation warning if invoked.
	/// @details Must be implemented by derived classes.
	void
	set_function_warning () override {
		std::function< T0(T1) > const getter_function_copy( getter_function_ );
		getter_function_ = std::bind(
			static_cast< T0(MasalaObjectAPIGetterDefinition::*)(std::function< T0( T1 ) >, T1 ) >( &MasalaObjectAPIGetterDefinition::warning_function_to_bind ), this, getter_function_copy,
			std::placeholders::_1
		);
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////


	/// @brief A name for input parameter 0.
	std::string const input_parameter0_name_;

	/// @brief A description of input parameter 0.
	std::string const input_parameter0_description_;

	/// @brief A name for what this getter returns.
	std::string const output_name_;

	/// @brief A description of what this getter returns.
	std::string const output_description_;

	/// @brief The function that we're binding to.
	std::function< T0(T1) > getter_function_;

}; // class MasalaObjectAPIGetterDefinition_OneInput

} // namespace getter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_OneInput_tmpl_hh