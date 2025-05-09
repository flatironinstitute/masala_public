/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/base/api/constructor/constructor_annotation/DeprecatedConstructorAnnotation.cc
/// @brief Implementations for a constructor annotation that indicates that a particular constructor has
/// been deprecated or will be deprecated in a future version of this library.  If the Masala library
/// version is greater than or equal to that indicated in this constructor, then the constructor is excluded from
/// the API definition.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/constructor/constructor_annotation/DeprecatedConstructorAnnotation.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace base {
namespace api {
namespace constructor {
namespace constructor_annotation {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////


/// @brief Constructor that only sets the deprecation version.  Warnings are always enabled.
DeprecatedConstructorAnnotation::DeprecatedConstructorAnnotation(
	std::string const & library_name,
	std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
) :
	Parent(),
	library_name_(library_name),
	version_set_at_which_warnings_start_( false ),
	version_at_which_warnings_start_( std::make_pair(0, 0) ),
	version_at_which_function_deprecated_( version_at_which_function_deprecated )
{}

/// @brief Constructor that only sets both the version at which warnings start and the deprecation version.
DeprecatedConstructorAnnotation::DeprecatedConstructorAnnotation(
	std::string const & library_name,
	std::pair< masala::base::Size, masala::base::Size > const & version_at_which_warnings_start,
	std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
) :
	Parent(),
	library_name_(library_name),
	version_set_at_which_warnings_start_( true ),
	version_at_which_warnings_start_( version_at_which_warnings_start ),
	version_at_which_function_deprecated_( version_at_which_function_deprecated )
{
	CHECK_OR_THROW(
		( version_at_which_warnings_start_.first < version_at_which_function_deprecated.first ) ||
		(
			version_at_which_warnings_start_.first == version_at_which_function_deprecated.first &&
			version_at_which_warnings_start_.second < version_at_which_function_deprecated.second
		),
		class_namespace_static() + "::" + class_name_static(),
		"DeprecatedConstructorAnnotation",
		"The version at which the function is deprecated must be after the version at which warnings start."
	);
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("DeprecatedConstructorAnnotation").
std::string
DeprecatedConstructorAnnotation::class_name() const {
	return "DeprecatedConstructorAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::constructor::constructor_annotation").
std::string
DeprecatedConstructorAnnotation::class_namespace() const {
	return "masala::base::api::constructor::constructor_annotation";
}


/// @brief Get the class name ("DeprecatedConstructorAnnotation").  Static version.
/*static*/
std::string
DeprecatedConstructorAnnotation::class_name_static() {
	return "DeprecatedConstructorAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::constructor::constructor_annotation").  Static version.
/*static*/
std::string
DeprecatedConstructorAnnotation::class_namespace_static() {
	return "masala::base::api::constructor::constructor_annotation";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get whether a version has been set for starting the warnings.
bool
DeprecatedConstructorAnnotation::version_set_at_which_warnings_start() const {
	return version_set_at_which_warnings_start_;
}

/// @brief Get the version at which warnings start.
/// @details Throws if no version has been set, so check whether a version has been set at which
/// warnings start using version_set_at_which_warnings_start() first before calling this function.
std::pair< masala::base::Size, masala::base::Size > const &
DeprecatedConstructorAnnotation::version_at_which_warnings_start() const {
	CHECK_OR_THROW_FOR_CLASS( version_set_at_which_warnings_start_, "version_at_which_warnings_start",
		"No version was set at which warnings should start."
	);
	return version_at_which_warnings_start_;
}

/// @brief Get the version at which the function is deprecated.
std::pair< masala::base::Size, masala::base::Size > const &
DeprecatedConstructorAnnotation::version_at_which_function_deprecated() const {
	return version_at_which_function_deprecated_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get any additional description that this annotation provides.
std::string
DeprecatedConstructorAnnotation::get_additional_description() const {
	std::string const outmsg1(
		"This function will be deprecated in version " + std::to_string( version_at_which_function_deprecated_.first ) +
		"." + std::to_string( version_at_which_function_deprecated_.second ) + " of the " + library_name_ + " Masala library."
	);
	if( version_set_at_which_warnings_start_ ) {
		return outmsg1 + "  Deprecation warnings will begin in version " + std::to_string( version_at_which_warnings_start_.first ) +
			"." + std::to_string( version_at_which_warnings_start_.second ) + ".";
	}
	return outmsg1;
}

/// @brief Modify the JSON description to indicate that this constructor should not be included in UIs or GUIs.
void
DeprecatedConstructorAnnotation::modify_json_description(
	nlohmann::json & json_description
) const {
	json_description["Will_Be_Deprecated"] = true;
	json_description["Library_Name_For_Deprecation_Version"] = library_name_;
	json_description["Deprecation_Major_Version"] = version_at_which_function_deprecated_.first;
	json_description["Deprecation_Minor_Version"] = version_at_which_function_deprecated_.second;
	if( version_set_at_which_warnings_start_ ) {
		json_description["Deprecation_Warning_Major_Version"] = version_at_which_function_deprecated_.first;
		json_description["Deprecation_Warning_Minor_Version"] = version_at_which_function_deprecated_.second;
	}
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign src to this.  Performs no mutex-locking.
/// @details Derived classes should override this, and the overrides should call this function.
void
DeprecatedConstructorAnnotation::protected_assign(
    MasalaFunctionAnnotation const & src
) /*override*/ {
    DeprecatedConstructorAnnotation const * src_cast_ptr( dynamic_cast< DeprecatedConstructorAnnotation const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " class could not be interpreted as a DeprecatedConstructorAnnotation object." );
    
	// TODO -- do any assignment here.
	library_name_ = src_cast_ptr->library_name_;
	version_set_at_which_warnings_start_ = src_cast_ptr->version_set_at_which_warnings_start_;
	version_at_which_warnings_start_ = src_cast_ptr->version_at_which_warnings_start_;
	version_at_which_function_deprecated_ = src_cast_ptr->version_at_which_function_deprecated_;

    MasalaConstructorAnnotation::protected_assign( src );
}

/// @brief Is this annotation one that can be applied to this constructor?
/// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This
/// override checks that (a) the constructor takes one input, and (b) that the one input is either a MasalaPluginAPISP, a MasalaEngineAPISP,
/// a MasalaDataRepresentationAPISP, or the equivalent const shared pointers, or instances or const instances of any of these.  This
/// function performs no mutex locking.
/// @returns True if it is compatible, false otherwise.  Called by the constructor API definition's add_constructor_annotation() function.
bool
DeprecatedConstructorAnnotation::protected_is_compatible_with_constructor(
	masala::base::api::constructor::MasalaObjectAPIConstructorDefinition const & constructor
) const /*override*/ {
	using masala::base::Size;
	Size const nannot( constructor.n_constructor_annotations() );
	for( Size i(0); i<nannot; ++i ) {
		DeprecatedConstructorAnnotationCSP annot_cast( std::dynamic_pointer_cast< DeprecatedConstructorAnnotation const >( constructor.constructor_annotation(i) ) );
		if( annot_cast != nullptr ) { return false; } // Cannot have more than one deprecation annotation.
	}
	return true;
}

} // namespace constructor_annotation
} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala
