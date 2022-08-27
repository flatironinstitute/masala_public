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

/// @file src/base/api/MasalaObjectAPIDefinition.cc
/// @brief A class that stores the definition for the API for an object.  Used
/// to auto-generate the public C++ headers, plus the bindings for Python
/// or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/MasalaObjectAPIDefinition.hh>

// Base headers
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>

// STL headers
#include <sstream>

namespace base {
namespace api {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor.
/// @param[in] api_class_name The name of the class for which we're
///            providing an API definition.
/// @param[in] api_class_description The description of the class for which
///			   we're providing an API definition.
MasalaObjectAPIDefinition::MasalaObjectAPIDefinition(
    std::string const & api_class_name,
    std::string const & api_class_description
) :
    base::MasalaObject(),
    api_class_name_( api_class_name ),
    api_class_description_( api_class_description )
{}

/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".
std::string
MasalaObjectAPIDefinition::class_name() const {
    return "MasalaObjectAPIDefinition";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a human-readable description of the API for a module.
std::string
MasalaObjectAPIDefinition::get_human_readable_description() const {
    using namespace base::api::constructor;
    using namespace base::api::setter;
    using namespace base::api::getter;
    using namespace base::api::work_function;

    std::ostringstream ss;
    ss << api_class_name_ << " API:\n\n";
    ss << api_class_description_ << "\n";

    if( !constructors_.empty() ) {
        ss << "\nCONSTRUCTORS\n";
        for(
            std::vector< MasalaObjectAPIConstructorDefinitionCSP >::const_iterator it( constructors_.begin() );
            it != constructors_.end();
            ++it
        ) {
            ss << "\n" << (*it)->get_constructor_human_readable_description();
        }
    }

    if( !setters_.empty() ) {
        ss << "\nSETTERS\n";
        for(
            std::vector< MasalaObjectAPISetterDefinitionCSP >::const_iterator it( setters_.begin() );
            it != setters_.end();
            ++it
        ) {
            ss << "\n" << (*it)->get_setter_human_readable_description();
        }
    }

    if( !getters_.empty() ) {
        ss << "\nGETTERS\n";
        for(
            std::vector< MasalaObjectAPIGetterDefinitionCSP >::const_iterator it( getters_.begin() );
            it != getters_.end();
            ++it
        ) {
            ss << "\n" << (*it)->get_getter_human_readable_description();
        }
    }

    if( !work_functions_.empty() ) {
        ss << "\nWORK FUNCTIONS\n";
        for(
            std::vector< MasalaObjectAPIWorkFunctionDefinitionCSP >::const_iterator it( work_functions_.begin() );
            it != work_functions_.end();
            ++it
        ) {
            ss << "\n" << (*it)->get_work_function_human_readable_description();
        }
    }

    return ss.str();
}

} // namespace api
} // namespace base