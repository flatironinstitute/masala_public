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

/// @file src/base/managers/engine/MasalaEngineManager.hh
/// @brief A static singleton for managing available engines.
/// @details Modules may register and retrieve engines by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngineManager_hh
#define Masala_src_base_managers_engine_MasalaEngineManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/engine/MasalaEngineManager.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginAPI.fwd.hh>
#include <base/managers/engine/MasalaEngine.fwd.hh>
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>
#include <base/managers/engine/MasalaEngineAPI.hh>

// STL headers:
#include <map>
#include <mutex>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A static singleton for managing available engines.
/// @details Modules may register and retrieve engines by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaEngineManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaEngineManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaEngineManager( MasalaEngineManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaEngineManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaEngineManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaEngineManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::engine".
    std::string
    class_namespace() const override;

    /// @brief Create an engine, by name.
    /// @details If throw_if_missing is true, this function will throw an exception if it can't
    /// find an engine creator for the specified engine type.  Otherwise, it will return nullptr.
    MasalaEngineAPISP
    create_engine(
        std::string const & engine_type,
        bool const throw_if_missing = true
    ) const;

    /// @brief Register an engine.
    /// @details An exception is thrown if the engine name is already registered.
    void
    register_engine(
        MasalaEngineCreatorCSP const & engine_creator
    );

    /// @brief Register a set of engines.
    /// @details An exception is thrown if any of the engine names are already registered.
    void
    register_engines(
        std::vector< MasalaEngineCreatorCSP > const & engine_creators
    );

	/// @brief Unregister an engine.
	/// @brief If the engine has not been registered, an exception is thrown.
	void
	unregister_engine(
		MasalaEngineCreatorCSP const & engine_creator
	);

	/// @brief Unregister a set of engines.
	/// @brief If an engine has not been registered, an exception is thrown.
	void
	unregister_engines(
		std::vector< MasalaEngineCreatorCSP > const & engine_creators
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Register an engine.
    /// @note The masala_engine_manager_mutex_ must be locked before this function is called.
    /// @details An exception is thrown if the engine name is already registered.
    void
    register_engine_mutex_locked(
        MasalaEngineCreatorCSP const & engine_creator
    );

	/// @brief Unregister an engine.
	/// @note The masala_engine_manager_mutex_ must be locked before this function is called.
	/// @details An exception is thrown if the engine name is not already registered.
	void
	unregister_engine_mutex_locked(
		MasalaEngineCreatorCSP const & engine_creator
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex to lock this object.
    mutable std::mutex masala_engine_manager_mutex_;

    /// @brief A map of string to engine creator.
    std::map< std::string, MasalaEngineCreatorCSP > engine_creators_;

};

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaEngineManager_hh