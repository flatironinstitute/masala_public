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

/// @file src/core/scoring/ScoringTermCache.hh
/// @brief Headers for a base class a container anything that a scoring term may
/// need to cache to facilitate repeated similar calculations.
/// @details Scoring terms may optionally read from AND write to this, during scoring.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_scoring_ScoringTermCache_hh
#define Masala_src_core_scoring_ScoringTermCache_hh

// Forward declarations:
#include <core/scoring/ScoringTermCache.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

namespace masala {
namespace core {
namespace scoring {

/// @brief A base class a container anything that a scoring term may need to cache
/// to facilitate repeated similar calculations.
/// @details Scoring terms may optionally read from AND write to this, during scoring.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ScoringTermCache : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	ScoringTermCache() = default;

	/// @brief Copy constructor.
	ScoringTermCache( ScoringTermCache const & ) = default;

	/// @brief Virtual destructor.
	virtual ~ScoringTermCache() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class ScoringTermCache

} // namespace scoring
} // namespace core
} // namespace masala

#endif //Masala_src_core_scoring_ScoringTermCache_hh