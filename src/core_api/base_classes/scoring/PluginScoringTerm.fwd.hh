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

/// @file src/core/scoring/PluginScoringTerm.fwd.hh
/// @brief Forward declarations for a base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_scoring_PluginScoringTerm_fwd_hh
#define Masala_src_core_api_base_classes_scoring_PluginScoringTerm_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace core_api {
namespace base_classes {
namespace scoring {

	class PluginScoringTerm;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using PluginScoringTermSP = MASALA_SHARED_POINTER< PluginScoringTerm >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using PluginScoringTermCSP = MASALA_SHARED_POINTER< PluginScoringTerm const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using PluginScoringTermWP = MASALA_WEAK_POINTER< PluginScoringTerm >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using PluginScoringTermCWP = MASALA_WEAK_POINTER< PluginScoringTerm const >;

} // namespace scoring
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif //Masala_src_core_api_base_classes_scoring_PluginScoringTerm_fwd_hh