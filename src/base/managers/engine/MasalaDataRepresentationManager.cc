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

/// @file src/base/managers/engine/MasalaDataRepresentationManager.cc
/// @brief A static singleton for managing available data representaitons.
/// @details Modules may register and retrieve data representations by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/engine/MasalaDataRepresentationManager.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationCreatorBase.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaDataRepresentationManagerHandle
MasalaDataRepresentationManager::get_instance() {
    static MasalaDataRepresentationManager config_manager;
    return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaDataRepresentationManager".
std::string
MasalaDataRepresentationManager::class_name() const {
    return "MasalaDataRepresentationManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::engine".
std::string
MasalaDataRepresentationManager::class_namespace() const {
    return "masala::base::managers::engine";
}

/// @brief Create a data representation, by name.
/// @details If throw_if_missing is true, this function will throw an exception if it can't
/// find an data representation creator for the specified data representation type.  Otherwise,
/// it will return nullptr.
MasalaDataRepresentationBaseSP
MasalaDataRepresentationManager::create_data_representation(
    std::string const & data_representation_type,
    bool const throw_if_missing /*= true*/
) const {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    std::map< std::string, MasalaDataRepresentationCreatorBaseCSP >::const_iterator it( data_representation_creators_.find(data_representation_type) );
    if( it == data_representation_creators_.end() ) {
        if( throw_if_missing ) {
            MASALA_THROW( class_namespace_and_name(), "create_data_representation", "Could not find data representation \"" + data_representation_type + "\".  Has it been registered?" );
        } else {
            return nullptr;
        }
    }
    return it->second->create_data_representation();
}

/// @brief Register a data representation, by name.
/// @details If throw_if_present is true, an exception is thrown if the data_representation_name is
/// already registered.  Otherwise, this silently replaces the registered data representation.
void
MasalaDataRepresentationManager::register_data_representation(
    std::string const & data_representation_name,
    MasalaDataRepresentationCreatorBaseCSP data_representation_creator,
    bool const throw_if_present /*= true*/
) {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    if( throw_if_present && data_representation_creators_.find(data_representation_name) != data_representation_creators_.end() ) {
        MASALA_THROW( class_namespace_and_name(), "register_data_representation", "DataRepresentation \"" + data_representation_name + "\" has already been registered!"  );
    }
    write_to_tracer( "Registering " + data_representation_name + " with MasalaDataRepresentationManager." );
    data_representation_creators_[data_representation_name] = data_representation_creator;
}

/// @brief Unregister a data representation, by name.
/// @brief If the data_representation_name data representation has not been registered,
/// then (a) if throw_if_missing is true, an exception is thrown, or (b) if it is false,
/// 
void
MasalaDataRepresentationManager::unregister_data_representation(
    std::string const & data_representation_name,
    bool const throw_if_missing /*= true*/
) {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    std::map< std::string, MasalaDataRepresentationCreatorBaseCSP >::const_iterator it( data_representation_creators_.find(data_representation_name) );
    if( it == data_representation_creators_.end() ) {
        if( throw_if_missing ) {
            MASALA_THROW( class_namespace_and_name(), "unregister_data_representation", "No data representation was registered with name \"" + data_representation_name + "\"." );
        } else {
            return;
        }
    }
    data_representation_creators_.erase(it);
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
