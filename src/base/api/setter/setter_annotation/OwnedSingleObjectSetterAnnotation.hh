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
#include <base/managers/plugin_module/MasalaPluginAPI.fwd.hh>

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
	/// @param[in] setter The setter to which we will be attaching this annotation.  This function will
	/// throw if the setter is not a single-input setter that takes a MasalaEngineAPISP or MasalaEngineAPICSP.
	/// @param[in] engine_manager_include_subcategory If true (the default), then
	/// subcategories of the given category are accepted.  If false, then the exact category
	/// must be used.
	void
	set_engine_manager_info(
		std::vector< std::string > const & engine_manager_input_object_category,
		std::vector< std::string > const & engine_manager_input_object_keywords,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter,
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
	/// @param[in] setter The setter to which we will be attaching this annotation.  This function will
	/// throw if the setter is not a single-input setter that takes a MasalaDataRepresentationAPISP or
	/// MasalaDataRepresentationAPICSP.
	/// @param[in] data_representation_manager_include_subcategory If true (the default), then
	/// subcategories of the given category are accepted.  If false, then the exact category
	/// must be used.
	void
	set_data_representation_manager_info(
		std::vector< std::string > const & data_representation_manager_input_object_category,
		std::vector< std::string > const & data_representation_manager_input_object_keywords,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter,
		bool const data_representation_manager_include_subcategory = true
	);

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Create an instance of the owned object type.
	/// @param object_name The name of the type to create.  Throws if this type is not known to the plugin manager, the engine manager if this
	/// is an engine setter, or the data representation manager if this is a data representation setter.
	/// @returns A shared pointer to a nonconst instance of the new object type.
	masala::base::managers::plugin_module::MasalaPluginAPISP
	create_owned_object(
		std::string const & object_name
	) const;

	/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
	/// @details This version takes a const shared pointer to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::plugin_module::MasalaPluginAPICSP const & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
	/// @details This version takes a nonconst shared pointer to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::plugin_module::MasalaPluginAPISP const & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
	/// @details This version takes a const reference to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::plugin_module::MasalaPluginAPI const & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Call the setter function, and pass it a MasalaPluginAPI object.
	/// @details This version takes a nonconst reference to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::plugin_module::MasalaPluginAPI & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Get a list of short names of objects that can be passed to this setter. 
	std::vector< std::string >
	get_short_names_of_eligible_owned_objects() const;

	/// @brief Get any additional description that this annotation provides.
	/// @details Intended for user-facing interfaces.  This override returns "Note that this setter sets a stored object that is wholly
	/// owned by this object (i.e. it has an OwnedSingleObjectSetterAnnotation attached to it).  The compatible object types that can be
	/// set are: ", followed by a list of compatible objects, or [NONE] if none are available.
	std::string
	get_additional_description() const override;

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


	/// @brief Get a list of names of objects that can be passed to this setter.
	/// @details This function should be called from a mutex-locked context.  If short_names is true, then
	/// only names are returned; otherwise, names and namespaces are returned.
	std::vector< std::string >
	protected_get_names_of_eligible_owned_objects( bool const short_names ) const;

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