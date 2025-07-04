/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/base/MasalaObject.hh
/// @brief A base class for all Masala derived classes.  This allows the possibility of having a
/// generic MasalaObject pointer or shared pointer.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_MasalaObject_hh
#define Masala_src_base_MasalaObject_hh

// Forward declarations:
#include <base/MasalaObject.fwd.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.fwd.hh>
#include <base/managers/configuration/ConfigurationBase.fwd.hh>
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.fwd.hh>
#include <base/managers/configuration/MasalaConfigurationManager.fwd.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.fwd.hh>

// STL headers:
#include <vector>

namespace masala {
namespace base {

/// @brief A base class for all Masala derived classes.  This allows the possibility of having a
/// generic MasalaObject pointer or shared pointer.
/// @note The MasalaConfigurationManager can access the private member functions (and data) of MasalaObjects.
/// This allows it to call load_configuration() when first needed.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObject {

	friend class masala::base::managers::configuration::MasalaConfigurationManager;

public:

	/// @brief Default constructor.
	MasalaObject() = default;

	/// @brief Copy constructor.
	MasalaObject( MasalaObject const & ) = default;

	/// @brief Virtual destructor.
	virtual ~MasalaObject() = default;

	/// @brief Every class can name itself.
	virtual std::string class_name() const = 0;

	/// @brief Every class can provide its own namespace.
	virtual std::string class_namespace() const = 0;

	/// @brief Returns result of class_namespace() + "::" + class_name().
	std::string class_namespace_and_name() const;

	/// @brief Get the namespace and name for this pure virtual base class.
	/// @returns "masala::base::MasalaObject"
    static
	std::string
	class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a string for the error message header, of the form:
	/// "Error in <namespace>::<class name>::<function name>(): ".
	/// @param[in] function_name The function from which we're calling this function,
	/// used to construct the string.  This should just be a function name, without
	/// namespace, class, colons, return type, parameters, or parentheses.
	/// @note This cannot be called from constructors!
	std::string
	get_errmsg_header(
		std::string const & function_name
	) const;

	/// @brief Does this object return an API definition?
	/// @details By default, returns false.  Derived classes might, though.
	bool has_api_definition();

	/// @brief Get an object describing the API for this object.
	/// @details Default implementation returns nullptr.  May be overridden by
	/// derived objects.
	/// @note This is a weak pointer rather than a shared pointer since the
	/// original object is expected to hold on to its API definition (which includes
	/// function pointers to the functions of the instance).  Querying whether the
	/// weak pointer can be converted to a shared pointer serves on a check as to
	/// whether it is safe to use the function pointers.  Not ideal, but better than
	/// nothing.
	virtual
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition();

	/// @brief Writes text to the tracer, using the MasalaTracerManager.
	/// @details Threadsafe, but DO NOT USE FROM CONSTRUCTOR!
	void
	write_to_tracer(
		std::string const & message
	) const;

	/// @brief Get a creator object for objects of this type.
	/// @details By default, returns nullptr.  Can be overridden by derived classes.
	virtual
	masala::base::managers::plugin_module::MasalaPluginCreatorCSP
	get_creator() const;

	/// @brief Get a list of categories that this object could be sorted into.
	/// @details This is for auto-generation of hierarchical documentation and user interfaces.
	/// Categories could be something like std::vector< std::string >{ "Manipulators", "Proteins", "Design" }.
	/// An object may be in more than one category.  Uses lists from the creator.  Returns an empty list if
	/// no creator.
	std::vector< std::vector< std::string > >
	get_categories() const;

	/// @brief Get a list of keywords associated with this object.
	/// @details This is also for auto-generation of documentation or user interfaces, to allow
	/// discoverability of functionality.  Unlike categories, which are hierarchical, keywords
	/// have no hierarchy.  Uses lists from the creator.  Returns an empty list if no creator.
	std::vector< std::string >
	get_keywords() const;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Create a configuration object for this object.
	/// @details Can trigger read from disk.  Private since it intended to be called only the first time
	/// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
	/// implementation throws.  Must be implemented by derived classes that have configurations.
	/// @note Receives an instance of a MasalaConfigurationManagerAuthorization object.  Since this has a
	/// private constructor, it can only be instantiated by the MasalaConfigurationManager, its only friend
	/// class.
	virtual
	masala::base::managers::configuration::ConfigurationBaseCSP
	load_configuration(
		masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const &
	) const;

}; // class MasalaObject

} // namespace base
} // namespace masala

#endif //Masala_src_base_MasalaObject_hh