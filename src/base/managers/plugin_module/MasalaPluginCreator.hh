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

	/// @brief Create an object of the desired type.
	/// @details Must be implemented by derived classes.
	virtual
	masala::base::managers::plugin_module::MasalaPluginSP
	create_plugin_object() const = 0;

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