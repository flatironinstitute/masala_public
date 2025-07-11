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

/// @file src/base/managers/mpi/MasalaMPIManager.fwd.hh
/// @brief Forward declarations for a static singleton for managing Masala behaviour in an MPI context.
/// @details This will ultimately handle two cases:
/// - External code is using MPI, and is calling Masala.
/// - Masala has launched MPI processes, and is handling MPI calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_mpi_MasalaMPIManager_fwd_hh
#define Masala_src_base_managers_mpi_MasalaMPIManager_fwd_hh

namespace masala {
namespace base {
namespace managers {
namespace mpi {

	class MasalaMPIManagerAccessKey;
	class MasalaMPIManager;

	/// Note that singletons define no shared pointers or weak pointers.  Nonconst to allow
	/// lazy loading of data.
	using MasalaMPIManagerHandle = MasalaMPIManager *;

} // namespace mpi
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_mpi_MasalaMPIManager_fwd_hh