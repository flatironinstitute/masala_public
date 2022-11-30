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

/// @file src/base/api/setter/MasalaObjectAPISetterDefinition.cc
/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/setter/MasalaObjectAPISetterDefinition.hh>

namespace masala {
namespace base {
namespace api {
namespace setter {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor, to be called by derived classes.
/// @param[in] setter_function_name The name of the setter function that
///			   we are describing here.
/// @param[in] setter_function_description The description of the setter function that
///			   we are describing here.
MasalaObjectAPISetterDefinition::MasalaObjectAPISetterDefinition(
    std::string const & setter_function_name,
    std::string const & setter_function_description
) :
    masala::base::MasalaObject(),
    setter_function_name_(setter_function_name),
    setter_function_description_(setter_function_description)
{}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the setter function.
std::string const &
MasalaObjectAPISetterDefinition::setter_function_name() const {
    return setter_function_name_;
}

/// @brief Get the setter function's description.
std::string const &
MasalaObjectAPISetterDefinition::setter_function_description() const {
    return setter_function_description_;
}

} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
