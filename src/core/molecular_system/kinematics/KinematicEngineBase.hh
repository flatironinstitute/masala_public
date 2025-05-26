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

/// @file src/core/molecular_system/kinematics/KinematicEngineBase.hh
/// @brief Headers for a base class for Masala kinematic data representations, which facilitate kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).  This class is not intended
/// to be instantiated outside of the API system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_molecular_system_kinematics_KinematicEngineBase_hh
#define Masala_src_core_molecular_system_kinematics_KinematicEngineBase_hh

// Forward declarations:
#include <core/molecular_system/kinematics/KinematicEngineBase.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentation.hh>

namespace masala {
namespace core {
namespace molecular_system {
namespace kinematics {

/// @brief A base class for Masala kinematic data representations, which facilitate kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).  This class is not intended
/// to be instantiated outside of the API system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class KinematicEngineBase : public masala::base::managers::engine::MasalaDataRepresentation {

	typedef masala::base::managers::engine::MasalaDataRepresentation Parent;
	typedef masala::base::managers::engine::MasalaDataRepresentationSP ParentSP;
	typedef masala::base::managers::engine::MasalaDataRepresentationCSP ParentCSP;

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
} // namespace molecular_system
} // namespace core
} // namespace masala

#endif //Masala_src_core_molecular_system_kinematics_KinematicEngineBase_hh