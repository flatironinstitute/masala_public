/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/base/enums/ChemicalBondTypeEnum.hh
/// @brief Declarations for the enum for chemical bond type.
/// @details Needs to be declared in masala::base to be accessible to API definitions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_enums_ChemicalBondTypeEnum_fwd_hh
#define Masala_src_base_enums_ChemicalBondTypeEnum_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace enums {

	/// @brief An enum for the type of bond.
	/// @details If this list is expanded, the core::chemistry::bonds::string_from_bond_type()
	/// function must be updated.
    enum class ChemicalBondType {
        INVALID_CHEMICAL_BOND_TYPE = -1, // Keep first.
        UNSPECIFIED_CHEMICAL_BOND_TYPE = 0, // Keep second.
        SINGLE_BOND = 1, // Keep third.
        DOUBLE_BOND = 2, // Keep fourth.
        TRIPLE_BOND = 3, // Keep fifth.
        PARTIAL_DOUBLE_BOND,
        COORDINATE_COVALENT_BOND, // To metals
        HYDROGEN_BOND,
        CATION_PI_BOND,
        PI_PI_BOND,
        HALOGEN_BOND,
        VIRTUAL_BOND, //Keep second-to-last.
        N_CHEMICAL_BOND_TYPES = VIRTUAL_BOND //Keep last.
    };

} // namespace enums
} // namespace base
} // namespace masala

#endif //Masala_src_base_enums_ChemicalBondTypeEnum_fwd_hh