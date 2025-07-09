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

/// @file src/numeric/optimization/annealing/AnnealingScheduleBase.cc
/// @brief A base class for all annealing schedules.  This class is
/// intended to be pure virtual, but can't fully be since it has to be instantiated to generate
/// the API.  But the API has protected constructors.
/// @details Annealing schedules return temperature as a function of number of calls.
/// @note DO NOT inherit from this class directly in plugin libraries!  Instead, inherit from
/// masala::numeric_api::base_classes::optimization::annealing::PluginAnnealingSchedule.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <numeric/optimization/annealing/AnnealingScheduleBase.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>

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
    masala::base::managers::plugin_module::MasalaPlugin( src )
{
    AnnealingScheduleBase::operator=( src ); 
}

/// @brief Assignment operator.
AnnealingScheduleBase &
AnnealingScheduleBase::operator=(
    AnnealingScheduleBase const &src
) {
    std::lock( annealing_schedule_mutex_, src.annealing_schedule_mutex_ );
    std::lock_guard< std::mutex > lock_this( annealing_schedule_mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lock_that( src.annealing_schedule_mutex_, std::adopt_lock );
    call_count_ = src.call_count_;
    return *this;
}

/// @brief Make a copy of this object.
AnnealingScheduleBaseSP
AnnealingScheduleBase::clone() const {
    return masala::make_shared< AnnealingScheduleBase >( *this );
}

/// @brief Make this object wholly independent.
void
AnnealingScheduleBase::make_independent() {
    std::lock_guard< std::mutex > lock( annealing_schedule_mutex_ );
    call_count_ = 0;
    api_definition_ = nullptr;
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
/// @details The base class implementation returns { { "AnnealingSchedule" } }
std::vector< std::vector< std::string > >
AnnealingScheduleBase::get_categories() const {
    return std::vector< std::vector< std::string > >{ { "AnnealingSchedule" } };
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

/// @brief Get the API definition for this class.
/// @details Implemented to ensure that there's a common API class that derived classes' APIs are based on.
masala::base::api::MasalaObjectAPIDefinitionCWP
AnnealingScheduleBase::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( annealing_schedule_mutex_ );

    if( api_definition_ == nullptr ) {
        MasalaObjectAPIDefinitionSP api_definition(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this, "A base class for annealing schedules.  Annealing schedules return temperature "
                "as a function of number of calls.  This class is like a pure virtual base class: it cannot "
                "be instantiated from API layers or higher, since its API definition specifies protected "
                "constructors.  Only derived classes can be instantiated.",
                false, true
            )
        );

        // Constructors
        ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( AnnealingScheduleBase, api_definition );

        //Setters
        api_definition->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::base::Size > >(
                "set_final_time_index", "Set the final time index in the annealing schedule.",
                "final_time_index", "The index of the final timepoint in the annealing schedule.",
                true, false, std::bind( &AnnealingScheduleBase::set_final_time_index, this, std::placeholders::_1 )
            )
        );
        api_definition->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset_call_count", "Reset this object's call count.",
                true, false, std::bind( &AnnealingScheduleBase::reset_call_count, this )
            )
        );

        // Work functions
        api_definition->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ZeroInput< masala::base::Real > >(
                "temperature", "Get the temperature at the current timepoint, and increment the timepoint counter",
                true, false, true, false,
                "temperature", "The temperature at the current timepoint.",
                std::bind( static_cast<masala::base::Real(AnnealingScheduleBase::*)() const>( &AnnealingScheduleBase::temperature ), this )
            )
        );
        api_definition->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< masala::base::Real, masala::base::Size > >(
                "temperature", "Get the temperature at the given timepoint.  This does not increment the "
                "timepoint counter.",
                true, false, true, false,
                "time_index", "The timepoint at which we are getting temperature.",
                "temperature",
                "The temperature at the current timepoint.",
                std::bind( static_cast<masala::base::Real(AnnealingScheduleBase::*)( masala::base::Size const ) const>( &AnnealingScheduleBase::temperature ), this, std::placeholders::_1 )
            )
        );

        api_definition_ = api_definition; // Nonconst to const.
    }
    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the index of the expected final call to temperature().
/// @details The base class throws; derived classes should override this.
void
AnnealingScheduleBase::set_final_time_index(
    masala::base::Size const //final_time_index
) {
    MASALA_THROW( class_namespace_and_name(), "set_final_time_index", "This function is not implemented in the base class.  It must be implemented in derived classes." );
}

/// @brief Reset the call count.
void
AnnealingScheduleBase::reset_call_count() {
    std::lock_guard< std::mutex > lock( annealing_schedule_mutex_ );
    call_count_ = 0;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Return temperature.
/// @details The base class throws; derived classes should override this.
masala::base::Real
AnnealingScheduleBase::temperature() const {
    MASALA_THROW( class_namespace_and_name(), "temperature", "This function is not implemented in the base class.  It must be implemented in derived classes." );
}

/// @brief Return temperature for the Nth timepoint.
/// @details The base class throws; derived classes should override this.
masala::base::Real
AnnealingScheduleBase::temperature(
    masala::base::Size const /*time_index*/
) const {
    MASALA_THROW( class_namespace_and_name(), "temperature", "This function is not implemented in the base class.  It must be implemented in derived classes." );
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the call count.
/// @note The annealing_schedule_mutex_ should be locked
/// before calling this function -- it performs no mutex locking itself.
masala::base::Size
AnnealingScheduleBase::call_count() const {
    return call_count_;
}

/// @brief Increment the call count.
/// @note The call count is mutable.  The annealing_schedule_mutex_ should be locked
/// before calling this function -- it performs no mutex locking itself.
void
AnnealingScheduleBase::increment_call_count() const {
    ++call_count_;
}

/// @brief Access the mutex in the base class.
std::mutex &
AnnealingScheduleBase::annealing_schedule_mutex() const {
    return annealing_schedule_mutex_;
}

/// @brief Access the API definition in the base class.
/// @details Performs no mutex locking.
masala::base::api::MasalaObjectAPIDefinitionCSP &
AnnealingScheduleBase::api_definition() {
    return api_definition_;
}

/// @brief Const access to the API definition in the base class.
/// @details Performs no mutex locking.
masala::base::api::MasalaObjectAPIDefinitionCSP const &
AnnealingScheduleBase::api_definition() const {
    return api_definition_;
}

} // namespace annealing
} // namespace optimization
} // namespace numeric
} // namespace masala
