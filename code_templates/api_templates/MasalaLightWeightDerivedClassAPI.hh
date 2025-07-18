<__COMMENTED_LICENCE__>

<__DOXYGEN_FILE_PATH_AND_HH_FILE_NAME__>
<__DOXYGEN_BRIEF_DESCRIPTION__>
<__DOXYGEN_DETAILED_DESCRIPTION__>
<__DOXYGEN_AUTHOR_AND_EMAIL__>
/// @note This file is an auto-generated API file.  Do not edit it, but instead
/// edit the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class's
/// get_api_definition() function.
/// Also note that this is a special case API object built for a lightweight
/// inner object that could be stack-allocated.

<__CPP_HH_HEADER_GUARD__>

// Unit header:
<__INCLUDE_FILE_PATH_AND_FWD_FILE_NAME__>

// Source class header:
<__INCLUDE_SOURCE_FILE_PATH_AND_HH_FILE_NAME__>

// Base headers:
<__INCLUDE_BASE_API_CLASS_HH_FILE__>

// Forward declarations for additional API headers:
<__CPP_ADDITIONAL_FWD_INCLUDES__>

// STL headers:
#include <mutex>

<__CPP_NAMESPACE__>

<__DOXYGEN_BRIEF_DESCRIPTION__>
<__DOXYGEN_DETAILED_DESCRIPTION__>
<__DOXYGEN_AUTHOR_AND_EMAIL__>
/// @note Note that this is a special case API object built for a lightweight
/// inner object that could be stack-allocated.
class <__SOURCE_CLASS_API_NAME__> : public <__BASE_API_CLASS_NAMESPACE_AND_NAME__> {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

<__CPP_CONSTRUCTOR_PROTOTYPES__>

public:

    /// @brief Constructor from object instance.
    /// @details Copies the object passed in.
    <__SOURCE_CLASS_API_NAME__>( <__SOURCE_CLASS_NAMESPACE_AND_NAME__> const & inner_object );

    /// @brief Destructor.
    ~<__SOURCE_CLASS_API_NAME__>() = default;

    /// @brief Assignment operator.
    /// @details Performs assignment on the inner object.
    <__SOURCE_CLASS_API_NAME__> &
    operator=(
        <__SOURCE_CLASS_API_NAME__> const & src
    );

    <__POSSIBLE_COMMENT_START_FOR_PROTECTED_CONSTRUCTOR_CLASSES__>
    /// @brief Clone operation: make a copy of this object and return
    /// a shared pointer to the copy.
    <__SOURCE_CLASS_API_NAME__>SP
    clone() const;

    /// @brief Deep clone operation: make a copy of this object and return
    /// a shared pointer to the copy, where the copy is fully independent
    /// (all contents also deep-cloned).
    <__SOURCE_CLASS_API_NAME__>SP
    deep_clone() const;
    <__POSSIBLE_COMMENT_END_FOR_PROTECTED_CONSTRUCTOR_CLASSES__>

    /// @brief Deep clone all of the internal data for this object, making it fully
    /// independent of any other object.
    void
    make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// NAMING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns Returns "<__SOURCE_CLASS_API_NAME__>".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns Returns "<__SOURCE_CLASS_API_NAMESPACE__>".
    std::string
    class_namespace() const override;

    /// @brief Get the name of the class for which this class provides an API.
    /// @returns Returns "<__SOURCE_CLASS_NAME__>".
    std::string
    inner_class_name() const override;

    /// @brief Get the namespace of the class for which this class provides an API.
    /// @returns Returns "<__SOURCE_CLASS_NAMESPACE__>".
    std::string
    inner_class_namespace() const override;

    /// @brief Get the API definition for the contained class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition_for_inner_class() override;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

<__CPP_SETTER_PROTOTYPES__>

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Const access to the inner object.
    <__SOURCE_CLASS_NAMESPACE_AND_NAME__> const &
    get_inner_object() const;

    /// @brief Nonconst access to the inner object.
    <__SOURCE_CLASS_NAMESPACE_AND_NAME__> &
    get_inner_object();

<__CPP_GETTER_PROTOTYPES__>

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

<__CPP_WORK_FUNCTION_PROTOTYPES__>

private:

////////////////////////////////////////////////////////////////////////////////
// DATA
////////////////////////////////////////////////////////////////////////////////

    // Note that the API mutex and inner object are defined in the base API class,
    // not in the derived API class.

}; //<__SOURCE_CLASS_API_NAME__>

<__CPP_END_NAMESPACE__>

<__CPP_END_HH_HEADER_GUARD__>
