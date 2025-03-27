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

/// @file src/base/MasalaNoAPIObject.hh
/// @brief Headers for a base class for all Masala derived classes that lack an API.
/// @details These might include lightweight classes used for caching data within a library, but which
/// are not intended to be configured by code outside that library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_MasalaNoAPIObject_hh
#define Masala_src_base_MasalaNoAPIObject_hh

// Forward declarations:
#include <base/MasalaNoAPIObject.fwd.hh>

// Parent header:
#include <base/MasalaObject.hh>

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

/// @brief A base class for all Masala derived classes that lack an API.
/// @details These might include lightweight classes used for caching data within a library, but which
/// are not intended to be configured by code outside that library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaNoAPIObject : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaNoAPIObject() = default;

	/// @brief Copy constructor.
	MasalaNoAPIObject( MasalaNoAPIObject const & ) = default;

	/// @brief Virtual destructor.
	virtual ~MasalaNoAPIObject() = default;

	/// @brief Every class can name itself.
	virtual std::string class_name() const = 0;

	/// @brief Every class can provide its own namespace.
	virtual std::string class_namespace() const = 0;

	/// @brief Get the namespace and name for this pure virtual base class.
	/// @returns "masala::base::MasalaNoAPIObject"
    static
	std::string
	class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get an object describing the API for this object.
	/// @details This and all derived classes return nullptr.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() final;

}; // class MasalaNoAPIObject

} // namespace base
} // namespace masala

#endif //Masala_src_base_MasalaNoAPIObject_hh