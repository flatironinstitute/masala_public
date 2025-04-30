/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/base/api/constructor/constructor_annotation/MasalaConstructorAnnotation.cc
/// @brief Implementations for a pure virtual base class for constructor function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).


// Unit headers:
#include <base/api/constructor/constructor_annotation/MasalaConstructorAnnotation.hh>

// Base headers:
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>

// Error handling:
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace api {
namespace constructor {
namespace constructor_annotation {

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign src to this.  Performs no mutex-locking.
/// @details Derived classes should override this, and the overrides should call this function.
void
MasalaConstructorAnnotation::protected_assign(
    MasalaFunctionAnnotation const & src
) /*override*/ {
    MasalaConstructorAnnotation const * src_cast_ptr( dynamic_cast< MasalaConstructorAnnotation const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "protected_assign", "The " + src.class_name() + " class could not be interpreted as a MasalaConstructorAnnotation object." );

    masala::base::api::function_annotation::MasalaFunctionAnnotation::protected_assign( src );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Is this annotation one that can be applied to this constructor?
/// @details This function locks the mutex and calls protected_is_compatible_with_constructor(), which must be implemented by derived classes.
/// @returns True if it is compatible, false otherwise.  Called by the constructor API definition's add_constructor_annotation() function.
bool
MasalaConstructorAnnotation::is_compatible_with_constructor(
    masala::base::api::constructor::MasalaObjectAPIConstructorDefinition const & constructor
) const {
    std::lock_guard< std::mutex > lock( mutex() );
    return protected_is_compatible_with_constructor( constructor );
}

/// @brief Get any additional description that this annotation provides.
/// @details Intended for user-facing interfaces.  Base class returns an empty string.  May be overridden by derived classes.
/*virtual*/
std::string
MasalaConstructorAnnotation::get_additional_description() const {
	return "";
}

} // namespace constructor_annotation
} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala
