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

/// @file src/core/molecular_system/kinematics/KinematicDataRepresentationBase.fwd.hh
/// @brief Forward declarations for a base class for Masala kinematic data representations, which facilitate kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).  This class is not intended
/// to be instantiated outside of the API system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_molecular_system_kinematics_KinematicDataRepresentationBase_fwd_hh
#define Masala_src_core_molecular_system_kinematics_KinematicDataRepresentationBase_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace core {
namespace molecular_system {
namespace kinematics {

	class KinematicDataRepresentationBase;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using KinematicDataRepresentationBaseSP = MASALA_SHARED_POINTER< KinematicDataRepresentationBase >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using KinematicDataRepresentationBaseCSP = MASALA_SHARED_POINTER< KinematicDataRepresentationBase const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using KinematicDataRepresentationBaseWP = MASALA_WEAK_POINTER< KinematicDataRepresentationBase >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using KinematicDataRepresentationBaseCWP = MASALA_WEAK_POINTER< KinematicDataRepresentationBase const >;

} // namespace kinematics
} // namespace molecular_system
} // namespace core
} // namespace masala

#endif //Masala_src_core_molecular_system_kinematics_KinematicDataRepresentationBase_fwd_hh