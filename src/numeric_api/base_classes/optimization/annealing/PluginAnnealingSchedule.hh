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
#include <base/types.hh>

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
	masala::numeric::optimization::annealing::AnnealingScheduleBaseSP clone() const override = 0;

	/// @brief Make this object wholly independent.
	/// @details Should be overridden for derived classes.
	void make_independent() override;

	/// @brief Make a copy of this object that is wholly independent.
	virtual masala::numeric::optimization::annealing::AnnealingScheduleBaseSP deep_clone() const = 0;

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

	/// @brief Get the name of this class.
	/// @details Overridden to make this class pure virtual.
	std::string class_name() const override = 0;

	/// @brief Get the namespace of this class.
	/// @details Overridden to make this class pure virtual.
	std::string class_namespace() const override = 0;

	/// @brief Derived plugin annealing schedules must implement their own API definitions.
	masala::base::api::MasalaObjectAPIDefinitionCWP get_api_definition() override = 0;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the index of the expected final call to temperature().
	/// @details Pure virtual; derived classes should override this.
	void
	set_final_time_index(
		masala::base::Size const final_time_index
	) override = 0;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Return temperature.
	/// @details Pure virtual; derived classes should override this.
	masala::numeric::Real
	temperature() const override = 0;

	/// @brief Return temperature for the Nth timepoint.
	/// @details Pure virtual; derived classes should override this.
	masala::numeric::Real
	temperature(
		masala::base::Size const time_index
	) const override = 0;


}; // class PluginAnnealingSchedule

} // namespace annealing
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_annealing_PluginAnnealingSchedule_hh