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

/// @file src/core/chemistry/atoms/AtomInstance.fwd.hh
/// @brief Forward declarations for a class contiaining a description of the properties of
/// a particular atom.
/// @note This stores element type, formal charge, partial charge,
/// hybridization state... everything EXCEPT atomic coordinates.
/// This class is not threadsafe.  Protocols ought not to have
/// multiple threads operating on the same atom (or should implement
/// suitable mutex locking to allow this).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_AtomInstance_fwd_hh
#define Masala_src_core_chemistry_atoms_AtomInstance_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

    class AtomInstance;

    using AtomInstanceSP = MASALA_SHARED_POINTER< AtomInstance >;
    using AtomInstanceCSP = MASALA_SHARED_POINTER< AtomInstance const >;
    using AtomInstanceWP = MASALA_WEAK_POINTER< AtomInstance >;
    using AtomInstanceCWP = MASALA_WEAK_POINTER< AtomInstance const >;

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

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_AtomInstance_fwd_hh