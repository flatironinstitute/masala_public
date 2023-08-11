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

/// @file src/base/managers/engine/MasalaDataRepresentation.fwd.hh
/// @brief Forward declarations for a pure virtual base class class for particular representations
/// of data that can be requested by engines for efficient manipulation of those data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentation_fwd_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentation_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

    class MasalaDataRepresentation;

    using MasalaDataRepresentationSP = MASALA_SHARED_POINTER< MasalaDataRepresentation >;
    using MasalaDataRepresentationCSP = MASALA_SHARED_POINTER< MasalaDataRepresentation const >;
    using MasalaDataRepresentationWP = MASALA_WEAK_POINTER< MasalaDataRepresentation >;
    using MasalaDataRepresentationCWP = MASALA_WEAK_POINTER< MasalaDataRepresentation const >;


} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentation_fwd_hh