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

/// @file src/numeric_api/base_classes/optimization/annealing/AnnealingSchedule.hh
/// @brief Headers for a base class for all annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_annealing_AnnealingSchedule_hh
#define Masala_src_numeric_api_base_classes_optimization_annealing_AnnealingSchedule_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/annealing/AnnealingSchedule.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPlugin.hh>

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

/// @brief A base class for all annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AnnealingSchedule : public masala::base::managers::plugin_module::MasalaPlugin {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	AnnealingSchedule();

	/// @brief Copy constructor.
	AnnealingSchedule( AnnealingSchedule const & );

	/// @brief Assignment operator.
	AnnealingSchedule & operator=( AnnealingSchedule const & );

	/// @brief Virtual destructor.
	virtual ~AnnealingSchedule() = default;

	/// @brief Make a copy of this object.
	virtual
	AnnealingScheduleSP clone() const = 0;

	/// @brief Make this object wholly independent.
	/// @details Should be overridden for derived classes.
	virtual
	void make_independent();

	/// @brief Make a copy of this object that is wholly independent.
	AnnealingScheduleSP deep_clone() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the hierarchical categories for this plugin class.
	/// @details The base class implementation returns { { "AnnealingSchedule" } }
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the ahierarchical keywords for this plugin class.
	/// @details The base class implementation returns { "annealing_schedule" }
	std::vector< std::string >
	get_keywords() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the index of the expected final call to temperature().
virtual
void
set_final_time_index(
	masala::numeric_api::Size const final_time_index
) = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Return temperature.
	virtual
	masala::numeric_api::Real
	temperature() const = 0;

	/// @brief Return temperature for the Nth timepoint.
	virtual
	masala::numeric_api::Real
	temperature(
		masala::numeric_api::Size const time_index
	) const = 0;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the call count.
	masala::numeric_api::Size call_count() const;

	/// @brief Increment the call count.
	/// @note The call count is mutable.
	void increment_call_count() const;

	/// @brief Reset the call count.
	void reset_call_count();

private:

	/// @brief Number of times the temperature() function has been called.
	mutable std::atomic< masala::numeric_api::Size > call_count_;

}; // class AnnealingSchedule

} // namespace annealing
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif //Masala_src_numeric_api_base_classes_optimization_annealing_AnnealingSchedule_hh