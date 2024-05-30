<__COMMENTED_LICENCE__>

<__DOXYGEN_CREATOR_FILE_PATH_AND_HH_FILE_NAME__>
/// @brief Headers for the creator for the
/// <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class.
/// @details Creators are needed to allow the Masala plugin system to use objects
/// defined in plugin libraries, and for the Masala file interpreter
/// system to be able to create file interpreters compatible with particular
/// engines.
<__DOXYGEN_AUTHOR_AND_EMAIL__>

<__CPP_CREATOR_HH_HEADER_GUARD__>

// Forward declarations:
<__CREATOR_INCLUDE_FILE_PATH_AND_FWD_FILE_NAME__>

// Base headers:
<__PLUGIN_CREATOR_BASE_INCLUDE_FILE__>

// STL headers:
#include <vector>
#include <string>

<__CPP_NAMESPACE__>

/// @brief Headers for the creator for the
/// <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class.
/// @details Creators are needed to allow the Masala plugin system to use objects
/// defined in plugin libraries, and for the Masala file interpreter
/// system to be able to create file interpreters compatible with particular
/// engines.
<__DOXYGEN_AUTHOR_AND_EMAIL__>
class <__CREATOR_CLASS_API_NAME__> : public <__PLUGIN_CREATOR_BASE_CLASS__> {

public:

	/// @brief Default constructor.
	<__CREATOR_CLASS_API_NAME__>() = default;

	/// @brief Copy constructor.
	<__CREATOR_CLASS_API_NAME__>( <__CREATOR_CLASS_API_NAME__> const & ) = default;

	/// @brief Virtual destructor.
	~<__CREATOR_CLASS_API_NAME__>() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS FOR MaslaPlugins
////////////////////////////////////////////////////////////////////////////////

	/// @brief Create an object of the desired type (in this case, a
	/// <__SOURCE_CLASS_NAMESPACE_AND_NAME__>,
	/// encapsulated in an API container).
	/// @returns A new instance of an <__SOURCE_CLASS_NAMESPACE_AND_NAME__> API container.
	/// @details Must be implemented by derived classes.
	masala::base::managers::plugin_module::MasalaPluginAPISP
	create_plugin_object() const override;

	/// @brief Create an object of the desired type (or, more precisely, an API container
	/// for an object of a desired type).
	/// @details Must be implemented by derived classes.
	masala::base::managers::plugin_module::MasalaPluginAPISP
	encapsulate_plugin_object_instance(
		masala::base::managers::plugin_module::MasalaPluginSP const & object
	) const override;

	/// @brief Create an object of the desired type (or, more precisely, an API container
	/// for an object of a desired type).
	/// @details Must be implemented by derived classes.
	masala::base::managers::plugin_module::MasalaPluginAPICSP
	encapsulate_const_plugin_object_instance(
		masala::base::managers::plugin_module::MasalaPluginCSP const & object
	) const override;

	/// @brief Return the names of the categories for this type of plugin object.
	/// @returns In this case, returns { <__PLUGIN_CATEGORIES__> }.
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector).
	/// A plugin can be in more than one hierarchical category, but must be in at least one.  The
	/// first one is used as the primary key.
	std::vector< std::vector< std::string > >
	get_plugin_object_categories() const override; 

	/// @brief Return keywords associated with this plugin module.
	/// @returns This override returns { <__PLUGIN_KEYWORDS__> }.
	std::vector< std::string >
	get_plugin_object_keywords() const override;

	/// @brief Get The name of the class of object that this creator creates.
	/// @returns This override returns "<__SOURCE_CLASS_NAME__>".
	std::string
	get_plugin_object_name() const override;

	/// @brief Get the namespace of the class of object that this creator creates.
	/// @returns This override returns "<__SOURCE_CLASS_NAMESPACE__>".
	std::string
	get_plugin_object_namespace() const override;

	/// @brief Get the class name for this class (the creator class).
	/// @returns Returns "<__CREATOR_CLASS_API_NAME__>".
	std::string class_name() const override;

	/// @brief Get the class namespace for this class (the creator class).
	/// @returns Returns "<__CREATOR_CLASS_API_NAMESPACE__>".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS FOR MaslaFileInterpreters
////////////////////////////////////////////////////////////////////////////////

   	/// @brief Get the descriptors for the file types that the file interpreter created by this creator manages.
	/// @details Descriptors may be something like "protein_data_bank_file".  A given file interpreter may
	/// manage more than one file type.
	/// @returns { <__FILE_INTERPRETER_FILE_DESCRIPTIONS__> }
	/// @note Must be implemented by derived classes.
	std::vector< std::string >
	get_file_interpreter_file_descriptors() const override;

	/// @brief Get the extensions for the file types that the file interpreter created by this creator manages.
	/// @details Extensions may be something like "pdb".  A given file interpreter may
	/// manage more than one file extension.
	/// @returns { <__FILE_INTERPRETER_FILE_EXTENSIONS__> }
	/// @note Must be implemented by derived classes.
	std::vector< std::string >
	get_file_interpreter_file_extensions() const override;

}; // class <__CREATOR_CLASS_API_NAME__>

<__CPP_END_NAMESPACE__>

<__CPP_END_HH_HEADER_GUARD__>
