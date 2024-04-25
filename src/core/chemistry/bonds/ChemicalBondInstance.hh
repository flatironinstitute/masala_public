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

/// @file src/core/chemistry/bonds/ChemicalBondInstance.hh
/// @brief A class containing a particular chemical bond between a pair of atoms.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_bonds_ChemicalBondInstance_hh
#define Masala_src_core_chemistry_bonds_ChemicalBondInstance_hh

// Forward declarations:
#include <core/chemistry/bonds/ChemicalBondInstance.fwd.hh>

// Core headers:
#include <base/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace bonds {


/// @brief A class containing a particular chemical bond between a pair of atoms.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ChemicalBondInstance : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    ChemicalBondInstance() = default;

    /// @brief Atoms constructor.
    ChemicalBondInstance(
        masala::core::chemistry::atoms::AtomInstanceCSP const & atom1,
        masala::core::chemistry::atoms::AtomInstanceCSP const & atom2,
        ChemicalBondType const bond_type
    );

    /// @brief Copy constructor.
    ChemicalBondInstance( ChemicalBondInstance const & ) = default;

    /// @brief Default destructor.
    ~ChemicalBondInstance() override = default;

    /// @brief Assignment operator.
    ChemicalBondInstance & operator=( ChemicalBondInstance const & ) = default;

    /// @brief Comparison operator.
    bool operator==( ChemicalBondInstance const & src ) const;

    /// @brief Comparison operator to a pair of atoms: is this a bond between these atoms?
    /// @details Returns true if either order matches.
    bool operator==( std::pair< masala::core::chemistry::atoms::AtomInstanceCSP, masala::core::chemistry::atoms::AtomInstanceCSP > const & src ) const;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    ChemicalBondInstanceSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual
    ChemicalBondInstanceSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "ChemicalBondInstance".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::bonds".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Set the bond type.
    void set_bond_type( ChemicalBondType const bond_type_in );

    /// @brief Get the bond type.
    ChemicalBondType bond_type() const;


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The first atom (ordered by memory index).
    masala::core::chemistry::atoms::AtomInstanceCSP atom1_;

    /// @brief The second atom (ordered by memory index).
    masala::core::chemistry::atoms::AtomInstanceCSP atom2_;

    /// @brief The type of bond this is.
    ChemicalBondType bond_type_ = ChemicalBondType::SINGLE_BOND;

};

} // namespace bonds
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_bonds_ChemicalBondInstance_hh