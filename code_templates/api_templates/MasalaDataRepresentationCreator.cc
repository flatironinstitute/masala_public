<__COMMENTED_LICENCE__>

<__DOXYGEN_CREATOR_FILE_PATH_AND_CC_FILE_NAME__>
/// @brief Function implementations for the creator for the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class.
/// @details Creators are needed to allow the Masala plugin system to use objects
/// defined in plugin libraries, and for the Masala engine and data representation
/// system to be able to create data representations compatible with particular
/// engines.
<__DOXYGEN_AUTHOR_AND_EMAIL__>
/// @note This file is an auto-generated API file.  Do not edit it, but instead
/// edit the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class's
/// get_api_definition() function.

// Header:
<__CREATOR_INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>

// Project headers:
<__API_INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>
<__INCLUDE_SOURCE_FILE_PATH_AND_HH_FILE_NAME__>

// STL headers:
#include <string>

<__CPP_NAMESPACE__>

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Create an object of the desired type (in this case, a
/// <__SOURCE_CLASS_NAMESPACE_AND_NAME__>,
/// encapsulated in an API container).
/// @returns A new instance of an <__SOURCE_CLASS_NAMESPACE_AND_NAME__> API container.
/// @details Must be implemented by derived classes.
masala::base::managers::plugin_module::MasalaPluginAPISP
<__CREATOR_CLASS_API_NAME__>::create_plugin_object() const {
	return masala::make_shared< <__SOURCE_CLASS_API_NAME__> >();
}

/// @brief Create an object of the desired type (or, more precisely, an API container
/// for an object of a desired type).
/// @details Must be implemented by derived classes.
masala::base::managers::plugin_module::MasalaPluginAPISP
<__CREATOR_CLASS_API_NAME__>::encapsulate_plugin_object_instance(
	masala::base::managers::plugin_module::MasalaPluginSP const & object
) const {
	return masala::make_shared< <__SOURCE_CLASS_API_NAME__> >(
		std::static_pointer_cast< <__SOURCE_CLASS_NAMESPACE_AND_NAME__> >(
			object
		)
	);
}

/// @brief Create an object of the desired type (or, more precisely, an API container
/// for an object of a desired type).
/// @details Must be implemented by derived classes.
masala::base::managers::plugin_module::MasalaPluginAPICSP
<__CREATOR_CLASS_API_NAME__>::encapsulate_const_plugin_object_instance(
	masala::base::managers::plugin_module::MasalaPluginCSP const & object
) const {
    // On the following line, note that std::const_pointer_cast is safe to use.  We might
    // cast away the constness of the object, but if we do, we effectively restore it by
    // encapsulating it in a const API object (in that case) that only allows const access.
    // This is ONLY allowed in Masala code that is auto-generated in a manner that ensures
    // that nothing unsafe is done with the nonconst object.
	return masala::make_shared< <__SOURCE_CLASS_API_NAME__> >(
		std::const_pointer_cast< <__SOURCE_CLASS_NAMESPACE_AND_NAME__> >(
			std::static_pointer_cast< <__SOURCE_CLASS_NAMESPACE_AND_NAME__> const >(
				object
			)
		)
	);
}

/// @brief Return the names of the categories for this type of plugin object.
/// @returns In this case, returns { <__PLUGIN_CATEGORIES__> }.
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector).
/// A plugin can be in more than one hierarchical category, but must be in at least one.  The
/// first one is used as the primary key.
std::vector< std::vector< std::string > >
<__CREATOR_CLASS_API_NAME__>::get_plugin_object_categories() const {
	return std::vector< std::vector< std::string > >{
		<__PLUGIN_CATEGORIES__>
	};
}

/// @brief Return keywords associated with this plugin module.
/// @returns This override returns { <__PLUGIN_KEYWORDS__> }.
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_plugin_object_keywords() const {
	return std::vector< std::string >{
		<__PLUGIN_KEYWORDS__>
	};
}

/// @brief Get The name of the class of object that this creator creates.
/// @returns This override returns "<__SOURCE_CLASS_NAME__>".
std::string
<__CREATOR_CLASS_API_NAME__>::get_plugin_object_name() const {
	return "<__SOURCE_CLASS_NAME__>";
}

