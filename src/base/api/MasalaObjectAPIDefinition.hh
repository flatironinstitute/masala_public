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

/// @file src/base/api/MasalaObjectAPIDefinition.hh
/// @brief A class that stores the definition for the API for an object.  Used
/// to auto-generate the public C++ headers, plus the bindings for Python
/// or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaObjectAPIDefinition_hh
#define Masala_src_base_api_MasalaObjectAPIDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/api/MasalaObjectAPIDefinition.fwd.hh>

// Base headers.
#include <base/types.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.fwd.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_TwoInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ThreeInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_FourInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_FiveInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ThreeInput.tmpl.hh>

// External headers.
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// STL headers.
#include <vector>
#include <string>

namespace masala {
namespace base {
namespace api {

/// @brief A class that stores the definition for the API for an object.  Used
/// to auto-generate the public C++ headers, plus the bindings for Python
/// or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPIDefinition : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIDefinition() = delete;

	/// @brief Options constructor.
	/// @param[in] this_object The object for which we're generating a description.
	/// @param[in] api_class_description The description of the class for which
	///			   we're providing an API definition.
	/// @param[in] is_lightweight Is this the API definition for a lightweight
	/// 		   object that could be stack-allocated?
	/// @param[in] has_protected_constructors Should the API class have protected constructors?
	///            This allows the class to effetively act as a pure virtual base class, that cannot
	///            itself be instantiated.
	MasalaObjectAPIDefinition(
		base::MasalaObject const & this_object,
		std::string const & api_class_description,
		bool const is_lightweight,
		bool const has_protected_constructors
	);

	/// @brief Copy constructor.
	MasalaObjectAPIDefinition( MasalaObjectAPIDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPIDefinition() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api".
	std::string class_namespace() const override;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".  Static version.
	static std::string class_name_static();

	/// @brief Every class can provide its own namespace.  This returns "masala::base::api".  Static version.
	static std::string class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC TEMPLATE MEMBER FUNCTIONS FOR ACCESSING SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a zero-parameter setter definition.
	/// @returns Nullptr if the function doesn't exist; a const weak pointer
	/// to the function otherwise.
	inline
	masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
	get_zeroinput_setter_function(
		std::string const & function_name
	) const {
		for( auto const & setter: setters_ ) {
			if( setter->num_input_parameters() == 0 && setter->setter_function_name() == function_name ) {
				return setter;
			}
		}
		return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
	}

	/// @brief Get a one-parameter setter definition.
	/// @returns Nullptr if the function doesn't exist; a const weak pointer
	/// to the function otherwise.
	template< typename P1 >
	inline
	masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
	get_oneinput_setter_function(
		std::string const & function_name
	) const {
		using namespace setter;

		for( auto const & setter: setters_ ) {
			if( setter->num_input_parameters() == 1 && setter->setter_function_name() == function_name ) {
				MasalaObjectAPISetterDefinition_OneInputCSP< P1 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_OneInput< P1 > const >( setter ) );
				if( setter_cast != nullptr ) {
					return setter;
				}
			}
		}
		return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
	}

	/// @brief Get a two-parameter setter definition.
	/// @returns Nullptr if the function doesn't exist; a const weak pointer
	/// to the function otherwise.
	template< typename P1, typename P2 >
	inline
	masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
	get_twoinput_setter_function(
		std::string const & function_name
	) const {
		using namespace setter;

		for( auto const & setter: setters_ ) {
			if( setter->num_input_parameters() == 2 && setter->setter_function_name() == function_name ) {
				MasalaObjectAPISetterDefinition_TwoInputCSP< P1, P2 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_TwoInput< P1, P2 > const >( setter ) );
				if( setter_cast != nullptr ) {
					return setter;
				}
			}
		}
		return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
	}

	/// @brief Get a three-parameter setter definition.
	/// @returns Nullptr if the function doesn't exist; a const weak pointer
	/// to the function otherwise.
	template< typename P1, typename P2, typename P3 >
	inline
	masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
	get_threeinput_setter_function(
		std::string const & function_name
	) const {
		using namespace setter;

		for( auto const & setter: setters_ ) {
			if( setter->num_input_parameters() == 3 && setter->setter_function_name() == function_name ) {
				MasalaObjectAPISetterDefinition_ThreeInputCSP< P1, P2, P3 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_ThreeInput< P1, P2, P3 > const >( setter ) );
				if( setter_cast != nullptr ) {
					return setter;
				}
			}
		}
		return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
	}

