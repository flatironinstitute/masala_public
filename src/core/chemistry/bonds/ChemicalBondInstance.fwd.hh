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

/// @file src/core/chemistry/bonds/ChemicalBondInstance.fwd.hh
/// @brief Forward declarations for a class containing a particular
/// chemical bond between a pair of atoms.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_bonds_ChemicalBondInstance_fwd_hh
#define Masala_src_core_chemistry_bonds_ChemicalBondInstance_fwd_hh

#include <base/managers/memory/util.hh>
#include <base/enums/ChemicalBondTypeEnum.fwd.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace bonds {

    class ChemicalBondInstance;

    using ChemicalBondInstanceSP = MASALA_SHARED_POINTER< ChemicalBondInstance >;
    using ChemicalBondInstanceCSP = MASALA_SHARED_POINTER< ChemicalBondInstance const >;
    using ChemicalBondInstanceWP = MASALA_WEAK_POINTER< ChemicalBondInstance >;
    using ChemicalBondInstanceCWP = MASALA_WEAK_POINTER< ChemicalBondInstance const >;

    using ChemicalBondType = masala::base::enums::ChemicalBondType;

} // namespace bonds
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_bonds_ChemicalBondInstance_fwd_hh