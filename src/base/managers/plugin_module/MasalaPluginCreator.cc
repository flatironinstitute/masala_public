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
	return get_plugin_object_name() == other.get_plugin_object_name() &&
		get_plugin_object_manager_key() == other.get_plugin_object_manager_key();
} // MasalaPluginCreator::operator==()
	
/// @brief Get the map key for the class of object that this creator creates.
/// @details The map key is the concatenated vector of base class names (separated by commas)
/// followed by a colon and then the object name.
std::string
MasalaPluginCreator::get_plugin_object_manager_key() const {
	std::stringstream ss;
	std::vector< std::vector< std::string > > const categories( get_plugin_object_categories() );
	CHECK_OR_THROW_FOR_CLASS(
		!categories.empty(), "get_plugin_object_manager_key",
		"No categories were specified for plugin object type \"" + get_plugin_object_name() + "\"."
	);
	std::vector< std::string > const & firstcategory( categories[0] );
	CHECK_OR_THROW_FOR_CLASS(
		!firstcategory.empty(), "get_plugin_object_manager_key",
		"No hierarchical category relationship was specified for the first category for "
		"plugin object type \"" + get_plugin_object_name() + "\"."
	);
	for( base::Size i(0), imax(firstcategory.size()); i<imax; ++i ) {
		ss << firstcategory[i];
		if( imax > 1 && i < imax - 1 ) {
			ss << ",";
		} else {
			ss << ":";
		}
	}
	ss << get_plugin_object_name();
	return ss.str();
} // MasalaPluginCreator::get_plugin_object_manager_key()

} // namespace plugin_module	
} // namespace managers
} // namespace base
} // namespace masala
