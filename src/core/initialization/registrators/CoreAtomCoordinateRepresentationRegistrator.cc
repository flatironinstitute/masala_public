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

/// @file src/base/managers/tracer/CoreAtomCoordinateRepresentationRegistrator.cc
/// @brief A static singleton that registers representations for atom coordinates
/// on first initialization.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <core/initialization/registrators/CoreAtomCoordinateRepresentationRegistrator.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationManager.hh>

// Core headers:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentationCreator.hh>

namespace masala {
namespace core {
namespace initialization {
namespace registrators {

/// @brief Instantiate the static singleton, triggering registration of the
/// atom coordinate representations.
void
CoreAtomCoordinateRepresentationRegistrator::register_atom_coordinate_representations() {
    static CoreAtomCoordinateRepresentationRegistrator atom_coord_rep_registrator;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
CoreAtomCoordinateRepresentationRegistrator::CoreAtomCoordinateRepresentationRegistrator() :
    masala::base::managers::engine::MasalaDataRepresentationRegistratorBase()
{
    masala::base::managers::engine::MasalaDataRepresentationManagerHandle manager(
        masala::base::managers::engine::MasalaDataRepresentationManager::get_instance()
    );
    CoreAtomCoordinateRepresentationRegistrator::write_to_tracer( "Registering core atom coordinate representations with the MasalaDataRepresentationManager." );
    // TODO: register all atom coordinate representations defined in core here.
    manager->register_data_representation( "masala::core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentation", masala::core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentationCreatorSP( new masala::core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentationCreator /*Note -- must use new, since constructor is protected.*/ ) );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "CoreAtomCoordinateRepresentationRegistrator".
std::string
CoreAtomCoordinateRepresentationRegistrator::class_name() const {
    return "CoreAtomCoordinateRepresentationRegistrator";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::core::initialization::registrators".
std::string
CoreAtomCoordinateRepresentationRegistrator::class_namespace() const {
    return "masala::core::initialization::registrators";
}

} // namespace registrators
} // namespace initialization
} // namespace core
} // namespace masala
