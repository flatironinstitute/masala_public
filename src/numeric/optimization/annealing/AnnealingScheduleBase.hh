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

/// @file src/numeric/optimization/annealing/AnnealingScheduleBase.hh
/// @brief Headers for a base class for all annealing schedules.  This class is
/// intended to be pure virtual, but can't fully be since it has to be instantiated to generate
/// the API.  But the API has protected constructors.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @note DO NOT inherit from this class directly in plugin libraries!  Instead, inherit from
/// masala::numeric_api::base_classes::optimization::annealing::PluginAnnealingSchedule.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_annealing_AnnealingScheduleBase_hh
#define Masala_src_numeric_optimization_annealing_AnnealingScheduleBase_hh

// Forward declarations:
#include <numeric/optimization/annealing/AnnealingScheduleBase.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Numeric API headers:
#include <base/types.hh>

// STL headers:
#include <vector>
#include <string>
#include <mutex>


namespace masala {
namespace numeric {
namespace optimization {
namespace annealing {

/// @brief A base class for all annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.  This class is
/// intended to be pure virtual, but can't fully be since it has to be instantiated to generate
/// the API.  But the API has protected constructors.
/// @note DO NOT inherit from this class directly in plugin libraries!  Instead, inherit from
/// masala::numeric_api::base_classes::optimization::annealing::PluginAnnealingSchedule.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AnnealingScheduleBase : public masala::base::managers::plugin_module::MasalaPlugin {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	AnnealingScheduleBase();

	/// @brief Copy constructor.
	AnnealingScheduleBase( AnnealingScheduleBase const & );

	/// @brief Assignment operator.
	AnnealingScheduleBase & operator=( AnnealingScheduleBase const & );

	/// @brief Virtual destructor.
	virtual ~AnnealingScheduleBase() = default;

	/// @brief Make a copy of this object.
	virtual
	AnnealingScheduleBaseSP clone() const;

	/// @brief Make this object wholly independent.
	/// @details Should be overridden for derived classes.
	virtual
	void make_independent();

	/// @brief Make a copy of this object that is wholly independent.
	virtual AnnealingScheduleBaseSP deep_clone() const;

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

	/// @brief Get the name of this class ("AnnealingScheduleBase").
	std::string class_name() const override;

	/// @brief Get the namespace of this class ("masala::numeric::optimization::annealing").
	std::string class_namespace() const override;

	/// @brief Get the API definition for this class.
	/// @details Implemented to ensure that there's a common API class that derived classes' APIs are based on.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the index of the expected final call to temperature().
	/// @details The base class throws; derived classes should override this.
	virtual
	void
	set_final_time_index(
		masala::base::Size const final_time_index
	);

	/// @brief Reset the call count.
	void reset_call_count();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Return temperature.
	/// @details The base class throws; derived classes should override this.
	/// @note This function should increment the call count.  If the call count is at N, then
	/// this function has been called N times.  The zero-based index of the last call is N-1.
	virtual
	masala::base::Real
	temperature() const;

	/// @brief Return temperature for the Nth timepoint.
	/// @details The base class throws; derived classes should override this.
	/// @note The time index is zero-based.
	virtual
	masala::base::Real
	temperature(
		masala::base::Size const time_index
	) const;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the call count.
	/// @note The annealing_schedule_mutex_ should be locked
	/// before calling this function -- it performs no mutex locking itself.
	masala::base::Size call_count() const;

	/// @brief Increment the call count.
	/// @note The call count is mutable.  The annealing_schedule_mutex_ should be locked
	/// before calling this function -- it performs no mutex locking itself.
	void increment_call_count() const;

	/// @brief Access the mutex in the base class.
	std::mutex & annealing_schedule_mutex() const;
	
	/// @brief Access the API definition in the base class.
	/// @details Performs no mutex locking.
	masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition();

	/// @brief Const access to the API definition in the base class.
	/// @details Performs no mutex locking.
	masala::base::api::MasalaObjectAPIDefinitionCSP const & api_definition() const;

private:

	/// @brief A mutex for this class.
	mutable std::mutex annealing_schedule_mutex_;

	/// @brief The API definition.  Could be nullptr.  Not copied.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief Number of times the temperature() function has been called.
	/// @note This is one more than the last timestep.  That is, a value of zero
	/// means that we have not yet performed the very first timestep.
	mutable masala::base::Size call_count_ = 0;

}; // class AnnealingScheduleBase

} // namespace annealing
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_annealing_AnnealingScheduleBase_hh