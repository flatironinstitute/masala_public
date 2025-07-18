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

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.cc
/// @brief A class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>

// Base headers
#include <base/error/ErrorHandling.hh>
#include <base/api/work_function/work_function_annotation/MasalaWorkFunctionAnnotation.hh>
#include <base/api/work_function/work_function_annotation/DeprecatedWorkFunctionAnnotation.hh>
#include <base/managers/version/MasalaVersionManager.hh>
#include <base/managers/version/MasalaModuleVersionInfo.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace base {
namespace api {
namespace work_function {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor, to be called by derived classes.
/// @param[in] work_function_name The name of the work function that
///			   we are describing here.
/// @param[in] work_function_description The description of the work function that
///			   we are describing here.
/// @param[in] is_const Is this work function a const function?
/// @param[in] returns_this_ref Does this function return reference (or const reference) to this?
/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
///            is NOT an override of a virtual function in a parent API class)?
/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
///            a function in a base API class?
MasalaObjectAPIWorkFunctionDefinition::MasalaObjectAPIWorkFunctionDefinition(
    std::string const & work_function_name,
    std::string const & work_function_description,
    bool const is_const,
    bool const returns_this_ref,
    bool const is_virtual_non_override_fxn,
    bool const is_override_of_api_virtual_fxn
) :
    masala::base::MasalaObject(),
    work_function_name_(work_function_name),
    work_function_description_(work_function_description),
    is_const_(is_const),
    returns_this_ref_(returns_this_ref),
    is_virtual_non_override_fxn_(is_virtual_non_override_fxn),
    is_override_of_api_virtual_fxn_(is_override_of_api_virtual_fxn)
{
    CHECK_OR_THROW(
        !(is_virtual_non_override_fxn_ && is_override_of_api_virtual_fxn_),
        "masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinition",
        "MasalaObjectAPIWorkFunctionDefinition",
        "The " + work_function_name + "() work function was specified to be both a virtual function that "
        "does not override a base API class function, AND a virtual function that does ovreride a base API "
        "class function.  At most only one of these can be true."
    );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the work function.
std::string const &
MasalaObjectAPIWorkFunctionDefinition::work_function_name() const {
    return work_function_name_;
}

/// @brief Get the work function's description.
std::string
MasalaObjectAPIWorkFunctionDefinition::work_function_description() const {
	if( work_function_annotations_.empty() ) {
        return work_function_description_;
    }
    std::ostringstream ss;
    ss << work_function_description_;
    for( auto const & wf_annotation : work_function_annotations_ ) {
        std::string const extra_description( wf_annotation->get_additional_description() );
        if( !extra_description.empty() ) {
            ss << "  " << extra_description;
        }
    }
    return ss.str();
}

/// @brief Get whether this work function is a const function.
bool
MasalaObjectAPIWorkFunctionDefinition::is_const() const {
    return is_const_;
}

/// @brief Does this function return reference (or const reference) to this?
bool
MasalaObjectAPIWorkFunctionDefinition::returns_this_ref() const {
    return returns_this_ref_;
}

/// @brief Is this function a virtual function that does NOT override
/// a function in a base class that has a defined API?
bool
MasalaObjectAPIWorkFunctionDefinition::is_virtual_non_override_fxn() const {
    return is_virtual_non_override_fxn_;
}

/// @brief Is this function an override of a virtual function in a base
/// class that has a defined API?
bool
MasalaObjectAPIWorkFunctionDefinition::is_override_of_api_virtual_fxn() const {
    return is_override_of_api_virtual_fxn_;
}

/// @brief Is this function one that triggers no mutex-locking?
bool
MasalaObjectAPIWorkFunctionDefinition::triggers_no_mutex_lock() const {
    return triggers_no_mutex_lock_;
}

/// @brief Does this function always return nullptr?  (Soemtimes true for some base classes versions
/// that are overridden by derived classes.)
bool
MasalaObjectAPIWorkFunctionDefinition::always_returns_nullptr() const {
    return always_returns_nullptr_;
}

/// @brief Get the number of work function annotations.
masala::base::Size
MasalaObjectAPIWorkFunctionDefinition::n_work_function_annotations() const {
    return work_function_annotations_.size();
}

/// @brief Access the Nth work function annotation.
work_function_annotation::MasalaWorkFunctionAnnotationCSP
MasalaObjectAPIWorkFunctionDefinition::work_function_annotation(
    masala::base::Size const work_function_annotation_index
) const {
    CHECK_OR_THROW_FOR_CLASS( work_function_annotation_index < work_function_annotations_.size(),
        "work_function_annotation", "This " + class_name() + " has " + std::to_string(work_function_annotations_.size())
        + " work function annotations.  Index " + std::to_string(work_function_annotation_index) + " is out of range."
    );
    return work_function_annotations_[work_function_annotation_index];
}

/// @brief Add a work function annotation.
/// @details Annotation is used directly, not cloned.
void
MasalaObjectAPIWorkFunctionDefinition::add_work_function_annotation(
    work_function_annotation::MasalaWorkFunctionAnnotationCSP const & annotation_in
) {
    CHECK_OR_THROW_FOR_CLASS(
		annotation_in->is_compatible_with_work_function( *this ),
		"add_work_function_annotation",
		"The " + annotation_in->class_name() + " work function annotation reports that it is incompatible with "
        "work function " + work_function_name_ + "."
	);
	work_function_annotations_.push_back( annotation_in );

    work_function_annotation::DeprecatedWorkFunctionAnnotationCSP deprecated_annotation(
		std::dynamic_pointer_cast< work_function_annotation::DeprecatedWorkFunctionAnnotation const >( annotation_in )
	);
	if( deprecated_annotation != nullptr ) {
		masala::base::managers::version::MasalaModuleVersionInfoCSP vers_info(
			masala::base::managers::version::MasalaVersionManager::get_instance()->get_library_version_info( deprecated_annotation->library_name() )
		);
		if( vers_info != nullptr ) {
			std::pair< Size, Size > const deprecated_vers( deprecated_annotation->version_at_which_function_deprecated() );
			major_deprecation_version_ = deprecated_vers.first;
			minor_deprecation_version_ = deprecated_vers.second;
			library_name_for_deprecation_warning_ = deprecated_annotation->library_name();
			std::pair< Size, Size > const vers( vers_info->major_version(), vers_info->minor_version() );
#ifndef MASALA_ENABLE_DEPRECATED_FUNCTIONS
			if( vers.first > deprecated_vers.first || ( vers.first == deprecated_vers.first && vers.second >= deprecated_vers.second ) ) {
				set_function_deprecated();
			} else
#endif // MASALA_ENABLE_DEPRECATED_FUNCTIONS
#ifndef MASALA_DISABLE_DEPRECATION_WARNINGS
			if( deprecated_annotation->version_set_at_which_warnings_start() ) {
				std::pair< Size, Size > const warning_vers( deprecated_annotation->version_at_which_warnings_start() );
				if( vers.first > warning_vers.first || ( vers.first == warning_vers.first && vers.second >= warning_vers.second ) ) {
					set_function_warning();
				}
			}
#else // MASALA_DISABLE_DEPRECATION_WARNINGS
			{}
#endif // MASALA_DISABLE_DEPRECATION_WARNINGS
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// ADDITIONAL SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Indicate that this function does not trigger mutex-locking.
void
MasalaObjectAPIWorkFunctionDefinition::set_triggers_no_mutex_lock() {
    triggers_no_mutex_lock_ = true;
}

/// @brief Indicate that this function always returns nullptr.  (Soemtimes true for some base classes versions
/// that are overridden by derived classes.)
void
MasalaObjectAPIWorkFunctionDefinition::set_always_returns_nullptr() {
    always_returns_nullptr_ = true;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given the annotators, modify the JSON description of this function.
void
MasalaObjectAPIWorkFunctionDefinition::modify_json_description_with_annotators(
	nlohmann::json & json_description
) const {
	for( auto const & annotation : work_function_annotations_ ) {
		annotation->modify_json_description( json_description );
	}
}

} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala
