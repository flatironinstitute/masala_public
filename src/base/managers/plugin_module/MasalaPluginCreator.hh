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
/// @brief Forward declarations for a pure virtual base class for creators
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

namespace masala {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief A base class for all Masala derived classes.  This allows the possibility of having a
/// generic MasalaPluginCreator pointer or shared pointer.
/// @note The MasalaConfigurationManager can access the private member functions (and data) of MasalaPluginCreators.
/// This allows it to call load_configuration() when first needed.
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
	masala::base::MasalaObjectSP
	create_plugin_object() const = 0;

}; // class MasalaPluginCreator

} // namespace plugin_module	
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_plugin_module_MasalaPluginCreator_hh