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

/// @file src/base/managers/plugin_module/MasalaDataRepresentationAPI.hh
/// @brief A base class for all Masala derived API classes for MasalaDataRepresentations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationAPI_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationAPI_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationAPI.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentation.fwd.hh>
#include <base/managers/plugin_module/MasalaPluginAPI.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A base class for Masala API derived classes for MasalaDataRepresentations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationAPI : public masala::base::managers::plugin_module::MasalaPluginAPI {

public:

	/// @brief Default constructor.
	MasalaDataRepresentationAPI() = default;

	/// @brief Copy constructor.
	MasalaDataRepresentationAPI( MasalaDataRepresentationAPI const & ) = default;

	/// @brief Destructor.
	virtual ~MasalaDataRepresentationAPI() = default;

	/// @brief Get the namespace and name for this pure virtual base class.
	/// @returns "masala::base::managers::engine::MasalaDataRepresentationAPI"
	static
	std::string
	class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Access the inner data representation object.
	/// @details Implemented by derived classes.
	/// @note Use this function with care!  Holding a shared pointer to the inner
	/// object can nullify the thread safety that the API object provides.
	virtual
	MasalaDataRepresentationSP
	get_inner_data_representation_object() = 0;

	/// @brief Access the inner data representation object (const access).
	/// @details Implemented by derived classes.
	/// @note Use this function with care!  Holding a const shared pointer to the inner
	/// object can nullify the thread safety that the API object provides.
	virtual
	MasalaDataRepresentationCSP
	get_inner_data_representation_object_const() const = 0;

	/// @brief Is the inner object empty?
	virtual bool inner_object_empty() const = 0;

	/// @brief Clear the data from the inner data representation object, but do not alter its configuration.
	virtual void inner_object_clear() = 0;

	/// @brief Reset the inner object completely (deleting data and clearing configuration).
	virtual void inner_object_reset() = 0;

}; // class MasalaDataRepresentationAPI

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaDataRepresentationAPI_hh