/// @brief Get the namespace of the class of object that this creator creates.
/// @returns This override returns <__SOURCE_CLASS_NAMESPACE__>.
std::string
<__CREATOR_CLASS_API_NAME__>::get_plugin_object_namespace() const {
	return "<__SOURCE_CLASS_NAMESPACE__>";
}

/// @brief Get the class name.
/// @returns Returns "<__CREATOR_CLASS_API_NAME__>".
std::string
<__CREATOR_CLASS_API_NAME__>::class_name() const {
	return "<__CREATOR_CLASS_API_NAME__>";
}

/// @brief Get the class namespace.
/// @returns Returns "<__CREATOR_CLASS_API_NAMESPACE__>".
std::string
<__CREATOR_CLASS_API_NAME__>::class_namespace() const {
	return "<__CREATOR_CLASS_API_NAMESPACE__>";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS FOR MaslaDataRepresentations
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the categories that this data representation plugin falls into.
/// @details Categories are hierarchical, with the hierarchy represented as a vector of
/// strings.  One data representation category can be classified into multiple categories.
/// @returns { <__DATA_REPRESENTATION_CATEGORIES__> }
std::vector< std::vector< std::string > >
<__CREATOR_CLASS_API_NAME__>::get_data_representation_categories() const {
	return std::vector< std::vector< std::string > > {
		<__DATA_REPRESENTATION_CATEGORIES__>
	};
}

/// @brief Get the MasalaEngines that with which this data representation plugin
/// is DEFINITELY compatible.  (There may be other engines with which it is also
/// compatible, so this is not necessarily an exhaustive list.)
/// @note The list is by full name (i.e. namespace + name), so for instance
/// "specialized_masala_plugins::optimizers::SpecializedChargeOptimizer".
/// @returns { <__DATA_REPRESENTATION_COMPATIBLE_ENGINES__> }
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_compatible_masala_engines() const {
	return std::vector< std::string >{ <__DATA_REPRESENTATION_COMPATIBLE_ENGINES__> };
}

/// @brief Get the MasalaEngines that with which this data representation plugin
/// is DEFINITELY NOT compatible.  (There may be other engines with which it is also
/// not compatible, so this is not necessarily an exhaustive list.)
/// @details The default implementation returns an empty list.
/// @note The list is by full name (i.e. namespace + name), so for instance
/// "specialized_masala_plugins::optimizers::SpecializedChargeOptimizer".
/// @returns { <__DATA_REPRESENTATION_INCOMPATIBLE_ENGINES__> }
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_incompatible_masala_engines() const {
	return std::vector< std::string >{ <__DATA_REPRESENTATION_INCOMPATIBLE_ENGINES__> };
}

/// @brief Get the properties that this MasalaDataRepresentation has.  (Note that this can be
/// a non-exhaustive list.  If one data representation says it has the property
/// "linearly-scaling", another could also be linearly scaling despite not listing this.)
/// @returns { <__DATA_REPRESENTATION_PRESENT_PROPERTIES__> }
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_present_data_representation_properties() const {
	return std::vector< std::string >{ <__DATA_REPRESENTATION_PRESENT_PROPERTIES__> };
}

/// @brief Get the properties of this MasalaDataRepresentation that might possibly be present.
/// @details Obviously, this is a non-exhuastive list.
/// @returns { <__DATA_REPRESENTATION_POSSIBLY_PRESENT_PROPERTIES__> }
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_possibly_present_data_representation_properties() const {
	return std::vector< std::string >{ <__DATA_REPRESENTATION_POSSIBLY_PRESENT_PROPERTIES__> };
}

/// @brief Get the properties that this MasalaDataRepresentation DEFINITELY lacks.
/// Note that this is inevitably a non-exhaustive list.
/// @returns { <__DATA_REPRESENTATION_ABSENT_PROPERTIES__> }
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_absent_data_representation_properties() const {
	return std::vector< std::string >{ <__DATA_REPRESENTATION_ABSENT_PROPERTIES__> };
}

/// @brief Get the properties of this MasalaDataRepresentation that might possibly be absent.
/// @details Obviously, this is a non-exhuastive list.
/// @returns { <__DATA_REPRESENTATION_POSSIBLY_ABSENT_PROPERTIES__> }
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_possibly_absent_data_representation_properties() const {
	return std::vector< std::string >{ <__DATA_REPRESENTATION_POSSIBLY_ABSENT_PROPERTIES__> };
}

<__CPP_END_NAMESPACE__>
