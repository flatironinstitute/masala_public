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

/// @file src/base/managers/engine/MasalaEngine.cc
/// @brief A base class for Masala engines, which perform hard calculations of a given type using
/// a given method.
/// @details Subclasses will be defined for kinematic calculations, packing calculations, minimization
/// calculations, etc.  Each of these in turn will have subclasses for performing these using different
/// math libraries, optimizers, hardware, etc.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <base/managers/engine/MasalaEngine.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief Is a particular data representation INcompatible with this engine?  Returns true to signal
/// incompatibility, false otherwise.
/// @details Default implementation always returns false.  May be overridden to allow engines to perform
/// runtime checks to assess whether a particular data representation will definitely NOT work with this
/// engine.
/// @note If this function returns false, it is not a guarantee that a data representation will work with
/// this engine, or work efficiently with this engine.
/*virtual*/
bool
MasalaEngine::data_representation_is_incompatible_with_engine(
    MasalaDataRepresentation const & //representation
) const {
    return false;
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
