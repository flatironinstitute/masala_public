/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.cc
/// @brief Implementations for a setter function annotation that indicates that a
/// function sets a type of object that is (a) wholly owned by the encapsulating object, and
/// (b) unique (i.e. an instance of the encapsulating object encapsulates only one instance
/// of the inner object).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/setter_annotation/PreferredTemplateDataRepresentationSetterAnnotation.hh>
#include <base/managers/plugin_module/MasalaPlugin.fwd.hh>
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>
#include <base/managers/engine/MasalaDataRepresentationAPI.hh>
#include <base/managers/engine/MasalaEngineAPI.hh>
#include <base/managers/engine/MasalaEngineCreator.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.hh>
#include <base/managers/engine/MasalaDataRepresentationManager.hh>
#include <base/managers/engine/MasalaEngineManager.hh>
#include <base/managers/engine/MasalaEngineRequest.hh>
#include <base/managers/engine/MasalaDataRepresentationRequest.hh>
#include <base/managers/engine/engine_request/MasalaEngineKeywordCriterion.hh>
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationKeywordCriterion.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/utility/container/container_util.tmpl.hh>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("OwnedSingleObjectSetterAnnotation").
std::string
OwnedSingleObjectSetterAnnotation::class_name() const {
	return "OwnedSingleObjectSetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
std::string
OwnedSingleObjectSetterAnnotation::class_namespace() const {
	return "masala::base::api::setter::setter_annotation";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief The category that can be passed to the MasalaPluginManager to get objects
/// of the type needed for this function.  Could be an empty vector
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::plugin_manager_input_object_category() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return plugin_manager_input_object_category_;
}

/// @brief When the MasalaPluginManager is interogated for objects of the appropriate
/// type by category, should we include subcategories?  Default true.
bool
OwnedSingleObjectSetterAnnotation::plugin_manager_include_subcategory() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return plugin_manager_include_subcategory_;
}

/// @brief The keywords that can be passed to the MasalaPluginManager to try to get objects
/// of the type needed for this function.  Could be an empty vector.
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::plugin_manager_input_object_keywords() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return plugin_manager_input_object_keywords_;
}

/// @brief Is the input object an engine?  False by default.
bool
OwnedSingleObjectSetterAnnotation::is_engine() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return is_engine_;
}

/// @brief The category that can be passed to the MasalaEngineManager to get objects
/// of the type needed for this function.  Could be an empty vector.
/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::engine_manager_input_object_category() const {
	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( is_engine_, "engine_manager_input_object_category",
		"The input object is not a Masala engine."
	);
	return engine_manager_input_object_category_;
}

/// @brief When the MasalaEngineManager is interogated for objects of the appropriate
/// type by category, should we include subcategories?  Default true.
/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
bool
OwnedSingleObjectSetterAnnotation::engine_manager_include_subcategory() const
{
	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( is_engine_, "engine_manager_include_subcategory",
		"The input object is not a Masala engine."
	);
	return engine_manager_include_subcategory_;
}

/// @brief The keywords that can be passed to the MasalaEngineManager to try to get objects
/// of the type needed for this function.  Could be an empty vector.
/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::engine_manager_input_object_keywords() const {
	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( is_engine_, "engine_manager_input_object_keywords",
		"The input object is not a Masala engine."
	);
	return engine_manager_input_object_keywords_;
}

/// @brief Is the input object a data representation?  False by default.
/// @note Throws if is_data_representation_ is false.  Check by calling
/// is_data_representation() first!
bool
OwnedSingleObjectSetterAnnotation::is_data_representation() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return is_data_representation_;
}

/// @brief The category that can be passed to the MasalaDataRepresentationManager to get objects
/// of the type needed for this function.  Could be an empty vector.
/// @note Throws if is_data_representation_ is false.  Check by calling
/// is_data_representation() first!
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::data_representation_manager_input_object_category() const {
	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( is_data_representation_, "data_representation_manager_input_object_category",
		"The input object is not a Masala data representation."
	);
	return data_representation_manager_input_object_category_;
}

