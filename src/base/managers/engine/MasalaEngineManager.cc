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

/// @file src/base/managers/engine/MasalaEngineManager.cc
/// @brief A static singleton for managing available engines.
/// @details Modules may register and retrieve engines by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/engine/MasalaEngineManager.hh>

// Base headers:
#include <base/managers/engine/MasalaEngineCreator.hh>
#include <base/managers/engine/MasalaEngineRequest.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaEngineManagerHandle
MasalaEngineManager::get_instance() {
    static MasalaEngineManager config_manager;
    return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaEngineManager".
std::string
MasalaEngineManager::class_name() const {
    return "MasalaEngineManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::engine".
std::string
MasalaEngineManager::class_namespace() const {
    return "masala::base::managers::engine";
}

/// @brief Create an engine, by name.
/// @details If throw_if_missing is true, this function will throw an exception if it can't
/// find an engine creator for the specified engine type.  Otherwise, it will return nullptr.
MasalaEngineAPISP
MasalaEngineManager::create_engine(
    std::string const & engine_type,
    bool const throw_if_missing /*= true*/
) const {
    std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
    std::map< std::string, MasalaEngineCreatorCSP >::const_iterator it( engine_creators_.find(engine_type) );
    if( it == engine_creators_.end() ) {
        if( throw_if_missing ) {
            MASALA_THROW( class_namespace_and_name(), "create_engine", "Could not find engine \"" + engine_type + "\".  Has it been registered?" );
        } else {
            return nullptr;
        }
    }
    return it->second->create_engine();
}

/// @brief Register an engine.
/// @details An exception is thrown if the engine name is already registered.
void
MasalaEngineManager::register_engine(
    MasalaEngineCreatorCSP const & engine_creator
) {
    std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
    register_engine_mutex_locked( engine_creator );
}

/// @brief Register a set of engines.
/// @details An exception is thrown if any of the engine names are already registered.
void
MasalaEngineManager::register_engines(
    std::vector< MasalaEngineCreatorCSP > const & engine_creators
) {
    std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
    for( auto const & engine_creator : engine_creators ) {
        register_engine_mutex_locked( engine_creator );
    }
}

/// @brief Unregister an engine.
/// @brief If the engine has not been registered, an exception is thrown.
void
MasalaEngineManager::unregister_engine(
    MasalaEngineCreatorCSP const & engine_creator
) {
	std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
	unregister_engine_mutex_locked( engine_creator );
}

/// @brief Unregister a set of engines.
/// @brief If an engine has not been registered, an exception is thrown.
void
MasalaEngineManager::unregister_engines(
    std::vector< MasalaEngineCreatorCSP > const & engine_creators
) {
	std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
	for( auto const & engine_creator : engine_creators ) {
		unregister_engine_mutex_locked( engine_creator );
	}
}

/// @brief Completely remove all engines.
void
MasalaEngineManager::reset() {
    {
        std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
        engine_creators_.clear();
    }
    write_to_tracer( "Reset the MasalaEngineManager.  No engines are registered." );
}

/// @brief Get the data representations compatible with a set of criteria encoded in a request object.
std::vector< MasalaEngineCreatorCSP >
MasalaEngineManager::get_compatible_engine_creators(
    MasalaEngineRequest const & request
) const {
    std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
    std::vector< MasalaEngineCreatorCSP > outvec;
    for( auto const & creator : engine_creators_ ) {
        if( request.engine_is_compatible_with_criteria( *(creator.second) ) ) {
            outvec.push_back( creator.second );
        }
    }
    outvec.shrink_to_fit();
    return outvec;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Register an engine.
/// @note The masala_engine_manager_mutex_ must be locked before this function is called.
/// @details An exception is thrown if the engine name is already registered.
void
MasalaEngineManager::register_engine_mutex_locked(
    MasalaEngineCreatorCSP const & engine_creator
) {
    CHECK_OR_THROW_FOR_CLASS( engine_creator != nullptr, "register_engine_mutex_locked",
        "A null pointer was passed to this function!  This is a program error, so consult the "
        "developer of the Masala plugin suite that created the error."
    );
    std::string const engine_name( engine_creator->get_plugin_object_namespace_and_name() );
    if( engine_creators_.find(engine_name) != engine_creators_.end() ) {
        MASALA_THROW( class_namespace_and_name(), "register_engine", "Engine \"" + engine_name + "\" has already been registered!"  );
    }
    engine_creators_[engine_name] = engine_creator;
    write_to_tracer( "Registered engine " + engine_name + " with the MasalaEngineManager." );
}

/// @brief Unregister an engine.
/// @note The masala_engine_manager_mutex_ must be locked before this function is called.
/// @details An exception is thrown if the engine name is not already registered.
void
MasalaEngineManager::unregister_engine_mutex_locked(
	MasalaEngineCreatorCSP const & engine_creator
) {
    CHECK_OR_THROW_FOR_CLASS( engine_creator != nullptr, "unregister_engine_mutex_locked",
        "A null pointer was passed to this function!  This is a program error, so consult the "
        "developer of the Masala plugin suite that created the error."
    );
	std::string const engine_name( engine_creator->get_plugin_object_namespace_and_name() );
	std::map< std::string, MasalaEngineCreatorCSP >::const_iterator it( engine_creators_.find(engine_name) );
	if( it == engine_creators_.end() ) {
		MASALA_THROW( class_namespace_and_name(), "unregister_engine_mutex_locked",
			"No engine was previously registered with name \"" + engine_name + "\"."
		);
	}
	engine_creators_.erase(it);
    write_to_tracer( "Unregistered engine " + engine_name + " from the MasalaEngineManager." );
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
