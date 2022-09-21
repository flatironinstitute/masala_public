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

/// @brief Clone operation: make a copy of this object and return
/// a shared pointer to the copy.
<__SOURCE_CLASS_API_NAME__>SP
<__SOURCE_CLASS_API_NAME__>::clone() const {
    std::lock_guard< std::mutex > lock( api_mutex_ );
    return std::make_shared< <__SOURCE_CLASS_API_NAME__> >( *this );
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

/// @brief Get the name of this class.  Returns "<__SOURCE_CLASS_API_NAME__>".
std::string
<__SOURCE_CLASS_API_NAME__>::class_name() const {
    return "<__SOURCE_CLASS_API_NAME__>";
}

/// @brief Get the namespace of this class.  Returns "<__SOURCE_CLASS_API_NAMESPACE__>".
std::string
<__SOURCE_CLASS_API_NAME__>::class_namespace() const {
    return "<__SOURCE_CLASS_API_NAMESPACE__>";
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

<__CPP_SETTER_IMPLEMENTATIONS__>

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

<__CPP_GETTER_IMPLEMENTATIONS__>

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

<__CPP_WORK_FUNCTION_IMPLEMENTATIONS__>

<__CPP_END_NAMESPACE__>