/// @brief When the MasalaDataRepresentationManager is interogated for objects of the appropriate
/// type by category, should we include subcategories?  Default true.
/// @note Throws if is_data_representation_ is false.  Check by calling
/// is_data_representation() first!
bool
OwnedSingleObjectSetterAnnotation::data_representation_manager_include_subcategory() const {
	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( is_data_representation_, "data_representation_manager_include_subcategory",
		"The input object is not a Masala data representation."
	);
	return data_representation_manager_include_subcategory_;
}

/// @brief The keywords that can be passed to the MasalaDataRepresentationManager to try to get objects
/// of the type needed for this function.  Could be an empty vector.
/// @note Throws if is_data_representation_ is false.  Check by calling
/// is_data_representation() first!
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::data_representation_manager_input_object_keywords() const {
	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( is_data_representation_, "data_representation_manager_input_object_keywords",
		"The input object is not a Masala data representation."
	);
	return data_representation_manager_input_object_keywords_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the information for the object types that this setter takes.
/// @param[in] plugin_manager_input_object_category The category that can be passed
/// to the plugin manager to get objects of the type that this setter function accepts.
/// Can be left as an empty vector.
/// @param[in] plugin_manager_input_object_keywords Keywords that can be passed to the
/// MasalaPluginManager to try to get objects of the type needed for this setter function.
/// Can be left as an empty vector.
/// @param[in] plugin_manager_include_subcategory If true (the default), then
/// subcategories of the given category are accepted.  If false, then the exact category
/// must be used.
void
OwnedSingleObjectSetterAnnotation::set_plugin_manager_info(
	std::vector< std::string > const & plugin_manager_input_object_category,
	std::vector< std::string > const & plugin_manager_input_object_keywords,
	bool const plugin_manager_include_subcategory //= true
) {
	std::lock_guard< std::mutex > lock( mutex() );
	plugin_manager_input_object_category_ = plugin_manager_input_object_category;
	plugin_manager_input_object_keywords_ = plugin_manager_input_object_keywords;
	plugin_manager_include_subcategory_ = plugin_manager_include_subcategory;
}

/// @brief Set the information for the engine object types that this setter takes.  Note
/// that this implicitly sets is_engine_ to true.
/// @param[in] engine_manager_input_object_category The category that can be passed
/// to the engine manager to get objects of the type that this setter function accepts.
/// Can be left as an empty vector.
/// @param[in] engine_manager_input_object_keywords Keywords that can be passed to the
/// MasalaEngineManager to try to get objects of the type needed for this setter function.
/// Can be left as an empty vector.
/// @param[in] setter The setter to which we will be attaching this annotation.  This function will
/// throw if the setter is not a single-input setter that takes a MasalaEngineAPISP or MasalaEngineAPICSP.
/// @param[in] engine_manager_include_subcategory If true (the default), then
/// subcategories of the given category are accepted.  If false, then the exact category
/// must be used.
void
OwnedSingleObjectSetterAnnotation::set_engine_manager_info(
	std::vector< std::string > const & engine_manager_input_object_category,
	std::vector< std::string > const & engine_manager_input_object_keywords,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter,
	bool const engine_manager_include_subcategory //= true
) {
	using namespace masala::base::managers::engine;
	using namespace masala::base::api::setter;

	std::lock_guard< std::mutex > lock( mutex() );

	CHECK_OR_THROW_FOR_CLASS( !is_data_representation_, "set_engine_manager_info", "Engine manager information cannot be set "
		"if a setter function accepts a data representation."
	);
	CHECK_OR_THROW_FOR_CLASS( setter.num_input_parameters() == 1 &&
		(
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP const & > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP const & > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI & > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * >( &setter ) != nullptr
		),
		"set_engine_manager_info",
		"Engine manager info can only be set for a setter function that accepts a single input: a MasalaEngineSP or MasalaEngineCSP.  Error with setter function "
		+ setter.setter_function_name() + "()."
	);
	is_engine_ = true;
	engine_manager_input_object_category_ = engine_manager_input_object_category;
	engine_manager_input_object_keywords_ = engine_manager_input_object_keywords;
	engine_manager_include_subcategory_ = engine_manager_include_subcategory;
}

/// @brief Set the information for the data representation object types that this setter takes.  Note
/// that this implicitly sets is_data_representation_ to true.
/// @param[in] data_representation_manager_input_object_category The category that can be passed
/// to the data representation manager to get objects of the type that this setter function accepts.
/// Can be left as an empty vector.
/// @param[in] data_representation_manager_input_object_keywords Keywords that can be passed to the
/// MasalaDataRepresentationManager to try to get objects of the type needed for this setter function.
/// Can be left as an empty vector.
/// @param[in] setter The setter to which we will be attaching this annotation.  This function will
/// throw if the setter is not a single-input setter that takes a MasalaDataRepresentationAPISP or
/// MasalaDataRepresentationAPICSP.
/// @param[in] data_representation_manager_include_subcategory If true (the default), then
/// subcategories of the given category are accepted.  If false, then the exact category
/// must be used.
void
OwnedSingleObjectSetterAnnotation::set_data_representation_manager_info(
	std::vector< std::string > const & data_representation_manager_input_object_category,
	std::vector< std::string > const & data_representation_manager_input_object_keywords,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter,
	bool const data_representation_manager_include_subcategory//= true
) {
	using namespace masala::base::managers::engine;
	using namespace masala::base::api::setter;

	std::lock_guard< std::mutex > lock( mutex() );

	CHECK_OR_THROW_FOR_CLASS( !is_engine_, "set_data_representation_manager_info", "Data representation manager information cannot be set "
		"if a setter function accepts an engine."
	);
	CHECK_OR_THROW_FOR_CLASS( setter.num_input_parameters() == 1 &&
		(
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP const & > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP const & > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI & > const * >( &setter ) != nullptr ||
			dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * >( &setter ) != nullptr
		),
		"set_data_representation_manager_info",
		"Data representation manager info can only be set for a setter function that accepts a single input: "
		"a MasalaDataRepresentationSP or MasalaDataRepresentationCSP."
	);
	is_data_representation_ = true;
	data_representation_manager_input_object_category_ = data_representation_manager_input_object_category;
	data_representation_manager_input_object_keywords_ = data_representation_manager_input_object_keywords;
	data_representation_manager_include_subcategory_ = data_representation_manager_include_subcategory;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Create an instance of the owned object type.
/// @param object_name The name of the type to create.  Throws if this type is not known to the plugin manager, the engine manager if this
/// is an engine setter, or the data representation manager if this is a data representation setter.
/// @returns A shared pointer to a nonconst instance of the new object type.
masala::base::managers::plugin_module::MasalaPluginAPISP
OwnedSingleObjectSetterAnnotation::create_owned_object(
	std::string const & object_name
) const {
	using namespace masala::base::managers::plugin_module;
	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( !( is_engine_ && is_data_representation_ ), "create_owned_object", "Program error: the object is listed as both an "
		"engine and a data representation.  This should be impossible.  Please consult a developer."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( true ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, object_name ),
			"create_owned_object", "The " + object_name + " class is not compatible with this object."
		);
	}

	MasalaPluginAPISP returnobj;
	if( is_data_representation_ ) {
		returnobj = masala::base::managers::engine::MasalaDataRepresentationManager::get_instance()->create_data_representation_by_short_name( object_name, false );
	} else if( is_engine_ ) {
		returnobj = masala::base::managers::engine::MasalaEngineManager::get_instance()->create_engine_by_short_name( object_name, false );
	} else {
		returnobj = masala::base::managers::plugin_module::MasalaPluginModuleManager::get_instance()->create_plugin_object_instance_by_short_name( plugin_manager_input_object_category_, object_name, plugin_manager_include_subcategory_ );
	}
	CHECK_OR_THROW_FOR_CLASS( returnobj != nullptr, "create_owned_object",
		"Could not find a suitable " + ( is_engine_ ? std::string("MasalaEngine") : ( is_data_representation_ ? std::string("MasalaDataRepresentation") : std::string("MasalaPlugin") ) )
		+ " named \"" + object_name + "\"."
	);
	return returnobj;
}

/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
/// @details This version takes a const shared pointer to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
/// this will throw if the object cannot be cast to the appropriate type.
void
OwnedSingleObjectSetterAnnotation::set_object(
	masala::base::managers::plugin_module::MasalaPluginAPICSP const & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::plugin_module;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);
	CHECK_OR_THROW_FOR_CLASS(!( is_engine_ && is_data_representation_ ), "set_object", "Program error: the \"" + setter.setter_function_name() + "\" setter "
		"definition was incorrectly configured.  It is annotated as taking both an engine and a data representation.  This is not possible.  Please "
		"consult a developer."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in->inner_class_namespace() + "::" + object_in->inner_class_name() ) ),
			"set_object", "The " + object_in->inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

	if( is_engine_ ) {
		MasalaEngineAPICSP object_in_cast( std::dynamic_pointer_cast< MasalaEngineAPI const >( object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaEngine object, but the " + object_in->inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaEngineCSP, a MasalaEngineCSP const &, or a MasalaEngine const &, but it does not!" );
	} else if( is_data_representation_ ) {
		MasalaDataRepresentationAPICSP object_in_cast( std::dynamic_pointer_cast< MasalaDataRepresentationAPI const >( object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaDataRepresentation object, but the " + object_in->inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaDataRepresentationCSP, a MasalaDataRepresentationCSP const &, or a MasalaDataRepresentation const &, but it does not!" );
	}

	// If we reach here, we're just taking a generic MasalaPluginAPI object.
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPICSP > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPICSP > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( object_in );
			return;
		}
	}
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPICSP const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPICSP const & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( object_in );
			return;
		}
	}
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( *object_in );
			return;
		}
	}
	MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaPluginCSP, a MasalaPluginCSP const &, or a MasalaPlugin const &, but it does not!" );
}

