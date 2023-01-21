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
#include <base/managers/plugin_module/MasalaPlugin.hh>

// External headers
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers
#include <sstream>

namespace masala {
namespace base {
namespace api {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor.
/// @param[in] this_object The object for which we're generating a description.
/// @param[in] api_class_description The description of the class for which
///			   we're providing an API definition.
/// @param[in] is_lightweight Is this the API definition for a lightweight
/// 		   object that could be stack-allocated?
MasalaObjectAPIDefinition::MasalaObjectAPIDefinition(
    base::MasalaObject const & this_object,
    std::string const & api_class_description,
    bool const is_lightweight
) :
    masala::base::MasalaObject(),
    api_class_name_( this_object.class_name() ),
    api_class_namespace_( this_object.class_namespace() ),
    api_class_description_( api_class_description ),
    is_lightweight_( is_lightweight )
{
    using namespace base::managers::plugin_module;
    MasalaPlugin const * this_object_cast( dynamic_cast< MasalaPlugin const * >(&this_object) );
    is_plugin_class_ = ( this_object_cast != nullptr );
    if( is_plugin_class_ ) {
        plugin_categories_ = this_object_cast->get_categories();
        plugin_keywords_ = this_object_cast->get_keywords();
    }
}

/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".
std::string
MasalaObjectAPIDefinition::class_name() const {
    return "MasalaObjectAPIDefinition";
}

/// @brief Every class can provide its own namespace.  This returns "masala::base::api".
std::string
MasalaObjectAPIDefinition::class_namespace() const {
    return "masala::base::api";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the class for which this object stores an API description.
std::string const &
MasalaObjectAPIDefinition::api_class_name() const {
    return api_class_name_;
}

/// @brief Get the namespace of the class for which this object stores an API description.
std::string const &
MasalaObjectAPIDefinition::api_class_namespace() const {
    return api_class_namespace_;
}

/// @brief Get the namespace and name of the class for which this object stores an API description.
std::string
MasalaObjectAPIDefinition::api_class_namespace_and_name() const {
    return api_class_namespace_ + "::" + api_class_name_;
}

/// @brief Get the description of the class for which this object stores an API description.
std::string const &
MasalaObjectAPIDefinition::api_class_description() const {
    return api_class_description_;
}

/// @brief Get a human-readable description of the API for a module.
/// @details Note that this does not cache the generated string, but generates it anew
/// each time.
std::string
MasalaObjectAPIDefinition::get_human_readable_description() const {
    using namespace masala::base::api::constructor;
    using namespace masala::base::api::setter;
    using namespace masala::base::api::getter;
    using namespace masala::base::api::work_function;

    std::ostringstream ss;
    ss << api_class_namespace_ << "::" << api_class_name_ << " API:\n\n";
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

    ss << "\nPROPERTIES\n";
    ss << "Is_Lightweight:\t" << ( is_lightweight_ ? "TRUE" : "FALSE" ) << "\n";
    ss << "Is_Plugin_Class:\t" << ( is_plugin_class_ ? "TRUE" : "FALSE" ) << "\n";

    if( is_plugin_class_ ) {
        ss << "\nPLUGIN_CATEGORIES:\n";
        for( auto const & category : plugin_categories_ ) {
            bool first( true );
            for( auto const & level : category ) {
                if( first ) {
                    first = false;
                } else {
                    ss << ", ";
                }
                ss << level;
            }
            ss << "\n";
        }

        ss << "\nPLUGIN_KEYWORDS:\n";
        {
            bool first( true );
            for( auto const & keyword : plugin_keywords_ ) {
                if( first ) {
                    first = false;
                } else {
                    ss << ", ";
                }
                ss << keyword;
            }
            ss << "\n";
        }
    }

    return ss.str();
}

/// @brief Get a JSON object describing the API for a module.
/// @details Note that this does not cache the generated JSON object, but generates it anew
/// each time.
MASALA_SHARED_POINTER< nlohmann::json >
MasalaObjectAPIDefinition::get_json_description() const {
    MASALA_SHARED_POINTER< nlohmann::json > json_ptr( masala::make_shared< nlohmann::json >() );
    nlohmann::json & json_api( *json_ptr );

    json_api["Title"] = "API description";
    json_api["Module"] = api_class_name_;
    json_api["ModuleNamespace"] = api_class_namespace_;
    json_api["Description"] = api_class_description_;
    json_api["Constructors"] = get_json_description_for_constructors();
    json_api["Setters"] = get_json_description_for_setters();
    json_api["Getters"] = get_json_description_for_getters();
    json_api["WorkFunctions"] = get_json_description_for_work_functions();

    json_api["Properties"] = std::map< std::string, bool >{
        { "Is_Lightweight", is_lightweight_ },
        { "Is_Plugin_Class", is_plugin_class_ }
    };

    if( is_plugin_class_ ) {
        json_api[ "Plugin_Categories" ] = plugin_categories_;
        json_api[ "Plugin_Keywords" ] = plugin_keywords_;
    } 

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
    masala::base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP constructor_in
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
    masala::base::api::setter::MasalaObjectAPISetterDefinitionCSP setter_in
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
    masala::base::api::getter::MasalaObjectAPIGetterDefinitionCSP getter_in
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
    masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP work_function_in
) {
    work_functions_.emplace_back( work_function_in );
}

/// @brief Get the categories that this object is in, if it is a plugin object.
/// @details A category is hierarchical, listed as a vector of strings.  For instance,
/// Fruit->CitrusFruit->Oranges would be stored as { {"Fruit", "CitrusFruit", "Oranges"} }.
/// An object can be in more than one category.
std::vector< std::vector< std::string > > const &
MasalaObjectAPIDefinition::plugin_categories() const {
    return plugin_categories_;
}

/// @brief Get the keywords for this object, if it is a plugin object.
std::vector< std::string > const &
MasalaObjectAPIDefinition::plugin_keywords() const {
    return plugin_keywords_;
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
    for( masala::base::Size i(0), imax(constructors_.size()); i<imax; ++i ) {
        constructor_jsons[i] = constructors_[i]->get_constructor_json_description();
    }

    json_api["Constructor_APIs"] = constructor_jsons;
    return json_api;
}

/// @brief Generate JSON descriptions for all of the setters.
/// @details Nothing is cached here, so this will generate a new JSON object
/// each time it is called.  This isn't super fast.
nlohmann::json
MasalaObjectAPIDefinition::get_json_description_for_setters() const {
    nlohmann::json json_api;
    json_api["N_Setters"] = setters_.size();

    std::vector< nlohmann::json > setter_jsons( setters_.size() );
    for( masala::base::Size i(0), imax(setters_.size()); i<imax; ++i ) {
        setter_jsons[i] = setters_[i]->get_setter_json_description();
    }

    json_api["Setter_APIs"] = setter_jsons;
    return json_api;
}

/// @brief Generate JSON descriptions for all of the getters.
/// @details Nothing is cached here, so this will generate a new JSON object
/// each time it is called.  This isn't super fast.
nlohmann::json
MasalaObjectAPIDefinition::get_json_description_for_getters() const {
    nlohmann::json json_api;
    json_api["N_Getters"] = getters_.size();

    std::vector< nlohmann::json > getter_jsons( getters_.size() );
    for( masala::base::Size i(0), imax(getters_.size()); i<imax; ++i ) {
        getter_jsons[i] = getters_[i]->get_getter_json_description();
    }

    json_api["Getter_APIs"] = getter_jsons;
    return json_api;
}

/// @brief Generate JSON descriptions for all of the work functions.
/// @details Nothing is cached here, so this will generate a new JSON object
/// each time it is called.  This isn't super fast.
nlohmann::json
MasalaObjectAPIDefinition::get_json_description_for_work_functions() const {
    nlohmann::json json_api;
    json_api["N_Work_Functions"] = work_functions_.size();

    std::vector< nlohmann::json > work_function_jsons( work_functions_.size() );
    for( masala::base::Size i(0), imax(work_functions_.size()); i<imax; ++i ) {
        work_function_jsons[i] = work_functions_[i]->get_work_function_json_description();
    }

    json_api["Work_Function_APIs"] = work_function_jsons;
    return json_api;
}

} // namespace api
} // namespace base
} // namespace masala