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

/// @file src/base/MasalaObject.cc
/// @brief A base class for all Masala objects.
/// @details Masala objects all define certain functions, such as write_to_tracer(),
/// class_name(), and class_namespace().
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/MasalaObject.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

// STL headers
#include <string>

namespace masala {
namespace base {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns result of class_namespace() + "::" + class_name().
std::string
MasalaObject::class_namespace_and_name() const {
    return class_namespace() + "::" + class_name();
}

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
    return masala::base::api::MasalaObjectAPIDefinitionCWP();
}

/// @brief Writes text to the tracer, using the MasalaTracerManager.
/// @details Threadsafe.
void
MasalaObject::write_to_tracer(
    std::string const & message
) const {
    masala::base::managers::tracer::MasalaTracerManagerHandle const tracer_handle( masala::base::managers::tracer::MasalaTracerManager::get_instance() );
    std::string const tracername( class_namespace_and_name() );
    if( tracer_handle->tracer_is_enabled( tracername ) ) {
        tracer_handle->write_to_tracer( tracername, message, true );
    }
}

/// @brief Get a list of categories that this object could be sorted into.
/// @details This is for auto-generation of hierarchical documentation and user interfaces.
/// Categories could be something like std::vector< std::string >{ "Manipulators", "Proteins", "Design" }.
/// An object may be in more than one category.  The default behaviour, overridable by sub-
/// classes, is to provide an empty list.
std::vector< std::vector< std::string > >
MasalaObject::get_categories() const {
    return std::vector< std::vector < std::string > >();
}

/// @brief Get a list of keywords associated with this object.
/// @details This is also for auto-generation of documentation or user interfaces, to allow
/// discoverability of functionality.  Unlike categories, which are hierarchical, keywords
/// have no hierarchy.  The default implementation produces an empty list.
std::set< std::string >
MasalaObject::get_keywords() const {
    return std::set< std::string >();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Create a configuration object for this object.
/// @details Can trigger read from disk.  Private since it intended to be called only the first time
/// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
/// implementation throws.  Must be implemented by derived classes that have configurations.
base::managers::configuration::ConfigurationBaseCSP
MasalaObject::load_configuration(
    masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const &
) const {
    MASALA_THROW( class_namespace_and_name(), "load_configuration", "The load_configuration() function has not been implemented for " + class_name() + "." );
}

} // namespace base
} // namespace masala
