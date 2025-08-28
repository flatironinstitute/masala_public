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

/// @file src/core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalInput.hh
/// @brief Headers for a base class for a container for additional
/// input into a scoring term that scores a whole molecular system.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTermAdditionalInput_hh
#define Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTermAdditionalInput_hh

// Forward declarations:
#include <core_api/base_classes/scoring/molecular_system/PluginWholeMolecularSystemScoringTermAdditionalInput.fwd.hh>

// Parent class:
#include <core_api/base_classes/scoring/PluginScoringTermAdditionalInput.hh>

// Base headers:

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {
namespace molecular_system {

/// @brief A base class for a container for additional input into a scoring term
/// that scores a whole molecular system.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginWholeMolecularSystemScoringTermAdditionalInput : public masala::core_api::base_classes::scoring::PluginScoringTermAdditionalInput {

public:

	/// @brief Default constructor.
	PluginWholeMolecularSystemScoringTermAdditionalInput() = default;

	/// @brief Copy constructor.
	PluginWholeMolecularSystemScoringTermAdditionalInput( PluginWholeMolecularSystemScoringTermAdditionalInput const & ) = default;

	/// @brief Virtual destructor.
	virtual ~PluginWholeMolecularSystemScoringTermAdditionalInput() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Override to make class pure virtual.
	std::string class_name() const override = 0;

	/// @brief Override to make class pure virtual.
	std::string class_namespace() const override = 0;

    /// @brief Get a list of categories that this object could be sorted into.
    /// @returns { { "ScoringTermAdditionalOutput", "WholeMolecularSystemScoringTermAdditionalInput" } }
    std::vector< std::vector< std::string > >
    get_categories() const override;

    /// @brief Get a list of keywords associated with this object.
    /// @returns { "scoring_term_additional_input", "whole_molecular_system" }
    std::vector< std::string >
    get_keywords() const override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class PluginWholeMolecularSystemScoringTermAdditionalInput

} // namespace molecular_system
} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif //Masala_src_core_api_base_classes_scoring_PluginWholeMolecularSystemScoringTermAdditionalInput_hh