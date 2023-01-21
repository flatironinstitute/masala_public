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

/// @file src/base/managers/engine/EigenLinalgCartesianAtomCoordinateRepresentationCreator.cc
/// @brief A creator for Eigen linear algebra Cartesian atom coordinate data representations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentationCreator.hh>

// Core headers:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the class name.
    /// @returns "EigenLinalgCartesianAtomCoordinateRepresentationCreator".
    std::string EigenLinalgCartesianAtomCoordinateRepresentationCreator::class_name() const { return "EigenLinalgCartesianAtomCoordinateRepresentationCreator"; }

    /// @brief Get the class namespace.
    /// @returns "masala::core::chemistry::atoms::coordinates"
    std::string EigenLinalgCartesianAtomCoordinateRepresentationCreator::class_namespace() const { return "masala::core::chemistry::atoms::coordinates"; }


////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Creators must implement a create_data_representation() function.
/// @details Protected so that this can only be called by the MasalaDataRepresentationManager,
/// for which this is a friend class.
base::managers::engine::MasalaDataRepresentationBaseSP
EigenLinalgCartesianAtomCoordinateRepresentationCreator::create_data_representation() const {
    return masala::make_shared< EigenLinalgCartesianAtomCoordinateRepresentation >();
}


} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
