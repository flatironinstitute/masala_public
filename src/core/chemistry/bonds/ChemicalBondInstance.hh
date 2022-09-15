/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/core/chemistry/bonds/ChemicalBondInstance.hh
/// @brief A class containing a particular chemical bond between a pair of atoms.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_bonds_ChemicalBondInstance_hh
#define Masala_src_core_chemistry_bonds_ChemicalBondInstance_hh

// Forward declarations:
#include <core/chemistry/bonds/ChemicalBondInstance.fwd.hh>

// Core headers:
#include <core/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

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

    /// @brief Copy constructor.
    ChemicalBondInstance( ChemicalBondInstance const & ) = default;

    /// @brief Default destructor.
    ~ChemicalBondInstance() override = default;

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

    /// @brief Every class can provide its own namespace.  This returns "core::chemistry::bonds".
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

    /// @brief The type of bond this is.
    ChemicalBondType bond_type_ = ChemicalBondType::SINGLE_BOND;

};

} // namespace bonds
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_bonds_ChemicalBondInstance_hh