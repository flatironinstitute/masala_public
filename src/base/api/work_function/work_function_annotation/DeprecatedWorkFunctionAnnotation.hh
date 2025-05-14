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

/// @file src/base/api/work_function/work_function_annotation/DeprecatedWorkFunctionAnnotation.hh
/// @brief Headers for a work function annotation that indicates that a particular work function has
/// been deprecated or will be deprecated in a future version of this library.  If the Masala library
/// version is greater than or equal to that indicated in this work function, then the work function is excluded from
/// the API definition.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_work_function_annotation_DeprecatedWorkFunctionAnnotation_hh
#define Masala_src_base_api_work_function_work_function_annotation_DeprecatedWorkFunctionAnnotation_hh

// Forward declarations:
#include <base/api/work_function/work_function_annotation/DeprecatedWorkFunctionAnnotation.fwd.hh>

// Base headers:
#include <base/api/work_function/work_function_annotation/MasalaWorkFunctionAnnotation.hh>
#include <base/managers/plugin_module/MasalaPluginAPI.fwd.hh>
#include <base/types.hh>

// STL headers:
#include <string>
#include <utility> // For std::pair.

namespace masala {
namespace base {
namespace api {
namespace work_function {
namespace work_function_annotation {

/// @brief A work function annotation that indicates that a particular work function has been deprecated or will be
/// deprecated in a future version of this library.  If the Masala library version is greater than or
/// equal to that indicated in this work function, then the work function is excluded from the API definition.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class DeprecatedWorkFunctionAnnotation : public masala::base::api::work_function::work_function_annotation::MasalaWorkFunctionAnnotation {

	typedef masala::base::api::work_function::work_function_annotation::MasalaWorkFunctionAnnotation Parent;
	typedef masala::base::api::work_function::work_function_annotation::MasalaWorkFunctionAnnotationSP ParentSP;
	typedef masala::base::api::work_function::work_function_annotation::MasalaWorkFunctionAnnotationCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	DeprecatedWorkFunctionAnnotation() = delete;

	/// @brief Constructor that only sets the deprecation version.  Warnings are always enabled.
	DeprecatedWorkFunctionAnnotation(
		std::string const & library_name,
		std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
	);

	/// @brief Constructor that only sets both the version at which warnings start and the deprecation version.
	DeprecatedWorkFunctionAnnotation(
		std::string const & library_name,
		std::pair< masala::base::Size, masala::base::Size > const & version_at_which_warnings_start,
		std::pair< masala::base::Size, masala::base::Size > const & version_at_which_function_deprecated
	);

	/// @brief Copy constructor.
	DeprecatedWorkFunctionAnnotation( DeprecatedWorkFunctionAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~DeprecatedWorkFunctionAnnotation() = default; 

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the class name ("DeprecatedWorkFunctionAnnotation").
	std::string class_name() const override;

	/// @brief Get the class namespace ("masala::base::api::work_function::work_function_annotation").
	std::string class_namespace() const override;

	/// @brief Get the class name ("DeprecatedWorkFunctionAnnotation").  Static version.
	static std::string class_name_static();

	/// @brief Get the class namespace ("masala::base::api::work_function::work_function_annotation").  Static version.
	static std::string class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get whether a version has been set for starting the warnings.
	bool
	version_set_at_which_warnings_start() const;

	/// @brief Get the version at which warnings start.
	/// @details Throws if no version has been set, so check whether a version has been set at which
	/// warnings start using version_set_at_which_warnings_start() first before calling this function.
	std::pair< masala::base::Size, masala::base::Size > const &
	version_at_which_warnings_start() const;

	/// @brief Get the version at which the function is deprecated.
	std::pair< masala::base::Size, masala::base::Size > const &
	version_at_which_function_deprecated() const;

	/// @brief Get the library name.
	std::string const & library_name() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get any additional description that this annotation provides.
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
    /// @returns True if it is compatible, false otherwise.  Called by the work function API definition's add_work_function_annotation() function.
    bool
    protected_is_compatible_with_work_function(
        masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinition const & work_function
    ) const override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The Masala library in which this function is defined.
	std::string library_name_;

	/// @brief Is there a version at which warnings should start?
	bool version_set_at_which_warnings_start_ = false;

	/// @brief The major and minor version number at which warnings start.
	std::pair< masala::base::Size, masala::base::Size > version_at_which_warnings_start_ = std::make_pair( 0, 0 );

	/// @brief The major and minor version number at which the function is deprecated.
	/// @details This is the version in the library in which the function is defined, not the version of Masala's core, necessarily.
	std::pair< masala::base::Size, masala::base::Size > version_at_which_function_deprecated_ = std::make_pair( 0, 0 );

}; // class DeprecatedWorkFunctionAnnotation

} // namespace work_function_annotation
} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_work_function_work_function_annotation_DeprecatedWorkFunctionAnnotation_hh