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

/// @file src/numeric/optimization/annealing/AnnealingScheduleBase.fwd.hh
/// @brief Forward declarations for a base class for all annealing schedules.  This class is
/// intended to be pure virtual, but can't fully be since it has to be instantiated to generate
/// the API.  But the API has protected constructors.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @note DO NOT inherit from this class directly in plugin libraries!  Instead, inherit from
/// masala::numeric_api::base_classes::optimization::annealing::PluginAnnealingSchedule.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_annealing_AnnealingScheduleBase_fwd_hh
#define Masala_src_numeric_optimization_annealing_AnnealingScheduleBase_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace annealing {

	class AnnealingScheduleBase;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using AnnealingScheduleBaseSP = MASALA_SHARED_POINTER< AnnealingScheduleBase >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using AnnealingScheduleBaseCSP = MASALA_SHARED_POINTER< AnnealingScheduleBase const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using AnnealingScheduleBaseWP = MASALA_WEAK_POINTER< AnnealingScheduleBase >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using AnnealingScheduleBaseCWP = MASALA_WEAK_POINTER< AnnealingScheduleBase const >;

} // namespace annealing
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_annealing_AnnealingScheduleBase_fwd_hh