/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
/// @details This version takes a nonconst shared pointer to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
/// this will throw if the object cannot be cast to the appropriate type.
void
OwnedSingleObjectSetterAnnotation::set_object(
	masala::base::managers::plugin_module::MasalaPluginAPISP const & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::plugin_module;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);
	CHECK_OR_THROW_FOR_CLASS(!( is_engine_ && is_data_representation_ ), "set_object", "Program error: the \"" + setter.setter_function_name() + "\" setter "
		"definition was incorrectly configured.  It is annotated as taking both an engine and a data representation.  This is not possible.  Please "
		"consult a developer."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in->inner_class_namespace() + "::" + object_in->inner_class_name() ) ),
			"set_object", "The " + object_in->inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

	if( is_engine_ ) {
		MasalaEngineAPISP object_in_cast( std::dynamic_pointer_cast< MasalaEngineAPI >( object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaEngine object, but the " + object_in->inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaEngineSP, a MasalaEngineSP const &, a MasalaEngine &, or a MasalaEngine const &, but it does not!" );
	} else if( is_data_representation_ ) {
		MasalaDataRepresentationAPISP object_in_cast( std::dynamic_pointer_cast< MasalaDataRepresentationAPI >( object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaDataRepresentation object, but the " + object_in->inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaDataRepresentationSP, a MasalaDataRepresentationSP const &, a MasalaDataRepresentation &, or a MasalaDataRepresentation const &, but it does not!" );
	}

	// If we reach here, we're just taking a generic MasalaPluginAPI object.
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPISP > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPISP > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( object_in );
			return;
		}
	}
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPISP const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPISP const & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( object_in );
			return;
		}
	}
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( *object_in );
			return;
		}
	}
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( *object_in );
			return;
		}
	}
	MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaPluginSP, a MasalaPluginSP const &, a MasalaPlugin &, or a MasalaPlugin const &, but it does not!" );
}

