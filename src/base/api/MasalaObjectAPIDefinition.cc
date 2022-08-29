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

// External headers
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

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

/// @brief Every class can provide its own namespace.  This returns "base::api".
std::string
MasalaObjectAPIDefinition::class_namespace() const {
    return "base::api";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a human-readable description of the API for a module.
/// @details Note that this does not cache the generated string, but generates it anew
/// each time.
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

/// @brief Get a JSON object describing the API for a module.
/// @details Note that this does not cache the generated JSON object, but generates it anew
/// each time.
std::shared_ptr< nlohmann::json >
MasalaObjectAPIDefinition::get_json_description() const {
    std::shared_ptr< nlohmann::json > json_ptr( std::make_shared< nlohmann::json >() );
    nlohmann::json & json_api( *json_ptr );

    json_api["Title"] = "API description";
    json_api["Module"] = api_class_name_;
    json_api["Description"] = api_class_description_;
    json_api["Constructors"] = get_json_description_for_constructors();
    // json_api["Setters"] = get_json_description_for_setters();
    // json_api["Getters"] = get_json_description_for_getters();
    // json_api["WorkFunctions"] = get_json_description_for_work_functions();

    return json_ptr;
}

/// @brief Begin iterator for the constructors.
std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::constructors_begin() const {
    return constructors_.cbegin();
}

/// @brief End iterator for the constructors.
std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::constructors_end() const {
    return constructors_.cend();
}

/// @brief Number of constructors.
base::Size
MasalaObjectAPIDefinition::n_constructors() const {
    return constructors_.size();
}

/// @brief Add a constructor.
void
MasalaObjectAPIDefinition::add_constructor(
    base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP constructor_in
) {
    constructors_.emplace_back( constructor_in );
}

/// @brief Begin iterator for the setters.
std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::setters_begin() const {
    return setters_.cbegin();
}

/// @brief End iterator for the setters.
std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::setters_end() const {
    return setters_.cend();
}

/// @brief Number of setters.
base::Size
MasalaObjectAPIDefinition::n_setters() const {
    return setters_.size();
}

/// @brief Add a setter.
void
MasalaObjectAPIDefinition::add_setter(
    base::api::setter::MasalaObjectAPISetterDefinitionCSP setter_in
) {
    setters_.emplace_back( setter_in );
}

/// @brief Begin iterator for the getters.
std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::getters_begin() const {
    return getters_.cbegin();
}

/// @brief End iterator for the getters.
std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::getters_end() const {
    return getters_.cend();
}

/// @brief Number of getters.
base::Size
MasalaObjectAPIDefinition::n_getters() const {
    return getters_.size();
}

/// @brief Add a getter.
void
MasalaObjectAPIDefinition::add_getter(
    base::api::getter::MasalaObjectAPIGetterDefinitionCSP getter_in
) {
    getters_.emplace_back( getter_in );
}

/// @brief Begin iterator for the work functions.
std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::work_functions_begin() const {
    return work_functions_.cbegin();
}

/// @brief End iterator for the work functions.
std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator
MasalaObjectAPIDefinition::work_functions_end() const {
    return work_functions_.cend();
}

/// @brief Number of work functions.
base::Size
MasalaObjectAPIDefinition::n_work_functions() const {
    return work_functions_.size();
}

/// @brief Add a work function.
void
MasalaObjectAPIDefinition::add_work_function(
    base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP work_function_in
) {
    work_functions_.emplace_back( work_function_in );
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Generate JSON descriptions for all of the constructors.
/// @details Nothing is cached here, so this will generate a new JSON object
/// each time it is called.  This isn't super fast.
nlohmann::json
MasalaObjectAPIDefinition::get_json_description_for_constructors() const {
    nlohmann::json json_api;
    json_api["N_Constructors"] = constructors_.size();

    std::vector< nlohmann::json > constructor_jsons( constructors_.size() );
    for( base::Size i(1), imax(constructors_.size()); i<=imax; ++i ) {
        constructor_jsons[i] = constructors_[i]->get_constructor_json_description();
    }

    json_api["Constructor_APIs"] = constructor_jsons;
    return json_api;
}

} // namespace api
} // namespace base