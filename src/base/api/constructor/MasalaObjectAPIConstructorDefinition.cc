/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
MasalaObjectAPIConstructorDefinition::MasalaObjectAPIConstructorDefinition(
    std::string const & constructor_name,
    std::string const & constructor_description
) :
    masala::base::MasalaObject(),
    constructor_name_(constructor_name),
    constructor_description_(constructor_description)
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

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala