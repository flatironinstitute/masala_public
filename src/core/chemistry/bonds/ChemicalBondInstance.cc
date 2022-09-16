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

namespace masala {
namespace core {
namespace chemistry {
namespace bonds {

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
ChemicalBondInstanceSP
ChemicalBondInstance::clone() const {
    return std::make_shared< ChemicalBondInstance >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
ChemicalBondInstanceSP
ChemicalBondInstance::deep_clone() const {
    ChemicalBondInstanceSP ChemicalBondInstance_copy( std::make_shared< ChemicalBondInstance >( *this ) );
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
