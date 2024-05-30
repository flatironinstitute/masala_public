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

/// @file src/core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTerm.cc
/// @brief A base class for all Masala scoring terms that score a whole structure.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTerm.hh>

// Core-API headers:
#include <core_api/auto_generated_api/scoring/ScoringTermAdditionalInput_API.hh>
#include <core_api/auto_generated_api/scoring/ScoringTermAdditionalOutput_API.hh>
#include <core_api/auto_generated_api/scoring/ScoringTermCache_API.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalInput.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalOutput.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermCache.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {
namespace molecular_system {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a list of categories that this object could be sorted into.
/// @returns { { "ScoringTerm", "WholeMolecularSystemScoringTerm" } }
std::vector< std::vector< std::string > >
PluginWholeMolecularSystemScoringTerm::get_categories() const {
	std::vector< std::vector< std::string > > base_categories( core_api::base_classes::scoring::PluginScoringTerm::get_categories() );
	for( auto & entry : base_categories ) {
		entry.push_back( "WholeMolecularSystemScoringTerm" );
	}
	return base_categories;
}

/// @brief Get a list of keywords associated with this object.
/// @returns { "scoring_term", "whole_molecular_system" }
std::vector< std::string >
PluginWholeMolecularSystemScoringTerm::get_keywords() const {
	std::vector< std::string > base_keywords( core_api::base_classes::scoring::PluginScoringTerm::get_keywords() );
	base_keywords.push_back( "whole_molecular_system" );
	return base_keywords;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
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
/// outputs.  Can be nullptr.  If non-null, this vector will empty (length zero).  The derived
/// class is responsible for ensuring that the vector is either kept at length zero
/// or populated with one output per molecular system.
std::vector< masala::base::Real >
PluginWholeMolecularSystemScoringTerm::score_derived(
    std::vector< MolecularSystem_APICSP > const & molecular_systems,
    std::vector< PluginScoringTermAdditionalInputCSP > const * const additional_inputs_ptr,
    std::vector< PluginScoringTermCacheSP > const * const caches_ptr,
    std::vector< PluginScoringTermAdditionalOutputCSP > * const additional_outputs_ptr
) const {
    using masala::base::Size;

    std::vector< PluginWholeMolecularSystemScoringTermAdditionalInputCSP > additional_inputs_cast(
        additional_inputs_ptr == nullptr ?
        0 :
        additional_inputs_ptr->size()
    );
    if( additional_inputs_ptr != nullptr ) {
        for( Size i(0); i<additional_inputs_ptr->size(); ++i ) {
            additional_inputs_cast[i] = std::static_pointer_cast< PluginWholeMolecularSystemScoringTermAdditionalInput const >( (*additional_inputs_ptr)[i] );
        }
    }

    std::vector< PluginWholeMolecularSystemScoringTermCacheSP > caches_cast(
        caches_ptr == nullptr ?
        0 :
        caches_ptr->size()
    );
    if( caches_ptr != nullptr ) {
        for( Size i(0); i<caches_ptr->size(); ++i ) {
            caches_cast[i] = std::static_pointer_cast< PluginWholeMolecularSystemScoringTermCache >( (*caches_ptr)[i] );
        }
    }

    std::vector< PluginWholeMolecularSystemScoringTermAdditionalOutputCSP > additional_outputs;

    std::vector< masala::base::Real > const outval(
        score_molecular_systems_derived(
            molecular_systems,
            ( additional_inputs_ptr == nullptr ) ? nullptr : &additional_inputs_cast,
            ( caches_ptr == nullptr ) ? nullptr : &caches_cast,
            ( additional_outputs_ptr == nullptr ) ? nullptr : &additional_outputs
        )
    );

    if( additional_outputs_ptr != nullptr && !additional_outputs.empty() ) {
        additional_outputs_ptr->clear();
        additional_outputs_ptr->resize( additional_outputs.size() );
        for( Size i(0); i<additional_outputs.size(); ++i ) {
            (*additional_outputs_ptr)[i] = additional_outputs[i];
        }
    }

    return outval;
}

} // namespace molecular_system
} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala
