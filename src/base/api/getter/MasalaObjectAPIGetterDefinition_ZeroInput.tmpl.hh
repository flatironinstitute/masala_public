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

	/// @brief Options constructor.
	/// @param[in] getter_function_name The name of the getter function that
	///			   we are describing here.
	/// @param[in] getter_function_description The description of the getter function that
	///			   we are describing here.
	/// @param[in] output_parameter_name The name for what the getter returns.
	/// @param[in] output_parameter_description The description of what the getter returns.
	/// @param[in] getter_function The actual getter function.
	MasalaObjectAPIGetterDefinition_ZeroInput(
		std::string const & getter_function_name,
		std::string const & getter_function_description,
		std::string const & output_parameter_name,
		std::string const & output_parameter_description,
		std::function< T0() > const & getter_function
	) :
		MasalaObjectAPIGetterDefinition( getter_function_name, getter_function_description ),
		output_name_( output_parameter_name ),
		output_description_( output_parameter_description ),
		getter_function_( getter_function )
	{}

	/// @brief Options constructor for custom output types (enums).
	/// @param[in] getter_function_name The name of the getter function that
	///			   we are describing here.
	/// @param[in] getter_function_description The description of the getter function that
	///			   we are describing here.
	/// @param[in] output_parameter_name The name for what the getter returns.
	/// @param[in] output_parameter_description The description of what the getter returns.
	/// @param[in] output_type_name The name of the output type.
	/// @param[in] output_type_namespace The namespace of the output type.
	/// @param[in] getter_function The actual getter function.
	MasalaObjectAPIGetterDefinition_ZeroInput(
		std::string const & getter_function_name,
		std::string const & getter_function_description,
		std::string const & output_parameter_name,
		std::string const & output_parameter_description,
		std::string const & output_type_name,
		std::string const & output_type_namespace,
		std::function< T0() > const & getter_function
	) :
		MasalaObjectAPIGetterDefinition( getter_function_name, getter_function_description, output_type_name, output_type_namespace ),
		output_name_( output_parameter_name ),
		output_description_( output_parameter_description ),
		getter_function_( getter_function )
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

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api::getter".
	std::string
	class_namespace() const override {
		return "masala::base::api::getter";
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
    	ss << "Getter:\t"
			<< ( has_custom_output_type_name() ? get_custom_output_type_namespace_and_name() : masala::base::api::name_from_type(base::api::type<T0>()) )
			<< " " << getter_function_name() << "() const:" << std::endl;
		ss << getter_function_description() << std::endl;
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

		// Inputs:
		json_api["Getter_N_Inputs"] = 0;

		// Outputs:
		nlohmann::json json_output;
		json_output[ "Output_Type" ] = ( has_custom_output_type_name() ? get_custom_output_type_namespace_and_name() : masala::base::api::name_from_type(base::api::type<T0>()) );
		json_output[ "Output_Description" ] = output_description_;
		json_output[ "Output_Name" ] = output_name_;
		json_output[ "Output_Is_Enum" ] = has_custom_output_type_name();
		json_api["Output"] = json_output;

		return json_api;
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A name for what this getter returns.
	std::string const output_name_;

	/// @brief A description of what this getter returns.
	std::string const output_description_;

	/// @brief The function that we're binding to.
	std::function< T0() > const getter_function_;

}; // class MasalaObjectAPIGetterDefinition_ZeroInput

} // namespace getter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_ZeroInput_tmpl_hh