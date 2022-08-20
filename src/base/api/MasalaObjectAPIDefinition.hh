/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/base/api/MasalaObjectAPIDefinition.hh
/// @brief A class that stores the definition for the API for an object.  Used
/// to auto-generate the public C++ headers, plus the bindings for Python
/// or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaObjectAPIDefinition_hh
#define Masala_src_base_api_MasalaObjectAPIDefinition_hh

// Base class.
#include <base/MasalaObject.hh>

// Forward declarations.
#include <base/api/MasalaObjectAPIDefinition.fwd.hh>

// Base headers.
#include <base/types.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition.fwd.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition.fwd.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.fwd.hh>

// STL headers.
#include <set>

namespace base {
namespace api {

/// @brief A class that stores the definition for the API for an object.  Used
/// to auto-generate the public C++ headers, plus the bindings for Python
/// or XML (or other scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPIDefinition : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaObjectAPIDefinition() = delete;

	/// @brief Options constructor.
	/// @param[in] api_class_name The name of the class for which we're
	///            providing an API definition.
	/// @param[in] api_class_description The description of the class for which
	///			   we're providing an API definition.
	MasalaObjectAPIDefinition(
		std::string const & api_class_name,
		std::string const & api_class_description
	);


	/// @brief Copy constructor.
	MasalaObjectAPIDefinition( MasalaObjectAPIDefinition const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaObjectAPIDefinition() override = default;

	/// @brief Every class can name itself.  This returns "MasalaObjectAPIDefinition".
	std::string class_name() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Begin iterator for the setters.
	inline
	std::set<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	setters_begin() const {
		return setters_.cbegin();
	}

	/// @brief End iterator for the setters.
	inline
	std::set<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	setters_end() const {
		return setters_.cend();
	}

	/// @brief Number of setters.
	inline
	base::Size
	n_setters() const {
		return setters_.size();
	}

	/// @brief Begin iterator for the getters.
	inline
	std::set<base::api::getter::GetterDefinitionCSP>::const_iterator
	getters_begin() const {
		return getters_.cbegin();
	}

	/// @brief End iterator for the getters.
	inline
	std::set<base::api::getter::GetterDefinitionCSP>::const_iterator
	getters_end() const {
		return getters_.cend();
	}

	/// @brief Number of getters.
	inline
	base::Size
	n_getters() const {
		return getters_.size();
	}

	/// @brief Begin iterator for the work functions.
	inline
	std::set<base::api::work_function::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	work_functions_begin() const {
		return work_functions_.cbegin();
	}

	/// @brief End iterator for the work functions.
	inline
	std::set<base::api::work_function::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	work_functions_end() const {
		return work_functions_.cend();
	}

	/// @brief Number of work functions.
	inline
	base::Size
	n_work_functions() const {
		return work_functions_.size();
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The name of the class for which we're providing an API definition.
	/// @details Must be set at construction time.
	std::string const api_class_name_;

	/// @brief The description of the class for which we're providing an API definition.
	/// @details Must be set at construction time.
	std::string const api_class_description_;

	/// @brief A list of setters.
	std::set<base::api::setter::MasalaObjectAPISetterDefinitionCSP> setters_;

	/// @brief A list of getters.
	std::set<base::api::getter::GetterDefinitionCSP> getters_;

	/// @brief A list of work functions.
	std::set<base::api::work_function::MasalaObjectAPISetterDefinitionCSP> work_functions_;


}; // class MasalaObjectAPIDefinition

} //namespace api
} //namespace base

#endif //Masala_src_base_api_MasalaObjectAPIDefinition_hh