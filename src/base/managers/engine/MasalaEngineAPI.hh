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

/// @file src/base/managers/plugin_module/MasalaEngineAPI.hh
/// @brief A base class for all Masala derived API classes for MasalaEngines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngineAPI_hh
#define Masala_src_base_managers_engine_MasalaEngineAPI_hh

// Forward declarations:
#include <base/managers/engine/MasalaEngineAPI.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginAPI.hh>
#include <base/managers/engine/MasalaEngine.fwd.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A base class for Masala API derived classes for MasalaEngines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineAPI : public masala::base::managers::plugin_module::MasalaPluginAPI {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS, DESTRUCTORS, AND NAMING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaEngineAPI() = default;

	/// @brief Copy constructor.
	MasalaEngineAPI( MasalaEngineAPI const & ) = default;

	/// @brief Destructor.
	virtual ~MasalaEngineAPI() = default;

	/// @brief Get the name of this class ("MasalaEngineAPI").
	inline std::string class_name() const override { return class_name_static(); }

	/// @brief Get the name of this class ("MasalaEngineAPI").
	inline static std::string class_name_static() { return "MasalaEngineAPI"; }

	/// @brief Get the namespace of this class ("masala::base::managers::engine").
	inline std::string class_namespace() const override { return class_namespace_static(); }

	/// @brief Get the name of this class ("masala::base::managers::engine").
	inline static std::string class_namespace_static() { return "masala::base::managers::engine"; }

	/// @brief Get the namespace and name of this class ("masala::base::managers::engine::MasalaEngineAPI").
	inline static std::string class_namespace_and_name_static() { return class_namespace_static() + "::" + class_name_static(); }

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the inner data representation object.
    /// @details Implemented by derived classes.
    /// @note Use this function with care!  Holding a shared pointer to the inner
    /// object can nullify the thread safety that the API object provides.
    virtual
    MasalaEngineSP
    get_inner_engine_object() = 0;

    /// @brief Access the inner data representation object (const access).
    /// @details Implemented by derived classes.
    /// @note Use this function with care!  Holding a const shared pointer to the inner
    /// object can nullify the thread safety that the API object provides.
    virtual
    MasalaEngineCSP
    get_inner_engine_object_const() const = 0;

}; // class MasalaEngineAPI

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaEngineAPI_hh