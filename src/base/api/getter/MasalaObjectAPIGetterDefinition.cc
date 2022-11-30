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

/// @file src/base/api/getter/MasalaObjectAPIGetterDefinition.cc
/// @brief A class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/getter/MasalaObjectAPIGetterDefinition.hh>

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
MasalaObjectAPIGetterDefinition::MasalaObjectAPIGetterDefinition(
    std::string const & getter_function_name,
    std::string const & getter_function_description
) :
    masala::base::MasalaObject(),
    getter_function_name_(getter_function_name),
    getter_function_description_(getter_function_description)
{}

/// @brief Options constructor, to be called by derived classes in cases in which we have a
/// custom output type (e.g. enums).
/// @param[in] getter_function_name The name of the getter function that
///			   we are describing here.
/// @param[in] getter_function_description The description of the getter function that
///			   we are describing here.
/// @param[in] output_type_name The name of the output type.
/// @param[in] output_type_namespace The namespace of the output type.
MasalaObjectAPIGetterDefinition::MasalaObjectAPIGetterDefinition(
    std::string const & getter_function_name,
    std::string const & getter_function_description,
    std::string const & output_type_name,
    std::string const & output_type_namespace
) :
    masala::base::MasalaObject(),
    getter_function_name_(getter_function_name),
    getter_function_description_(getter_function_description),
    custom_output_type_name_( output_type_name ),
    custom_output_type_namespace_( output_type_namespace )
{}

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