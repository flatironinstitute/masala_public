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

/// @file src/numeric/optimization/annealing/AnnealingScheduleBase.cc
/// @brief A base class for all annealing schedules.  This class is
/// intended to be pure virtual, but can't fully be since it has to be instantiated to generate
/// the API.  But the API has protected constructors.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <numeric/optimization/annealing/AnnealingScheduleBase.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.hh>

// STL headers
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace annealing {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor.
AnnealingScheduleBase::AnnealingScheduleBase() :
    masala::base::managers::plugin_module::MasalaPlugin(),
    call_count_(0)
{}

/// @brief Copy constructor.
AnnealingScheduleBase::AnnealingScheduleBase(
    AnnealingScheduleBase const &src 
) :
    masala::base::managers::plugin_module::MasalaPlugin( src ),
    call_count_( src.call_count_.load() )
{}

/// @brief Assignment operator.
AnnealingScheduleBase &
AnnealingScheduleBase::operator=(
    AnnealingScheduleBase const &src
) {
    call_count_ = src.call_count_.load();
    return *this;
}

/// @brief Make this object wholly independent.
void
AnnealingScheduleBase::make_independent() {
    call_count_ = 0;
}

/// @brief Make a copy of this object that is wholly independent.
AnnealingScheduleBaseSP
AnnealingScheduleBase::deep_clone() const {
    AnnealingScheduleBaseSP new_object( clone() );
    new_object->make_independent();
    return new_object;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the hierarchical categories for this plugin class.
/// @details The base class implementation returns { { "AnnealingScheduleBase" } }
std::vector< std::vector< std::string > >
AnnealingScheduleBase::get_categories() const {
    return std::vector< std::vector< std::string > >{ { "AnnealingScheduleBase" } };
}

/// @brief Get the ahierarchical keywords for this plugin class.
/// @details The base class implementation returns { "annealing_schedule" }
std::vector< std::string >
AnnealingScheduleBase::get_keywords() const {
    return std::vector< std::string >{ "annealing_schedule" };
}

/// @brief Get the name of this class ("AnnealingScheduleBase").
std::string
AnnealingScheduleBase::class_name() const {
    return "AnnealingScheduleBase";
}

    /// @brief Get the namespace of this class ("masala::numeric::optimization::annealing").
std::string
AnnealingScheduleBase::class_namespace() const {
    return "masala::numeric::optimization::annealing";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the index of the expected final call to temperature().
/// @details The base class throws; derived classes should override this.
void
AnnealingScheduleBase::set_final_time_index(
    masala::numeric::Size const //final_time_index
) {
    MASALA_THROW( class_namespace_and_name(), "set_final_time_index", "This function is not implemented in the base class.  It must be implemented in derived classes." );
}

/// @brief Reset the call count.
void
AnnealingScheduleBase::reset_call_count() {
    call_count_ = 0;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Return temperature.
/// @details The base class throws; derived classes should override this.
masala::numeric::Real
AnnealingScheduleBase::temperature() const {
    MASALA_THROW( class_namespace_and_name(), "temperature", "This function is not implemented in the base class.  It must be implemented in derived classes." );
}

/// @brief Return temperature for the Nth timepoint.
/// @details The base class throws; derived classes should override this.

masala::numeric::Real
AnnealingScheduleBase::temperature(
    masala::numeric::Size const time_index
) const {
    MASALA_THROW( class_namespace_and_name(), "temperature", "This function is not implemented in the base class.  It must be implemented in derived classes." );
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the call count.
masala::numeric::Size
AnnealingScheduleBase::call_count() const {
    return call_count_.load();
}

/// @brief Increment the call count.
/// @note The call count is mutable.
void
AnnealingScheduleBase::increment_call_count() const {
    ++call_count_;
}

} // namespace annealing
} // namespace optimization
} // namespace numeric
} // namespace masala
