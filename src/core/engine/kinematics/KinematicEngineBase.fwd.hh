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

/// @file src/core/engine/kinematics/KinematicEngineBase.fwd.hh
/// @brief Forward declarations for a base class for Masala kinematic engines, which perform kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_engine_kinematics_KinematicEngineBase_fwd_hh
#define Masala_src_core_engine_kinematics_KinematicEngineBase_fwd_hh

#include <memory> // For std::shared_ptr

namespace masala {
namespace core {
namespace engine {
namespace kinematics {

	class KinematicEngineBase;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	using KinematicEngineBaseSP = std::shared_ptr< KinematicEngineBase >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	using KinematicEngineBaseCSP = std::shared_ptr< KinematicEngineBase const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	using KinematicEngineBaseWP = std::weak_ptr< KinematicEngineBase >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	using KinematicEngineBaseCWP = std::weak_ptr< KinematicEngineBase const >;

} // namespace kinematics
} // namespace engine
} // namespace core
} // namespace masala

#endif //Masala_src_core_engine_kinematics_KinematicEngineBase_fwd_hh