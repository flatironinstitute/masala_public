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

/// @file src/base/api/setter/setter_annotation/MasalaSetterFunctionAnnotation.hh
/// @brief Headers for a pure virtual base class for setter function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_setter_annotation_MasalaSetterFunctionAnnotation_hh
#define Masala_src_base_api_setter_setter_annotation_MasalaSetterFunctionAnnotation_hh

// Forward declarations:
#include <base/api/setter/setter_annotation/MasalaSetterFunctionAnnotation.fwd.hh>

// Base headers:
#include <base/api/function_annotation/MasalaFunctionAnnotation.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition.fwd.hh>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

/// @brief A pure virtual base class for function setter annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaSetterFunctionAnnotation : public masala::base::api::function_annotation::MasalaFunctionAnnotation {

public:

	/// @brief Default constructor.
	MasalaSetterFunctionAnnotation() = default;

	/// @brief Copy constructor.
	MasalaSetterFunctionAnnotation( MasalaSetterFunctionAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~MasalaSetterFunctionAnnotation() = default; 

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Assign src to this.  Performs no mutex-locking.
    /// @details Derived classes should override this, and the overrides should call this function.
    void protected_assign( MasalaFunctionAnnotation const & src ) override;

    /// @brief Is this annotation one that can be applied to this setter?
    /// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This function should
    /// perform no mutex locking.
    /// @returns True if it is compatible, false otherwise.  Called by the setter API definition's add_setter_annotation() function.
    virtual
    bool
    protected_is_compatible_with_setter(
        masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
    ) const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is this annotation one that can be applied to this setter?
	/// @details This function locks the mutex and calls protected_is_compatible_with_setter(), which must be implemented by derived classes.
	/// @returns True if it is compatible, false otherwise.  Called by the setter API definition's add_setter_annotation() function.
	bool
	is_compatible_with_setter(
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

}; // class MasalaSetterFunctionAnnotation

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_setter_annotation_MasalaSetterFunctionAnnotation_hh