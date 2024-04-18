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

/// @file src/core/scoring/ScoringTerm.hh
/// @brief Headers for a base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_scoring_ScoringTerm_hh
#define Masala_src_core_scoring_ScoringTerm_hh

// Forward declarations:
#include <core/scoring/ScoringTerm.fwd.hh>

// Core API headers:
#include <core/scoring/ScoringTermAdditionalInput.fwd.hh>
#include <core/scoring/ScoringTermAdditionalOutput.fwd.hh>
#include <core/scoring/ScoringTermCache.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/MasalaObject.hh>

// STL headers:
#include <vector>

namespace masala {
namespace core {
namespace scoring {

/// @brief A base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ScoringTerm : public masala::base::MasalaObject {

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

	/// @brief Needed for API definition.
	std::string class_name() const override;

	/// @brief Needed for API definition.
	std::string class_namespace() const override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class ScoringTerm

} // namespace scoring
} // namespace core
} // namespace masala

#endif //Masala_src_core_scoring_ScoringTerm_hh