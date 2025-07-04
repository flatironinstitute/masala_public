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

/// @file src/base/managers/engine/MasalaEngineCreator.cc
/// @brief A pure virtual base class for creators for engines.
/// @details Subclasses will be needed for each Masala engine type that a library defines.
/// These must be registered with the MasalaEngineManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <base/managers/engine/MasalaEngineCreator.hh>

// Base headers:
#include <base/managers/engine/MasalaEngineAPI.hh>
#ifndef NDEBUG
#include <base/error/ErrorHandling.hh>
#endif

namespace masala {
namespace base {
namespace managers {
namespace engine {


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief The create_engine() function just calls the
/// create_plugin_object() function under the hood.
MasalaEngineAPISP
MasalaEngineCreator::create_engine() const {
#ifndef NDEBUG
    // In debiug builds, double-check return type.
    MasalaEngineAPISP returnobj( std::dynamic_pointer_cast< MasalaEngineAPI >( create_plugin_object() ) );
    CHECK_OR_THROW_FOR_CLASS( returnobj != nullptr, "create_engine", "The " + returnobj->inner_class_name() + " class is not an engine!" );
    return returnobj;
#else
    // In release builds, assume that return type is fine.
    return std::static_pointer_cast< MasalaEngineAPI >( create_plugin_object() );
#endif
}


} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