	/// @brief Get a four-parameter setter definition.
	/// @returns Nullptr if the function doesn't exist; a const weak pointer
	/// to the function otherwise.
	template< typename P1, typename P2, typename P3, typename P4 >
	inline
	masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
	get_fourinput_setter_function(
		std::string const & function_name
	) const {
		using namespace setter;

		for( auto const & setter: setters_ ) {
			if( setter->num_input_parameters() == 4 && setter->setter_function_name() == function_name ) {
				MasalaObjectAPISetterDefinition_FourInputCSP< P1, P2, P3, P4 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_FourInput< P1, P2, P3, P4 > const >( setter ) );
				if( setter_cast != nullptr ) {
					return setter;
				}
			}
		}
		return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
	}

	/// @brief Get a five-parameter setter definition.
	/// @returns Nullptr if the function doesn't exist; a const weak pointer
	/// to the function otherwise.
	template< typename P1, typename P2, typename P3, typename P4, typename P5 >
	inline
	masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
	get_fiveinput_setter_function(
		std::string const & function_name
	) const {
		using namespace setter;

		for( auto const & setter: setters_ ) {
			if( setter->num_input_parameters() == 5 && setter->setter_function_name() == function_name ) {
				MasalaObjectAPISetterDefinition_FiveInputCSP< P1, P2, P3, P4, P5 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_FiveInput< P1, P2, P3, P4, P5 > const >( setter ) );
				if( setter_cast != nullptr ) {
					return setter;
				}
			}
		}
		return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
	}

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of the class for which this object stores an API description.
	std::string const & api_class_name() const;

	/// @brief Get the namespace of the class for which this object stores an API description.
	std::string const & api_class_namespace() const;

	/// @brief Get the namespace and name of the class for which this object stores an API description.
	std::string api_class_namespace_and_name() const;

	/// @brief Get the description of the class for which this object stores an API description.
	std::string const & api_class_description() const;

	/// @brief Should the API class have protected constructors?
	/// @details This allows the class to effetively act as a pure virtual base class, that cannot
	/// itself be instantiated.
	bool has_protected_constructors() const;

	/// @brief Get a human-readable description of the API for a module.
	/// @details Note that this does not cache the generated string, but generates it anew
	/// each time.
	std::string
	get_human_readable_description() const;

	/// @brief Get a JSON object describing the API for a module.
	/// @details Note that this does not cache the generated JSON object, but generates it anew
	/// each time.
	MASALA_SHARED_POINTER< nlohmann::json >
	get_json_description() const;

	/// @brief Begin iterator for the constructors.
	std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP>::const_iterator
	constructors_begin() const;

	/// @brief End iterator for the constructors.
	std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP>::const_iterator
	constructors_end() const;

	/// @brief Number of constructors.
	base::Size
	n_constructors() const;

	/// @brief Add a constructor.
	void
	add_constructor(
		base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP constructor_in
	);

	/// @brief Begin iterator for the setters.
	std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	setters_begin() const;

	/// @brief End iterator for the setters.
	std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	setters_end() const;

	/// @brief Number of setters.
	base::Size
	n_setters() const;

	/// @brief Add a setter.
	void
	add_setter(
		base::api::setter::MasalaObjectAPISetterDefinitionCSP setter_in
	);

	/// @brief Begin iterator for the getters.
	std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator
	getters_begin() const;

	/// @brief End iterator for the getters.
	std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator
	getters_end() const;

	/// @brief Number of getters.
	base::Size
	n_getters() const;

	/// @brief Add a getter.
	void
	add_getter(
		base::api::getter::MasalaObjectAPIGetterDefinitionCSP getter_in
	);

	/// @brief Begin iterator for the work functions.
	std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator
	work_functions_begin() const;

	/// @brief End iterator for the work functions.
	std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator
	work_functions_end() const;

	/// @brief Number of work functions.
	base::Size
	n_work_functions() const;

	/// @brief Add a work function.
	void
	add_work_function(
		base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP work_function_in
	);

	/// @brief Is this the API for a lightweight object that could be stack-allocated?
	/// @details If so, the API container will store the object directly, not an owning pointer to it. 
	inline bool is_lightweight() const { return is_lightweight_; }

	/// @brief Is this a plugin class that could be registered with the plugin manager?
	/// @details If so, in addition to the API container, an API container creator (suitable for
	/// registering with the plugin manager) will be auto-generated.
	inline bool is_plugin_class() const { return is_plugin_class_; }

	/// @brief Is this a MasalaEngine class that should be registered with the engine manager?
	/// @details If so, the API creator will derive from MasalaEngineCreator and the API will
	/// derive from MasalaEngineAPI.
	inline bool is_engine_class() const { return is_engine_class_; }

	/// @brief Is this a MasalaDataRepresentation class that should be registered with the data
	/// representation manager?
	/// @details If so, the API creator will derive from MasalaDataRepresentationCreator and the
	/// API will derive from MasalaDataRepresentationAPI.
	inline bool is_data_representation_class() const { return is_data_representation_class_; }

	/// @brief Get the categories that this object is in, if it is a plugin object.
	/// @details A category is hierarchical, listed as a vector of strings.  For instance,
	/// Fruit->CitrusFruit->Oranges would be stored as { {"Fruit", "CitrusFruit", "Oranges"} }.
	/// An object can be in more than one category.
	std::vector< std::vector< std::string > > const &
	plugin_categories() const;

	/// @brief Get the keywords for this object, if it is a plugin object.
	std::vector< std::string > const &
	plugin_keywords() const;

	/// @brief Get the categories that this object is in, if it is a MasalaEngine object.
	/// @details A category is hierarchical, listed as a vector of strings.  For instance,
	/// Fruit->CitrusFruit->Oranges would be stored as { {"Fruit", "CitrusFruit", "Oranges"} }.
	/// An object can be in more than one category.
	std::vector< std::vector< std::string > > const &
	engine_categories() const;

	/// @brief Get the categories that this object is in, if it is a MasalaDataRepresentation
	/// object.
	std::vector< std::vector< std::string > > const &
	data_representation_categories() const;

	/// @brief Get the properties that this object definitely has, if it is a
	/// MasalaDataRepresentation object.
	std::vector< std::string > const &
	data_representation_present_properties() const;

	/// @brief Get the properties that this object definitely does not have , if it is a
	/// MasalaDataRepresentation object.
	std::vector< std::string > const &
	data_representation_absent_properties() const;

	/// @brief Get the properties that this object could have, if it is a
	/// MasalaDataRepresentation object.
	std::vector< std::string > const &
	data_representation_possibly_present_properties() const;

	/// @brief Get the properties that this object could be lacking, if it is a
	/// MasalaDataRepresentation object.
	std::vector< std::string > const &
	data_representation_possibly_absent_properties() const;

	/// @brief Get the MasalaEngines that this object is definitely compatible with, if it is
	/// a MasalaDataRepresentation object.
	std::vector< std::string > const &
	data_representation_compatible_engines() const;

	/// @brief Get the MasalaEngines that this object is definitely not compatible with, if it
	/// is a MasalaDataRepresentation object.
	std::vector< std::string > const &
	data_representation_incompatible_engines() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Generate JSON descriptions for all of the constructors.
	/// @details Nothing is cached here, so this will generate a new JSON object
	/// each time it is called.  This isn't super fast.
	nlohmann::json get_json_description_for_constructors() const;

	/// @brief Generate JSON descriptions for all of the setters.
	/// @details Nothing is cached here, so this will generate a new JSON object
	/// each time it is called.  This isn't super fast.
	nlohmann::json get_json_description_for_setters() const;

	/// @brief Generate JSON descriptions for all of the getters.
	/// @details Nothing is cached here, so this will generate a new JSON object
	/// each time it is called.  This isn't super fast.
	nlohmann::json get_json_description_for_getters() const;

	/// @brief Generate JSON descriptions for all of the work functions.
	/// @details Nothing is cached here, so this will generate a new JSON object
	/// each time it is called.  This isn't super fast.
	nlohmann::json get_json_description_for_work_functions() const;

	/// @brief Given a vector of strings, write a header followed by the vector as a comma-separated list,
	/// or [NONE] if the vector is empty.
	void write_list_to_stream( std::ostringstream & ss, std::string const & header, std::vector< std::string > const & list_to_write ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of the class for which we're providing an API definition.
	/// @details Must be set at construction time.
	std::string const api_class_name_;

	/// @brief The namespace of the class for which we're providing an API definition.
	/// @details Must be set at construction time.
	std::string const api_class_namespace_;

	/// @brief The description of the class for which we're providing an API definition.
	/// @details Must be set at construction time.
	std::string const api_class_description_;

	/// @brief Should the API class have protected constructors?
	/// @details This allows the class to effetively act as a pure virtual base class, that cannot
	/// itself be instantiated.
	bool const has_protected_constructors_ = false;

	/// @brief A list of constructors.
	std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP> constructors_;

	/// @brief A list of setters.
	std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP> setters_;

	/// @brief A list of getters.
	std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP> getters_;

	/// @brief A list of work functions.
	std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP> work_functions_;

	/// @brief Is this the API for a lightweight object that could be stack-allocated?
	/// @details If so, the API container will store the object directly, not an owning pointer to it.
	bool is_lightweight_ = false;

	/// @brief Is this a plugin class that could be registered with the plugin manager?
	/// @details If so, in addition to the API container, an API container creator (suitable for
	/// registering with the plugin manager) will be auto-generated.
	bool is_plugin_class_ = false;

	/// @brief Is this a MasalaEngine class?
	/// @details If so, the API creator is derived from MasalaEngineCreator instead of
	/// MasalaPluginCreator, and the API is derived from MasalaEngineAPI instead of
	/// MasalaPluginAPI.
	bool is_engine_class_ = false;

	/// @brief Is this a MasalaDataRepresentation class?
	/// @details If so, the API creator is derived from MasalaDataRepresentationCreator instead of
	/// MasalaPluginCreator, and the API is derived from MasalaDataRepresentationAPI instead of
	/// MasalaPluginAPI.
	bool is_data_representation_class_ = false;

	/// @brief The categories that this object is in, if it is a plugin object.
	/// @details A category is hierarchical, listed as a vector of strings.  For instance,
	/// Fruit->CitrusFruit->Oranges would be stored as { {"Fruit", "CitrusFruit", "Oranges"} }.
	/// An object can be in more than one category.
	std::vector< std::vector< std::string > > plugin_categories_;

	/// @brief The keywords for this object, if it is a plugin object.
	std::vector< std::string > plugin_keywords_;

	/// @brief The categories that this object is in, if it is a MasalaEngine object.
	/// @details A category is hierarchical, listed as a vector of strings.  For instance,
	/// Fruit->CitrusFruit->Oranges would be stored as { {"Fruit", "CitrusFruit", "Oranges"} }.
	/// An object can be in more than one category.
	std::vector< std::vector< std::string > > engine_categories_;

	/// @brief The categories that this object is in, if it is a MasalaDataRepresentation object.
	/// @details A category is hierarchical, listed as a vector of strings.  For instance,
	/// Fruit->CitrusFruit->Oranges would be stored as { {"Fruit", "CitrusFruit", "Oranges"} }.
	/// An object can be in more than one category.
	std::vector< std::vector< std::string > > data_representation_categories_;

	/// @brief The properties that this object definitely has, if it is a MasalaDataRepresentation
	/// object.
	std::vector< std::string > data_representation_present_properties_;

	/// @brief The properties that this object definitely does not have , if it is a
	/// MasalaDataRepresentation object.
	std::vector< std::string > data_representation_absent_properties_;

	/// @brief The properties that this object could have, if it is a
	/// MasalaDataRepresentation object.
	std::vector< std::string > data_representation_possibly_present_properties_;

	/// @brief The properties that this object could be lacking, if it is a
	/// MasalaDataRepresentation object.
	std::vector< std::string > data_representation_possibly_absent_properties_;

	/// @brief The MasalaEngines that this object is definitely compatible with, if it is
	/// a MasalaDataRepresentation object.
	std::vector< std::string > data_representation_compatible_engines_;

	/// @brief The MasalaEngines that this object is definitely not compatible with, if it
	/// is a MasalaDataRepresentation object.
	std::vector< std::string > data_representation_incompatible_engines_;

}; // class MasalaObjectAPIDefinition

} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_MasalaObjectAPIDefinition_hh