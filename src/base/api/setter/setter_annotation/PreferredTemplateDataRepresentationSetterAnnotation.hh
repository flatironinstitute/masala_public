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

/// @file src/base/api/setter/setter_annotation/PreferredTemplateDataRepresentationSetterAnnotation.hh
/// @brief Headers for a setter function annotation that indicates that a
/// function accepts an empty but configured MasalaDataRepresentation object to use as a
/// template for code requesting empty containers for data.  The set object will be deep-cloned
/// and handed out to requesting code by a corresponding getter function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_setter_annotation_PreferredTemplateDataRepresentationSetterAnnotation_hh
#define Masala_src_base_api_setter_setter_annotation_PreferredTemplateDataRepresentationSetterAnnotation_hh

// Forward declarations:
#include <base/api/setter/setter_annotation/PreferredTemplateDataRepresentationSetterAnnotation.fwd.hh>

// Base headers:
#include <base/api/setter/setter_annotation/MasalaSetterFunctionAnnotation.hh>
#include <base/managers/engine/MasalaDataRepresentationAPI.fwd.hh>

// STL headers:
#include <string>
#include <vector>

namespace masala {
namespace base {
namespace api {
namespace setter {
namespace setter_annotation {


/// @brief A setter function annotation that indicates that a function accepts an empty but
/// configured MasalaDataRepresentation object to use as a template for code requesting
/// empty containers for data.  The set object will be deep-cloned and handed out to
/// requesting code by a corresponding getter function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PreferredTemplateDataRepresentationSetterAnnotation : public masala::base::api::setter::setter_annotation::MasalaSetterFunctionAnnotation {

public:

	/// @brief Default constructor.
	PreferredTemplateDataRepresentationSetterAnnotation() = default;

	/// @brief Copy constructor.
	PreferredTemplateDataRepresentationSetterAnnotation( PreferredTemplateDataRepresentationSetterAnnotation const & ) = default;

	/// @brief Virtual destructor.
	virtual ~PreferredTemplateDataRepresentationSetterAnnotation() = default; 

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the class name ("PreferredTemplateDataRepresentationSetterAnnotation").
	std::string class_name() const override;

	/// @brief Get the class namespace ("masala::base::api::setter::setter_annotation").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief The category that can be passed to the MasalaDataRepresentationManager to get objects
	/// of the type needed for this function.  Could be an empty vector.
	std::vector< std::string > const &
	data_representation_manager_input_object_category() const;

	/// @brief When the MasalaDataRepresentationManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	bool
	data_representation_manager_include_subcategory() const;

	/// @brief The keywords that can be passed to the MasalaDataRepresentationManager to try to get objects
	/// of the type needed for this function.  Could be an empty vector.
	std::vector< std::string > const &
	data_representation_manager_input_object_keywords() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the information for the data representation object types that this setter takes.
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

	/// @brief Create an empty, unconfigured instance of the data representation object type.
	/// @param object_name The name of the type to create.  Throws if this type is not known to the data representation manager.
	/// @returns A shared pointer to a nonconst instance of the new object type.
	masala::base::managers::engine::MasalaDataRepresentationAPISP
	create_empty_data_representation(
		std::string const & object_name
	) const;

	/// @brief Call the setter function, and pass it a MasalaDataRepresentationAPICSP const instance.
	/// @details This version takes a const shared pointer to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::engine::MasalaDataRepresentationAPICSP const & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Call the setter function, and pass it a MasalaDataRepresentationAPISP const instance.
	/// @details This version takes a nonconst shared pointer to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::engine::MasalaDataRepresentationAPISP const & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Call the setter function, and pass it a MasalaDataRepresentationAPI const instance.
	/// @details This version takes a const reference to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::engine::MasalaDataRepresentationAPI const & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Call the setter function, and pass it a MasalaDataRepresentationAPI nonconst instance.
	/// @details This version takes a nonconst reference to the object.  If this setter expects a MasalaEngine or a MasalaDataRepresentation,
	/// this will throw if the object cannot be cast to the appropriate type.
	void
	set_object(
		masala::base::managers::engine::MasalaDataRepresentationAPI & object_in,
		masala::base::api::setter::MasalaObjectAPISetterDefinition const & setter
	) const;

	/// @brief Get a list of short names of objects that can be passed to this setter. 
	std::vector< std::string >
	get_short_names_of_eligible_owned_objects() const;

	/// @brief Get any additional description that this annotation provides.
	/// @details Intended for user-facing interfaces.  This override returns "Note that this setter sets an configured data representation object that
	/// is empty of any data, which can be used as a template for creating data representations.  The compatible data representation types that can be
	/// set are: ", followed by a list of compatible data representations, or [NONE] if none are available.
	std::string
	get_additional_description() const override;

	/// @brief Modify the JSON description.
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


	/// @brief Get a list of names of objects that can be passed to this setter.
	/// @details This function should be called from a mutex-locked context.  If short_names is true, then
	/// only names are returned; otherwise, names and namespaces are returned.
	std::vector< std::string >
	protected_get_names_of_eligible_owned_objects( bool const short_names ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The category that can be passed to the MasalaDataRepresentationManager to get objects
	/// of the type needed for this function.
	std::vector< std::string > data_representation_manager_input_object_category_;

	/// @brief When the MasalaDataRepresentationManager is interogated for objects of the appropriate
	/// type by category, should we include subcategories?  Default true.
	bool data_representation_manager_include_subcategory_ = true;

	/// @brief The keywords that can be passed to the MasalaDataRepresentationManager to try to get objects
	/// of the type needed for this function.
	std::vector< std::string > data_representation_manager_input_object_keywords_;

}; // class PreferredTemplateDataRepresentationSetterAnnotation

} // namespace setter_annotation
} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_setter_annotation_PreferredTemplateDataRepresentationSetterAnnotation_hh