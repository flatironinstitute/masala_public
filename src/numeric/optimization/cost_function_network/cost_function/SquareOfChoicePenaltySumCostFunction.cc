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

/// @file src/numeric/optimization/cost_function_network/cost_function/SquareOfChoicePenaltySumCostFunction.cc
/// @brief Implementation for a pure virtual base class for SquareOfChoicePenaltySumCostFunctions.
/// @details SquareOfChoicePenaltySumCostFunctions define a penalty function which is based on the following:
/// - A penalty is assigned to each choice.
/// - The selected choices' penalties are summed, and a constant is added.
/// - The sum is squared, and this is returned as the penalty.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/SquareOfChoicePenaltySumCostFunction.hh>

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.
SquareOfChoicePenaltySumCostFunction::SquareOfChoicePenaltySumCostFunction(
    SquareOfChoicePenaltySumCostFunction const & src
) :
    ChoicePenaltySumBasedCostFunction< masala::base::Real >( src )
{
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    assign_mutex_locked( src );
}

// @brief Assignment operator.
SquareOfChoicePenaltySumCostFunction &
SquareOfChoicePenaltySumCostFunction::operator=(
    SquareOfChoicePenaltySumCostFunction const & src
) {
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    assign_mutex_locked( src );
    return *this;
}

/// @brief Make a copy of this object.
CostFunctionSP
SquareOfChoicePenaltySumCostFunction::clone() const {
    return masala::make_shared< SquareOfChoicePenaltySumCostFunction >( *this );
}

