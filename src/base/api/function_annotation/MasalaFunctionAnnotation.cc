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

/// @file src/base/api/function_annotation/MasalaFunctionAnnotation.cc
/// @brief Impementations for a pure virtual base class for function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <base/api/function_annotation/MasalaFunctionAnnotation.hh>

namespace masala {
namespace base {
namespace api {
namespace function_annotation {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.  Implemented manually due to mutex.
MasalaFunctionAnnotation::MasalaFunctionAnnotation(
    MasalaFunctionAnnotation const & src
) :
    masala::base::MasalaObject( src )
{
    std::lock( mutex_, src.mutex_ );
    std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
    protected_assign( src );
}

/// @brief Assignment operator.  Implemented manually due to mutex.
MasalaFunctionAnnotation &
MasalaFunctionAnnotation::operator=(
    MasalaFunctionAnnotation const & src
) {
    std::lock( mutex_, src.mutex_ );
    std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
    protected_assign( src );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get any additional description that this annotation provides.
/// @details Intended for user-facing interfaces.  Base class returns an empty string.  May be overridden by derived classes.
/*virtual*/
std::string
MasalaFunctionAnnotation::get_additional_description() const {
	return "";
}

/// @brief Modify the JSON description for this function.
/// @details Should be implemented by derived classes.  Base class version does nothing.
/*virtual*/
void
MasalaFunctionAnnotation::modify_json_description(
	nlohmann::json & //json_description
) const {
	//GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


/// @brief Assign src to this.  Performs no mutex-locking.
/// @details Derived classes should override this, and the overrides should call this function.
/*virtual*/
void
MasalaFunctionAnnotation::protected_assign(
    MasalaFunctionAnnotation const & //src
) {
    // GNDN.
}


} // namespace function_annotation
} // namespace api
} // namespace base
} // namespace masala
