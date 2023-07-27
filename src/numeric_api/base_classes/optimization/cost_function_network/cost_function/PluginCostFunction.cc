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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunction.cc
/// @brief Implementation for a non-instantiable base class for PluginCostFunctions.
/// @details PluginCostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)  The PluginCostFunction class derives from CostFunction,
/// and permits cost functions to be defined in plug-in libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunction.hh>

// Numeric headers:

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor (protected in API).
PluginCostFunction::PluginCostFunction(
    PluginCostFunction const & src
) :
    masala::numeric::optimization::cost_function_network::cost_function::CostFunction( src )
{
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    assign_mutex_locked( src );
}

// @brief Assignment operator.
PluginCostFunction &
PluginCostFunction::operator=(
    PluginCostFunction const & src
) {
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    assign_mutex_locked( src );
    return *this;
}

/// @brief Make a copy of this object.
masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP
PluginCostFunction::clone() const {
    return masala::make_shared< PluginCostFunction >(*this);
}

/// @brief Make a fully independent copy of this object.
PluginCostFunctionSP
PluginCostFunction::deep_clone() const {
    PluginCostFunctionSP new_object( std::static_pointer_cast< PluginCostFunction >( clone() ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
void
PluginCostFunction::make_independent() {
    std::lock_guard< std::mutex > lock( mutex() );
    make_independent_mutex_locked();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "CostFunction" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
PluginCostFunction::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunction" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric" }
std::vector< std::string >
PluginCostFunction::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function",
		"numeric"
	};
}

/// @brief Get the category for this MasalaDataRepresentation.
/// @returns { { "CostFunction" } }.
std::vector< std::vector< std::string > >
PluginCostFunction::get_data_representation_categories() const {
    return std::vector< std::vector< std::string > >{ { "CostFunction" } };
}

/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
/// is compatible.
/// @returns An empty list.
std::vector< std::string >
PluginCostFunction::get_compatible_masala_engines() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation.
/// @returns { "cost_function" }.
std::vector< std::string >
PluginCostFunction::get_present_data_representation_properties() const {
    return std::vector< std::string >{ "cost_function" };
}

/// @brief Get the class name ("PluginCostFunction").
/*static*/
std::string
PluginCostFunction::class_name_static() {
    return "PluginCostFunction";
}

/// @brief Get the class namespace ("masala::numeric_api::base_classes::optimization::cost_function_network::cost_function").
/*static*/
std::string
PluginCostFunction::class_namespace_static() {
    return "masala::numeric_api::base_classes::optimization::cost_function_network::cost_function";
}

/// @brief Get the class name.  Calls class_name_static().
std::string
PluginCostFunction::class_name() const {
    return class_name_static();
}

/// @brief Get the class namespace.  Calls class_namespace_static().
std::string
PluginCostFunction::class_namespace() const {
    return class_namespace_static();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the API definition for this (non-instantiable) class.
masala::base::api::MasalaObjectAPIDefinitionCWP
PluginCostFunction::get_api_definition() {
    using namespace masala::base::api;
    using masala::base::Size;
    using masala::base::Real;

    std::lock_guard< std::mutex > lock( mutex() );
    if( api_definition_mutex_locked() == nullptr ) {
        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this, "A plugin cost function, used in cost function network optimization algorithms.",
                false, true
            )
        );

        ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( PluginCostFunction, api_def );

        {
            work_function::MasalaObjectAPIWorkFunctionDefinitionSP compute_cost_function_def(
                masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< Real, std::vector< Size > const & > >(
                    "compute_cost_function", "Given a selection of choices at variable nodes, compute the cost function.  Note that no mutex-locking is performed.",
                    true, false, true, false,
                    "candidate_solution", "The indices of the selected node choices, indexed by variable node index.",
                    "cost_function", "The square of the total number of features that are unsatisfied, multiplied by the weight of this cost function.",
                    std::bind( &PluginCostFunction::compute_cost_function, this, std::placeholders::_1 )               
                )
            );
            compute_cost_function_def->set_triggers_no_mutex_lock();
            api_def->add_work_function( compute_cost_function_def );
        }
        {
            work_function::MasalaObjectAPIWorkFunctionDefinitionSP compute_cost_function_difference_def(
                masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< Real, std::vector< Size > const &, std::vector< Size > const & > >(
                    "compute_cost_function_difference", "Given an old selection of choices at variable nodes and a new selection, "
                    "compute the cost function difference.  Note that no mutex-locking is performed.",
                    true, false, true, false,
                    "candidate_solution_old", "The indices of the selected node choices for the OLD selection, indexed by variable node index.",
                    "candidate_solution_new", "The indices of the selected node choices for the NEW selection, indexed by variable node index.",
                    "cost_function", "The difference of the squares of the total number of features that are unsatisfied, multiplied by the weight of this cost function.",
                    std::bind( &PluginCostFunction::compute_cost_function_difference,
                        this, std::placeholders::_1, std::placeholders::_2
                    )               
                )
            );
            compute_cost_function_difference_def->set_triggers_no_mutex_lock();
            api_def->add_work_function( compute_cost_function_difference_def );
        }

        api_definition_mutex_locked() = api_def;
    }
    return api_definition_mutex_locked();
}

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
