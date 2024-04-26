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

/// @file src/core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTerm.hh
/// @brief Headers for a base class for all Masala scoring terms that score a whole structure.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTerm_hh
#define Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTerm_hh

// Forward declarations:
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTerm.fwd.hh>

// Parent class:
#include <core_api/base_classes/scoring/PluginScoringTerm.hh>

// Core API headers:
#include <core_api/auto_generated_api/molecular_system/MolecularSystem_API.fwd.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalInput.fwd.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalOutput.fwd.hh>
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermCache.fwd.hh>
#include <core_api/auto_generated_api/scoring/ScoringTermAdditionalInput_API.fwd.hh>
#include <core_api/auto_generated_api/scoring/ScoringTermAdditionalOutput_API.fwd.hh>
#include <core_api/auto_generated_api/scoring/ScoringTermCache_API.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <vector>

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {
namespace molecular_system {

/// @brief A base class for all Masala scoring terms that score a whole structure.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginWholeMolecularSystemScoringTerm : public masala::core_api::base_classes::scoring::PluginScoringTerm {

	typedef masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API MolecularSystem_API;
	typedef masala::core_api::auto_generated_api::molecular_system::MolecularSystem_APISP MolecularSystem_APISP;
	typedef masala::core_api::auto_generated_api::molecular_system::MolecularSystem_APICSP MolecularSystem_APICSP;

	typedef masala::core_api::auto_generated_api::scoring::ScoringTermAdditionalInput_API ScoringTermAdditionalInput_API;
	typedef masala::core_api::auto_generated_api::scoring::ScoringTermAdditionalInput_APISP ScoringTermAdditionalInput_APISP;
	typedef masala::core_api::auto_generated_api::scoring::ScoringTermAdditionalInput_APICSP ScoringTermAdditionalInput_APICSP;

	typedef masala::core_api::auto_generated_api::scoring::ScoringTermAdditionalOutput_API ScoringTermAdditionalOutput_API;
	typedef masala::core_api::auto_generated_api::scoring::ScoringTermAdditionalOutput_APISP ScoringTermAdditionalOutput_APISP;
	typedef masala::core_api::auto_generated_api::scoring::ScoringTermAdditionalOutput_APICSP ScoringTermAdditionalOutput_APICSP;

	typedef masala::core_api::auto_generated_api::scoring::ScoringTermCache_API ScoringTermCache_API;
	typedef masala::core_api::auto_generated_api::scoring::ScoringTermCache_APISP ScoringTermCache_APISP;
	typedef masala::core_api::auto_generated_api::scoring::ScoringTermCache_APICSP ScoringTermCache_APICSP;

public:

	/// @brief Default constructor.
	PluginWholeMolecularSystemScoringTerm() = default;

	/// @brief Copy constructor.
	PluginWholeMolecularSystemScoringTerm( PluginWholeMolecularSystemScoringTerm const & ) = default;

	/// @brief Virtual destructor.
	virtual ~PluginWholeMolecularSystemScoringTerm() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Override to make class pure virtual.
	std::string class_name() const override = 0;

	/// @brief Override to make class pure virtual.
	std::string class_namespace() const override = 0;

    /// @brief Get a list of categories that this object could be sorted into.
    /// @returns { { "ScoringTerm", "WholeMolecularSystemScoringTerm" } }
    std::vector< std::vector< std::string > >
    get_categories() const override;

    /// @brief Get a list of keywords associated with this object.
    /// @returns { "scoring_term", "whole_molecular_system" }
    std::vector< std::string >
    get_keywords() const override;

protected:

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
	score_derived(
		std::vector< MolecularSystem_APICSP > const & molecular_systems,
		std::vector< PluginScoringTermAdditionalInputCSP > const * const additional_inputs_ptr,
		std::vector< PluginScoringTermCacheSP > const * const caches_ptr,
		std::vector< PluginScoringTermAdditionalOutputCSP > * const additional_outputs_ptr
	) const override;

	/// @brief Score a vector of structures (molecular systems), and produce a
	/// corresponding vector of scores.  This function must be implemented by derived
	/// classes.
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
	virtual
	std::vector< masala::base::Real >
	score_molecular_systems_derived(
		std::vector< MolecularSystem_APICSP > const & molecular_systems,
		std::vector< PluginWholeMolecularSystemScoringTermAdditionalInputCSP > const * const additional_inputs_ptr,
		std::vector< PluginWholeMolecularSystemScoringTermCacheSP > const * const caches_ptr,
		std::vector< PluginWholeMolecularSystemScoringTermAdditionalOutputCSP > * const additional_outputs_ptr
	) const = 0;

}; // class PluginWholeMolecularSystemScoringTerm

} // namespace molecular_system
} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif //Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTerm_hh