<__COMMENTED_LICENCE__>

<__DOXYGEN_CREATOR_FILE_PATH_AND_FWD_FILE_NAME__>
/// @brief Forward declaration for the creator for the
/// <__SOURCE_CLASS_NAMESPACE_AND_NAME__> class.
/// @details Creators are needed to allow the Masala plugin system to use objects
/// defined in plugin libraries.
<__DOXYGEN_AUTHOR_AND_EMAIL__>

<__CPP_CREATOR_FWD_HEADER_GUARD__>

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

<__CPP_NAMESPACE__>

	class <__CREATOR_CLASS_API_NAME__>;

	using <__CREATOR_CLASS_API_NAME__>SP = MASALA_SHARED_POINTER< <__CREATOR_CLASS_API_NAME__> >;
	using <__CREATOR_CLASS_API_NAME__>CSP = MASALA_SHARED_POINTER< <__CREATOR_CLASS_API_NAME__> const >;
	using <__CREATOR_CLASS_API_NAME__>WP = MASALA_WEAK_POINTER< <__CREATOR_CLASS_API_NAME__> >;
	using <__CREATOR_CLASS_API_NAME__>CWP = MASALA_WEAK_POINTER< <__CREATOR_CLASS_API_NAME__> const >;

<__CPP_END_NAMESPACE__>

<__CPP_END_FWD_HEADER_GUARD__>
