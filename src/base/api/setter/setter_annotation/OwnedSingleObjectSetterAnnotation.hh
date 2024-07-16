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

/// @file src/base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.hh
/// @brief Headers for a setter function annotation that indicates that a
/// function sets a type of object that is (a) wholly owned by the encapsulating object, and
/// (b) unique (i.e. an instance of the encapsulating object encapsulates only one instance
/// of the inner object).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_setter_annotation_OwnedSingleObjectSetterAnnotation_hh
#define Masala_src_base_api_setter_setter_annotation_OwnedSingleObjectSetterAnnotation_hh

// Forward declarations:
#include <base/api/setter/setter_annotation/OwnedSingleObjectSetterAnnotation.fwd.hh>

// Base headers:
#include <base/api/setter/setter_annotation/MasalaSetterFunctionAnnotation.hh>

// STL headers:
#include <string>
#include <vector>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {

/// @brief A setter function annotation that indicates that a
/// function sets a type of object that is (a) wholly owned by the encapsulating object, and
/// (b) unique (i.e. an instance of the encapsulating object encapsulates only one instance
/// of the inner object).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class OwnedSingleObjectSetterAnnotation : public masala::base::api::setter::setter_annotation::MasalaSetterFunctionAnnotation {

public:

	/// @brief Default constructor.
	OwnedSingleObjectSetterAnnotation() = default;

	/// @brief Copy constructor.
	OwnedSingleObjectSetterAnnotation( OwnedSingleObjectSetterAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~OwnedSingleObjectSetterAnnotation() = default; 

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the class name ("OwnedSingleObjectSetterAnnotation").
	std::string class_name() const override;

	/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief The category that can be passed to the MasalaPluginManager to get objects
	/// of the type needed for this function.  Could be an empty vector
	std::vector< std::string > const &
	plugin_manager_input_object_category() const;

	/// @brief When the MasalaPluginManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	bool
	plugin_manager_include_subcategory() const;

	/// @brief The keywords that can be passed to the MasalaPluginManager to try to get objects
	/// of the type needed for this function.  Could be an empty vector.
	std::vector< std::string > const &
	plugin_manager_input_object_keywords() const;

	/// @brief Is the input object an engine?  False by default.
	bool
	is_engine() const;

	/// @brief The category that can be passed to the MasalaEngineManager to get objects
	/// of the type needed for this function.  Could be an empty vector.
	/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
	std::vector< std::string > const &
	engine_manager_input_object_category() const;

	/// @brief When the MasalaEngineManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
	bool
	engine_manager_include_subcategory() const;

	/// @brief The keywords that can be passed to the MasalaEngineManager to try to get objects
	/// of the type needed for this function.  Could be an empty vector.
	/// @note Throws if is_engine_ is false.  Check by calling is_engine() first!
	std::vector< std::string > const &
	engine_manager_input_object_keywords() const;

	/// @brief Is the input object a data representation?  False by default.
	/// @note Throws if is_data_representation_ is false.  Check by calling
	/// is_data_representation() first!
	bool
	is_data_representation() const;

	/// @brief The category that can be passed to the MasalaDataRepresentationManager to get objects
	/// of the type needed for this function.  Could be an empty vector.
	/// @note Throws if is_data_representation_ is false.  Check by calling
	/// is_data_representation() first!
	std::vector< std::string > const &
	data_representation_manager_input_object_category() const;

	/// @brief When the MasalaDataRepresentationManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	/// @note Throws if is_data_representation_ is false.  Check by calling
	/// is_data_representation() first!
	bool
	data_representation_manager_include_subcategory() const;

	/// @brief The keywords that can be passed to the MasalaDataRepresentationManager to try to get objects
	/// of the type needed for this function.  Could be an empty vector.
	/// @note Throws if is_data_representation_ is false.  Check by calling
	/// is_data_representation() first!
	std::vector< std::string > const &
	data_representation_manager_input_object_keywords() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the information for the plugin object types that this setter takes.
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
	set_plugin_manager_info(
		std::vector< std::string > const & plugin_manager_input_object_category,
		std::vector< std::string > const & plugin_manager_input_object_keywords,
		bool const plugin_manager_include_subcategory = true
	);

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
	set_engine_manager_info(
		std::vector< std::string > const & engine_manager_input_object_category,
		std::vector< std::string > const & engine_manager_input_object_keywords,
		bool const engine_manager_include_subcategory = true
	);

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
	set_data_representation_manager_info(
		std::vector< std::string > const & data_representation_manager_input_object_category,
		std::vector< std::string > const & data_representation_manager_input_object_keywords,
		bool const data_representation_manager_include_subcategory = true
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The category that can be passed to the MasalaPluginManager to get objects
	/// of the type needed for this function.
	std::vector< std::string > plugin_manager_input_object_category_;

	/// @brief When the MasalaPluginManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	bool plugin_manager_include_subcategory_ = true;

	/// @brief The keywords that can be passed to the MasalaPluginManager to try to get objects
	/// of the type needed for this function.
	std::vector< std::string > plugin_manager_input_object_keywords_;

	/// @brief Is the input object an engine?  False by default.
	bool is_engine_ = false;

	/// @brief The category that can be passed to the MasalaEngineManager to get objects
	/// of the type needed for this function.
	std::vector< std::string > engine_manager_input_object_category_;

	/// @brief When the MasalaEngineManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	bool engine_manager_include_subcategory_ = true;

	/// @brief The keywords that can be passed to the MasalaEngineManager to try to get objects
	/// of the type needed for this function.
	std::vector< std::string > engine_manager_input_object_keywords_;

	/// @brief Is the input object a data representation?  False by default.
	bool is_data_representation_ = false;

	/// @brief The category that can be passed to the MasalaDataRepresentationManager to get objects
	/// of the type needed for this function.
	std::vector< std::string > data_representation_manager_input_object_category_;

	/// @brief When the MasalaDataRepresentationManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	bool data_representation_manager_include_subcategory_ = true;

	/// @brief The keywords that can be passed to the MasalaDataRepresentationManager to try to get objects
	/// of the type needed for this function.
	std::vector< std::string > data_representation_manager_input_object_keywords_;

}; // class OwnedSingleObjectSetterAnnotation

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_setter_annotation_OwnedSingleObjectSetterAnnotation_hh