/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
/// @details This version takes a const reference to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
/// this will throw if the object cannot be cast to the appropriate type.
void
OwnedSingleObjectSetterAnnotation::set_object(
	masala::base::managers::plugin_module::MasalaPluginAPI const & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::plugin_module;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);
	CHECK_OR_THROW_FOR_CLASS(!( is_engine_ && is_data_representation_ ), "set_object", "Program error: the \"" + setter.setter_function_name() + "\" setter "
		"definition was incorrectly configured.  It is annotated as taking both an engine and a data representation.  This is not possible.  Please "
		"consult a developer."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in.inner_class_namespace() + "::" + object_in.inner_class_name() ) ),
			"set_object", "The " + object_in.inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

	if( is_engine_ ) {
		MasalaEngineAPI const * object_in_ptr_cast( dynamic_cast< MasalaEngineAPI const * >( &object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_ptr_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaEngine object, but the " + object_in.inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_ptr_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaEngine const &, but it does not!" );
	} else if( is_data_representation_ ) {
		MasalaDataRepresentationAPI const * object_in_ptr_cast( dynamic_cast< MasalaDataRepresentationAPI const * >( &object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_ptr_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaDataRepresentation object, but the " + object_in.inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_ptr_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaDataRepresentation const &, but it does not!" );
	}

	// If we reach here, we're just taking a generic MasalaPluginAPI object.
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( object_in );
			return;
		}
	}
	MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaPlugin const &, but it does not!" );
}

