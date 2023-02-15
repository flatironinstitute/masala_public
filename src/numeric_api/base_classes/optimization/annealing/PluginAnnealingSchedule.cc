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

/// @file src/numeric_api/base_classes/optimization/annealing/PluginAnnealingSchedule.cc
/// @brief A base class for all plugin annealing schedules.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <numeric_api/base_classes/optimization/annealing/PluginAnnealingSchedule.hh>

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
PluginAnnealingSchedule::PluginAnnealingSchedule() :
    masala::numeric::optimization::annealing::AnnealingScheduleBase()
{}

/// @brief Copy constructor.
PluginAnnealingSchedule::PluginAnnealingSchedule(
    PluginAnnealingSchedule const &src 
) :
    masala::numeric::optimization::annealing::AnnealingScheduleBase( src )
{}

/// @brief Assignment operator.
PluginAnnealingSchedule &
PluginAnnealingSchedule::operator=(
    PluginAnnealingSchedule const &src
) {
    masala::numeric::optimization::annealing::AnnealingScheduleBase::operator=( src );
    return *this;
}

/// @brief Make this object wholly independent.
void
PluginAnnealingSchedule::make_independent() {
    masala::numeric::optimization::annealing::AnnealingScheduleBase::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the hierarchical categories for this plugin class.
/// @details The base class implementation returns { { "PluginAnnealingSchedule" } }
std::vector< std::vector< std::string > >
PluginAnnealingSchedule::get_categories() const {
    return masala::numeric::optimization::annealing::AnnealingScheduleBase::get_categories();
}

/// @brief Get the ahierarchical keywords for this plugin class.
/// @details The base class implementation returns { "annealing_schedule" }
std::vector< std::string >
PluginAnnealingSchedule::get_keywords() const {
    return masala::numeric::optimization::annealing::AnnealingScheduleBase::get_keywords();
}

} // namespace annealing
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
