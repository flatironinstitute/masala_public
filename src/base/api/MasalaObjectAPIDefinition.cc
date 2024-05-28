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
#include <base/managers/plugin_module/MasalaPlugin.hh>
#include <base/managers/engine/MasalaEngine.hh>
#include <base/managers/engine/MasalaDataRepresentation.hh>
#include <base/managers/file_interpreter/MasalaFileInterpreter.hh>
#include <base/error/ErrorHandling.hh>

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
/// @param[in] has_protected_constructors Should the API class have protected constructors?
///            This allows the class to effetively act as a pure virtual base class, that cannot
///            itself be instantiated.
MasalaObjectAPIDefinition::MasalaObjectAPIDefinition(
    base::MasalaObject const & this_object,
    std::string const & api_class_description,
    bool const is_lightweight,
    bool const has_protected_constructors
) :
    masala::base::MasalaObject(),
    api_class_name_( this_object.class_name() ),
    api_class_namespace_( this_object.class_namespace() ),
    api_class_description_( api_class_description ),
    has_protected_constructors_( has_protected_constructors ),
    is_lightweight_( is_lightweight )
{
    using namespace masala::base::managers::plugin_module;
    using namespace masala::base::managers::engine;
    using namespace masala::base::managers::file_interpreter;
    {
        MasalaPlugin const * this_object_cast( dynamic_cast< MasalaPlugin const * >(&this_object) );
        is_plugin_class_ = ( this_object_cast != nullptr );
        if( is_plugin_class_ ) {
            plugin_categories_ = this_object_cast->get_categories();
            plugin_keywords_ = this_object_cast->get_keywords();
        }
    }
    {
        MasalaEngine const * this_object_engine_cast( dynamic_cast< MasalaEngine const * >(&this_object) );
        is_engine_class_ = ( this_object_engine_cast != nullptr );
        if( is_engine_class_ ) {
            engine_categories_ = this_object_engine_cast->get_engine_categories();
        }
    }
    {
        MasalaDataRepresentation const * this_object_datarep_cast( dynamic_cast< MasalaDataRepresentation const * >(&this_object) );
        is_data_representation_class_ = ( this_object_datarep_cast != nullptr );
        if( is_data_representation_class_ ) {
            data_representation_categories_ = this_object_datarep_cast->get_data_representation_categories();
            data_representation_present_properties_ = this_object_datarep_cast->get_present_data_representation_properties();
            data_representation_absent_properties_ = this_object_datarep_cast->get_absent_data_representation_properties();
            data_representation_possibly_present_properties_ = this_object_datarep_cast->get_possibly_present_data_representation_properties();
            data_representation_possibly_absent_properties_ = this_object_datarep_cast->get_possibly_absent_data_representation_properties();
            data_representation_compatible_engines_ = this_object_datarep_cast->get_compatible_masala_engines();
            data_representation_incompatible_engines_ = this_object_datarep_cast->get_incompatible_masala_engines();
        }
    }
    {
        MasalaFileInterpreter const * this_object_fileint_cast( dynamic_cast< MasalaFileInterpreter const * >(&this_object) );
        is_file_interpreter_class_ = ( this_object_fileint_cast != nullptr );
        if( is_file_interpreter_class_ ) {
            file_interpreter_file_descriptions_ = this_object_fileint_cast->get_file_descriptors();
            file_interpreter_file_extensions_ = this_object_fileint_cast->get_file_extensions();
        }
    }

    CHECK_OR_THROW( !( is_engine_class_ && is_data_representation_class_ ),
        class_namespace_static() + "::" + class_name_static(),
        "MasalaObjectAPIDefinition",
        "The " + api_class_name_ + " class was found to be both a MasalaEngine and a "
        "MasalaDataRepresentation.  Masala's build system does not permit this!"
    );
    CHECK_OR_THROW( !( is_engine_class_ && is_file_interpreter_class_ ),
        class_namespace_static() + "::" + class_name_static(),
        "MasalaObjectAPIDefinition",
        "The " + api_class_name_ + " class was found to be both a MasalaEngine and a "
        "MasalaFileInterpreter.  Masala's build system does not permit this!"
    );
    CHECK_OR_THROW( !( is_data_representation_class_ && is_file_interpreter_class_ ),
        class_namespace_static() + "::" + class_name_static(),
        "MasalaObjectAPIDefinition",
        "The " + api_class_name_ + " class was found to be both a MasalaDataRepresentation and a "
        "MasalaFileInterpreter.  Masala's build system does not permit this!"
    );
}

