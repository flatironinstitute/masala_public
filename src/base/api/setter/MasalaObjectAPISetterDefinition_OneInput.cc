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

/// @file src/base/api/MasalaObjectAPISetterDefinition_OneInput.cc
/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.hh>

namespace base {
namespace api {
namespace setter {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////
    
/// @brief Every class can name itself.  This returns "MasalaObjectAPISetterDefinition_OneInput".
std::string
MasalaObjectAPISetterDefinition_OneInput::class_name() const {
    return "MasalaObjectAPISetterDefinition_OneInput";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a human-readable description of this setter.
/// @details Used for auto-generated help.  Must be implemented by
/// derived classes.
std::string
MasalaObjectAPISetterDefinition_OneInput::get_setter_human_readable_description() const {
    TODO TODO TODO
}

/// @brief Get a JSON description of this setter.
/// @details Used for auto-generated help.  Must be implemented by
/// derived classes.
// json_return_type ???
// MasalaObjectAPISetterDefinition_OneInput::get_setter_json_description() const {
//    
//}
// TODO TODO TODO

} // namespace setter
} // namespace api
} // namespace base