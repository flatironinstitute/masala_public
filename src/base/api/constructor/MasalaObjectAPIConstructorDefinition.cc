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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition.cc
/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>

namespace masala {
namespace base {
namespace api {
namespace constructor {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor, to be called by derived classes.
/// @param[in] constructor_name The name of the constructor that
///			   we are describing here.  Should match the T0 class name.
/// @param[in] constructor_description The description of the constructor that
///			   we are describing here.
/// @param[in] is_protected_constructor Should the API's class constructor be
///            protected?  This allows the API class to act like a pure virtual
///            base class, preventing instantiation.
MasalaObjectAPIConstructorDefinition::MasalaObjectAPIConstructorDefinition(
    std::string const & constructor_name,
    std::string const & constructor_description,
    bool const is_protected_constructor
) :
    masala::base::MasalaObject(),
    constructor_name_(constructor_name),
    constructor_description_(constructor_description),
    is_protected_constructor_(is_protected_constructor)
{}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the constructor.  Should match the T0 class name.
std::string const &
MasalaObjectAPIConstructorDefinition::constructor_name() const {
    return constructor_name_;
}

/// @brief Get the constructor's description.
std::string const &
MasalaObjectAPIConstructorDefinition::constructor_description() const {
    return constructor_description_;
}

/// @brief Should the API's class constructor be protected?
/// @details This allows the API class to act like a pure virtual base class, preventing instantiation.
bool
MasalaObjectAPIConstructorDefinition::is_protected_constructor() const {
    return is_protected_constructor_;
}

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala