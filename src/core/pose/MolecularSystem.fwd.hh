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

/// @file src/core/pose/MolecularSystem.fwd.hh
/// @brief Forward declarations for a class representing a molecular structure.
/// @details MolecularSystems store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_pose_MolecularSystem_fwd_hh
#define Masala_src_core_pose_MolecularSystem_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace core {
namespace pose {

    class MolecularSystem;

    using MolecularSystemSP = MASALA_SHARED_POINTER< MolecularSystem >;
    using MolecularSystemCSP = MASALA_SHARED_POINTER< MolecularSystem const >;
    using MolecularSystemWP = MASALA_WEAK_POINTER< MolecularSystem >;
    using MolecularSystemCWP = MASALA_WEAK_POINTER< MolecularSystem const >;

} // namespace pose
} // namespace core
} // namespace masala

#endif // Masala_src_core_pose_MolecularSystem_fwd_hh