/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
/// @details This version takes a nonconst reference to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
/// this will throw if the object cannot be cast to the appropriate type.
void
OwnedSingleObjectSetterAnnotation::set_object(
	masala::base::managers::plugin_module::MasalaPluginAPI & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::plugin_module;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );

	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);
	CHECK_OR_THROW_FOR_CLASS(!( is_engine_ && is_data_representation_ ), "set_object", "Program error: the \"" + setter.setter_function_name() + "\" setter "
		"definition was incorrectly configured.  It is annotated as taking both an engine and a data representation.  This is not possible.  Please "
		"consult a developer."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in.inner_class_namespace() + "::" + object_in.inner_class_name() ) ),
			"set_object", "The " + object_in.inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

	if( is_engine_ ) {
		MasalaEngineAPI * object_in_ptr_cast( dynamic_cast< MasalaEngineAPI * >( &object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_ptr_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaEngine object, but the " + object_in.inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_ptr_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_ptr_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaEngine & (const or nonconst), but it does not!" );
	} else if( is_data_representation_ ) {
		MasalaDataRepresentationAPI * object_in_ptr_cast( dynamic_cast< MasalaDataRepresentationAPI * >( &object_in ) );
		CHECK_OR_THROW_FOR_CLASS( object_in_ptr_cast != nullptr, "set_object", "Expected the input to the \"" + setter.setter_function_name() + "\" function to be "
			"a MasalaDataRepresentation object, but the " + object_in.inner_class_name() + " class name is not."
		);
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_ptr_cast );
				return;
			}
		}
		{
			MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * >( &setter ) );
			if( setter_cast != nullptr ) {
				setter_cast->function( *object_in_ptr_cast );
				return;
			}
		}
		MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaDataRepresentation & (const or nonconst), but it does not!" );
	}

	// If we reach here, we're just taking a generic MasalaPluginAPI object.
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( object_in );
			return;
		}
	}
	{
		MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * setter_cast( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * >( &setter ) );
		if( setter_cast != nullptr ) {
			setter_cast->function( object_in );
			return;
		}
	}
	MASALA_THROW( class_namespace() + "::" + class_name(), "set_object", "Expected the setter function to accept a MasalaPlugin & (const or nonconst), but it does not!" );
}