/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".
std::string
MasalaObjectAPIDefinition::class_name() const {
    return class_name_static();
}

/// @brief Every class can provide its own namespace.  This returns "masala::base::api".
std::string
MasalaObjectAPIDefinition::class_namespace() const {
    return class_namespace_static();
}

/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".  Static version.
/*static*/
std::string
MasalaObjectAPIDefinition::class_name_static() {
    return "MasalaObjectAPIDefinition";
}

/// @brief Every class can provide its own namespace.  This returns "masala::base::api".  Static version.
/*static*/
std::string
MasalaObjectAPIDefinition::class_namespace_static() {
    return "masala::base::api";
}

/// @brief Every class can provide its own namespace.  This returns "masala::base::api".  Static version.
/*static*/
std::string
MasalaObjectAPIDefinition::class_namespace_and_name_static() {
    return "masala::base::api::MasalaObjectAPIDefinition";
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

/// @brief Should the API class have protected constructors?
/// @details This allows the class to effetively act as a pure virtual base class, that cannot
/// itself be instantiated.
bool
MasalaObjectAPIDefinition::has_protected_constructors() const {
    return has_protected_constructors_;
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
    ss << "Has_Protected_Constructors:\t" << ( has_protected_constructors_ ? "TRUE" : "FALSE" ) << "\n";
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

    ss << "Is_Engine_Class:\t" << ( is_engine_class_ ? "TRUE" : "FALSE" ) << "\n";
    if( is_engine_class_ ) {
        ss << "\nENGINE_CATEGORIES:\n";
        for( auto const & category : engine_categories_ ) {
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
    }

    ss << "Is_Data_Representation_Class:\t" << ( is_data_representation_class_ ? "TRUE" : "FALSE" ) << "\n";
    if( is_data_representation_class_ ) {
        ss << "\nDATA_REPRESENTATION_CATEGORIES:\n";
        for( auto const & category : data_representation_categories_ ) {
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
        write_list_to_stream( ss, "DATA_REPRESENTATION_PRESENT_PROPERTIES", data_representation_present_properties_ );
        write_list_to_stream( ss, "DATA_REPRESENTATION_ABSENT_PROPERTIES", data_representation_absent_properties_ );
        write_list_to_stream( ss, "DATA_REPRESENTATION_POSSIBLY_PRESENT_PROPERTIES", data_representation_possibly_present_properties_ );
        write_list_to_stream( ss, "DATA_REPRESENTATION_POSSIBLY_ABSENT_PROPERTIES", data_representation_possibly_absent_properties_ );
        write_list_to_stream( ss, "DATA_REPRESENTATION_COMPATIBLE_ENGINES", data_representation_compatible_engines_ );
        write_list_to_stream( ss, "DATA_REPRESENTATION_INCOMPATIBLE_ENGINES", data_representation_incompatible_engines_ );
    }

	ss << "Is_File_Interpreter_Class:\t" << ( is_file_interpreter_class_ ? "TRUE" : "FALSE" ) << "\n";
	if( is_file_interpreter_class_ ) {
		write_list_to_stream( ss, "FILE_INTERPRETER_FILETYPE_DESCRIPTIONS", file_interpreter_file_descriptions_ );
		write_list_to_stream( ss, "FILE_INTERPRETER_FILETYPE_EXTENSIONS", file_interpreter_file_extensions_ );
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
        { "Is_Plugin_Class", is_plugin_class_ },
        { "Is_Engine_Class", is_engine_class_ },
		{ "Is_File_Interpreter_Class", is_file_interpreter_class_ },
        { "Is_Data_Representation_Class", is_data_representation_class_ },
        { "Has_Protected_Constructors", has_protected_constructors_ }
    };

    if( is_plugin_class_ ) {
        json_api[ "Plugin_Categories" ] = plugin_categories_;
        json_api[ "Plugin_Keywords" ] = plugin_keywords_;
    }
    if( is_engine_class_ ) {
        json_api[ "Engine_Categories" ] = engine_categories_;
    }
    if( is_data_representation_class_ ) {
        json_api[ "Data_Representation_Categories" ] = data_representation_categories_;
        json_api[ "Data_Representation_Present_Properties" ] = data_representation_present_properties_;
        json_api[ "Data_Representation_Absent_Properties" ] = data_representation_absent_properties_;
        json_api[ "Data_Representation_Possibly_Present_Properties" ] = data_representation_possibly_present_properties_;
        json_api[ "Data_Representation_Possibly_Absent_Properties" ] = data_representation_possibly_absent_properties_;
        json_api[ "Data_Representation_Compatible_Engines" ] = data_representation_compatible_engines_;
        json_api[ "Data_Representation_Incompatible_Engines" ] = data_representation_incompatible_engines_;
    }

	if( is_file_interpreter_class_ ) {
        json_api[ "File_Interpreter_FileType_Descriptions" ] = file_interpreter_file_descriptions_;
        json_api[ "File_Interpreter_FileType_Extensions" ] = file_interpreter_file_extensions_;
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

/// @brief Get the categories that this object is in, if it is a MasalaEngine object.
/// @details A category is hierarchical, listed as a vector of strings.  For instance,
/// Fruit->CitrusFruit->Oranges would be stored as { {"Fruit", "CitrusFruit", "Oranges"} }.
/// An object can be in more than one category.
std::vector< std::vector< std::string > > const &
MasalaObjectAPIDefinition::engine_categories() const {
    return engine_categories_;
}

/// @brief Get the categories that this object is in, if it is a MasalaDataRepresentation
/// object.
std::vector< std::vector< std::string > > const &
MasalaObjectAPIDefinition::data_representation_categories() const {
    return data_representation_categories_;
}

/// @brief Get the properties that this object definitely has, if it is a
/// MasalaDataRepresentation object.
std::vector< std::string > const &
MasalaObjectAPIDefinition::data_representation_present_properties() const {
    return data_representation_present_properties_;
}

/// @brief Get the properties that this object definitely does not have , if it is a
/// MasalaDataRepresentation object.
std::vector< std::string > const &
MasalaObjectAPIDefinition::data_representation_absent_properties() const {
    return data_representation_absent_properties_;
}

/// @brief Get the properties that this object could have, if it is a
/// MasalaDataRepresentation object.
std::vector< std::string > const &
MasalaObjectAPIDefinition::data_representation_possibly_present_properties() const {
    return data_representation_possibly_present_properties_;
}

/// @brief Get the properties that this object could be lacking, if it is a
/// MasalaDataRepresentation object.
std::vector< std::string > const &
MasalaObjectAPIDefinition::data_representation_possibly_absent_properties() const {
    return data_representation_possibly_absent_properties_;
}

/// @brief Get the MasalaEngines that this object is definitely compatible with, if it is
/// a MasalaDataRepresentation object.
std::vector< std::string > const &
MasalaObjectAPIDefinition::data_representation_compatible_engines() const {
    return data_representation_compatible_engines_;
}

/// @brief Get the MasalaEngines that this object is definitely not compatible with, if it
/// is a MasalaDataRepresentation object.
std::vector< std::string > const &
MasalaObjectAPIDefinition::data_representation_incompatible_engines() const {
    return data_representation_incompatible_engines_;
}

/// @brief Get the descriptions of the file type(s) that this file interpreter interprets, if this
/// is a file interpreter class.
std::vector< std::string > const &
MasalaObjectAPIDefinition::file_interpreter_file_descriptions() const {
	return file_interpreter_file_descriptions_;
}

/// @brief Get the file extension(s) of the file type(s) that this file interpreter interprets, if this
/// is a file interpreter class.
std::vector< std::string > const &
MasalaObjectAPIDefinition::file_interpreter_file_extensions() const {
	return file_interpreter_file_extensions_;
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

/// @brief Given a vector of strings, write a header followed by the vector as a comma-separated list,
/// or [NONE] if the vector is empty.
void
MasalaObjectAPIDefinition::write_list_to_stream(
    std::ostringstream & ss,
    std::string const & header,
    std::vector< std::string > const & list_to_write
) const {
    ss << "\n" << header << ":\n";
    bool first( true );
    if( list_to_write.empty() ) {
        ss << "[NONE]\n";
    } else {
        for( auto const & entry : list_to_write ) {
            if( first ) {
                first = false;
            } else {
                ss << ", ";
            }
            ss << entry;
        }
        ss << "\n";
    }
}

} // namespace api
} // namespace base
} // namespace masala