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

/// @file src/base/managers/engine/engine_request/MasalaEngineOrCriterion.cc
/// @brief Implementations for a class for imposing that at least one of two or more conditions be true when selecting engines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/engine_request/MasalaEngineOrCriterion.hh>

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
/// @returns "MasalaEngineOrCriterion".
std::string
MasalaEngineOrCriterion::class_name() const {
    return class_name_static();
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
std::string
MasalaEngineOrCriterion::class_namespace() const {
    return class_namespace_static();
}

/// @brief Get the name of this class.
/// @returns "MasalaEngineOrCriterion".
/*static*/
std::string
MasalaEngineOrCriterion::class_name_static() {
    return "MasalaEngineOrCriterion";
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
/*static*/
std::string
MasalaEngineOrCriterion::class_namespace_static() {
    return "masala::base::managers::engine::engine_request";
}

/// @brief Determine whether a particular engine is compatible with this criterion.
/// @returns True if it is compatible, false otherwise.
bool
MasalaEngineOrCriterion::engine_is_compatible_with_criterion(
    masala::base::managers::engine::MasalaEngineCreator const & creator
) const {
    CHECK_OR_THROW_FOR_CLASS( !or_criteria_.empty(), "data_representation_is_compatible_with_criterion", "At least one criterion must be passed to this class for AND logic to work." );
	for( auto const & criterion : or_criteria_ ) {
		if( (criterion->engine_is_compatible_with_criterion( creator )) ) {
			return true;
		}
	}
    return false;
}

/// @brief Add a MasalaEngineRequestCriterion to the set of criteria, at least one of which
/// must be true for this criterion to pass.
/// @details The input criterion is used directly, not cloned.
void
MasalaEngineOrCriterion::add_criterion(
	MasalaEngineRequestCriterionCSP const & criterion_in
) {
    CHECK_OR_THROW_FOR_CLASS( criterion_in != nullptr, "add_criterion", "A null pointer was passed to this function." );
	or_criteria_.push_back( criterion_in );
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
