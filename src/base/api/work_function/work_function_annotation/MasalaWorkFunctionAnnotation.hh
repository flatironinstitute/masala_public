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

/// @file src/base/api/work_function/work_function_annotation/MasalaWorkFunctionAnnotation.hh
/// @brief Headers for a pure virtual base class for work function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_work_function_annotation_MasalaWorkFunctionAnnotation_hh
#define Masala_src_base_api_work_function_work_function_annotation_MasalaWorkFunctionAnnotation_hh

// Forward declarations:
#include <base/api/work_function/work_function_annotation/MasalaWorkFunctionAnnotation.fwd.hh>

// Base headers:
#include <base/api/function_annotation/MasalaFunctionAnnotation.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.fwd.hh>

namespace masala {
namespace base {
namespace api {
namespace work_function {
namespace work_function_annotation {

/// @brief A pure virtual base class for work function annotations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaWorkFunctionAnnotation : public masala::base::api::function_annotation::MasalaFunctionAnnotation {

public:

	/// @brief Default constructor.
	MasalaWorkFunctionAnnotation() = default;

	/// @brief Copy constructor.
	MasalaWorkFunctionAnnotation( MasalaWorkFunctionAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~MasalaWorkFunctionAnnotation() = default; 

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Assign src to this.  Performs no mutex-locking.
    /// @details Derived classes should override this, and the overrides should call this function.
    void protected_assign( MasalaFunctionAnnotation const & src ) override;

    /// @brief Is this annotation one that can be applied to this work_function?
    /// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This function should
    /// perform no mutex locking.
    /// @returns True if it is compatible, false otherwise.  Called by the work_function API definition's add_work_function_annotation() function.
    virtual
    bool
    protected_is_compatible_with_work_function(
        masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinition const & work_function
    ) const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is this annotation one that can be applied to this work_function?
	/// @details This function locks the mutex and calls protected_is_compatible_with_work_function(), which must be implemented by derived classes.
	/// @returns True if it is compatible, false otherwise.  Called by the work_function API definition's add_work_function_annotation() function.
	bool
	is_compatible_with_work_function(
		masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinition const & work_function
	) const;

	/// @brief Get any additional description that this annotation provides.
	/// @details Intended for user-facing interfaces.  Base class returns an empty string.  May be overridden by derived classes.
	virtual
	std::string
	get_additional_description() const;

}; // class MasalaWorkFunctionAnnotation

} // namespace work_function_annotation
} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_work_function_work_function_annotation_MasalaWorkFunctionAnnotation_hh