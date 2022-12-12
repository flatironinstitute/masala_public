<__COMMENTED_LICENCE__>

<__DOXYGEN_CREATOR_FILE_PATH_AND_CC_FILE_NAME__>
/// @brief Function implementations for the creator for the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class.
/// @details Creators are needed to allow the Masala plugin system to use objects
/// defined in plugin libraries.
<__DOXYGEN_AUTHOR_AND_EMAIL__>
/// @note This file is an auto-generated API file.  Do not edit it, but instead
/// edit the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class's
/// get_api_definition() function.

// Header:
<__CREATOR_INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>

// Project headers:
<__API_INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>

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
masala::base::managers::plugin_module::MasalaPluginSP
<__CREATOR_CLASS_API_NAME__>::create_plugin_object() const {
	return masala::make_shared< <__SOURCE_CLASS_API_NAME__> >();
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

<__CPP_END_NAMESPACE__>
