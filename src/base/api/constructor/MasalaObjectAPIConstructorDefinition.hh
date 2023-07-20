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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition.hh
/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.fwd.hh>

// External headers.
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// STL headers.
#include <string>

namespace masala {
namespace base {
namespace api {
namespace constructor {

/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a pure virtual base class.  Derived classes are for
/// one-parameter, two-parameter, three-parameter, etc. constructors.
/// @note A constructor must take one or more inputs, and must have no return value.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPIConstructorDefinition : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIConstructorDefinition() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] constructor_name The name of the constructor that
	///			   we are describing here.  Should match the T0 class name.
	/// @param[in] constructor_description The description of the constructor that
	///			   we are describing here.
	MasalaObjectAPIConstructorDefinition(
		std::string const & constructor_name,
		std::string const & constructor_description
	);

	/// @brief Copy constructor.
	MasalaObjectAPIConstructorDefinition( MasalaObjectAPIConstructorDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPIConstructorDefinition() override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this constructor.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	std::string
	get_constructor_human_readable_description() const = 0;

	/// @brief Get a JSON description of this constructor.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	nlohmann::json
	get_constructor_json_description() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of the constructor.  Should match the T0 class name.
	std::string const & constructor_name() const;

	/// @brief Get the constructor's description.
	std::string const & constructor_description() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of the constructor.
	/// @details Must be set on construction.  Should match the T0 class name.
	std::string const constructor_name_;

	/// @brief The description of the constructor.
	/// @details Must be set on construction.
	std::string const constructor_description_;

}; // class MasalaObjectAPIConstructorDefinition

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorDefinition_hh