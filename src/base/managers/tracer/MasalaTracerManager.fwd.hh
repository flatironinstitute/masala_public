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

/// @file src/base/managers/tracer/MasalaTracerManager.fwd.hh
/// @brief Forward declarations for a static singleton for managing output to the tracer (screen
/// and/or logfile(s)).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_tracer_MasalaTracerManager_fwd_hh
#define Masala_src_base_managers_tracer_MasalaTracerManager_fwd_hh

namespace masala {
namespace base {
namespace managers {
namespace tracer {

    class MasalaTracerManager;

    /// Note that singletons define no shared pointers or weak pointers.  Nonconst to allow
    /// lazy loading of data.
    using MasalaTracerManagerHandle = MasalaTracerManager *;

} // namespace tracer
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_tracer_MasalaTracerManager_fwd_hh