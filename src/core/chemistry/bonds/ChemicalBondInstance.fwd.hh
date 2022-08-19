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

/// @file src/core/chemistry/bonds/ChemicalBondInstance.fwd.hh
/// @brief Forward declarations for a class containing a particular
/// chemical bond between a pair of atoms.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_bonds_ChemicalBondInstance_fwd_hh
#define Masala_src_core_chemistry_bonds_ChemicalBondInstance_fwd_hh

#include <memory>

namespace core {
namespace chemistry {
namespace bonds {

    class ChemicalBondInstance;

    using ChemicalBondInstanceSP = std::shared_ptr< ChemicalBondInstance >;
    using ChemicalBondInstanceCSP = std::shared_ptr< ChemicalBondInstance const >;
    using ChemicalBondInstanceWP = std::weak_ptr< ChemicalBondInstance >;
    using ChemicalBondInstanceCWP = std::weak_ptr< ChemicalBondInstance const >;

    /// @brief An enum for the type of bond.
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
        N_HYBRIDIZATION_STATES = VIRTUAL_BOND //Keep last.
    };

} // namespace bonds
} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_bonds_ChemicalBondInstance_fwd_hh