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

/// @file src/base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh
/// @brief A class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_hh
#define Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.fwd.hh>
#include <base/api/work_function/work_function_annotation/MasalaWorkFunctionAnnotation.fwd.hh>

// Base headers.
#include <base/types.hh>

// External headers.
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// STL headers.
#include <string>

namespace masala {
namespace base {
namespace api {
namespace work_function {

/// @brief A class that stores the definition for a work function, as part
/// of the API for an object.  Used to auto-generate the public C++ headers,
/// plus the bindings for Python or XML (or other scripting languages).
/// @details This is a pure virtual base class.  Derived classes are for
/// one-parameter, two-parameter, three-parameter, etc. work functions.
/// @note A work function can take any number of inputs, and can return anything.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPIWorkFunctionDefinition : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIWorkFunctionDefinition() = delete;

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
	MasalaObjectAPIWorkFunctionDefinition(
		std::string const & work_function_name,
		std::string const & work_function_description,
		bool const is_const,
		bool const returns_this_ref,
		bool const is_virtual_non_override_fxn,
		bool const is_override_of_api_virtual_fxn
	);

	/// @brief Copy constructor.
	MasalaObjectAPIWorkFunctionDefinition( MasalaObjectAPIWorkFunctionDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPIWorkFunctionDefinition() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of this work function.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	std::string
	get_work_function_human_readable_description() const = 0;

	/// @brief Get a JSON description of this work function.
	/// @details Used for auto-generated help.  Must be implemented by
	/// derived classes.
	virtual
	nlohmann::json
	get_work_function_json_description() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of the work function.
	std::string const & work_function_name() const;

	/// @brief Get the work function's description (including any added text from function annotations).
	std::string work_function_description() const;

	/// @brief Get whether this work function is a const function.
	bool is_const() const;

	/// @brief Does this function return reference (or const reference) to this?
	bool returns_this_ref() const;

	/// @brief Is this function a virtual function that does NOT override
	/// a function in a base class that has a defined API?
	bool is_virtual_non_override_fxn() const;

	/// @brief Is this function an override of a virtual function in a base
	/// class that has a defined API?
	bool is_override_of_api_virtual_fxn() const;

	/// @brief Is this function one that triggers no mutex-locking?
	bool triggers_no_mutex_lock() const;

	/// @brief Does this function always return nullptr?  (Soemtimes true for some base classes versions
	/// that are overridden by derived classes.)
	bool always_returns_nullptr() const;

	/// @brief Access the Nth work function annotation.
	work_function_annotation::MasalaWorkFunctionAnnotationCSP work_function_annotation( masala::base::Size const work_function_annotation_index ) const;

	/// @brief Add a work function annotation.
	/// @details Annotation is used directly, not cloned.
	void add_work_function_annotation( work_function_annotation::MasalaWorkFunctionAnnotationCSP const & annotation_in );

	/// @brief Get the number of input parameters.
	/// @details Must be implemented by derived classes.
	virtual masala::base::Size num_input_parameters() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// ADDITIONAL SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Indicate that this function does not trigger mutex-locking.
	void set_triggers_no_mutex_lock();

	/// @brief Indicate that this function always returns nullptr.  (Soemtimes true for some base classes versions
	/// that are overridden by derived classes.)
	void set_always_returns_nullptr();

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

	/// @brief The name of the work function.
	/// @details Must be set on construction.
	std::string const work_function_name_;

	/// @brief The description of the work function.
	/// @details Must be set on construction.
	std::string const work_function_description_;

	/// @brief Is this work function a const function?
	/// @details Must be set on construction.
	bool const is_const_ = false;

	/// @brief Does this function return reference (or const reference) to this?
	bool const returns_this_ref_ = false;

	/// @brief Is this function a virtual function that does NOT override
	/// a function in a base class that has a defined API?
	bool is_virtual_non_override_fxn_ = false;

	/// @brief Is this function an override of a virtual function in a base
	/// class that has a defined API?
	bool is_override_of_api_virtual_fxn_ = false;

	/// @brief Is this function one that does NOT trigger mutex-locking?
	bool triggers_no_mutex_lock_ = false;

	/// @brief Does this function always return nullptr?  (Soemtimes true for some base classes versions
	/// that are overridden by derived classes.)
	bool always_returns_nullptr_ = false;

	/// @brief Additional annotations that this function has attached to it.
	std::vector< work_function_annotation::MasalaWorkFunctionAnnotationCSP > work_function_annotations_;

}; // class MasalaObjectAPIWorkFunctionDefinition

} // namespace work_function
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_work_function_MasalaObjectAPIWorkFunctionDefinition_hh