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

/// @brief Register an engine, by name.
/// @details If throw_if_present is true, an exception is thrown if the engine_name is
/// already registered.  Otherwise, this silently replaces the registered engine.
void
MasalaEngineManager::register_engine(
    std::string const & engine_name,
    MasalaEngineCreatorCSP engine_creator,
    bool const throw_if_present /*= true*/
) {
    std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
    if( throw_if_present && engine_creators_.find(engine_name) != engine_creators_.end() ) {
        MASALA_THROW( class_namespace_and_name(), "register_engine", "Engine \"" + engine_name + "\" has already been registered!"  );
    }
    engine_creators_[engine_name] = engine_creator;
}

/// @brief Unregister an engine, by name.
/// @brief If the engine_name engine has not been registered, then (a) if throw_if_missing
/// is true, an exception is thrown, or (b) if it is false, nothing happens.
void
MasalaEngineManager::unregister_engine(
    std::string const & engine_name,
    bool const throw_if_missing /*= true*/
) {
    std::lock_guard< std::mutex > lock( masala_engine_manager_mutex_ );
    std::map< std::string, MasalaEngineCreatorCSP >::const_iterator it( engine_creators_.find(engine_name) );
    if( it == engine_creators_.end() ) {
        if( throw_if_missing ) {
            MASALA_THROW( class_namespace_and_name(), "unregister_engine", "No engine was registered with name \"" + engine_name + "\"." );
        } else {
            return;
        }
    }
    engine_creators_.erase(it);
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