/// @brief Make a copy of this object that is fully independent.
SquareOfChoicePenaltySumCostFunctionSP
SquareOfChoicePenaltySumCostFunction::deep_clone() const {
    SquareOfChoicePenaltySumCostFunctionSP new_object( std::static_pointer_cast< SquareOfChoicePenaltySumCostFunction >( this->clone() ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
void
SquareOfChoicePenaltySumCostFunction::make_independent() {
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
SquareOfChoicePenaltySumCostFunction::get_categories() const {
	return ChoicePenaltySumBasedCostFunction::get_categories();
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric", "choice_penalty_sum_based", "quadratic", "squared" }
std::vector< std::string >
SquareOfChoicePenaltySumCostFunction::get_keywords() const {
	std::vector< std::string > outvec( ChoicePenaltySumBasedCostFunction< masala::base::Real >::get_keywords() );
    outvec.push_back( "quadratic" );
    outvec.push_back( "squared" );
    return outvec;
}

/// @brief Get the name of this class ("SquareOfChoicePenaltySumCostFunction").
std::string
SquareOfChoicePenaltySumCostFunction::class_name() const {
    return "SquareOfChoicePenaltySumCostFunction";
}

/// @brief Get the namespace of this class ("masala::numeric::optimization::cost_function_network::cost_function").
std::string
SquareOfChoicePenaltySumCostFunction::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network::cost_function";
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given a selection of choices at variable nodes, compute the cost function.
/// @details This version computes the sum of the selected choices plus a constant,
/// then squares the result.
/// @note No mutex-locking is performed!
masala::base::Real
SquareOfChoicePenaltySumCostFunction::compute_cost_function(
    std::vector< masala::base::Size > const & candidate_solution
) const {
    masala::base::Real const sum( ChoicePenaltySumBasedCostFunction< masala::base::Real >::compute_cost_function( candidate_solution ) );
    return sum*sum;
}

/// @brief Given an old selection of choices at variable nodes and a new selection,
/// compute the cost function difference.
/// @details This version computes the sum of the old selected choices plus a constant,
/// then squares the result.  It repeats this for the new selected choices, then returns
/// the difference.
/// @note No mutex-locking is performed!
masala::base::Real
SquareOfChoicePenaltySumCostFunction::compute_cost_function_difference(
    std::vector< masala::base::Size > const & candidate_solution_old,
    std::vector< masala::base::Size > const & candidate_solution_new
) const {
    masala::base::Real const oldsum( ChoicePenaltySumBasedCostFunction< masala::base::Real >::compute_cost_function( candidate_solution_old ) );
    masala::base::Real const newsum( ChoicePenaltySumBasedCostFunction< masala::base::Real >::compute_cost_function( candidate_solution_new ) );
    return ( newsum * newsum ) - ( oldsum * oldsum );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API of this object.
masala::base::api::MasalaObjectAPIDefinitionCWP
SquareOfChoicePenaltySumCostFunction::get_api_definition() {
    using masala::base::Size;
    using masala::base::Real;
    using namespace masala::base::api;
    std::lock_guard< std::mutex > lock( mutex() );
    if( api_definition_mutex_locked() == nullptr ) {
        
        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this, "A cost function which sums the penalties of the individual choices that were selected for "
                "a given solution, adds a constant, and squares the result.", false, false
            )
        );

        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( SquareOfChoicePenaltySumCostFunction, api_def );

        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput<bool> >(
                "finalized", "Has the data-entry phase ended and the object been locked?",
                "finalized", "True if we have finalized this object, false otherwise.",
                false, false, std::bind( &SquareOfChoicePenaltySumCostFunction::finalized, this )
            )
        );

        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
                "set_constant_offset", "Set the constant to be added to all penalty sums.",
                "constant_offset", "The constant to be added to the penalty sum before the whole thing is squared.",
                false, false, std::bind( &SquareOfChoicePenaltySumCostFunction::set_constant_offset, this, std::placeholders::_1 )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< Size, std::vector< Real > const & > >(
                "set_penalties_for_all_choices_at_node", "Set the penalties for all of the choices at one node.",
                "absolute_node_index", "The absolute index of the node for which we're setting penalties.",
                "penalties_by_choice_index", "The penalties for all of the choices, indexed by choice index.",
                false, false,
                std::bind( &SquareOfChoicePenaltySumCostFunction::set_penalties_for_all_choices_at_node, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );

        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< void, std::vector< Size > const & > >(
                "finalize", "Indicate that all data input is complete.", false, false, false, false,
                "variable_node_indices", "A list of all of the absolute node indices for nodes that have more than "
                "one choice, indexed by variable node index.", "void", "No output.",
                std::bind( &SquareOfChoicePenaltySumCostFunction::finalize, this, std::placeholders::_1 )
            )
        );
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< Real, std::vector< Size > const & > >(
                "compute_cost_function", "Given a selection of choices at variable nodes, compute the cost function.  This version "
                "computes the sum of the selected choices plus a constant, then squares the result.", true, false, false, false,
                "candidate_solution", "A candidate solution, as a vector of choices for each variable position (i.e. position with "
                "more than one choice).", "score", "The output score: the sum of the penalties for the selected choices, plus a constant "
                "offset, all squared.", std::bind( &SquareOfChoicePenaltySumCostFunction::compute_cost_function, this, std::placeholders::_1 )
            )
        );
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< Real, std::vector< Size > const &, std::vector< Size > const & > >(
                "compute_cost_function_difference", "Given an old selection of choices at variable nodes and a new selection, compute "
                "the cost function difference.  This version computes the sum of the old selected choices plus a constant, then "
                "squares the result.  It repeats this for the new selected choices, then returns the difference.",
                true, false, false, false,
                "candidate_solution_old", "The old candidate solution, as a vector of choices for each variable position.",
                "candidate_solution_new", "The new candidate solution, as a vector of choices for each variable position.",
                "score", "The output score: the difference of the sum of the penalties for the selected choices, plus a constant "
                "offset, all squared.",
                std::bind( &SquareOfChoicePenaltySumCostFunction::compute_cost_function_difference, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );
    
        api_definition_mutex_locked() = api_def;
    }
    return api_definition_mutex_locked();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Indicate that all data input is complete.  Performs no mutex-locking.
/// @param[in] variable_node_indices A list of all of the absolute node indices
/// for nodes that have more than one choice, indexed by variable node index.
/// @details The base class function simply marks this object as finalized.  Should
/// be overridden, and overrides should call parent class protected_finalize().
void
SquareOfChoicePenaltySumCostFunction::protected_finalize(
    std::vector< masala::base::Size > const & variable_node_indices
) {
    using masala::base::Size;
    using masala::base::Real;

    //TODO do any finalization needed here.

    ChoicePenaltySumBasedCostFunction< masala::base::Real >::finalize( variable_node_indices );
}

/// @brief Override of assign_mutex_locked().  Calls parent function.
/// @details Throws if src is not a SquareOfChoicePenaltySumCostFunction.
void
SquareOfChoicePenaltySumCostFunction::assign_mutex_locked(
    CostFunction const & src
) {
    SquareOfChoicePenaltySumCostFunction const * const src_cast_ptr( dynamic_cast< SquareOfChoicePenaltySumCostFunction const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "assign_mutex_locked", "Cannot assign a SquareOfChoicePenaltySumCostFunction given an input " + src.class_name() + " object!  Object types do not match." );

    // TODO OTHER ASSIGNMENT.

    ChoicePenaltySumBasedCostFunction< masala::base::Real >::assign_mutex_locked( src );
}

/// @brief Make this object fully independent.  Assumes mutex was already locked.
/// Should be called by overrides.
void
SquareOfChoicePenaltySumCostFunction::make_independent_mutex_locked() {
    // GNDN
    ChoicePenaltySumBasedCostFunction< masala::base::Real >::make_independent_mutex_locked();
}

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
