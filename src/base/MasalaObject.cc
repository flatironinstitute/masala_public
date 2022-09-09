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

/// @file src/core/pose/Pose.cc
/// @brief A class representing a molecular structure.
/// @details Poses store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/MasalaObject.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers
#include <string>

namespace base {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a string for the error message header, of the form:
/// "Error in <namespace>::<class name>::<function name>(): ".
/// @param[in] function_name The function from which we're calling this function,
/// used to construct the string.  This should just be a function name, without
/// namespace, class, colons, return type, parameters, or parentheses.
/// @note This cannot be called from constructors!
std::string
MasalaObject::get_errmsg_header(
    std::string const & function_name
) const {
    return "Error in " + class_namespace() + "::" + class_name() + "::" + function_name + "(): ";
}

/// @brief Does this object return an API definition?
/// @details By default, returns false.  Derived classes might, though.
bool
MasalaObject::has_api_definition() {
    return get_api_definition().lock() != nullptr;
}

/// @brief Get an object describing the API for this object.
/// @details Default implementation returns nullptr.  May be overridden by
/// derived objects.
base::api::MasalaObjectAPIDefinitionCWP
MasalaObject::get_api_definition() {
    return base::api::MasalaObjectAPIDefinitionCWP();
}

/// @brief Returns result of class_namespace() + "::" + class_name().
std::string
MasalaObject::class_namespace_and_name() const {
    return class_namespace() + "::" + class_name();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Create a configuration object for this object.
/// @details Can trigger read from disk.  Private since it intended to be called only the first time
/// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
/// implementation throws.  Must be implemented by derived classes that have configurations.
base::managers::configuration::ConfigurationBaseCSP
MasalaObject::load_configuration() const {
    MASALA_THROW( class_namespace_and_name(), "load_configuration", "The load_configuration() function has not been implemented for " + class_name() + "." );
}

} // namespace base
