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

/// @file src/base/managers/engine/MasalaDataRepresentationCreator.fwd.hh
/// @brief Forward declarations for a pure virtual base class for creators for
/// data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationCreator_fwd_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationCreator_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

    class MasalaDataRepresentationCreator;

    using MasalaDataRepresentationCreatorSP = MASALA_SHARED_POINTER< MasalaDataRepresentationCreator >;
    using MasalaDataRepresentationCreatorCSP = MASALA_SHARED_POINTER< MasalaDataRepresentationCreator const >;
    using MasalaDataRepresentationCreatorWP = MASALA_WEAK_POINTER< MasalaDataRepresentationCreator >;
    using MasalaDataRepresentationCreatorCWP = MASALA_WEAK_POINTER< MasalaDataRepresentationCreator const >;


} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationCreator_fwd_hh