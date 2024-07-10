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
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief The category that can be passed to the MasalaPluginManager to get objects
/// of the type needed for this function.  Could be an empty vector
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::plugin_manager_input_object_category() const {
	return plugin_manager_input_object_category_;
}

/// @brief When the MasalaPluginManager is interogated for objects of the appropriate
/// type by category, should we include subcategories?  Default true.
bool
OwnedSingleObjectSetterAnnotation::plugin_manager_include_subcategory() const {
	return plugin_manager_include_subcategory_;
}

/// @brief The keywords that can be passed to the MasalaPluginManager to try to get objects
/// of the type needed for this function.  Could be an empty vector.
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::plugin_manager_input_object_keywords() const {
	return plugin_manager_input_object_keywords_;
}

/// @brief Is the input object an engine?  False by default.
bool
OwnedSingleObjectSetterAnnotation::is_engine() const {
	return is_engine_;
}

/// @brief The category that can be passed to the MasalaEngineManager to get objects
/// of the type needed for this function.  Could be an empty vector.
/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::engine_manager_input_object_category() const {
	CHECK_OR_THROW_FOR_CLASS( is_engine_, "engine_manager_input_object_category",
		"The input object is not a Masala engine."
	);
	return engine_manager_input_object_category_;
}

/// @brief When the MasalaEngineManager is interogated for objects of the appropriate
/// type by category, should we include subcategories?  Default true.
/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
bool
OwnedSingleObjectSetterAnnotation::engine_manager_include_subcategory() const
{
	CHECK_OR_THROW_FOR_CLASS( is_engine_, "engine_manager_include_subcategory",
		"The input object is not a Masala engine."
	);
	return engine_manager_include_subcategory_;
}

/// @brief The keywords that can be passed to the MasalaEngineManager to try to get objects
/// of the type needed for this function.  Could be an empty vector.
/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::engine_manager_input_object_keywords() const {
	CHECK_OR_THROW_FOR_CLASS( is_engine_, "engine_manager_input_object_keywords",
		"The input object is not a Masala engine."
	);
	return engine_manager_input_object_keywords_;
}

/// @brief Is the input object a data representation?  False by default.
/// @note Throws if is_data_representation_ is false.  Check by calling
/// is_data_representation() first!
bool
OwnedSingleObjectSetterAnnotation::is_data_representation() const {
	return is_data_representation_;
}

/// @brief The category that can be passed to the MasalaDataRepresentationManager to get objects
/// of the type needed for this function.  Could be an empty vector.
/// @note Throws if is_data_representation_ is false.  Check by calling
/// is_data_representation() first!
std::vector< std::string > const &
OwnedSingleObjectSetterAnnotation::data_representation_manager_input_object_category() const {
	CHECK_OR_THROW_FOR_CLASS( is_data_representation_, "data_representation_manager_input_object_category",
		"The input object is not a Masala data representation."
	);
	return data_representation_manager_input_object_category_;
}

/// @brief When the MasalaDataRepresentationManager is interogated for objects of the appropriate
/// type by category, should we include subcategories?  Default true.
/// @note Throws if is_data_representation_ is false.  Check by calling
/// is_data_representation() first!
bool
OwnedSingleObjectSetterAnnotation::data_representation_manager_include_subcategory() const {
	CHECK_OR_THROW_FOR_CLASS( is_data_representation_, "data_representation_manager_include_subcategory",
		"The input object is not a Masala data representation."
	);
	return data_representation_manager_include_subcategory_;
}

	/// @brief The keywords that can be passed to the MasalaDataRepresentationManager to try to get objects
	/// of the type needed for this function.  Could be an empty vector.
	/// @note Throws if is_data_representation_ is false.  Check by calling
	/// is_data_representation() first!
	std::vector< std::string > const &
	OwnedSingleObjectSetterAnnotation::data_representation_manager_input_object_keywords() const {
	CHECK_OR_THROW_FOR_CLASS( is_data_representation_, "data_representation_manager_input_object_keywords",
		"The input object is not a Masala data representation."
	);
	return data_representation_manager_input_object_keywords_;
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
	is_engine_ = true;
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
	is_data_representation_ = true;
	data_representation_manager_input_object_category_ = data_representation_manager_input_object_category;
	data_representation_manager_input_object_keywords_ = data_representation_manager_input_object_keywords;
	data_representation_manager_include_subcategory_ = data_representation_manager_include_subcategory;
}

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala
