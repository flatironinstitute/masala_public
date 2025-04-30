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

/// @file src/base/api/getter/MasalaObjectAPIGetterDefinition.hh
/// @brief A class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_hh
#define Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/types.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition.fwd.hh>
#include <base/api/getter/getter_annotation/MasalaGetterFunctionAnnotation.fwd.hh>

// External headers
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// STL headers.
#include <string>

namespace masala {
namespace base {
namespace api {
namespace getter {

/// @brief A class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a pure virtual base class.  Derived classes are for
/// zero-parameter, one-parameter, two-parameter, three-parameter, etc. getters.
/// @note A getter can take zero or more inputs, and must return one non-void output.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPIGetterDefinition : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIGetterDefinition() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] getter_function_name The name of the getter function that
	///			   we are describing here.
	/// @param[in] getter_function_description The description of the getter function that
	///			   we are describing here.
	/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
	///            is NOT an override of a virtual function in a parent API class)?
	/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
	///            a function in a base API class?
	MasalaObjectAPIGetterDefinition(
		std::string const & getter_function_name,
		std::string const & getter_function_description,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn
	);

	/// @brief Copy constructor.
	MasalaObjectAPIGetterDefinition( MasalaObjectAPIGetterDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPIGetterDefinition() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this getter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	std::string
	get_getter_human_readable_description() const = 0;

	/// @brief Get a JSON description of this getter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	nlohmann::json
	get_getter_json_description() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of the getter function.
	std::string const & getter_function_name() const;

	/// @brief Get the getter function's description.
	/// @note Returns a copy rather than an instance of a string because there may be additional description generated on the fly
	/// (e.g. by getter annotations).
	std::string getter_function_description() const;

	/// @brief Is this function a virtual function that does NOT override
	/// a function in a base class that has a defined API?
	bool is_virtual_non_override_fxn() const;

	/// @brief Is this function an override of a virtual function in a base
	/// class that has a defined API?
	bool is_override_of_api_virtual_fxn() const;

	/// @brief Get the number of getter annotations.
	masala::base::Size n_getter_annotations() const;

	/// @brief Access the Nth getter annotation.
	getter_annotation::MasalaGetterFunctionAnnotationCSP getter_annotation( masala::base::Size const getter_annotation_index ) const;

	/// @brief Add a getter annotation.
	/// @details Annotation is used directly, not cloned.
	void add_getter_annotation( getter_annotation::MasalaGetterFunctionAnnotationCSP const & annotation_in );

	/// @brief Get the number of input parameters for this getter.
	/// @details Pure virtual; must be overridden by derived classes.
	virtual masala::base::Size num_input_parameters() const = 0;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of the getter function.
	/// @details Must be set on construction.
	std::string const getter_function_name_;

	/// @brief The description of the getter function.
	/// @details Must be set on construction.
	std::string const getter_function_description_;

	/// @brief Is this function a virtual function that does NOT override
	/// a function in a base class that has a defined API?
	bool is_virtual_non_override_fxn_ = false;

	/// @brief Is this function an override of a virtual function in a base
	/// class that has a defined API?
	bool is_override_of_api_virtual_fxn_ = false;

	/// @brief Additional annotations that this function has attached to it.
	std::vector< getter_annotation::MasalaGetterFunctionAnnotationCSP > getter_annotations_;

}; // class MasalaObjectAPIGetterDefinition

} // namespace getter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_getter_MasalaObjectAPIGetterDefinition_hh