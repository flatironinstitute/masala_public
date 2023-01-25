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

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.cc
/// @brief A class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>

// Base headers
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace api {
namespace work_function {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

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
MasalaObjectAPIWorkFunctionDefinition::MasalaObjectAPIWorkFunctionDefinition(
    std::string const & work_function_name,
    std::string const & work_function_description,
    bool const is_const,
    bool const returns_this_ref,
    bool const is_virtual_non_override_fxn,
    bool const is_override_of_api_virtual_fxn
) :
    masala::base::MasalaObject(),
    work_function_name_(work_function_name),
    work_function_description_(work_function_description),
    is_const_(is_const),
    returns_this_ref_(returns_this_ref),
    is_virtual_non_override_fxn_(is_virtual_non_override_fxn),
    is_override_of_api_virtual_fxn_(is_override_of_api_virtual_fxn)
{
    CHECK_OR_THROW(
        !(is_virtual_non_override_fxn_ && is_override_of_api_virtual_fxn_),
        "masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinition",
        "MasalaObjectAPIWorkFunctionDefinition",
        "The " + work_function_name + "() work function was specified to be both a virtual function that "
        "does not override a base API class function, AND a virtual function that does ovreride a base API "
        "class function.  At most only one of these can be true."
    );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the work function.
std::string const &
MasalaObjectAPIWorkFunctionDefinition::work_function_name() const {
    return work_function_name_;
}

/// @brief Get the work function's description.
std::string const &
MasalaObjectAPIWorkFunctionDefinition::work_function_description() const {
    return work_function_description_;
}

/// @brief Get whether this work function is a const function.
bool
MasalaObjectAPIWorkFunctionDefinition::is_const() const {
    return is_const_;
}

/// @brief Does this function return reference (or const reference) to this?
bool
MasalaObjectAPIWorkFunctionDefinition::returns_this_ref() const {
    return returns_this_ref_;
}

/// @brief Is this function a virtual function that does NOT override
/// a function in a base class that has a defined API?
bool
MasalaObjectAPIWorkFunctionDefinition::is_virtual_non_override_fxn() const {
    return is_virtual_non_override_fxn_;
}

/// @brief Is this function an override of a virtual function in a base
/// class that has a defined API?
bool
MasalaObjectAPIWorkFunctionDefinition::is_override_of_api_virtual_fxn() const {
    return is_override_of_api_virtual_fxn_;
}

} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala
