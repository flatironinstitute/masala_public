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

/// @file src/base/enums/AtomHybridizationStateEnum.fwd.hh
/// @brief Declarations for the enum for chemical bond type.
/// @details Needs to be declared in masala::base to be accessible to API definitions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_enums_AtomHybridizationStateEnum_fwd_hh
#define Masala_src_base_enums_AtomHybridizationStateEnum_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace enums {

    /// @brief An enum for the hybridization state of an atom.
	/// @details If this is added to, then string_from_atom_hybridization_state_enum() should be updated.
    enum class AtomHybridizationState {
        INVALID_HYBRIDIZATION_STATE = -1, // Keep first.
        UNKNOWN_HYBRIDIZATION_STATE = 0, // Keep second.
        sp = 1, // Keep third.
        FIRST_HYBRIDIZATION_STATE = sp, // Keep fourth.
        sp2,
        sp3,
        s, // No hybridization -- just S-shell for hydrogen or helium.
        OTHER_HYBRIDIZATION_STATE, //Keep second-to-last.
        N_HYBRIDIZATION_STATES = OTHER_HYBRIDIZATION_STATE //Keep last.
    };

} // namespace enums
} // namespace base
} // namespace masala

#endif //Masala_src_base_enums_AtomHybridizationStateEnum_fwd_hh