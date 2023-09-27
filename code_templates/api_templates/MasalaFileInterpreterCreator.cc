<__COMMENTED_LICENCE__>

<__DOXYGEN_CREATOR_FILE_PATH_AND_CC_FILE_NAME__>
/// @brief Function implementations for the creator for the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class.
/// @details Creators are needed to allow the Masala plugin system to use objects
/// defined in plugin libraries, and for the Masala file interpreter
/// system to be able to create file interpreters compatible with particular
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

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

<__IS_SOURCE_CLASS_API_NOT_INSTANTIABLE__>

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
#ifdef <__SOURCE_CLASS_API_NAME__>_NOT_INSTANTIABLE
	MASALA_THROW( "<__CREATOR_CLASS_API_NAME__>", "create_plugin_object",
		"The <__SOURCE_CLASS_API_NAME__> data representation class is not instantiable."
	);
	return nullptr;
#else
	return masala::make_shared< <__SOURCE_CLASS_API_NAME__> >();
#endif
}

/// @brief Create an object of the desired type (or, more precisely, an API container
/// for an object of a desired type).
/// @details Must be implemented by derived classes.
masala::base::managers::plugin_module::MasalaPluginAPISP
<__CREATOR_CLASS_API_NAME__>::encapsulate_plugin_object_instance(
	masala::base::managers::plugin_module::MasalaPluginSP const & <__OBJECT_OR_COMMENTED__>
) const {
#ifdef <__SOURCE_CLASS_API_NAME__>_NOT_INSTANTIABLE
	MASALA_THROW( "<__CREATOR_CLASS_API_NAME__>", "encapsulate_plugin_object_instance",
		"The <__SOURCE_CLASS_API_NAME__> data representation class is not instantiable."
	);
	return nullptr;
#else
	return masala::make_shared< <__SOURCE_CLASS_API_NAME__> >(
		std::static_pointer_cast< <__SOURCE_CLASS_NAMESPACE_AND_NAME__> >(
			object
		)
	);
#endif
}

/// @brief Create an object of the desired type (or, more precisely, an API container
/// for an object of a desired type).
/// @details Must be implemented by derived classes.
masala::base::managers::plugin_module::MasalaPluginAPICSP
<__CREATOR_CLASS_API_NAME__>::encapsulate_const_plugin_object_instance(
	masala::base::managers::plugin_module::MasalaPluginCSP const & <__OBJECT_OR_COMMENTED__>
) const {
#ifdef <__SOURCE_CLASS_API_NAME__>_NOT_INSTANTIABLE
	MASALA_THROW( "<__CREATOR_CLASS_API_NAME__>", "encapsulate_const_plugin_object_instance",
		"The <__SOURCE_CLASS_API_NAME__> data representation class is not instantiable."
	);
	return nullptr;
#else
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
#endif
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
// PUBLIC MEMBER FUNCTIONS FOR MaslaFileInterpreters
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the descriptors for the file types that the file interpreter created by this creator manages.
/// @details Descriptors may be something like "protein_data_bank_file".  A given file interpreter may
/// manage more than one file type.
/// @returns { <__FILE_INTERPRETER_FILE_DESCRIPTIONS__> }
/// @note Must be implemented by derived classes.
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_file_interpreter_file_descriptors() const {
	return { <__FILE_INTERPRETER_FILE_DESCRIPTIONS__> };
}

/// @brief Get the extensions for the file types that the file interpreter created by this creator manages.
/// @details Extensions may be something like "pdb".  A given file interpreter may
/// manage more than one file extension.
/// @returns { <__FILE_INTERPRETER_FILE_EXTENSIONS__> }
/// @note Must be implemented by derived classes.
std::vector< std::string >
<__CREATOR_CLASS_API_NAME__>::get_file_interpreter_file_extensions() const {
	return { <__FILE_INTERPRETER_FILE_EXTENSIONS__> };
}

<__CPP_END_NAMESPACE__>
