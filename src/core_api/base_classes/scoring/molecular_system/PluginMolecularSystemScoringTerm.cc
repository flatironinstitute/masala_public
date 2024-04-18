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

/// @file src/core_api/base_classes/scoring/molecular_system/PluginMolecularSystemScoringTerm.cc
/// @brief A base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core_api/base_classes/scoring/molecular_system/PluginMolecularSystemScoringTerm.hh>

// Core-API headers:
#include <core_api/auto_generated_api/scoring/ScoringTermAdditionalInput_API.hh>
#include <core_api/auto_generated_api/scoring/ScoringTermAdditionalOutput_API.hh>
#include <core_api/auto_generated_api/scoring/ScoringTermCache_API.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginMolecularSystemScoringTermAdditionalInput.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginMolecularSystemScoringTermAdditionalOutput.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginMolecularSystemScoringTermCache.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/plugin_module/MasalaPluginMolecularSystemModuleManager.hh>
#include <base/managers/plugin_module/MasalaPluginMolecularSystemCreator.hh>

// STL headers:

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {
namespace molecular_system {

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
PluginMolecularSystemScoringTerm::score(
    std::vector< MolecularSystem_APICSP > const & molecular_systems,
    std::vector< ScoringTermAdditionalInput_APICSP > const * const additional_inputs_ptr,
    std::vector< ScoringTermCache_APISP > const * const caches_ptr,
    std::vector< ScoringTermAdditionalOutput_APICSP > * const additional_outputs_ptr
) const {
    CHECK_OR_THROW_FOR_CLASS( molecular_systems.size() >= 1, "score", "At least one molecular system must be "
        "present in the ensemble to score."
    );
    if( additional_inputs_ptr != nullptr ) {
        CHECK_OR_THROW_FOR_CLASS( additional_inputs_ptr->size() == molecular_systems.size(),
            "score", "The number of additional inputs (" + std::to_string( additional_inputs_ptr->size() )
            + " did not match the number of molecular systems being scored (" + std::to_string( molecular_systems.size() )
            + ")."
        );
    }
    if( caches_ptr != nullptr ) {
        CHECK_OR_THROW_FOR_CLASS( caches_ptr->size() == molecular_systems.size(),
            "score", "The number of scoring caches (" + std::to_string( caches_ptr->size() )
            + " did not match the number of molecular systems being scored (" + std::to_string( molecular_systems.size() )
            + ")."
        );
    }
    if( additional_outputs_ptr != nullptr ) {
        additional_outputs_ptr->clear();
    }

    // Convert vectors of API containers to vectors of inner objects:
    std::vector< PluginMolecularSystemScoringTermAdditionalInputCSP > additional_inputs_inner( additional_inputs_ptr == nullptr ? 0 : additional_inputs_ptr->size() );
    if( additional_inputs_ptr != nullptr ) {
        for( masala::base::Size i(0); i<additional_inputs_ptr->size(); ++i ) {
            additional_inputs_inner[i] = std::static_pointer_cast< PluginMolecularSystemScoringTermAdditionalInput const >( (*additional_inputs_ptr)[i]->get_inner_object() );
        }
    }
    std::vector< PluginMolecularSystemScoringTermCacheSP > caches_inner( caches_ptr == nullptr ? 0 : caches_ptr->size() );
    if( caches_ptr != nullptr ) {
        for( masala::base::Size i(0); i<caches_ptr->size(); ++i ) {
            caches_inner[i] = std::static_pointer_cast< PluginMolecularSystemScoringTermCache >( (*caches_ptr)[i]->get_inner_object() );
        }
    }
    std::vector< PluginMolecularSystemScoringTermAdditionalOutputCSP > additional_outputs_inner;

    std::vector< masala::base::Real > const outval(
        score_derived(
            molecular_systems,
            ( additional_inputs_ptr == nullptr ? nullptr : &additional_inputs_inner ),
            ( caches_ptr == nullptr ? nullptr : &caches_inner ),
            ( additional_outputs_ptr == nullptr ? nullptr : &additional_outputs_inner )
        )
    );

	CHECK_OR_THROW_FOR_CLASS( outval.size() == molecular_systems.size(),
		"score", "The output vector of scores had size " + std::to_string( outval.size() )
		+ ", but we had " + std::to_string( molecular_systems.size() ) + " molecular systems."
	);

    // Encapsulate additional outputs in API containers.
    if( additional_outputs_ptr != nullptr ) {
        CHECK_OR_THROW_FOR_CLASS( additional_outputs_inner.empty() || additional_outputs_inner.size() == molecular_systems.size(),
            "score", "Expected additional outputs from scoring to be empty or of equal size to the molecular systems vector ("
            + std::to_string( molecular_systems.size() ) + "), but got a vector of length " + std::to_string( additional_outputs_inner.size() )
            + "."
        );
        if( !additional_outputs_inner.empty() ) {
            additional_outputs_ptr->clear();
            additional_outputs_ptr->resize( additional_outputs_inner.size() );
            
            // Get a handle for the plugin manager:
            masala::base::managers::plugin_module::MasalaPluginMolecularSystemModuleManagerHandle pman(
                masala::base::managers::plugin_module::MasalaPluginMolecularSystemModuleManager::get_instance()
            );

            for( masala::base::Size i(0); i<additional_outputs_inner.size(); ++i ) {
                (*additional_outputs_ptr)[i] = std::static_pointer_cast< ScoringTermAdditionalOutput_API const >(
                    pman->encapsulate_const_plugin_object_instance( additional_outputs_inner[i] )
                );
            }
        }
    }

    return outval;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace molecular_system
} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala
