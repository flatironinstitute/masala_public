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

/// @file src/base/api/setter/MasalaObjectAPISetterDefinition.hh
/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_hh
#define Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_hh

// Base class.
#include <base/MasalaObject.hh>
#include <base/types.hh>

// Forward declarations.
#include <base/api/setter/MasalaObjectAPISetterDefinition.fwd.hh>

// External headers.
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// Base headers.
#include <base/api/setter/setter_annotation/MasalaSetterFunctionAnnotation.fwd.hh>
#include <base/error/ErrorHandling.hh>

// STL headers.
#include <string>
#include <vector>
#include <functional>

namespace masala {
namespace base {
namespace api {
namespace setter {

/// @brief A class that stores the definition for a setter function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a pure virtual base class.  Derived classes are for
/// one-parameter, two-parameter, three-parameter, etc. setters.
/// @note A setter must take one or more inputs, and must return void.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPISetterDefinition : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPISetterDefinition() = delete;

	/// @brief Options constructor, to be called by derived classes.
	/// @param[in] setter_function_name The name of the setter function that
	///			   we are describing here.
	/// @param[in] setter_function_description The description of the setter function that
	///			   we are describing here.
	/// @param[in] is_virtual_non_override_fxn Is this function a virtual function (one that
	///            is NOT an override of a virtual function in a parent API class)?
	/// @param[in] is_override_of_api_virtual_fxn Is this function a virtual override function of
	///            a function in a base API class?
	MasalaObjectAPISetterDefinition(
		std::string const & setter_function_name,
		std::string const & setter_function_description,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn
	);

	/// @brief Copy constructor.
	MasalaObjectAPISetterDefinition( MasalaObjectAPISetterDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPISetterDefinition() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this setter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	std::string
	get_setter_human_readable_description() const = 0;

	/// @brief Get a JSON description of this setter.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	nlohmann::json
	get_setter_json_description() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of the setter function.
	std::string const & setter_function_name() const;

	/// @brief Get the setter function's description.
	/// @note Returns a copy rather than an instance of a string because there may be additional description generated on the fly
	/// (e.g. by setter annotations).
	std::string setter_function_description() const;

	/// @brief Is this function a virtual function that does NOT override
	/// a function in a base class that has a defined API?
	bool is_virtual_non_override_fxn() const;

	/// @brief Is this function an override of a virtual function in a base
	/// class that has a defined API?
	bool is_override_of_api_virtual_fxn() const;

	/// @brief Get the number of setter annotations.
	masala::base::Size n_setter_annotations() const;

	/// @brief Access the Nth setter annotation.
	setter_annotation::MasalaSetterFunctionAnnotationCSP setter_annotation( masala::base::Size const setter_annotation_index ) const;

	/// @brief Add a setter annotation.
	/// @details Annotation is used directly, not cloned.
	void add_setter_annotation( setter_annotation::MasalaSetterFunctionAnnotationCSP const & annotation_in );

	/// @brief Get the number of input parameters for this setter.
	/// @details Pure virtual; must be overridden by derived classes.
	virtual masala::base::Size num_input_parameters() const = 0;

	/// @brief Set the function to throw a deprecation error if invoked.
	/// @details Must be implemented by derived classes.
	virtual void set_function_deprecated () = 0;

	/// @brief We replace the function that would have been called with this error message if the function is deprecated.
	template <typename... Ts >
	void
	deprecated_function_to_bind(
		Ts... //args
	) {
		MASALA_THROW( class_namespace() + "::" + class_name(), "deprecated_function_to_bind", "The setter function \""
			+ setter_function_name_ + "()\" has been deprecated as of version " + std::to_string( major_deprecation_version_ )
			+ "." + std::to_string( minor_deprecation_version_ ) + " of the " + library_name_for_deprecation_warning_
			+ " library.  (Note that you can re-enable it by compiling with the "
			"-DMASALA_ENABLE_DEPRECATED_FUNCTIONS compiler flag set.  However, we cannot guarantee that things will "
			"work as expected.)"
		);
	}

	/// @brief Set the function to give a deprecation warning if invoked.
	/// @details Must be implemented by derived classes.
	virtual void set_function_warning () = 0;

	/// @brief We replace the function that would have been called with this warning message, followed by the function call,
	/// if the function is soon to be deprecated.
	template <typename... Ts >
	void
	warning_function_to_bind(
		std::function< void(Ts...) > const fxn,
		Ts... args
	) {
		write_to_tracer( "Warning! The setter function \"" + setter_function_name_ + "()\" will be deprecated as of version "
			+ std::to_string( major_deprecation_version_ ) + "." + std::to_string( minor_deprecation_version_ )
			+ " of the " + library_name_for_deprecation_warning_ + " library.  "
			"(Note that you can disable this warning by compiling with the -DMASALA_DISABLE_DEPRECATION_WARNINGS "
			"compiler flag set.)"
		);
		fxn( args... );
	}

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given the annotators, modify the JSON description of this function.
	void
	modify_json_description_with_annotators(
		nlohmann::json & json_description
	) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of the setter function.
	/// @details Must be set on construction.
	std::string const setter_function_name_;

	/// @brief The description of the setter function.
	/// @details Must be set on construction.
	std::string const setter_function_description_;

	/// @brief Is this function a virtual function that does NOT override
	/// a function in a base class that has a defined API?
	bool is_virtual_non_override_fxn_ = false;

	/// @brief Is this function an override of a virtual function in a base
	/// class that has a defined API?
	bool is_override_of_api_virtual_fxn_ = false;

	/// @brief Additional annotations that this function has attached to it.
	std::vector< setter_annotation::MasalaSetterFunctionAnnotationCSP > setter_annotations_;

	/// @brief The major version at which this will be deprecated.
	masala::base::Size major_deprecation_version_ = 0;

	/// @brief The minor version at which this will be deprecated.
	masala::base::Size minor_deprecation_version_ = 0;

	/// @brief The library name, used for deprecation warnings.
	std::string library_name_for_deprecation_warning_;

}; // class MasalaObjectAPISetterDefinition

} // namespace setter
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_setter_MasalaObjectAPISetterDefinition_hh