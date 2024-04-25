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

/// @file src/core/chemistry/bonds/ChemicalBondInstance.cc
/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/bonds/ChemicalBondInstance.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>
#include <sstream>

namespace masala {
namespace core {
namespace chemistry {
namespace bonds {

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

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Atoms constructor.
ChemicalBondInstance::ChemicalBondInstance(
    masala::core::chemistry::atoms::AtomInstanceCSP const & atom1,
    masala::core::chemistry::atoms::AtomInstanceCSP const & atom2,
    ChemicalBondType const bond_type
) :
    masala::base::MasalaObject(),
    atom1_(atom1),
    atom2_(atom2),
    bond_type_(bond_type)
{
    if( atom1_.get() > atom2_.get() ) {
        std::swap( atom1_, atom2_ );
    }
}

/// @brief Comparison operator.
bool
ChemicalBondInstance::operator==(
    ChemicalBondInstance const & src
) const {
    return (
        src.atom1_.get() == atom1_.get() &&
        src.atom2_.get() == atom2_.get() &&
        src.bond_type_ == bond_type_
    );
}

/// @brief Comparison operator to a pair of atoms: is this a bond between these atoms?
/// @details Returns true if either order matches.
bool
ChemicalBondInstance::operator==(
    std::pair<
        masala::core::chemistry::atoms::AtomInstanceCSP,
        masala::core::chemistry::atoms::AtomInstanceCSP
    > const & src
) const {
    return ( src.first.get() == atom1_.get() && src.second.get() == atom2_.get() ) ||
        ( src.first.get() == atom2_.get() && src.second.get() == atom1_.get() );
}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
ChemicalBondInstanceSP
ChemicalBondInstance::clone() const {
    return masala::make_shared< ChemicalBondInstance >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
ChemicalBondInstanceSP
ChemicalBondInstance::deep_clone() const {
    ChemicalBondInstanceSP ChemicalBondInstance_copy( masala::make_shared< ChemicalBondInstance >( *this ) );
    ChemicalBondInstance_copy->make_independent();
    return ChemicalBondInstance_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Be sure to update this function whenever a private member is added!
void
ChemicalBondInstance::make_independent() {
    // Currently GNDN.
}

/// @brief Returns "ChemicalBondInstance".
std::string
ChemicalBondInstance::class_name() const {
    return "ChemicalBondInstance";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::bonds".
std::string
ChemicalBondInstance::class_namespace() const {
    return "masala::core::chemistry::bonds";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the bond type.
void
ChemicalBondInstance::set_bond_type(
    ChemicalBondType const bond_type_in
) {
    CHECK_OR_THROW(
        bond_type_in != ChemicalBondType::INVALID_CHEMICAL_BOND_TYPE,
        class_namespace_and_name(),
        "set_bond_type",
        "An invalid chemical bond type was specified."
    );
    bond_type_ = bond_type_in;
}

/// @brief Get the bond type.
ChemicalBondType
ChemicalBondInstance::bond_type() const {
    return bond_type_;
}

} // namespace bonds
} // namespace chemistry
} // namespace core
} // namespace masala
