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

/// @file src/base/managers/plugin_module/MasalaPluginCreator.cc
/// @brief A pure virtual base class for creators for plugin modules.
/// @details This allows plugins to be defined in other libraries and
/// registered at runtime with the central manager class, without the code
/// in this library having to know about the particular plugins available.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Header:
#include <base/managers/plugin_module/MasalaPluginCreator.hh>

// Base headers:
#include <base/types.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Comparison operator.
bool
MasalaPluginCreator::operator==(
	MasalaPluginCreator const & other
) const {
	return get_plugin_object_namespace_and_name() == other.get_plugin_object_namespace_and_name() &&
		get_plugin_object_manager_key() == other.get_plugin_object_manager_key();
} // MasalaPluginCreator::operator==()

/// @brief Get the namespace and name of the class of object that this creator creates.
std::string
MasalaPluginCreator::get_plugin_object_namespace_and_name() const {
	return get_plugin_object_namespace() + "::" + get_plugin_object_name();
}
	
/// @brief Get the map key for the class of object that this creator creates.
/// @details The map key is the concatenated vector of base class names (separated by commas)
/// followed by a colon and then the object name.
std::string
MasalaPluginCreator::get_plugin_object_manager_key() const {
	std::stringstream ss;
	std::vector< std::vector< std::string > > const categories( get_plugin_object_categories() );
	CHECK_OR_THROW_FOR_CLASS(
		!categories.empty(), "get_plugin_object_manager_key",
		"No categories were specified for plugin object type \"" + get_plugin_object_namespace_and_name() + "\"."
	);
	std::vector< std::string > const & firstcategory( categories[0] );
	CHECK_OR_THROW_FOR_CLASS(
		!firstcategory.empty(), "get_plugin_object_manager_key",
		"No hierarchical category relationship was specified for the first category for "
		"plugin object type \"" + get_plugin_object_namespace_and_name() + "\"."
	);
	for( base::Size i(0), imax(firstcategory.size()); i<imax; ++i ) {
		ss << firstcategory[i];
		if( imax > 1 && i < imax - 1 ) {
			ss << ",";
		} else {
			ss << ":";
		}
	}
	ss << get_plugin_object_namespace_and_name();
	return ss.str();
} // MasalaPluginCreator::get_plugin_object_manager_key()

} // namespace plugin_module	
} // namespace managers
} // namespace base
} // namespace masala
