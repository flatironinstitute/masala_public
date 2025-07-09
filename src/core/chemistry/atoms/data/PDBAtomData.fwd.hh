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

/// @file src/core/chemistry/atoms/data/PDBAtomData.fwd.hh
/// @brief Forward declarations for a container class for data attached
/// to an atom that was read from a PDB file.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_data_PDBAtomData_fwd_hh
#define Masala_src_core_chemistry_atoms_data_PDBAtomData_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace data {

    class PDBAtomData;

    using PDBAtomDataSP = MASALA_SHARED_POINTER< PDBAtomData >;
    using PDBAtomDataCSP = MASALA_SHARED_POINTER< PDBAtomData const >;
    using PDBAtomDataWP = MASALA_WEAK_POINTER< PDBAtomData >;
    using PDBAtomDataCWP = MASALA_WEAK_POINTER< PDBAtomData const >;

} // data
} // atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_data_PDBAtomData_fwd_hh