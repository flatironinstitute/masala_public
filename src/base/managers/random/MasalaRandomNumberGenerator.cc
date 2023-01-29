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

/// @file src/base/managers/engine/MasalaRandomNumberGenerator.cc
/// @brief Implementations for a static singleton for generating random numbers, with unique random seeds
/// for each process and thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/random/MasalaRandomNumberGenerator.hh>

// Base headers:
#include <base/managers/engine/MasalaEngineCreatorBase.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace managers {
namespace random {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaRandomNumberGeneratorHandle
MasalaRandomNumberGenerator::get_instance() {
    static thread_local MasalaRandomNumberGenerator random_generator;
    return &random_generator;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaRandomNumberGenerator".
std::string
MasalaRandomNumberGenerator::class_name() const {
    return "MasalaRandomNumberGenerator";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::random".
std::string
MasalaRandomNumberGenerator::class_namespace() const {
    return "masala::base::managers::random";
}

} // namespace random
} // namespace managers
} // namespace base
} // namespace masala
