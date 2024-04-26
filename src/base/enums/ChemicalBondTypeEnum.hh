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
/// @brief Headers for utility functions for the enum for chemical bond type.
/// @details Needs to be declared in masala::base to be accessible to API definitions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_enums_ChemicalBondTypeEnum_hh
#define Masala_src_base_enums_ChemicalBondTypeEnum_hh

#include <base/enums/ChemicalBondTypeEnum.fwd.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace enums {

/// @brief Utility function to get a bond type from a string.
/// @details Returns INVALID_CHEMICAL_BOND_TYPE if string can't be parsed.
ChemicalBondType
bond_type_from_string(
	std::string const & bond_type_string
);

/// @brief Utility function to get a bond type string from a bbond type.
std::string
string_from_bond_type(
	ChemicalBondType const bond_type
);

/// @brief Provide a string listing all allowed bond types.
std::string
list_bond_types(
	std::string const & delimiter,
	bool const include_and
);

} // namespace enums
} // namespace base
} // namespace masala

#endif //Masala_src_base_enums_ChemicalBondTypeEnum_hh