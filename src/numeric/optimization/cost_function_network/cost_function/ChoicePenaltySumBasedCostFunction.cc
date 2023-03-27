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

/// @file src/numeric/optimization/cost_function_network/cost_function/ChoicePenaltySumBasedCostFunction.cc
/// @brief Implementation for a pure virtual base class for ChoicePenaltySumBasedCostFunctions.
/// @details ChoicePenaltySumBasedCostFunctions define a penalty function which is based on the following:
/// - A penalty is assigned to each choice.
/// - The selected choices' penalties are summed, and a constant is added.
/// - An R->R (nonlinear) function is applied to the sum, and this is returned as the penalty.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/ChoicePenaltySumBasedCostFunction.hh>

// STL headers:
#include <vector>
#include <string>

// Base headers:
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
ChoicePenaltySumBasedCostFunction::ChoicePenaltySumBasedCostFunction(
    ChoicePenaltySumBasedCostFunction const & src
) :
    CostFunction( src )
{
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    assign_mutex_locked( src );
}

// @brief Assignment operator.
ChoicePenaltySumBasedCostFunction &
ChoicePenaltySumBasedCostFunction::operator=(
    ChoicePenaltySumBasedCostFunction const & src
) {
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    assign_mutex_locked( src );
    return *this;
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
ChoicePenaltySumBasedCostFunction::get_categories() const {
	return CostFunction::get_categories();
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric", "choice_penalty_sum_based" }
std::vector< std::string >
ChoicePenaltySumBasedCostFunction::get_keywords() const {
	std::vector< std::string > outvec( CostFunction::get_keywords() );
    outvec.push_back( "choice_penalty_sum_based" );
    return outvec;
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the penalties for all of the choices at one node.
/// @param[in] absolute_node_index The absolute index of the ndoe for which we're setting penalties.
/// @param[in] penalties_by_choice_index The penalties for all of the choices, indexed by choice index.
/// @note Only in debug mode do we check that these have not already been set.
void
ChoicePenaltySumBasedCostFunction::set_penalties_for_all_choices_at_node(
    masala::base::Size const absolute_node_index,
    std::vector< masala::base::Real > const & penalties_by_choice_index
) {
    using masala::base::Size;
    using masala::base::Real;

    std::lock_guard< std::mutex > lock( mutex() );
    CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "set_penalties_for_all_choices_at_node",
        "This function cannot be called after the " + class_name() + " has been finalized."
    );

    Size const nchoices( penalties_by_choice_index.size() );

#ifndef NDEBUG
    // Debug-mode checks:
    for( Size i(0); i<nchoices; ++i ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
            penalties_by_absolute_node_and_choice_.count( std::make_pair( absolute_node_index, i ) ) == 0,
            "set_penalties_for_all_choices_at_node",
            "Penalties for node " + std::to_string( absolute_node_index ) + ", choice " + std::to_string( i )
            + " have already been set."
        );
    }
#endif

    for( Size i(0); i<nchoices; ++i ) {
        penalties_by_absolute_node_and_choice_[ std::make_pair( absolute_node_index, i ) ] = penalties_by_choice_index[i];
    }
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Indicate that all data input is complete.  Performs no mutex-locking.
/// @param[in] variable_node_indices A list of all of the absolute node indices
/// for nodes that have more than one choice, indexed by variable node index.
/// @details The base class function simply marks this object as finalized.  Should
/// be overridden, and overrides should call parent class protected_finalize().
void
ChoicePenaltySumBasedCostFunction::protected_finalize(
    std::vector< masala::base::Size > const & variable_node_indices
) {
    using masala::base::Size;
    using masala::base::Real;

    std::unordered_map< Size, Size > absolute_to_variable_index;
    for( Size i(0), imax(variable_node_indices.size()); i<imax; ++i ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
            absolute_to_variable_index.count( variable_node_indices[i] ) == 0, "protected_finalize", "The absolute index " + std::to_string( variable_node_indices[i] ) + " appears more than once in the list of absolute node indices."
        );
        absolute_to_variable_index[variable_node_indices[i]] = i;
    }

    for(
        std::unordered_map< std::pair< Size, Size >, Real, base::size_pair_hash >::const_iterator it( penalties_by_absolute_node_and_choice_.cbegin() );
        it != penalties_by_absolute_node_and_choice_.cend();
        ++it
    ) {
        Size const absindex( it->first.first );
        Size const choiceindex( it->first.second );
        Real const penalty( it->second );
        std::unordered_map< Size, Size >::const_iterator it2( absolute_to_variable_index.find( absindex ) );
        if( it2 != absolute_to_variable_index.end() ) {
            Size const varindex( it2->second );
            std::pair< Size, Size > const key( std::make_pair( varindex, choiceindex ) );
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( penalties_by_variable_node_and_choice_.count( key ) == 0, "protected_finalize", "The key (" + std::to_string( key.first ) + ", " + std::to_string( key.second ) + ") is already in the penalties_by_variable_node_and_choice_ map!" );
            penalties_by_variable_node_and_choice_[key] = penalty;
        }
    }
    penalties_by_absolute_node_and_choice_.clear(); // Save memory.

    CostFunction::protected_finalize( variable_node_indices );
}

/// @brief Override of assign_mutex_locked().  Calls parent function.
/// @details Throws if src is not a ChoicePenaltySumBasedCostFunction.
void
ChoicePenaltySumBasedCostFunction::assign_mutex_locked(
    CostFunction const & src
) {
    ChoicePenaltySumBasedCostFunction const * const src_cast_ptr( dynamic_cast< ChoicePenaltySumBasedCostFunction const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "assign_mutex_locked", "Cannot assign a ChoicePenaltySumBasedCostFunction given an input " + src.class_name() + " object!  Object types do not match." );

    penalties_by_absolute_node_and_choice_ = src_cast_ptr->penalties_by_absolute_node_and_choice_;
    penalties_by_variable_node_and_choice_ = src_cast_ptr->penalties_by_variable_node_and_choice_;
    // TODO OTHER ASSIGNMENT.

    CostFunction::assign_mutex_locked( src );
}

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
