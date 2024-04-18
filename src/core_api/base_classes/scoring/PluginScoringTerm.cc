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

/// @file src/core_api/base_classes/scoring/PluginScoringTerm.cc
/// @brief A base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core_api/base_classes/scoring/PluginScoringTerm.hh>

// Base headers:

// STL headers:

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Score a vector of structures (molecular systems), and produce a
/// corresponding vector of scores.
/// @param[in] molecular_systems A vector of at least one molecular system to score.
/// @param[in] additional_inputs_ptr A pointer to a vector of (optional) additional
/// inputs.  Can be nullptr.  If non-null, the vector must contain one entry for each
/// molecular system.
/// @param[in] caches_ptr A pointer to a vector of (optional) cache containers to permit
/// data that persists from scoring attempt to scoring attempt to be stored.  Can be
/// nullptr.  If non-null, the vector must contain one entry for each molecular system.
/// @param[in] additional_inputs_ptr A pointer to a vector of (optional) additional
/// outputs.  Can be nullptr.  If non-null, this vector will be cleared and populated
/// with one output per molecular system.
std::vector< masala::base::Real >
PluginScoringTerm::score(
	std::vector< MolecularSystem_APICSP > const & molecular_systems,
	std::vector< ScoringTermAdditionalInput_APICSP > const * const additional_inputs_ptr,
	std::vector< ScoringTermCache_APISP > const * const caches_ptr,
	std::vector< ScoringTermAdditionalOutput_APICSP > const * additional_outputs_ptr
) const {
	TODO TODO TODO;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala
