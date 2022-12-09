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

/// @file src/base/managers/plugin_module/MasalaPlugin.hh
/// @brief Headers for a pure virtual base class for plugin modules.
/// @details This allows plugins to be defined in other libraries and
/// registered at runtime with the central manager class, without the code
/// in this library having to know about the particular plugins available.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_plugin_module_MasalaPlugin_hh
#define Masala_src_base_managers_plugin_module_MasalaPlugin_hh

// Parent class:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/plugin_module/MasalaPlugin.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief A pure virtual base class for plugin modules.
/// @details This allows plugins to be defined in other libraries and
/// registered at runtime with the central manager class, without the code
/// in this library having to know about the particular plugins available.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaPlugin : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaPlugin() = default;

	/// @brief Copy constructor.
	MasalaPlugin( MasalaPlugin const & ) = default;

	/// @brief Virtual destructor.
	~MasalaPlugin() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the category or categories for this plugin class.
    /// @details Pure virtual; must be implemented by derived classes.
    /// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
    /// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
    /// in more than one hierarchical category (in which case there would be more than one
    /// entry in the outher vector), but must be in at least one.  The first one is used as
    /// the primary key.
    virtual
    std::vector< std::vector< std::string > >
    get_categories() const = 0;

    /// @brief Get the keywords for this plugin class.
    /// @details Pure virtual; must be implemented by derived classes.
    virtual
    std::vector< std::string >
    get_keywords() const = 0;

}; // class MasalaPlugin

} // namespace plugin_module	
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_plugin_module_MasalaPlugin_hh