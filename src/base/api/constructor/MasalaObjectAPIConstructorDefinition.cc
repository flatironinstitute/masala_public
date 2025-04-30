/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorDefinition.cc
/// @brief A class that stores the definition for a constructor, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.hh>

// Base headers.
#include <base/error/ErrorHandling.hh>
#include <base/api/constructor/constructor_annotation/MasalaConstructorAnnotation.hh>

// STL headers.
#include <sstream>

namespace masala {
namespace base {
namespace api {
namespace constructor {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor, to be called by derived classes.
/// @param[in] constructor_name The name of the constructor that
///			   we are describing here.  Should match the T0 class name.
/// @param[in] constructor_description The description of the constructor that
///			   we are describing here.
MasalaObjectAPIConstructorDefinition::MasalaObjectAPIConstructorDefinition(
    std::string const & constructor_name,
    std::string const & constructor_description
) :
    masala::base::MasalaObject(),
    constructor_name_(constructor_name),
    constructor_description_(constructor_description)
{}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of the constructor.  Should match the T0 class name.
std::string const &
MasalaObjectAPIConstructorDefinition::constructor_name() const {
    return constructor_name_;
}

/// @brief Get the constructor's description.
/// @note Returns a copy rather than an instance of a string because there may be additional description generated on the fly
/// (e.g. by constructor annotations).
std::string
MasalaObjectAPIConstructorDefinition::constructor_description() const {
    if( constructor_annotations_.empty() ) {
        return constructor_description_;
    }
    std::ostringstream ss;
    ss << constructor_description_;
    for( auto const & constructor_annotation : constructor_annotations_ ) {
        std::string const extra_description( constructor_annotation->get_additional_description() );
        if( !extra_description.empty() ) {
            ss << "  " << extra_description;
        }
    }
    return ss.str();
}

/// @brief Get the number of constructor annotations.
masala::base::Size
MasalaObjectAPIConstructorDefinition::n_constructor_annotations() const {
	return constructor_annotations_.size();
}

/// @brief Access the Nth constructor annotation.
constructor_annotation::MasalaConstructorAnnotationCSP
MasalaObjectAPIConstructorDefinition::constructor_annotation(
	masala::base::Size const constructor_annotation_index
) const {
	CHECK_OR_THROW_FOR_CLASS( constructor_annotation_index < constructor_annotations_.size(),
		"constructor_annotation", "This " + class_name() + " has " + std::to_string(constructor_annotations_.size())
		+ " constructor function annotations.  Index " + std::to_string(constructor_annotation_index) + " is out of range."
	);
	return constructor_annotations_[constructor_annotation_index];
}

/// @brief Add a constructor annotation.
/// @details Annotation is used directly, not cloned.
void
MasalaObjectAPIConstructorDefinition::add_constructor_annotation(
	constructor_annotation::MasalaConstructorAnnotationCSP const & annotation_in
) {
	CHECK_OR_THROW_FOR_CLASS(
		annotation_in->is_compatible_with_constructor( *this ),
		"add_constructor_annotation",
		"The " + annotation_in->class_name() + " constructor annotation reports that it is incompatible with constructor function " + constructor_name_ + "."
	);
	constructor_annotations_.push_back( annotation_in );
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given the annotators, modify the JSON description of this function.
void
MasalaObjectAPIConstructorDefinition::modify_json_description_with_annotators(
	nlohmann::json & json_description
) const {
	for( auto const & annotation : constructor_annotations_ ) {
		annotation->modify_json_description( json_description );
	}
}

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala