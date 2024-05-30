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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreterCreator.fwd.hh
/// @brief Forward declarations for a pure virtual base class for creators for
/// file interpreters.
/// @details Creators must be registered with the MasalaFileInterpreterManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_file_interpreter_MasalaFileInterpreterCreator_fwd_hh
#define Masala_src_base_managers_file_interpreter_MasalaFileInterpreterCreator_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

    class MasalaFileInterpreterCreator;

    using MasalaFileInterpreterCreatorSP = MASALA_SHARED_POINTER< MasalaFileInterpreterCreator >;
    using MasalaFileInterpreterCreatorCSP = MASALA_SHARED_POINTER< MasalaFileInterpreterCreator const >;
    using MasalaFileInterpreterCreatorWP = MASALA_WEAK_POINTER< MasalaFileInterpreterCreator >;
    using MasalaFileInterpreterCreatorCWP = MASALA_WEAK_POINTER< MasalaFileInterpreterCreator const >;


} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_file_interpreter_MasalaFileInterpreterCreator_fwd_hh