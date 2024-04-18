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

/// @file src/core_api/base_classes/scoring/ScoringTerm.hh
/// @brief Headers for a base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_scoring_ScoringTerm_hh
#define Masala_src_core_api_base_classes_scoring_ScoringTerm_hh

// Forward declarations:
#include <core_api/base_classes/scoring/ScoringTerm.fwd.hh>

// Core API headers:
#include <core_api/auto_generated_api/molecular_system/MolecularSystem_API.fwd.hh>
#include <core_api/base_classes/scoring/ScoringTermAdditionalInput.fwd.hh>
#include <core_api/base_classes/scoring/ScoringTermAdditionalOutput.fwd.hh>
#include <core_api/base_classes/scoring/ScoringTermCache.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/types.hh>

// STL headers:
#include <vector>

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {

/// @brief A base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ScoringTerm {

	typedef masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API MolecularSystem_API;
	typedef masala::core_api::auto_generated_api::molecular_system::MolecularSystem_APISP MolecularSystem_APISP;
	typedef masala::core_api::auto_generated_api::molecular_system::MolecularSystem_APICSP MolecularSystem_APICSP;

public:

	/// @brief Default constructor.
	ScoringTerm() = default;

	/// @brief Copy constructor.
	ScoringTerm( ScoringTerm const & ) = default;

	/// @brief Virtual destructor.
	virtual ~ScoringTerm() = default;

public:

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
	score(
		std::vector< MolecularSystem_APICSP > const & molecular_systems,
		std::vector< ScoringTermAdditionalInputCSP > const * const additional_inputs_ptr,
		std::vector< ScoringTermCacheSP > const * const caches_ptr,
		std::vector< ScoringTermAdditionalOutputCSP > const * additional_outputs_ptr
	) const;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class ScoringTerm

} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif //Masala_src_core_api_base_classes_scoring_ScoringTerm_hh