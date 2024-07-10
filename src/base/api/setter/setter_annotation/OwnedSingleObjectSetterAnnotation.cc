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

/// @file src/base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.cc
/// @brief Implementations for a setter function annotation that indicates that a
/// function sets a type of object that is (a) wholly owned by the encapsulating object, and
/// (b) unique (i.e. an instance of the encapsulating object encapsulates only one instance
/// of the inner object).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("OwnedSingleObjectSetterAnnotation").
std::string
OwnedSingleObjectSetterAnnotation::class_name() const {
	return "OwnedSingleObjectSetterAnnotation";
}

/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
std::string
OwnedSingleObjectSetterAnnotation::class_namespace() const {
	return "masala::base::api::setter::setter_annotation";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the information for the object types that this setter takes.
/// @param[in] plugin_manager_input_object_category The category that can be passed
/// to the plugin manager to get objects of the type that this setter function accepts.
/// Can be left as an empty vector.
/// @param[in] plugin_manager_input_object_keywords Keywords that can be passed to the
/// MasalaPluginManager to try to get objects of the type needed for this setter function.
/// Can be left as an empty vector.
/// @param[in] plugin_manager_include_subcategory If true (the default), then
/// subcategories of the given category are accepted.  If false, then the exact category
/// must be used.
void
OwnedSingleObjectSetterAnnotation::set_plugin_manager_info(
	std::vector< std::string > const & plugin_manager_input_object_category,
	std::vector< std::string > const & plugin_manager_input_object_keywords,
	bool const plugin_manager_include_subcategory = true
) {
	plugin_manager_input_object_category_ = plugin_manager_input_object_category;
	plugin_manager_input_object_keywords_ = plugin_manager_input_object_keywords;
	plugin_manager_include_subcategory_ = plugin_manager_include_subcategory;
}

/// @brief Set the information for the engine object types that this setter takes.  Note
/// that this implicitly sets is_engine_ to true.
/// @param[in] engine_manager_input_object_category The category that can be passed
/// to the engine manager to get objects of the type that this setter function accepts.
/// Can be left as an empty vector.
/// @param[in] engine_manager_input_object_keywords Keywords that can be passed to the
/// MasalaEngineManager to try to get objects of the type needed for this setter function.
/// Can be left as an empty vector.
/// @param[in] engine_manager_include_subcategory If true (the default), then
/// subcategories of the given category are accepted.  If false, then the exact category
/// must be used.
void
OwnedSingleObjectSetterAnnotation::set_engine_manager_info(
	std::vector< std::string > const & engine_manager_input_object_category,
	std::vector< std::string > const & engine_manager_input_object_keywords,
	bool const engine_manager_include_subcategory = true
) {
	engine_manager_input_object_category_ = engine_manager_input_object_category;
	engine_manager_input_object_keywords_ = engine_manager_input_object_keywords;
	engine_manager_include_subcategory_ = engine_manager_include_subcategory;
}

/// @brief Set the information for the data representation object types that this setter takes.  Note
/// that this implicitly sets is_data_representation_ to true.
/// @param[in] data_representation_manager_input_object_category The category that can be passed
/// to the data representation manager to get objects of the type that this setter function accepts.
/// Can be left as an empty vector.
/// @param[in] data_representation_manager_input_object_keywords Keywords that can be passed to the
/// MasalaDataRepresentationManager to try to get objects of the type needed for this setter function.
/// Can be left as an empty vector.
/// @param[in] data_representation_manager_include_subcategory If true (the default), then
/// subcategories of the given category are accepted.  If false, then the exact category
/// must be used.
void
OwnedSingleObjectSetterAnnotation::set_data_representation_manager_info(
	std::vector< std::string > const & data_representation_manager_input_object_category,
	std::vector< std::string > const & data_representation_manager_input_object_keywords,
	bool const data_representation_manager_include_subcategory = true
) {
	data_representation_manager_input_object_category_ = data_representation_manager_input_object_category;
	data_representation_manager_input_object_keywords_ = data_representation_manager_input_object_keywords;
	data_representation_manager_include_subcategory_ = data_representation_manager_include_subcategory;
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
