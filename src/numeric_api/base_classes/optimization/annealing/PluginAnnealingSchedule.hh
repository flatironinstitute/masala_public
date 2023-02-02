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

/// @file src/numeric_api/base_classes/optimization/annealing/PluginAnnealingSchedule.hh
/// @brief Headers for a base class for all plugin annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_annealing_PluginAnnealingSchedule_hh
#define Masala_src_numeric_api_base_classes_optimization_annealing_PluginAnnealingSchedule_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/annealing/PluginAnnealingSchedule.fwd.hh>

// Base headers:
#include <numeric/optimization/annealing/AnnealingScheduleBase.hh>

// Numeric API headers:
#include <numeric_api/types.hh>

// STL headers:
#include <atomic>
#include <vector>
#include <string>


namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace annealing {

/// @brief A base class for all plugin annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginAnnealingSchedule : public masala::numeric::optimization::annealing::AnnealingScheduleBase {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginAnnealingSchedule();

	/// @brief Copy constructor.
	PluginAnnealingSchedule( PluginAnnealingSchedule const & );

	/// @brief Assignment operator.
	PluginAnnealingSchedule & operator=( PluginAnnealingSchedule const & );

	/// @brief Virtual destructor.
	virtual ~PluginAnnealingSchedule() = default;

	/// @brief Make a copy of this object.
	masala::numeric::optimization::annealing::AnnealingScheduleBaseSP clone() const override;

	/// @brief Make this object wholly independent.
	/// @details Should be overridden for derived classes.
	void make_independent() override;

	/// @brief Make a copy of this object that is wholly independent.
	PluginAnnealingScheduleSP deep_clone() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the hierarchical categories for this plugin class.
	/// @details The base class implementation returns { { "PluginAnnealingSchedule" } }
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the ahierarchical keywords for this plugin class.
	/// @details The base class implementation returns { "annealing_schedule" }
	std::vector< std::string >
	get_keywords() const override;


}; // class PluginAnnealingSchedule

} // namespace annealing
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_annealing_PluginAnnealingSchedule_hh