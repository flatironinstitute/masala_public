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

/// @file src/core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalOutput.cc
/// @brief A base class for a container for additional output from a scoring term that scores a whole molecular system.
/// @details Scoring terms may optionally produce additional output, beyond a single score.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalOutput.hh>

// Base headers:

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
/// @returns { { "ScoringTermAdditionalOutput", "WholeMolecularSystemScoringTermAdditionalOutput" } }
std::vector< std::vector< std::string > >
PluginWholeMolecularSystemScoringTermAdditionalOutput::get_categories() const {
	std::vector< std::vector< std::string > > base_categories( core_api::base_classes::scoring::PluginScoringTermAdditionalOutput::get_categories() );
	for( auto & entry : base_categories ) {
		entry.push_back( "WholeMolecularSystemScoringTermAdditionalOutput" );
	}
	return base_categories;
}

/// @brief Get a list of keywords associated with this object.
/// @returns { "scoring_term_additional_output", "whole_molecular_system" }
std::vector< std::string >
PluginWholeMolecularSystemScoringTermAdditionalOutput::get_keywords() const {
	std::vector< std::string > base_keywords( core_api::base_classes::scoring::PluginScoringTermAdditionalOutput::get_keywords() );
	base_keywords.push_back( "whole_molecular_system" );
	return base_keywords;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace molecular_system
} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala
