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

/// @file src/base/managers/engine/MasalaDataRepresentationCreator.hh
/// @brief A pure virtual base class for creators for data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationCreator_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationCreator_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginCreator.hh>
#include <base/managers/engine/MasalaDataRepresentationAPI.fwd.hh>
#include <base/managers/engine/MasalaDataRepresentationManager.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A pure virtual base class for creators for data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationCreator : public masala::base::managers::plugin_module::MasalaPluginCreator {

    friend class masala::base::managers::engine::MasalaDataRepresentationManager;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationCreator() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationCreator( MasalaDataRepresentationCreator const & ) = delete;

    // Destructor.
    ~MasalaDataRepresentationCreator() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Creators must implement a create_data_representation() function.  Under the
    /// hood this just calls create_plugin_object().
    MasalaDataRepresentationAPISP
    create_data_representation() const;

};

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationCreator_hh