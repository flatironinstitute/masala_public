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

/// @file src/core/scoring/ScoringTermAdditionalInput.hh
/// @brief Headers for a base class a container for additional
/// input into a scoring term.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_scoring_ScoringTermAdditionalInput_hh
#define Masala_src_core_scoring_ScoringTermAdditionalInput_hh

// Forward declarations:
#include <core/scoring/ScoringTermAdditionalInput.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

namespace masala {
namespace core {
namespace scoring {

/// @brief A base class a container for additional input into a scoring term.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ScoringTermAdditionalInput : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	ScoringTermAdditionalInput() = default;

	/// @brief Copy constructor.
	ScoringTermAdditionalInput( ScoringTermAdditionalInput const & ) = default;

	/// @brief Virtual destructor.
	virtual ~ScoringTermAdditionalInput() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class ScoringTermAdditionalInput

} // namespace scoring
} // namespace core
} // namespace masala

#endif //Masala_src_core_scoring_ScoringTermAdditionalInput_hh