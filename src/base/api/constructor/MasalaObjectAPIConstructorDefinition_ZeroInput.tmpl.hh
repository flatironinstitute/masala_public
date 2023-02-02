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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh
/// @brief A template class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a derived class for no-input constructors.  The type T0 defines
/// the type for which we're defining a constructor.
/// @note A constructor must take zero or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_tmpl_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_tmpl_hh

// Base class.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>

// Forward declarations.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.fwd.hh>

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
/// @details This is a derived class for no-input constructors.  The type T0 defines
/// the type for which we're defining a constructor.
/// @note A constructor must take zero or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
template< typename T0 >
class MasalaObjectAPIConstructorDefinition_ZeroInput : public MasalaObjectAPIConstructorDefinition {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIConstructorDefinition_ZeroInput() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] constructor_name The name of the constructor that
	///			   we are describing here.  Should match the T0 class name.
	/// @param[in] constructor_description The description of the constructor that
	///			   we are describing here.
	/// @param[in] is_protected_constructor Should the API's class constructor be
	///            protected?  This allows the API class to act like a pure virtual
	///            base class, preventing instantiation.
	MasalaObjectAPIConstructorDefinition_ZeroInput(
		std::string const & constructor_name,
		std::string const & constructor_description,
		bool const is_protected_constructor
	) :
		MasalaObjectAPIConstructorDefinition(
			constructor_name,
			constructor_description,
			is_protected_constructor
		)
	{}

	/// @brief Copy constructor.
	MasalaObjectAPIConstructorDefinition_ZeroInput( MasalaObjectAPIConstructorDefinition_ZeroInput const & ) = default;

	/// @brief Pure virtual destructor.
	~MasalaObjectAPIConstructorDefinition_ZeroInput() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIConstructorDefinition_ZeroInput".
	std::string
	class_name() const override {
		return "MasalaObjectAPIConstructorDefinition_ZeroInput";
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
    	ss << "Constructor:\t" << constructor_name() << "():" << std::endl;
		ss << constructor_description() << std::endl;
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
		json_api["Is_Protected"] = is_protected_constructor();

		//Inputs:
		json_api["Constructor_N_Inputs"] = 0;
		
		return json_api;
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Create an instance of this class using the constructor.
	MASALA_SHARED_POINTER< T0 >
	create_object() const {
		return masala::make_shared< T0 >();
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

}; // class MasalaObjectAPIConstructorDefinition_ZeroInput

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_ZeroInput_tmpl_hh