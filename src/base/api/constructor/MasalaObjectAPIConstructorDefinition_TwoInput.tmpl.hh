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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition_TwoInput.tmpl.hh
/// @brief A template class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for two-input constructors.  The types T1 and T2
/// define the input type, and the type T0 defines the type for which we're defining
/// a constructor.
/// @note A constructor must take zero or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_TwoInput_tmpl_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_TwoInput_tmpl_hh

// Base class.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>

// Forward declarations.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_TwoInput.fwd.hh>

// Base headers.
#include <base/api/names_from_types.tmpl.hh>

// External headers.
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers.
#include <sstream>

namespace masala {
namespace base {
namespace api {
namespace constructor {

/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for two-input constructors.  The types T1 and T2
/// define the input type, and the type T0 defines the type for which we're defining
/// a constructor.
/// @note A constructor must take zero or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0, typename T1, typename T2 >
class MasalaObjectAPIConstructorDefinition_TwoInput : public MasalaObjectAPIConstructorDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIConstructorDefinition_TwoInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] constructor_name The name of the constructor that
	///			   we are describing here.  Should match the T0 class name.
	/// @param[in] constructor_description The description of the constructor that
	///			   we are describing here.
	/// @param[in] input_parameter0_name The name of the first input parameter.
	/// @param[in] input_parameter0_description The description of the first input parameter.
	/// @param[in] input_parameter1_name The name of the second input parameter.
	/// @param[in] input_parameter1_description The description of the second input parameter.
	MasalaObjectAPIConstructorDefinition_TwoInput(
		std::string const & constructor_name,
		std::string const & constructor_description,
		std::string const & input_parameter0_name,
		std::string const & input_parameter0_description,
		std::string const & input_parameter1_name,
		std::string const & input_parameter1_description
	) :
		MasalaObjectAPIConstructorDefinition( constructor_name, constructor_description ),
		input_parameter0_name_(input_parameter0_name),
		input_parameter0_description_(input_parameter0_description),
		input_parameter1_name_(input_parameter1_name),
		input_parameter1_description_(input_parameter1_description)
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIConstructorDefinition_TwoInput( MasalaObjectAPIConstructorDefinition_TwoInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIConstructorDefinition_TwoInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIConstructorDefinition_TwoInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIConstructorDefinition_TwoInput";
	}

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api::constructor".
	std::string
	class_namespace() const override {
		return "masala::base::api::constructor";
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
    	ss << "Constructor:\t" << constructor_name() << "( "
			<< masala::base::api::name_from_type(base::api::type<T1>()) << ", "
			<< masala::base::api::name_from_type(base::api::type<T2>()) << " ):"
			<< std::endl;
		ss << constructor_description() << std::endl;
		ss << "Input 0:\t" << input_parameter0_name_ << "\t" << input_parameter0_description_ << std::endl;
		ss << "Input 1:\t" << input_parameter1_name_ << "\t" << input_parameter1_description_ << std::endl;
		return ss.str();
	}

	/// @brief Get a JSON description of this constructor.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	nlohmann::json
	get_constructor_json_description() const override {
		nlohmann::json json_api;
		json_api["Constructor_Name"] = constructor_name();
		json_api["Constructor_Description"] = constructor_description();
		json_api["Is_Const"] = false; //Constructors are never const.

		//Inputs:
		json_api["Constructor_N_Inputs"] = 1;

		nlohmann::json json_input0;
		json_input0["Input_Index"] = 0;
		json_input0["Input_Type"] = masala::base::api::name_from_type(base::api::type< T1 >());
		json_input0["Input_Name"] = input_parameter0_name_;
		json_input0["Input_Description"] = input_parameter0_description_;

		nlohmann::json json_input1;
		json_input1["Input_Index"] = 1;
		json_input1["Input_Type"] = masala::base::api::name_from_type(base::api::type< T2 >());
		json_input1["Input_Name"] = input_parameter1_name_;
		json_input1["Input_Description"] = input_parameter1_description_;

		nlohmann::json json_inputs;
		json_inputs["Input_0"] = json_input0;
		json_inputs["Input_1"] = json_input1;

		json_api["Inputs"] = json_inputs;

		return json_api;
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Create an instance of this class using the constructor.
	MASALA_SHARED_POINTER< T0 >
	create_object( T1 const & input_parameter_0, T2 const & input_parameter_1 ) const {
		return masala::make_shared< T0 >( input_parameter_0, input_parameter_1 );
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of input parameter 0.
	/// @details Must be set on construction.
	std::string const input_parameter0_name_;

	/// @brief The name of input parameter 1.
	/// @details Must be set on construction.
	std::string const input_parameter1_name_;

	/// @brief A description of input parameter 0.
	/// @details Must be set on construction.
	std::string const input_parameter0_description_;

	/// @brief A description of input parameter 1.
	/// @details Must be set on construction.
	std::string const input_parameter1_description_;

}; // class MasalaObjectAPIConstructorDefinition_TwoInput

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_TwoInput_tmpl_hh