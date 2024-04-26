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

/// @file src/base/enums/ChemicalBondTypeEnum.cc
/// @brief Implementations for utility functions for the enum for chemical bond type.
/// @details Needs to be declared in masala::base to be accessible to API definitions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#include <base/enums/ChemicalBondTypeEnum.hh>

// Base headers:
#include <base/types.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace base {
namespace enums {

/// @brief Utility function to get a bond type from a string.
/// @details Returns INVALID_CHEMICAL_BOND_TYPE if string can't be parsed.
ChemicalBondType
bond_type_from_string(
	std::string const & bond_type_string
) {
	using masala::base::Size;
	for( Size i(1); i<=static_cast<Size>( ChemicalBondType::N_CHEMICAL_BOND_TYPES ); ++i ) {
		if( bond_type_string == string_from_bond_type( static_cast<ChemicalBondType>(i) ) ) {
			return static_cast<ChemicalBondType>(i);
		}
	}
	return ChemicalBondType::INVALID_CHEMICAL_BOND_TYPE;
}

/// @brief Utility function to get a bond type string from a bbond type.
std::string
string_from_bond_type(
	ChemicalBondType const bond_type
) {
	switch( bond_type ) {
		case ChemicalBondType::SINGLE_BOND :
			return "single_bond";
		case ChemicalBondType::DOUBLE_BOND :
			return "double_bond";
		case ChemicalBondType::TRIPLE_BOND :
			return "triple_bond";
		case ChemicalBondType::PARTIAL_DOUBLE_BOND :
			return "partial_double_bond";
		case ChemicalBondType::COORDINATE_COVALENT_BOND :
			return "coordinate_covalent_bond";
		case ChemicalBondType::HYDROGEN_BOND :
			return "hydrogen_bond";
		case ChemicalBondType::CATION_PI_BOND :
			return "cation_pi_bond";
		case ChemicalBondType::PI_PI_BOND :
			return "pi_pi_bond";
		case ChemicalBondType::HALOGEN_BOND :
			return "halogen_bond";
		case ChemicalBondType::VIRTUAL_BOND :
			return "virtual_bond";
		default:
			MASALA_THROW( "masala::core::chemistry::bonds", "string_from_bond_type",
				"Invalid bond type provided to this function."
			);
	}

	return "";
}

/// @brief Provide a string listing all allowed bond types.
std::string
list_bond_types(
	std::string const & delimiter,
	bool const include_and
) {
	using masala::base::Size;
	std::ostringstream ss;
	for( Size i(1); i<=static_cast<Size>( ChemicalBondType::N_CHEMICAL_BOND_TYPES ); ++i ) {
		if( i > 1 ) {
			ss << delimiter;
		}
		if( include_and && i == static_cast<Size>( ChemicalBondType::N_CHEMICAL_BOND_TYPES ) )  {
			ss << "and ";
		}
		ss << string_from_bond_type( static_cast<ChemicalBondType>(i) );
	}
	return ss.str();
}

} // namespace enums
} // namespace base
} // namespace masala
