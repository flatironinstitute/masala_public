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

/// @file src/base/api/getter/getter_annotation/NoUIGetterAnnotation.cc
/// @brief Implementations for a getter function annotation that suggests to calling code that a
/// function should not be part of user-facing user interfaces.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/getter/getter_annotation/NoUIGetterAnnotation.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace base {
namespace api {
namespace getter {
namespace getter_annotation {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("NoUIGetterAnnotation").
std::string
NoUIGetterAnnotation::class_name() const {
	return "NoUIGetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::getter::getter_annotation").
std::string
NoUIGetterAnnotation::class_namespace() const {
	return "masala::base::api::getter::getter_annotation";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get any additional description that this annotation provides.
/// @details This override returns "This getter is not intended for inclusion in user interfaces or graphical user interfaces."
std::string
NoUIGetterAnnotation::get_additional_description() const {
	return "This getter is not intended for inclusion in user interfaces or graphical user interfaces.";
}

/// @brief Modify the JSON description to indicate that this getter should not be included in UIs or GUIs.
void
NoUIGetterAnnotation::modify_json_description(
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
NoUIGetterAnnotation::protected_assign(
    MasalaFunctionAnnotation const & src
) /*override*/ {
    NoUIGetterAnnotation const * src_cast_ptr( dynamic_cast< NoUIGetterAnnotation const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " class could not be interpreted as a NoUIGetterAnnotation object." );
    
	// TODO -- do any assignment here.

    MasalaGetterFunctionAnnotation::protected_assign( src );
}

/// @brief Is this annotation one that can be applied to this getter?
/// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This
/// override checks that (a) the getter takes one input, and (b) that the one input is either a MasalaPluginAPISP, a MasalaEngineAPISP,
/// a MasalaDataRepresentationAPISP, or the equivalent const shared pointers, or instances or const instances of any of these.  This
/// function performs no mutex locking.
/// @returns True if it is compatible, false otherwise.  Called by the getter API definition's add_getter_annotation() function.
bool
NoUIGetterAnnotation::protected_is_compatible_with_getter(
	masala::base::api::getter::MasalaObjectAPIGetterDefinition const & /*getter*/
) const /*override*/ {
	 return true;
}

} // namespace getter_annotation
} // namespace getter
} // namespace api
} // namespace base
} // namespace masala
