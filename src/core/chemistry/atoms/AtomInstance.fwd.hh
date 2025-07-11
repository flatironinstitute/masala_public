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
#include <base/enums/AtomHybridizationStateEnum.fwd.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

    class AtomInstance;

    using AtomInstanceSP = MASALA_SHARED_POINTER< AtomInstance >;
    using AtomInstanceCSP = MASALA_SHARED_POINTER< AtomInstance const >;
    using AtomInstanceWP = MASALA_WEAK_POINTER< AtomInstance >;
    using AtomInstanceCWP = MASALA_WEAK_POINTER< AtomInstance const >;

	using masala::base::enums::AtomHybridizationState;

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_AtomInstance_fwd_hh