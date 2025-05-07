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

/// @file src/base/api/setter/setter_annotation/DeprecatedSetterAnnotation.hh
/// @brief Headers for a setter annotation that indicates that a particular setter has
/// been deprecated or will be deprecated in a future version of this library.  If the Masala library
/// version is greater than or equal to that indicated in this setter, then the setter is excluded from
/// the API definition.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_setter_annotation_DeprecatedSetterAnnotation_hh
#define Masala_src_base_api_setter_setter_annotation_DeprecatedSetterAnnotation_hh

// Forward declarations:
#include <base/api/setter/setter_annotation/DeprecatedSetterAnnotation.fwd.hh>

// Base headers:
#include <base/api/setter/setter_annotation/MasalaSetterFunctionAnnotation.hh>
#include <base/managers/plugin_module/MasalaPluginAPI.fwd.hh>
#include <base/types.hh>

// STL headers:
#include <string>
#include <utility> // For std::pair.

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

/// @brief A setter annotation that indicates that a particular setter has been deprecated or will be
/// deprecated in a future version of this library.  If the Masala library version is greater than or
/// equal to that indicated in this setter, then the setter is excluded from the API definition.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class DeprecatedSetterAnnotation : public masala::base::api::setter::setter_annotation::MasalaSetterFunctionAnnotation {

	typedef masala::base::api::setter::setter_annotation::MasalaSetterFunctionAnnotation Parent;
	typedef masala::base::api::setter::setter_annotation::MasalaSetterFunctionAnnotationSP ParentSP;
	typedef masala::base::api::setter::setter_annotation::MasalaSetterFunctionAnnotationCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	DeprecatedSetterAnnotation() = delete;

	/// @brief Constructor that only sets the deprecation version.  Warnings are always enabled.
	DeprecatedSetterAnnotation(
		std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
	);

	/// @brief Constructor that only sets both the version at which warnings start and the deprecation version.
	DeprecatedSetterAnnotation(
		std::pair< masala::base::Size, masala::base::Size > const & version_at_which_warnings_start,
		std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
	);

	/// @brief Copy constructor.
	DeprecatedSetterAnnotation( DeprecatedSetterAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~DeprecatedSetterAnnotation() = default; 

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the class name ("DeprecatedSetterAnnotation").
	std::string class_name() const override;

	/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
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
	/// @details This override returns "This setter is not intended for inclusion in user interfaces or graphical user interfaces."
	std::string
	get_additional_description() const override;

	/// @brief Modify the JSON description to indicate that this setter should not be included in UIs or GUIs.
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

	/// @brief Is this annotation one that can be applied to this setter?
    /// @details This function is pure virtual.  Derived classes must override this to implement their own checks.  This
	/// override checks that (a) the setter takes one input, and (b) that the one input is either a MasalaPluginAPISP, a MasalaEngineAPISP,
	/// a MasalaDataRepresentationAPISP, or the equivalent const shared pointers, or instances or const instances of any of these.  This
	/// function performs no mutex locking.
    /// @returns True if it is compatible, false otherwise.  Called by the setter API definition's add_setter_annotation() function.
    bool
    protected_is_compatible_with_setter(
        masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
    ) const override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is there a version at which warnings should start?
	bool version_set_at_which_warnings_start_ = false;

	/// @brief The major and minor version number at which warnings start.
	std::pair< masala::base::Size, masala::base::Size > version_at_which_warnings_start_ = std::make_pair( 0, 0 );

	/// @brief The major and minor version number at which the function is deprecated.
	/// @details This is the version in the library in which the function is defined, not the version of Masala's core, necessarily.
	std::pair< masala::base::Size, masala::base::Size > version_at_which_function_deprecated_ = std::make_pair( 0, 0 );

}; // class DeprecatedSetterAnnotation

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_setter_annotation_DeprecatedSetterAnnotation_hh