/// @brief Get a list of short names of objects that can be passed to this setter. 
std::vector< std::string >
OwnedSingleObjectSetterAnnotation::get_short_names_of_eligible_owned_objects() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return protected_get_names_of_eligible_owned_objects( true );
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign src to this.  Performs no mutex-locking.
/// @details Derived classes should override this, and the overrides should call this function.
void
OwnedSingleObjectSetterAnnotation::protected_assign(
    MasalaFunctionAnnotation const & src
) /*override*/ {
    OwnedSingleObjectSetterAnnotation const * src_cast_ptr( dynamic_cast< OwnedSingleObjectSetterAnnotation const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " class could not be interpreted as a OwnedSingleObjectSetterAnnotation object." );
    OwnedSingleObjectSetterAnnotation const & src_cast( *src_cast_ptr );
	
	plugin_manager_input_object_category_ = src_cast.plugin_manager_input_object_category_;
	plugin_manager_include_subcategory_ = src_cast.plugin_manager_include_subcategory_;
	plugin_manager_input_object_keywords_ = src_cast.plugin_manager_input_object_keywords_;
	is_engine_ = src_cast.is_engine_;
	engine_manager_input_object_category_ = src_cast.engine_manager_input_object_category_;
	engine_manager_include_subcategory_ = src_cast.engine_manager_include_subcategory_;
	engine_manager_input_object_keywords_ = src_cast.engine_manager_input_object_keywords_;
	is_data_representation_ = src_cast.is_data_representation_;
	data_representation_manager_input_object_category_ = src_cast.data_representation_manager_input_object_category_;
	data_representation_manager_include_subcategory_ = src_cast.data_representation_manager_include_subcategory_;
	data_representation_manager_input_object_keywords_ = src_cast.data_representation_manager_input_object_keywords_;

    MasalaSetterFunctionAnnotation::protected_assign( src );
}

/// @brief Is this annotation one that can be applied to this setter?
/// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This
/// override checks that (a) the setter takes one input, and (b) that the one input is either a MasalaPluginAPISP, a MasalaEngineAPISP,
/// a MasalaDataRepresentationAPISP, or the equivalent const shared pointers, or instances or const instances of any of these.  This
/// function performs no mutex locking.
/// @returns True if it is compatible, false otherwise.  Called by the setter API definition's add_setter_annotation() function.
bool
OwnedSingleObjectSetterAnnotation::protected_is_compatible_with_setter(
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const /*override*/ {
	using namespace masala::base::api::setter;
	using namespace masala::base::api::setter::setter_annotation;
	using namespace masala::base::managers::plugin_module;
	using namespace masala::base::managers::engine;

	if( setter.num_input_parameters() != 1 ) { return false; }

	// Check that this setter is NOT marked with an incompatible annotation.
	Size const n_extant_annotations( setter.n_setter_annotations() );
	for( Size i(0); i<n_extant_annotations; ++i ) {
		if( std::dynamic_pointer_cast< PreferredTemplateDataRepresentationSetterAnnotation const >( setter.setter_annotation(i) ) != nullptr ) {
			write_to_tracer( "Error!  The " + setter.setter_function_name() + "() setter is marked with a PreferredTemplateDataRepresentationSetterAnnotation, "
				"which means it cannot also be marked with a OwnedSingleObjectSetterAnnotation."
			);
			return false;
		} else if( std::dynamic_pointer_cast< OwnedSingleObjectSetterAnnotation const >( setter.setter_annotation(i) ) != nullptr ) {
			write_to_tracer( "Error!  The " + setter.setter_function_name() + "() setter is already marked with a OwnedSingleObjectSetterAnnotation, "
				"which means it cannot also be marked with another OwnedSingleObjectSetterAnnotation."
			);
			return false;
		}
	}

	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPISP > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPICSP > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP > const * >( &setter ) != nullptr ) { return true; }

	// Nonconst references to const shared pointers don't really make sense in this context.  These probably shouldn't be supported:
	// if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPISP & > const * >( &setter ) != nullptr ) { return true; }
	// if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP & > const * >( &setter ) != nullptr ) { return true; }
	// if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP & > const * >( &setter ) != nullptr ) { return true; }
	// if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPICSP & > const * >( &setter ) != nullptr ) { return true; }
	// if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP & > const * >( &setter ) != nullptr ) { return true; }
	// if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP & > const * >( &setter ) != nullptr ) { return true; }

	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPISP const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPISP const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPICSP const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPICSP const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP const & > const * >( &setter ) != nullptr ) { return true; }

	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaPluginAPI const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaEngineAPI const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * >( &setter ) != nullptr ) { return true; }

	return false;
}

