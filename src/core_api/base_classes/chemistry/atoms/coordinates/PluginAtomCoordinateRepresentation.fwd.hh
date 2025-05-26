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

/// @file src/core_api/base_classes/chemistry/atoms/coordinates/PluginAtomCoordinateRepresentation.fwd.hh
/// @brief Forward declarations for a pure virtual base class class for the container
/// of a collection of atom coordinates, represented in a manner that can make manipulations
/// very efficient, to be implemented in plugin libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_chemistry_atoms_coordinates_PluginAtomCoordinateRepresentation_fwd_hh
#define Masala_src_core_api_base_classes_chemistry_atoms_coordinates_PluginAtomCoordinateRepresentation_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace chemistry {
namespace atoms {
namespace coordinates {

    class PluginAtomCoordinateRepresentation;

    using PluginAtomCoordinateRepresentationSP = MASALA_SHARED_POINTER< PluginAtomCoordinateRepresentation >;
    using PluginAtomCoordinateRepresentationCSP = MASALA_SHARED_POINTER< PluginAtomCoordinateRepresentation const >;
    using PluginAtomCoordinateRepresentationWP = MASALA_WEAK_POINTER< PluginAtomCoordinateRepresentation >;
    using PluginAtomCoordinateRepresentationCWP = MASALA_WEAK_POINTER< PluginAtomCoordinateRepresentation const >;

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_chemistry_atoms_coordinates_PluginAtomCoordinateRepresentation_fwd_hh