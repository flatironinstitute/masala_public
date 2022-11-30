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

/// @file src/core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.fwd.hh
/// @brief Forward declarations for a container of atom coordinates, using the Eigen linear
/// algebra library's data structures.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_fwd_hh
#define Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {

    class EigenLinalgCartesianAtomCoordinateRepresentation;

    using EigenLinalgCartesianAtomCoordinateRepresentationSP = MASALA_SHARED_POINTER< EigenLinalgCartesianAtomCoordinateRepresentation >;
    using EigenLinalgCartesianAtomCoordinateRepresentationCSP = MASALA_SHARED_POINTER< EigenLinalgCartesianAtomCoordinateRepresentation const >;
    using EigenLinalgCartesianAtomCoordinateRepresentationWP = MASALA_WEAK_POINTER< EigenLinalgCartesianAtomCoordinateRepresentation >;
    using EigenLinalgCartesianAtomCoordinateRepresentationCWP = MASALA_WEAK_POINTER< EigenLinalgCartesianAtomCoordinateRepresentation const >;

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentation_fwd_hh