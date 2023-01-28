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

/// @file src/numeric_api/base_classes/optimization/annealing/AnnealingSchedule.cc
/// @brief A base class for all annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <numeric_api/base_classes/optimization/annealing/AnnealingSchedule.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.hh>

// STL headers
#include <string>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace annealing {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor.
AnnealingSchedule::AnnealingSchedule() :
    masala::base::managers::plugin_module::MasalaPlugin(),
    call_count_(0)
{}

/// @brief Copy constructor.
AnnealingSchedule::AnnealingSchedule(
    AnnealingSchedule const &src 
) :
    masala::base::managers::plugin_module::MasalaPlugin( src ),
    call_count_( src.call_count_.load() )
{}

/// @brief Assignment operator.
AnnealingSchedule &
AnnealingSchedule::operator=(
    AnnealingSchedule const &src
) {
    call_count_ = src.call_count_.load();
}

/// @brief Make this object wholly independent.
void
AnnealingSchedule::make_independent() {
    call_count_ = 0;
}

/// @brief Make a copy of this object that is wholly independent.
AnnealingScheduleSP
AnnealingSchedule::deep_clone() const {
    AnnealingScheduleSP new_object( clone() );
    new_object->make_independent();
    return new_object;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the hierarchical categories for this plugin class.
/// @details The base class implementation returns { { "AnnealingSchedule" } }
std::vector< std::vector< std::string > >
AnnealingSchedule::get_categories() const {
    return std::vector< std::vector< std::string > >{ { "AnnealingSchedule" } };
}

/// @brief Get the ahierarchical keywords for this plugin class.
/// @details The base class implementation returns { "annealing_schedule" }
std::vector< std::string >
AnnealingSchedule::get_keywords() const {
    return std::vector< std::string >{ "annealing_schedule" };
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the call count.
masala::numeric_api::Size
AnnealingSchedule::call_count() const {
    return call_count_.load();
}

/// @brief Increment the call count.
void
AnnealingSchedule::increment_call_count() {
    ++call_count_;
}

/// @brief Reset the call count.
void
AnnealingSchedule::reset() {
    call_count_ = 0;
}

} // namespace annealing
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
