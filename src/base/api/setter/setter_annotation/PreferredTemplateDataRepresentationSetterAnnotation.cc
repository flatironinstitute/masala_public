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

/// @file src/base/api/setter/setter_annotation/PreferredTemplateDataRepresentationSetterAnnotation.cc
/// @brief Implementations for a setter function annotation that indicates that a
/// function accepts an empty but configured MasalaDataRepresentation object to use as a
/// template for code requesting empty containers for data.  The set object will be deep-cloned
/// and handed out to requesting code by a corresponding getter function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/setter/setter_annotation/PreferredTemplateDataRepresentationSetterAnnotation.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/managers/engine/MasalaDataRepresentationAPI.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.hh>
#include <base/managers/engine/MasalaDataRepresentationManager.hh>
#include <base/managers/engine/MasalaDataRepresentationRequest.hh>
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

/// @brief Get the class name ("PreferredTemplateDataRepresentationSetterAnnotation").
std::string
PreferredTemplateDataRepresentationSetterAnnotation::class_name() const {
	return "PreferredTemplateDataRepresentationSetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
std::string
PreferredTemplateDataRepresentationSetterAnnotation::class_namespace() const {
	return "masala::base::api::setter::setter_annotation";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief The category that can be passed to the MasalaDataRepresentationManager to get objects
/// of the type needed for this function.  Could be an empty vector.
std::vector< std::string > const &
PreferredTemplateDataRepresentationSetterAnnotation::data_representation_manager_input_object_category() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return data_representation_manager_input_object_category_;
}

/// @brief When the MasalaDataRepresentationManager is interogated for objects of the appropriate
/// type by category, should we include subcategories?  Default true.
bool
PreferredTemplateDataRepresentationSetterAnnotation::data_representation_manager_include_subcategory() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return data_representation_manager_include_subcategory_;
}

/// @brief The keywords that can be passed to the MasalaDataRepresentationManager to try to get objects
/// of the type needed for this function.  Could be an empty vector.
std::vector< std::string > const &
PreferredTemplateDataRepresentationSetterAnnotation::data_representation_manager_input_object_keywords() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return data_representation_manager_input_object_keywords_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

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
PreferredTemplateDataRepresentationSetterAnnotation::set_data_representation_manager_info(
	std::vector< std::string > const & data_representation_manager_input_object_category,
	std::vector< std::string > const & data_representation_manager_input_object_keywords,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter,
	bool const data_representation_manager_include_subcategory//= true
) {
	using namespace masala::base::managers::engine;
	using namespace masala::base::api::setter;

	std::lock_guard< std::mutex > lock( mutex() );

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
	data_representation_manager_input_object_category_ = data_representation_manager_input_object_category;
	data_representation_manager_input_object_keywords_ = data_representation_manager_input_object_keywords;
	data_representation_manager_include_subcategory_ = data_representation_manager_include_subcategory;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Create an empty, unconfigured instance of the data representation object type.
/// @param object_name The name of the type to create.  Throws if this type is not known to the data representation manager.
/// @returns A shared pointer to a nonconst instance of the new object type.
masala::base::managers::engine::MasalaDataRepresentationAPISP
PreferredTemplateDataRepresentationSetterAnnotation::create_empty_data_representation(
	std::string const & object_name
) const {
	using namespace masala::base::managers::engine;
	std::lock_guard< std::mutex > lock( mutex() );

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( true ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, object_name ),
			"create_owned_object", "The " + object_name + " class is not compatible with this object."
		);
	}

	MasalaDataRepresentationAPISP returnobj(
		masala::base::managers::engine::MasalaDataRepresentationManager::get_instance()->create_data_representation( object_name, false )
	);
	CHECK_OR_THROW_FOR_CLASS( returnobj != nullptr, "create_owned_object",
		"Could not find a suitable MasalaDataRepresentation named \"" + object_name + "\"."
	);
	return returnobj;
}

/// @brief Call the setter function, and pass it a MasalaDataRepresentationAPICSP const instance.
/// @details This version takes a const shared pointer to the object.
void
PreferredTemplateDataRepresentationSetterAnnotation::set_object(
	masala::base::managers::engine::MasalaDataRepresentationAPICSP const & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in->inner_class_namespace() + "::" + object_in->inner_class_name() ) ),
			"set_object", "The " + object_in->inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

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

