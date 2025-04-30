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

/// @file src/base/api/work_function/work_function_annotation/NoUIWorkFunctionAnnotation.hh
/// @brief Headers for a work_function function annotation that suggests to calling code that a
/// function should not be part of user-facing user interfaces.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_work_function_annotation_NoUIWorkFunctionAnnotation_hh
#define Masala_src_base_api_work_function_work_function_annotation_NoUIWorkFunctionAnnotation_hh

// Forward declarations:
#include <base/api/work_function/work_function_annotation/NoUIWorkFunctionAnnotation.fwd.hh>

// Base headers:
#include <base/api/work_function/work_function_annotation/MasalaWorkFunctionAnnotation.hh>
#include <base/managers/plugin_module/MasalaPluginAPI.fwd.hh>

// STL headers:
#include <string>
#include <vector>

namespace masala {
namespace base {
namespace api {
namespace work_function {
namespace work_function_annotation {

/// @brief A work function function annotation that suggests to calling code that a function should not be part of
/// user-facing user interfaces.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class NoUIWorkFunctionAnnotation : public masala::base::api::work_function::work_function_annotation::MasalaWorkFunctionAnnotation {

public:

	/// @brief Default constructor.
	NoUIWorkFunctionAnnotation() = default;

	/// @brief Copy constructor.
	NoUIWorkFunctionAnnotation( NoUIWorkFunctionAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~NoUIWorkFunctionAnnotation() = default; 

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the class name ("NoUIWorkFunctionAnnotation").
	std::string class_name() const override;

	/// @brief Get the class namespace ("masala::base::api::work_function::work_function_annotation").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get any additional description that this annotation provides.
	/// @details This override returns "This work function is not intended for inclusion in user interfaces or graphical user interfaces."
	std::string
	get_additional_description() const override;

	/// @brief Modify the JSON description to indicate that this work function should not be included in UIs or GUIs.
	void
	modify_json_description(
		nlohmann::json & json_description
	) const override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Assign src to this.  Performs no mutex-locking.
    /// @details Derived classes should override this, and the overrides should call this function.
    void protected_assign( MasalaFunctionAnnotation const & src ) override;

	/// @brief Is this annotation one that can be applied to this work function?
    /// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This
	/// override checks that (a) the work function takes one input, and (b) that the one input is either a MasalaPluginAPISP, a MasalaEngineAPISP,
	/// a MasalaDataRepresentationAPISP, or the equivalent const shared pointers, or instances or const instances of any of these.  This
	/// function performs no mutex locking.
    /// @returns True if it is compatible, false otherwise.  Called by the work_function API definition's add_work_function_annotation() function.
    bool
    protected_is_compatible_with_work_function(
        masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinition const & work_function
    ) const override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

}; // class NoUIWorkFunctionAnnotation

} // namespace work_function_annotation
} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_work_function_work_function_annotation_NoUIWorkFunctionAnnotation_hh