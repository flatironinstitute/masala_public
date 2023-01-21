<__COMMENTED_LICENCE__>

<__DOXYGEN_FILE_PATH_AND_CC_FILE_NAME__>
<__DOXYGEN_BRIEF_DESCRIPTION__>
<__DOXYGEN_DETAILED_DESCRIPTION__>
<__DOXYGEN_AUTHOR_AND_EMAIL__>
/// @note This file is an auto-generated API file.  Do not edit it, but instead
/// edit the <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class's
/// get_api_definition() function.

// Unit header:
<__INCLUDE_FILE_PATH_AND_HH_FILE_NAME__>

// Source class header:
<__INCLUDE_SOURCE_FILE_PATH_AND_HH_FILE_NAME__>

// Additional API headers:
<__CPP_ADDITIONAL_HH_INCLUDES__>

// STL header:
#include <string>

<__CPP_NAMESPACE__>

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

<__CPP_CONSTRUCTOR_IMPLEMENTATIONS__>

/// @brief Constructor from shared pointer to object.
/// @details Directly uses the object that is passed in.  Does not clone it.
<__SOURCE_CLASS_API_NAME__>::<__SOURCE_CLASS_API_NAME__>(
    <__SOURCE_CLASS_NAMESPACE_AND_NAME__>SP const & inner_object
) :
    <__BASE_API_CLASS_NAMESPACE_AND_NAME__>(),
    inner_object_( inner_object )
{}

/// @brief Assignment operator.
/// @details Performs assignment on the inner object.
<__SOURCE_CLASS_API_NAME__> &
<__SOURCE_CLASS_API_NAME__>::operator=(
    <__SOURCE_CLASS_API_NAME__> const & src
) {
    std::lock_guard< std::mutex > lock( api_mutex_ );
    std::lock_guard< std::mutex > lock2( src.api_mutex_ );
    (*inner_object_) = (*src.inner_object_);
    return *this;
}

/// @brief Clone operation: make a copy of this object and return
/// a shared pointer to the copy.
<__SOURCE_CLASS_API_NAME__>SP
<__SOURCE_CLASS_API_NAME__>::clone() const {
    std::lock_guard< std::mutex > lock( api_mutex_ );
    return masala::make_shared< <__SOURCE_CLASS_API_NAME__> >( *this );
}

/// @brief Deep clone operation: make a copy of this object and return
/// a shared pointer to the copy, where the copy is fully independent
/// (all contents also deep-cloned).
<__SOURCE_CLASS_API_NAME__>SP    
<__SOURCE_CLASS_API_NAME__>::deep_clone() const {
    std::lock_guard< std::mutex > lock( api_mutex_ );
    <__SOURCE_CLASS_API_NAME__>SP object_copy( clone() );
    object_copy->make_independent();
    return object_copy;
}

/// @brief Deep clone all of the internal data for this object, making it fully
/// independent of any other object.
void
<__SOURCE_CLASS_API_NAME__>::make_independent() {
    std::lock_guard< std::mutex > lock( api_mutex_ );
    inner_object_ = inner_object_->deep_clone();
}

////////////////////////////////////////////////////////////////////////////////
// NAMING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this class.
/// @returns Returns "<__SOURCE_CLASS_API_NAME__>".
std::string
<__SOURCE_CLASS_API_NAME__>::class_name() const {
    return "<__SOURCE_CLASS_API_NAME__>";
}

/// @brief Get the namespace of this class.
/// @returns Returns "<__SOURCE_CLASS_API_NAMESPACE__>".
std::string
<__SOURCE_CLASS_API_NAME__>::class_namespace() const {
    return "<__SOURCE_CLASS_API_NAMESPACE__>";
}

/// @brief Get the name of the class for which this class provides an API.
/// @returns Returns "<__SOURCE_CLASS_NAME__>".
std::string
<__SOURCE_CLASS_API_NAME__>::inner_class_name() const {
    return inner_object_->class_name();
}

/// @brief Get the namespace of the class for which this class provides an API.
/// @returns Returns "<__SOURCE_CLASS_NAMESPACE__>".
std::string
<__SOURCE_CLASS_API_NAME__>::inner_class_namespace() const {
    return inner_object_->class_namespace();
}

/// @brief Get the API definition for the contained class.
/// @details Must be implemented by derived classes.
masala::base::api::MasalaObjectAPIDefinitionCWP
<__SOURCE_CLASS_API_NAME__>::get_api_definition_for_inner_class() {
    return inner_object_->get_api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

<__CPP_SETTER_IMPLEMENTATIONS__>

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Const access to the inner object.
<__SOURCE_CLASS_NAMESPACE_AND_NAME__>CSP
<__SOURCE_CLASS_API_NAME__>::get_inner_object() const {
    std::lock_guard< std::mutex > lock_guard( api_mutex_ );
    return inner_object_;
}

<__CPP_GETTER_IMPLEMENTATIONS__>

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

<__CPP_WORK_FUNCTION_IMPLEMENTATIONS__>

<__CPP_END_NAMESPACE__>