/// @brief Call the setter function, and pass it a MasalaDataRepresentationAPISP const instance.
/// @details This version takes a nonconst shared pointer to the object.
void
PreferredTemplateDataRepresentationSetterAnnotation::set_object(
	masala::base::managers::engine::MasalaDataRepresentationAPISP const & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in->inner_class_namespace() + "::" + object_in->inner_class_name() ) ),
			"set_object", "The " + object_in->inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

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

/// @brief Call the setter function, and pass it a MasalaDataRepresentationAPI const instance.
/// @details This version takes a const reference to the object.
void
PreferredTemplateDataRepresentationSetterAnnotation::set_object(
	masala::base::managers::engine::MasalaDataRepresentationAPI const & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );
	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in.inner_class_namespace() + "::" + object_in.inner_class_name() ) ),
			"set_object", "The " + object_in.inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

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

/// @brief Call the setter function, and pass it a MasalaPluginAPI nonconst instance.
/// @details This version takes a nonconst reference to the object.
void
PreferredTemplateDataRepresentationSetterAnnotation::set_object(
	masala::base::managers::engine::MasalaDataRepresentationAPI & object_in,
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( mutex() );

	CHECK_OR_THROW_FOR_CLASS( setter.n_setter_annotations() == 1, "set_object", "Expected the \"" + setter.setter_function_name() + "\" to take one input, but it"
		"takes " + std::to_string( setter.n_setter_annotations() ) + " inputs."
	);

	{
		std::vector< std::string > const & eligible_objects( protected_get_names_of_eligible_owned_objects( false ) );
		CHECK_OR_THROW_FOR_CLASS(
			base::utility::container::has_value( eligible_objects, std::string( object_in.inner_class_namespace() + "::" + object_in.inner_class_name() ) ),
			"set_object", "The " + object_in.inner_class_name() + " class is not something that can be passed to the " + setter.setter_function_name() + "() function."
		);
	}

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

/// @brief Get a list of short names of objects that can be passed to this setter. 
std::vector< std::string >
PreferredTemplateDataRepresentationSetterAnnotation::get_short_names_of_eligible_owned_objects() const {
	std::lock_guard< std::mutex > lock( mutex() );
	return protected_get_names_of_eligible_owned_objects( true );
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign src to this.  Performs no mutex-locking.
/// @details Derived classes should override this, and the overrides should call this function.
void
PreferredTemplateDataRepresentationSetterAnnotation::protected_assign(
    MasalaFunctionAnnotation const & src
) /*override*/ {
    PreferredTemplateDataRepresentationSetterAnnotation const * src_cast_ptr( dynamic_cast< PreferredTemplateDataRepresentationSetterAnnotation const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " class could not be interpreted as a PreferredTemplateDataRepresentationSetterAnnotation object." );
    PreferredTemplateDataRepresentationSetterAnnotation const & src_cast( *src_cast_ptr );
	
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
PreferredTemplateDataRepresentationSetterAnnotation::protected_is_compatible_with_setter(
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
) const /*override*/ {
	using namespace masala::base::api::setter;
	using namespace masala::base::managers::engine;

	if( setter.num_input_parameters() != 1 ) { return false; }

	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPISP const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPICSP const & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI & > const * >( &setter ) != nullptr ) { return true; }
	if( dynamic_cast< MasalaObjectAPISetterDefinition_OneInput< MasalaDataRepresentationAPI const & > const * >( &setter ) != nullptr ) { return true; }

	return false;
}

/// @brief Get a list of names of objects that can be passed to this setter.
/// @details This function should be called from a mutex-locked context.  If short_names is true, then
/// only names are returned; otherwise, names and namespaces are returned.
std::vector< std::string >
PreferredTemplateDataRepresentationSetterAnnotation::protected_get_names_of_eligible_owned_objects(
	bool const short_names
) const {
	using namespace masala::base::managers::engine;
	using namespace masala::base::managers::engine::data_representation_request;


	std::vector< std::string > outvec;
	
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

	outvec.shrink_to_fit();

	return outvec;
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
