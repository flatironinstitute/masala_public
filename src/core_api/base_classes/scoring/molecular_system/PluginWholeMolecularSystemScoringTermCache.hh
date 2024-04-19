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

/// @file src/core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermCache.hh
/// @brief Headers for a base class for a container anything that a scoring term that
/// scores a whole molecular system. may need to cache to facilitate repeated similar
/// calculations.
/// @details Scoring terms may optionally read from AND write to this, during scoring.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTermCache_hh
#define Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTermCache_hh

// Forward declarations:
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermCache.fwd.hh>

// Parent class:
#include <core_api/base_classes/scoring/PluginScoringTermCache.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {
namespace molecular_system {

/// @brief A base class for a container anything that a scoring term that scores a
/// whole molecular system may need to cache to facilitate repeated similar calculations.
/// @details Scoring terms may optionally read from AND write to this, during scoring.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginWholeMolecularSystemScoringTermCache : public masala::core_api::base_classes::scoring::PluginScoringTermCache {

public:

	/// @brief Default constructor.
	PluginWholeMolecularSystemScoringTermCache() = default;

	/// @brief Copy constructor.
	PluginWholeMolecularSystemScoringTermCache( PluginWholeMolecularSystemScoringTermCache const & ) = default;

	/// @brief Virtual destructor.
	virtual ~PluginWholeMolecularSystemScoringTermCache() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Override to make class pure virtual.
	std::string class_name() const override = 0;

	/// @brief Override to make class pure virtual.
	std::string class_namespace() const override = 0;

    /// @brief Get a list of categories that this object could be sorted into.
    /// @returns { { "ScoringTermCache", "WholeMolecularSystemScoringTermCache" } }
    std::vector< std::vector< std::string > >
    get_categories() const override;

    /// @brief Get a list of keywords associated with this object.
    /// @returns { "scoring_term_additional_cache", "whole_molecular_system" }
    std::vector< std::string >
    get_keywords() const override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class PluginWholeMolecularSystemScoringTermCache

} // namespace molecular_system
} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif //Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTermCache_hh