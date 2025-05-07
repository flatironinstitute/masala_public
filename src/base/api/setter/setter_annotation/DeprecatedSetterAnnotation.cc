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

/// @file src/base/api/setter/setter_annotation/DeprecatedSetterAnnotation.cc
/// @brief Implementations for a setter annotation that indicates that a particular setter has
/// been deprecated or will be deprecated in a future version of this library.  If the Masala library
/// version is greater than or equal to that indicated in this setter, then the setter is excluded from
/// the API definition.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/setter/setter_annotation/DeprecatedSetterAnnotation.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////


/// @brief Constructor that only sets the deprecation version.  Warnings are always enabled.
DeprecatedSetterAnnotation::DeprecatedSetterAnnotation(
	std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
) :
	Parent(),
	version_set_at_which_warnings_start_( false ),
	version_at_which_warnings_start_( std::make_pair(0, 0) ),
	version_at_which_function_deprecated_( version_at_which_function_deprecated )
{}

/// @brief Constructor that only sets both the version at which warnings start and the deprecation version.
DeprecatedSetterAnnotation::DeprecatedSetterAnnotation(
	std::pair< masala::base::Size, masala::base::Size > const & version_at_which_warnings_start,
	std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
) :
	Parent(),
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
		"DeprecatedSetterAnnotation",
		"The version at which the function is deprecated must be after the version at which warnings start."
	);
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("DeprecatedSetterAnnotation").
std::string
DeprecatedSetterAnnotation::class_name() const {
	return "DeprecatedSetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
std::string
DeprecatedSetterAnnotation::class_namespace() const {
	return "masala::base::api::setter::setter_annotation";
}


/// @brief Get the class name ("DeprecatedSetterAnnotation").  Static version.
/*static*/
std::string
DeprecatedSetterAnnotation::class_name_static() {
	return "DeprecatedSetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").  Static version.
/*static*/
std::string
DeprecatedSetterAnnotation::class_namespace_static() {
	return "masala::base::api::setter::setter_annotation";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get whether a version has been set for starting the warnings.
bool
DeprecatedSetterAnnotation::version_set_at_which_warnings_start() const {
	return version_set_at_which_warnings_start_;
}

/// @brief Get the version at which warnings start.
/// @details Throws if no version has been set, so check whether a version has been set at which
/// warnings start using version_set_at_which_warnings_start() first before calling this function.
std::pair< masala::base::Size, masala::base::Size > const &
DeprecatedSetterAnnotation::version_at_which_warnings_start() const {
	CHECK_OR_THROW_FOR_CLASS( version_set_at_which_warnings_start_, "version_at_which_warnings_start",
		"No version was set at which warnings should start."
	);
	return version_at_which_warnings_start_;
}

/// @brief Get the version at which the function is deprecated.
std::pair< masala::base::Size, masala::base::Size > const &
DeprecatedSetterAnnotation::version_at_which_function_deprecated() const {
	return version_at_which_function_deprecated_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get any additional description that this annotation provides.
/// @details This override returns "This setter is not intended for inclusion in user interfaces or graphical user interfaces."
std::string
DeprecatedSetterAnnotation::get_additional_description() const {
	return "This setter is not intended for inclusion in user interfaces or graphical user interfaces.";
}

/// @brief Modify the JSON description to indicate that this setter should not be included in UIs or GUIs.
void
DeprecatedSetterAnnotation::modify_json_description(
	nlohmann::json & json_description
) const {
	json_description["Not_For_User_Interface"] = true;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign src to this.  Performs no mutex-locking.
/// @details Derived classes should override this, and the overrides should call this function.
void
DeprecatedSetterAnnotation::protected_assign(
    MasalaFunctionAnnotation const & src
) /*override*/ {
    DeprecatedSetterAnnotation const * src_cast_ptr( dynamic_cast< DeprecatedSetterAnnotation const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " class could not be interpreted as a DeprecatedSetterAnnotation object." );
    
	// TODO -- do any assignment here.

    MasalaSetterFunctionAnnotation::protected_assign( src );
}

/// @brief Is this annotation one that can be applied to this setter?
/// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This
/// override checks that (a) the setter takes one input, and (b) that the one input is either a MasalaPluginAPISP, a MasalaEngineAPISP,
/// a MasalaDataRepresentationAPISP, or the equivalent const shared pointers, or instances or const instances of any of these.  This
/// function performs no mutex locking.
/// @returns True if it is compatible, false otherwise.  Called by the setter API definition's add_setter_annotation() function.
bool
DeprecatedSetterAnnotation::protected_is_compatible_with_setter(
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & /*setter*/
) const /*override*/ {
	 return true;
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
