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

/// @file src/core_api/base_classes/scoring/PluginScoringTermAdditionalOutput.hh
/// @brief Headers for a base class for a container for additional
/// output from a scoring term.
/// @details Scoring terms may optionally produce additional output, beyond
/// a single score.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_scoring_PluginScoringTermAdditionalOutput_hh
#define Masala_src_core_api_base_classes_scoring_PluginScoringTermAdditionalOutput_hh

// Forward declarations:
#include <core_api/base_classes/scoring/PluginScoringTermAdditionalOutput.fwd.hh>

// Parent class:
#include <core/scoring/ScoringTermAdditionalOutput.hh>

// Base headers:


// STL headers:

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {

/// @brief A base class for a container for additional output from a scoring term.
/// @details Scoring terms may optionally produce additional output, beyond
/// a single score.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginScoringTermAdditionalOutput : public masala::core::scoring::ScoringTermAdditionalOutput {

public:

	/// @brief Default constructor.
	PluginScoringTermAdditionalOutput() = default;

	/// @brief Copy constructor.
	PluginScoringTermAdditionalOutput( PluginScoringTermAdditionalOutput const & ) = default;

	/// @brief Virtual destructor.
	virtual ~PluginScoringTermAdditionalOutput() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Override to make class pure virtual.
	std::string class_name() const override = 0;

	/// @brief Override to make class pure virtual.
	std::string class_namespace() const override = 0;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class PluginScoringTermAdditionalOutput

} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif //Masala_src_core_api_base_classes_scoring_PluginScoringTermAdditionalOutput_hh