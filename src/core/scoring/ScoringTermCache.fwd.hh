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

/// @file src/core/scoring/ScoringTermCache.fwd.hh
/// @brief Forward declarations for a base class a container anything that a scoring term may
/// need to cache to facilitate repeated similar calculations.
/// @details Scoring terms may optionally read from AND write to this, during scoring.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_scoring_ScoringTermCache_fwd_hh
#define Masala_src_core_scoring_ScoringTermCache_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace core {
namespace scoring {

	class ScoringTermCache;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using ScoringTermCacheSP = MASALA_SHARED_POINTER< ScoringTermCache >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using ScoringTermCacheCSP = MASALA_SHARED_POINTER< ScoringTermCache const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using ScoringTermCacheWP = MASALA_WEAK_POINTER< ScoringTermCache >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using ScoringTermCacheCWP = MASALA_WEAK_POINTER< ScoringTermCache const >;

} // namespace scoring
} // namespace core
} // namespace masala

#endif //Masala_src_core_scoring_ScoringTermCache_fwd_hh