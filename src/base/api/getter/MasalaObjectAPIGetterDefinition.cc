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

/// @file src/base/api/getter/MasalaObjectAPIGetterDefinition.cc
/// @brief A class that stores the definition for a getter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/getter/MasalaObjectAPIGetterDefinition.hh>

// Base headers
#include <base/error/ErrorHandling.hh>
#include <base/api/getter/getter_annotation/MasalaGetterFunctionAnnotation.hh>
#include <base/api/getter/getter_annotation/DeprecatedGetterAnnotation.hh>
#include <base/managers/version/MasalaVersionManager.hh>
#include <base/managers/version/MasalaModuleVersionInfo.hh>

// STL headers
#include <sstream>

namespace masala {
namespace base {
namespace api {
namespace getter {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor, to be called by derived classes.
/// @param[in] getter_function_name The name of the getter function that
///			   we are describing here.
/// @param[in] getter_function_description The description of the getter function that
///			   we are describing here.
/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
///            is NOT an override of a virtual function in a parent API class)?
/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
///            a function in a base API class?
MasalaObjectAPIGetterDefinition::MasalaObjectAPIGetterDefinition(
    std::string const & getter_function_name,
    std::string const & getter_function_description,
    bool const is_virtual_non_override_fxn,
    bool const is_override_of_api_virtual_fxn
) :
    masala::base::MasalaObject(),
    getter_function_name_(getter_function_name),
    getter_function_description_(getter_function_description),
    is_virtual_non_override_fxn_(is_virtual_non_override_fxn),
    is_override_of_api_virtual_fxn_(is_override_of_api_virtual_fxn)
{
    CHECK_OR_THROW(
        !(is_virtual_non_override_fxn_ && is_override_of_api_virtual_fxn_),
        "masala::base::api::getter::MasalaObjectAPIGetterDefinition",
        "MasalaObjectAPIGetterDefinition",
        "The " + getter_function_name + "() getter function was specified to be both a virtual function that "
        "does not override a base API class function, AND a virtual function that does ovreride a base API "
        "class function.  At most only one of these can be true."
    );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the getter function.
std::string const &
MasalaObjectAPIGetterDefinition::getter_function_name() const {
    return getter_function_name_;
}

/// @brief Get the getter function's description.
/// @note Returns a copy rather than an instance of a string because there may be additional description generated on the fly
/// (e.g. by getter annotations).
std::string
MasalaObjectAPIGetterDefinition::getter_function_description() const {
	if( getter_annotations_.empty() ) {
		return getter_function_description_;
	}
	std::ostringstream ss;
	ss << getter_function_description_;
	for( auto const & getter_annotation : getter_annotations_ ) {
		std::string const extra_description( getter_annotation->get_additional_description() );
		if( !extra_description.empty() ) {
			ss << "  " << extra_description;
		}
	}
	return ss.str();
}

/// @brief Is this function a virtual function that does NOT override
/// a function in a base class that has a defined API?
bool
MasalaObjectAPIGetterDefinition::is_virtual_non_override_fxn() const {
    return is_virtual_non_override_fxn_;
}

/// @brief Is this function an override of a virtual function in a base
/// class that has a defined API?
bool
MasalaObjectAPIGetterDefinition::is_override_of_api_virtual_fxn() const {
    return is_override_of_api_virtual_fxn_;
}

/// @brief Get the number of getter annotations.
masala::base::Size
MasalaObjectAPIGetterDefinition::n_getter_annotations() const {
	return getter_annotations_.size();
}

/// @brief Access the Nth getter annotation.
getter_annotation::MasalaGetterFunctionAnnotationCSP
MasalaObjectAPIGetterDefinition::getter_annotation(
	masala::base::Size const getter_annotation_index
) const {
	CHECK_OR_THROW_FOR_CLASS( getter_annotation_index < getter_annotations_.size(),
		"getter_annotation", "This " + class_name() + " has " + std::to_string(getter_annotations_.size())
		+ " getter function annotations.  Index " + std::to_string(getter_annotation_index) + " is out of range."
	);
	return getter_annotations_[getter_annotation_index];
}

/// @brief Add a getter annotation.
/// @details Annotation is used directly, not cloned.
void
MasalaObjectAPIGetterDefinition::add_getter_annotation(
	getter_annotation::MasalaGetterFunctionAnnotationCSP const & annotation_in
) {
	CHECK_OR_THROW_FOR_CLASS(
		annotation_in->is_compatible_with_getter( *this ),
		"add_getter_annotation",
		"The " + annotation_in->class_name() + " getter annotation reports that it is incompatible with getter function " + getter_function_name_ + "."
	);
	getter_annotations_.push_back( annotation_in );
    getter_annotation::DeprecatedGetterAnnotationCSP deprecated_annotation(
		std::dynamic_pointer_cast< getter_annotation::DeprecatedGetterAnnotation const >( annotation_in )
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
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given the annotators, modify the JSON description of this function.
void
MasalaObjectAPIGetterDefinition::modify_json_description_with_annotators(
	nlohmann::json & json_description
) const {
	for( auto const & annotation : getter_annotations_ ) {
		annotation->modify_json_description( json_description );
	}
}

} // namespace getter
} // namespace api
} // namespace base
} // namespace masala