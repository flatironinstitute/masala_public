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

/// @file src/core_api/base_classes/scoring/PluginScoringTermAdditionalInput.hh
/// @brief Headers for a base class a container for additional
/// input into a scoring term.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_scoring_PluginScoringTermAdditionalInput_hh
#define Masala_src_core_api_base_classes_scoring_PluginScoringTermAdditionalInput_hh

// Forward declarations:
#include <core_api/base_classes/scoring/PluginScoringTermAdditionalInput.fwd.hh>

// Parent class:
#include <core/scoing/ScoringTermAdditionalInput.hh>

// Base headers:


// STL headers:

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {

/// @brief A base class a container for additional input into a scoring term.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginScoringTermAdditionalInput : public masala::core::scoring::ScoringTermAdditionalInput {

public:

	/// @brief Default constructor.
	PluginScoringTermAdditionalInput() = default;

	/// @brief Copy constructor.
	PluginScoringTermAdditionalInput( PluginScoringTermAdditionalInput const & ) = default;

	/// @brief Virtual destructor.
	virtual ~PluginScoringTermAdditionalInput() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class PluginScoringTermAdditionalInput

} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif //Masala_src_core_api_base_classes_scoring_PluginScoringTermAdditionalInput_hh