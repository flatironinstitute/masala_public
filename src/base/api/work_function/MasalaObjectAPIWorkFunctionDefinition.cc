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

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.cc
/// @brief A class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>

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
MasalaObjectAPIWorkFunctionDefinition::MasalaObjectAPIWorkFunctionDefinition(
    std::string const & work_function_name,
    std::string const & work_function_description,
    bool const is_const
) :
    base::MasalaObject(),
    work_function_name_(work_function_name),
    work_function_description_(work_function_description),
    is_const_(is_const)
{}

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

} // namespace work_function
} // namespace api
} // namespace base