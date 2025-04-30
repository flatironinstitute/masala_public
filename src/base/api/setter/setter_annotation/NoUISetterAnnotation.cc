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

/// @file src/base/api/setter/setter_annotation/NoUISetterAnnotation.cc
/// @brief Implementations for a setter function annotation that suggests to calling code that a
/// function should not be part of user-facing user interfaces.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/setter/setter_annotation/NoUISetterAnnotation.hh>

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
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("NoUISetterAnnotation").
std::string
NoUISetterAnnotation::class_name() const {
	return "NoUISetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
std::string
NoUISetterAnnotation::class_namespace() const {
	return "masala::base::api::setter::setter_annotation";
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
/// @details This override returns "This setter is not intended for inclusion in user interfaces or graphical user interfaces."
std::string
NoUISetterAnnotation::get_additional_description() const {
	return "This setter is not intended for inclusion in user interfaces or graphical user interfaces.";
}

/// @brief Modify the JSON description to indicate that this setter should not be included in UIs or GUIs.
void
NoUISetterAnnotation::modify_json_description(
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
NoUISetterAnnotation::protected_assign(
    MasalaFunctionAnnotation const & src
) /*override*/ {
    NoUISetterAnnotation const * src_cast_ptr( dynamic_cast< NoUISetterAnnotation const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " class could not be interpreted as a NoUISetterAnnotation object." );
    
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
NoUISetterAnnotation::protected_is_compatible_with_setter(
	masala::base::api::setter::MasalaObjectAPISetterDefinition const & /*setter*/
) const /*override*/ {
	 return true;
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
