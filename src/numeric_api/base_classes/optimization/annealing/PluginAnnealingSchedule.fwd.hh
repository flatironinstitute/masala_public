/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/optimization/annealing/PluginAnnealingSchedule.fwd.hh
/// @brief Forward declarations for a base class for all plugin annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_annealing_PluginAnnealingSchedule_fwd_hh
#define Masala_src_numeric_api_base_classes_optimization_annealing_PluginAnnealingSchedule_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace annealing {

	class PluginAnnealingSchedule;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using PluginAnnealingScheduleSP = MASALA_SHARED_POINTER< PluginAnnealingSchedule >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using PluginAnnealingScheduleCSP = MASALA_SHARED_POINTER< PluginAnnealingSchedule const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using PluginAnnealingScheduleWP = MASALA_WEAK_POINTER< PluginAnnealingSchedule >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using PluginAnnealingScheduleCWP = MASALA_WEAK_POINTER< PluginAnnealingSchedule const >;

} // namespace annealing
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_annealing_PluginAnnealingSchedule_fwd_hh
