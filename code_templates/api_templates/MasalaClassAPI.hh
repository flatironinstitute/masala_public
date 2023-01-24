<__COMMENTED_LICENCE__>

<__DOXYGEN_FILE_PATH_AND_HH_FILE_NAME__>
<__DOXYGEN_BRIEF_DESCRIPTION__>
<__DOXYGEN_DETAILED_DESCRIPTION__>
<__DOXYGEN_AUTHOR_AND_EMAIL__>
/// @note This file is an auto-generated API file.  Do not edit it, but instead
/// edit the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class's
/// get_api_definition() function.

<__CPP_HH_HEADER_GUARD__>

// Unit header:
<__INCLUDE_FILE_PATH_AND_FWD_FILE_NAME__>

// Source class forward header:
<__INCLUDE_SOURCE_FILE_PATH_AND_FWD_FILE_NAME__>

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
class <__SOURCE_CLASS_API_NAME__> : public <__BASE_API_CLASS_NAMESPACE_AND_NAME__> {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

<__CPP_CONSTRUCTOR_PROTOTYPES__>

    /// @brief Constructor from shared pointer to object.
    /// @details Directly uses the object that is passed in.  Does not clone it.
    <__SOURCE_CLASS_API_NAME__>( <__SOURCE_CLASS_NAMESPACE_AND_NAME__>SP const & inner_object );

    /// @brief Destructor.
    ~<__SOURCE_CLASS_API_NAME__>() = default;

    /// @brief Assignment operator.
    /// @details Performs assignment on the inner object.
    <__SOURCE_CLASS_API_NAME__> &
    operator=(
        <__SOURCE_CLASS_API_NAME__> const & src
    );

    /// @brief Clone operation: make a copy of this object and return
    /// a shared pointer to the copy.
    <__SOURCE_CLASS_API_NAME__>SP
    clone() const;

    /// @brief Deep clone operation: make a copy of this object and return
    /// a shared pointer to the copy, where the copy is fully independent
    /// (all contents also deep-cloned).
    <__SOURCE_CLASS_API_NAME__>SP
    deep_clone() const;

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
    /// @details Must be implemented by derived classes.
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
    <__SOURCE_CLASS_NAMESPACE_AND_NAME__>CSP
    get_inner_object() const;

<__CPP_GETTER_PROTOTYPES__>

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

<__CPP_WORK_FUNCTION_PROTOTYPES__>

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED DATA ACCESS FOR DERIVED CLASSES
////////////////////////////////////////////////////////////////////////////////

    /// @brief Assumes that the mutex has been locked.  Performs no mutex-locking.
    /// @note This is a nonconst instance of the inner object nonconst pointer, so both the
    /// pointer and the object that it points to can be changed.
    <__SOURCE_CLASS_NAMESPACE_AND_NAME__>SP & inner_object();

    /// @brief Assumes that the mutex has been locked.  Performs no mutex-locking.
    /// @note Version for const access.
    <__SOURCE_CLASS_NAMESPACE_AND_NAME__>CSP const inner_object() const;

    /// @brief Access the base class mutex from derived classes.
    /// @note The mutex is mutable, so this function can be const.
    std::mutex & api_mutex() const;

private:

////////////////////////////////////////////////////////////////////////////////
// DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for locking the API.
    mutable std::mutex api_mutex_;

    /// @brief The instance of the class for which we're providing an API.
    <__SOURCE_CLASS_NAMESPACE_AND_NAME__>SP inner_object_;

}; //<__SOURCE_CLASS_API_NAME__>

<__CPP_END_NAMESPACE__>

<__CPP_END_HH_HEADER_GUARD__>
