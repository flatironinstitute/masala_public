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

/// @file src/core/engine/kinematics/KinematicEngineBase.hh
/// @brief A base class for Masala kinematic engines, which perform kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_engine_kinematics_KinematicEngineBase_hh
#define Masala_src_core_engine_kinematics_KinematicEngineBase_hh

// Forward declarations:
#include <core/engine/kinematics/KinematicEngineBase.fwd.hh>

// Core headers:
#include <core/engine/MasalaEngine.hh>

namespace masala {
namespace core {
namespace engine {
namespace kinematics {

/// @brief A base class for Masala kinematic engines, which perform kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class KinematicEngineBase : public masala::core::engine::MasalaEngine {

public:

	/// @brief Default constructor.
	KinematicEngineBase() = default;

	/// @brief Copy constructor.
	KinematicEngineBase( KinematicEngineBase const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~KinematicEngineBase() = default;

}; // class KinematicEngineBase

} // namespace kinematics
} // namespace engine
} // namespace core
} // namespace masala

#endif //Masala_src_core_engine_kinematics_KinematicEngineBase_hh