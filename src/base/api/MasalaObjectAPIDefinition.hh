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
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition.fwd.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition.fwd.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition.fwd.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.fwd.hh>

// External headers.
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// STL headers.
#include <vector>
#include <string>

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

	/// @brief Every class can provide its own namespace.  This returns "base::api".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a human-readable description of the API for a module.
	/// @details Note that this does not cache the generated string, but generates it anew
	/// each time.
	std::string
	get_human_readable_description() const;

	/// @brief Get a JSON object describing the API for a module.
	/// @details Note that this does not cache the generated JSON object, but generates it anew
	/// each time.
	std::shared_ptr< nlohmann::json >
	get_json_description() const;

	/// @brief Begin iterator for the constructors.
	std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP>::const_iterator
	constructors_begin() const;

	/// @brief End iterator for the constructors.
	std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP>::const_iterator
	constructors_end() const;

	/// @brief Number of constructors.
	base::Size
	n_constructors() const;

	/// @brief Add a constructor.
	void
	add_constructor(
		base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP constructor_in
	);

	/// @brief Begin iterator for the setters.
	std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	setters_begin() const;

	/// @brief End iterator for the setters.
	std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator
	setters_end() const;

	/// @brief Number of setters.
	base::Size
	n_setters() const;

	/// @brief Add a setter.
	void
	add_setter(
		base::api::setter::MasalaObjectAPISetterDefinitionCSP setter_in
	);

	/// @brief Begin iterator for the getters.
	std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator
	getters_begin() const;

	/// @brief End iterator for the getters.
	std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator
	getters_end() const;

	/// @brief Number of getters.
	base::Size
	n_getters() const;

	/// @brief Add a getter.
	void
	add_getter(
		base::api::getter::MasalaObjectAPIGetterDefinitionCSP getter_in
	);

	/// @brief Begin iterator for the work functions.
	std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator
	work_functions_begin() const;

	/// @brief End iterator for the work functions.
	std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator
	work_functions_end() const;

	/// @brief Number of work functions.
	base::Size
	n_work_functions() const;

	/// @brief Add a work function.
	void
	add_work_function(
		base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP work_function_in
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Generate JSON descriptions for all of the constructors.
	/// @details Nothing is cached here, so this will generate a new JSON object
	/// each time it is called.  This isn't super fast.
	nlohmann::json get_json_description_for_constructors() const;

	/// @brief Generate JSON descriptions for all of the setters.
	/// @details Nothing is cached here, so this will generate a new JSON object
	/// each time it is called.  This isn't super fast.
	nlohmann::json get_json_description_for_setters() const;

	/// @brief Generate JSON descriptions for all of the getters.
	/// @details Nothing is cached here, so this will generate a new JSON object
	/// each time it is called.  This isn't super fast.
	nlohmann::json get_json_description_for_getters() const;

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

	/// @brief A list of constructors.
	std::vector<base::api::constructor::MasalaObjectAPIConstructorDefinitionCSP> constructors_;

	/// @brief A list of setters.
	std::vector<base::api::setter::MasalaObjectAPISetterDefinitionCSP> setters_;

	/// @brief A list of getters.
	std::vector<base::api::getter::MasalaObjectAPIGetterDefinitionCSP> getters_;

	/// @brief A list of work functions.
	std::vector<base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP> work_functions_;


}; // class MasalaObjectAPIDefinition

} //namespace api
} //namespace base

#endif //Masala_src_base_api_MasalaObjectAPIDefinition_hh