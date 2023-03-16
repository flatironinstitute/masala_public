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

/// @file src/core/chemistry/MolecularGeometryConfiguration.fwd.hh
/// @brief Forward declarations for a container of configuration settings for a
/// MolecularGeometry object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_MolecularGeometryConfiguration_fwd_hh
#define Masala_src_core_chemistry_MolecularGeometryConfiguration_fwd_hh

// STL headers
#include <base/managers/memory/util.hh>

namespace masala {
namespace core {
namespace chemistry {

    class MolecularGeometryConfiguration;

    using MolecularGeometryConfigurationSP = MASALA_SHARED_POINTER< MolecularGeometryConfiguration >;
    using MolecularGeometryConfigurationCSP = MASALA_SHARED_POINTER< MolecularGeometryConfiguration const >;
    using MolecularGeometryConfigurationWP = MASALA_WEAK_POINTER< MolecularGeometryConfiguration >;
    using MolecularGeometryConfigurationCWP = MASALA_WEAK_POINTER< MolecularGeometryConfiguration const>;

} // namespace chemistry
} // namespace core
} // namespace masala

#endif //Masala_src_core_chemistry_MolecularGeometryConfiguration_fwd_hh
