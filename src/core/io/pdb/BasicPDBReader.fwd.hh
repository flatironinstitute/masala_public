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

/// @file src/core/chemistry/BasicPDBReader.fwd.hh
/// @brief Forward declarations for a class for reading the basic information
/// from a PDB file quickly, and setting up a minimal molecular system.
/// @note This is intended for testing only.  The proper PDB reader will be in the
/// standard Masala plugins library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_io_pdb_BasicPDBReader_fwd_hh
#define Masala_src_core_io_pdb_BasicPDBReader_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace core {
namespace io {
namespace pdb {

    class BasicPDBReader;

    using BasicPDBReaderSP = MASALA_SHARED_POINTER< BasicPDBReader >;
    using BasicPDBReaderCSP = MASALA_SHARED_POINTER< BasicPDBReader const >;
    using BasicPDBReaderWP = MASALA_WEAK_POINTER< BasicPDBReader >;
    using BasicPDBReaderCWP = MASALA_WEAK_POINTER< BasicPDBReader const >;

} // namespace pdb
} // namespace io
} // namespace core
} // namespace masala

#endif // Masala_src_core_io_pdb_BasicPDBReader_fwd_hh