/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/base/managers/engine/engine_request/MasalaEngineNotCriterion.cc
/// @brief Implementations for a class for imposing a condition be false when selecting engines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/engine_request/MasalaEngineNotCriterion.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>
#include <base/managers/engine/MasalaEngineCreator.hh>
// #include <base/managers/tracer/MasalaTracerManager.hh> // DELETE ME

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this class.
/// @returns "MasalaEngineNotCriterion".
std::string
MasalaEngineNotCriterion::class_name() const {
    return class_name_static();
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
std::string
MasalaEngineNotCriterion::class_namespace() const {
    return class_namespace_static();
}

/// @brief Get the name of this class.
/// @returns "MasalaEngineNotCriterion".
/*static*/
std::string
MasalaEngineNotCriterion::class_name_static() {
    return "MasalaEngineNotCriterion";
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
/*static*/
std::string
MasalaEngineNotCriterion::class_namespace_static() {
    return "masala::base::managers::engine::engine_request";
}

/// @brief Determine whether a particular engine is compatible with this criterion.
/// @returns True if it is compatible, false otherwise.
bool
MasalaEngineNotCriterion::engine_is_compatible_with_criterion(
    masala::base::managers::engine::MasalaEngineCreator const & creator
) const {
	CHECK_OR_THROW_FOR_CLASS( not_criterion_ != nullptr, "engine_is_compatible_with_criterion",
		"A criterion must be set in order for the MasalaEngineNotCriterion to negate it."
	);
	return !( not_criterion_->engine_is_compatible_with_criterion(creator) );
}

/// @brief Set a MasalaEngineRequestCriterion that must be false in order for this criterion
/// to evaluate to true.
/// @details The input criterion is used directly, not cloned.  Overwrites anything previously set.
void
MasalaEngineNotCriterion::set_criterion(
    MasalaEngineRequestCriterionCSP const & criterion_in
) {
	not_criterion_ = criterion_in;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
