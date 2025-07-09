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

/// @file src/base/managers/engine/MasalaDataRepresentationCreator.cc
/// @brief A pure virtual base class for creators for data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Header:
#include <base/managers/engine/MasalaDataRepresentationCreator.hh>

// Base includes:
#include <base/managers/engine/MasalaDataRepresentationAPI.hh>
#ifndef NDEBUG
#include <base/error/ErrorHandling.hh>
#endif

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name, static version.
/// @returns "MasalaDataRepresentationCreator".
/*static*/
std::string
MasalaDataRepresentationCreator::class_name_static() {
    return "MasalaDataRepresentationCreator";
}

/// @brief Get the class namespace, static version.
/// @returns "masala::base::managers::engine".
/*static*/
std::string
MasalaDataRepresentationCreator::class_namespace_static() {
    return "masala::base::managers::engine";
}

/// @brief Get the class namespace and name, static version.
/// @returns "masala::base::managers::engine::MasalaDataRepresentationCreator".
/*static*/
std::string
MasalaDataRepresentationCreator::class_namespace_and_name_static() {
    return class_namespace_static() + "::" + class_name_static();
}

/// @brief Creators must implement a create_data_representation() function.  Under the
/// hood this just calls create_plugin_object().
MasalaDataRepresentationAPISP
MasalaDataRepresentationCreator::create_data_representation() const {
#ifndef NDEBUG
    // In debiug builds, double-check return type.
    MasalaDataRepresentationAPISP returnobj( std::dynamic_pointer_cast< MasalaDataRepresentationAPI >( create_plugin_object() ) );
    CHECK_OR_THROW_FOR_CLASS( returnobj != nullptr, "create_data_representation", "The " + returnobj->inner_class_name() + " class is not an engine!" );
    return returnobj;
#else
    // In release builds, assume that return type is fine.
    return std::static_pointer_cast< MasalaDataRepresentationAPI >( create_plugin_object() );
#endif
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
