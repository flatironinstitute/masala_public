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

/// @file src/base/api/getter/MasalaObjectAPIGetterDefinition.cc
/// @brief A class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/getter/MasalaObjectAPIGetterDefinition.hh>

// Base headers
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace api {
namespace getter {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor, to be called by derived classes.
/// @param[in] getter_function_name The name of the getter function that
///			   we are describing here.
/// @param[in] getter_function_description The description of the getter function that
///			   we are describing here.
/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
///            is NOT an override of a virtual function in a parent API class)?
/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
///            a function in a base API class?
MasalaObjectAPIGetterDefinition::MasalaObjectAPIGetterDefinition(
    std::string const & getter_function_name,
    std::string const & getter_function_description,
    bool const is_virtual_non_override_fxn,
    bool const is_override_of_api_virtual_fxn
) :
    masala::base::MasalaObject(),
    getter_function_name_(getter_function_name),
    getter_function_description_(getter_function_description),
    is_virtual_non_override_fxn_(is_virtual_non_override_fxn),
    is_override_of_api_virtual_fxn_(is_override_of_api_virtual_fxn)
{
    CHECK_OR_THROW(
        !(is_virtual_non_override_fxn_ && is_override_of_api_virtual_fxn_),
        "masala::base::api::getter::MasalaObjectAPIGetterDefinition",
        "MasalaObjectAPIGetterDefinition",
        "The " + getter_function_name + "() getter function was specified to be both a virtual function that "
        "does not override a base API class function, AND a virtual function that does ovreride a base API "
        "class function.  At most only one of these can be true."
    );
}

/// @brief Options constructor, to be called by derived classes in cases in which we have a
/// custom output type (e.g. enums).
/// @param[in] getter_function_name The name of the getter function that
///			   we are describing here.
/// @param[in] getter_function_description The description of the getter function that
///			   we are describing here.
/// @param[in] output_type_name The name of the output type.
/// @param[in] output_type_namespace The namespace of the output type.
/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
///            is NOT an override of a virtual function in a parent API class)?
/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
///            a function in a base API class?
MasalaObjectAPIGetterDefinition::MasalaObjectAPIGetterDefinition(
    std::string const & getter_function_name,
    std::string const & getter_function_description,
    std::string const & output_type_name,
    std::string const & output_type_namespace,
    bool const is_virtual_non_override_fxn,
    bool const is_override_of_api_virtual_fxn
) :
    masala::base::MasalaObject(),
    getter_function_name_(getter_function_name),
    getter_function_description_(getter_function_description),
    custom_output_type_name_( output_type_name ),
    custom_output_type_namespace_( output_type_namespace ),
    is_virtual_non_override_fxn_(is_virtual_non_override_fxn),
    is_override_of_api_virtual_fxn_(is_override_of_api_virtual_fxn)
{
    CHECK_OR_THROW(
        !(is_virtual_non_override_fxn_ && is_override_of_api_virtual_fxn_),
        "masala::base::api::getter::MasalaObjectAPIGetterDefinition",
        "MasalaObjectAPIGetterDefinition",
        "The " + getter_function_name + "() getter function was specified to be both a virtual function that "
        "does not override a base API class function, AND a virtual function that does ovreride a base API "
        "class function.  At most only one of these can be true."
    );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the getter function.
std::string const &
MasalaObjectAPIGetterDefinition::getter_function_name() const {
    return getter_function_name_;
}

/// @brief Get the getter function's description.
std::string const &
MasalaObjectAPIGetterDefinition::getter_function_description() const {
    return getter_function_description_;
}

/// @brief Does this class define a custom output type name?
bool
MasalaObjectAPIGetterDefinition::has_custom_output_type_name() const {
    return !custom_output_type_name_.empty();
}

/// @brief Get the custom output type name and namespace.
std::string
MasalaObjectAPIGetterDefinition::get_custom_output_type_namespace_and_name() const {
    return custom_output_type_namespace_ + "::" + custom_output_type_name_;
}

} // namespace getter
} // namespace api
} // namespace base
} // namespace masala