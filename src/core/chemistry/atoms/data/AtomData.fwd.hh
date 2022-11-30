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

/// @file src/core/chemistry/atoms/data/AtomData.fwd.hh
/// @brief Forward declarations for a container data for additional optional
/// data that might be attached to an atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_data_AtomData_fwd_hh
#define Masala_src_core_chemistry_atoms_data_AtomData_fwd_hh

#include <memory>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace data {

    class AtomData;

    using AtomDataSP = std::shared_ptr< AtomData >;
    using AtomDataCSP = std::shared_ptr< AtomData const >;
    using AtomDataWP = std::weak_ptr< AtomData >;
    using AtomDataCWP = std::weak_ptr< AtomData const >;

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_data_AtomData_fwd_hh