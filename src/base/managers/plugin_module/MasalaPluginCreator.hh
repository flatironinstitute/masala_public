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

/// @file src/base/managers/plugin_module/MasalaPluginCreator.hh
/// @brief Headers for a pure virtual base class for creators
/// for plugin modules.
/// @details This allows plugins to be defined in other libraries and
/// registered at runtime with the central manager class, without the code
/// in this library having to know about the particular plugins available.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_plugin_module_MasalaPluginCreator_hh
#define Masala_src_base_managers_plugin_module_MasalaPluginCreator_hh

// Parent class:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/plugin_module/MasalaPluginCreator.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginAPI.fwd.hh>
#include <base/managers/plugin_module/MasalaPlugin.fwd.hh>

// STL headers:
#include <vector>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief A pure virtual base class for creators for plugin modules.
/// @details This allows plugins to be defined in other libraries and
/// registered at runtime with the central manager class, without the code
/// in this library having to know about the particular plugins available.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaPluginCreator : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaPluginCreator() = default;

	/// @brief Copy constructor.
	MasalaPluginCreator( MasalaPluginCreator const & ) = default;

	/// @brief Virtual destructor.
	~MasalaPluginCreator() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Comparison operator.
	bool operator==( MasalaPluginCreator const & other ) const;

	/// @brief Create an object of the desired type (or, more precisely, an API container
	/// for an object of a desired type).
	/// @details Must be implemented by derived classes.
	virtual
	masala::base::managers::plugin_module::MasalaPluginAPISP
	create_plugin_object() const = 0;

	/// @brief Create an object of the desired type (or, more precisely, an API container
	/// for an object of a desired type).
	/// @details Must be implemented by derived classes.
	virtual
	masala::base::managers::plugin_module::MasalaPluginAPISP
	encapsulate_plugin_object_instance(
		masala::base::managers::plugin_module::MasalaPluginSP const & object
	) const = 0;

	/// @brief Create an object of the desired type (or, more precisely, an API container
	/// for an object of a desired type).
	/// @details Must be implemented by derived classes.
	virtual
	masala::base::managers::plugin_module::MasalaPluginAPICSP
	encapsulate_const_plugin_object_instance(
		masala::base::managers::plugin_module::MasalaPluginCSP const & object
	) const = 0;

	/// @brief Return the names of the categories for this type of plugin object.
	/// @details For example, Selector, AtomSelector, etc.
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector).
	/// A plugin can be in more than one hierarchical category, but must be in at least one.  The
	/// first one is used as the primary key.
	virtual
	std::vector< std::vector< std::string > >
	get_plugin_object_categories() const = 0; 

	/// @brief Return keywords associated with this plugin module.  For instance,
	/// "protein", "design", "metalloprotein".
	virtual
	std::vector< std::string >
	get_plugin_object_keywords() const = 0;

	/// @brief Get The name of the class of object that this creator creates.
	virtual
	std::string
	get_plugin_object_name() const = 0;

	/// @brief Get the namespace of the class of object that this creator creates.
	virtual
	std::string
	get_plugin_object_namespace() const = 0;

	/// @brief Get the namespace and name of the class of object that this creator creates.
	std::string
	get_plugin_object_namespace_and_name() const;
	
	/// @brief Get the map key for the class of object that this creator creates.
	/// @details The map key is the concatenated vector of base class names (separated by commas)
	/// followed by a colon and then the object name.
	std::string
	get_plugin_object_manager_key() const;

}; // class MasalaPluginCreator

} // namespace plugin_module	
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_plugin_module_MasalaPluginCreator_hh