/// @brief Get a list of names of objects that can be passed to this setter.
/// @details This function should be called from a mutex-locked context.  If short_names is true, then
/// only names are returned; otherwise, names and namespaces are returned.
std::vector< std::string >
OwnedSingleObjectSetterAnnotation::protected_get_names_of_eligible_owned_objects(
	bool const short_names
) const {
	using namespace masala::base::managers::engine;
	using namespace masala::base::managers::engine::engine_request;
	using namespace masala::base::managers::engine::data_representation_request;
	using namespace masala::base::managers::plugin_module;

	CHECK_OR_THROW_FOR_CLASS(!( is_engine_ && is_data_representation_ ), "protected_get_names_of_eligible_owned_objects", "Program error: this setter "
		"definition was incorrectly configured.  It is annotated as taking both an engine and a data representation.  This is not possible.  Please "
		"consult a developer."
	);

	std::vector< std::string > outvec;
	if( is_engine_ ) {
		MasalaEngineRequest engine_request;
		if( !engine_manager_input_object_category_.empty() ) {
			engine_request.add_engine_category_requirement( std::vector< std::vector< std::string > >{ engine_manager_input_object_category_ }, engine_manager_include_subcategory_ );
		}
		if( !engine_manager_input_object_keywords_.empty() ) {
			MasalaEngineKeywordCriterionSP keyword_criterion( masala::make_shared< MasalaEngineKeywordCriterion >() );
			keyword_criterion->set_criterion_mode( MasalaEngineKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD );
			keyword_criterion->set_keywords( engine_manager_input_object_keywords_ );
			engine_request.add_engine_criterion( keyword_criterion );
		}
		std::vector<MasalaEngineCreatorCSP> const compatible_creators(
			MasalaEngineManager::get_instance()->get_compatible_engine_creators( engine_request )
		);
		outvec.reserve( compatible_creators.size() );
		for( auto const & creator : compatible_creators ) {
			if( short_names ) {
				outvec.push_back( creator->get_plugin_object_name() );
			} else {
				outvec.push_back( creator->get_plugin_object_namespace_and_name() );
			}
		}
	} else if( is_data_representation_ ) {
		MasalaDataRepresentationRequest dr_request;
		if( !data_representation_manager_input_object_category_.empty() ) {
			dr_request.add_data_representation_category_requirement( std::vector< std::vector< std::string > >{ data_representation_manager_input_object_category_ }, data_representation_manager_include_subcategory_ );
		}
		if( !data_representation_manager_input_object_keywords_.empty() ) {
			MasalaDataRepresentationKeywordCriterionSP keyword_criterion( masala::make_shared< MasalaDataRepresentationKeywordCriterion >() );
			keyword_criterion->set_criterion_mode( MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD );
			keyword_criterion->set_keywords( data_representation_manager_input_object_keywords_ );
			dr_request.add_data_representation_criterion( keyword_criterion );
		}
		std::vector<MasalaDataRepresentationCreatorCSP> const compatible_creators(
			MasalaDataRepresentationManager::get_instance()->get_compatible_data_representation_creators( dr_request )
		);
		outvec.reserve( compatible_creators.size() );
		for( auto const & creator : compatible_creators ) {
			if( short_names ) {
				outvec.push_back( creator->get_plugin_object_name() );
			} else {
				outvec.push_back( creator->get_plugin_object_namespace_and_name() );
			}
		}
	} else {
		if( short_names ) {
			outvec = MasalaPluginModuleManager::get_instance()->get_short_names_of_plugins_by_category(
				plugin_manager_input_object_category_, plugin_manager_include_subcategory_
			);
		} else {
			outvec = MasalaPluginModuleManager::get_instance()->get_list_of_plugins_by_category(
				plugin_manager_input_object_category_, plugin_manager_include_subcategory_, true
			);
		}
	}

	return outvec;
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
