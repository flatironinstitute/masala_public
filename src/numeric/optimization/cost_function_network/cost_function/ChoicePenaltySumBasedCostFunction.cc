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
template< typename T >
ChoicePenaltySumBasedCostFunction<T>::ChoicePenaltySumBasedCostFunction(
    ChoicePenaltySumBasedCostFunction<T> const & src
) :
    CostFunction( src )
{
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    assign_mutex_locked( src );
}

// @brief Assignment operator.
template< typename T >
ChoicePenaltySumBasedCostFunction<T> &
ChoicePenaltySumBasedCostFunction<T>::operator=(
    ChoicePenaltySumBasedCostFunction<T> const & src
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
template< typename T >
std::vector< std::vector< std::string > >
ChoicePenaltySumBasedCostFunction<T>::get_categories() const {
	return CostFunction::get_categories();
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric", "choice_penalty_sum_based" }
template< typename T >
std::vector< std::string >
ChoicePenaltySumBasedCostFunction<T>::get_keywords() const {
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
/// @param[in] absolute_node_index The absolute index of the node for which we're setting penalties.
/// @param[in] penalties_by_choice_index The penalties for all of the choices, indexed by choice index.
/// @note Only in debug mode do we check that these have not already been set.
template< typename T >
void
ChoicePenaltySumBasedCostFunction<T>::set_penalties_for_all_choices_at_node(
    masala::base::Size const absolute_node_index,
    std::vector< T > const & penalties_by_choice_index
) {
    using masala::base::Size;

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
        //write_to_tracer( "Set penalty for node " + std::to_string(absolute_node_index) + " choice " + std::to_string(i) + " to " + std::to_string(penalties_by_choice_index[i]) );
    }
    //write_to_tracer( "Set penalties for node " + std::to_string(absolute_node_index) + "'s " + std::to_string(penalties_by_choice_index.size()) + " choices." );
}

/// @brief Set the penalty for a choice at a node.
/// @param[in] absolute_node_index The absolute index of the node for which we're setting penalties.
/// @param[in] choice_index The index of the choice at this node for which we're setting penalties.
/// @param[in] penalty_value The penalty value.
/// @note Only in debug mode do we check that these have not already been set.
template< typename T >
void
ChoicePenaltySumBasedCostFunction<T>::set_penalty_for_choice_at_node(
    masala::base::Size const absolute_node_index,
    masala::base::Size const choice_index,
    T const penalty_value
) {
    using masala::base::Size;
    std::lock_guard< std::mutex > lock( mutex() );
    CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "set_penalty_for_choice_at_node",
        "This function cannot be called after the " + class_name() + " has been finalized."
    );

#ifndef NDEBUG
    // Debug-mode checks:
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        penalties_by_absolute_node_and_choice_.count( std::make_pair( absolute_node_index, choice_index ) ) == 0,
        "set_penalty_for_choice_at_node",
        "The penalty for node " + std::to_string( absolute_node_index ) + ", choice "
        + std::to_string( choice_index ) + " has already been set."
    );
#endif

    penalties_by_absolute_node_and_choice_[ std::make_pair( absolute_node_index, choice_index ) ] = penalty_value;
}

/// @brief Set the constant offset.
template< typename T >
void
ChoicePenaltySumBasedCostFunction<T>::set_constant_offset(
    T const constant_offset
) {
    std::lock_guard< std::mutex > lock( mutex() );
    CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "set_constant_offset",
        "This function cannot be called after the " + class_name() + " has been finalized."
    );
    write_to_tracer( "Set constant offset to " + std::to_string( constant_offset ) + "." );
    constant_offset_ = constant_offset;
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given a selection of choices at variable nodes, compute the cost function.
/// @details This version just computes the sum of the penalties of the selected choices.
/// @note No mutex-locking is performed!
template< typename T >
masala::base::Real
ChoicePenaltySumBasedCostFunction<T>::compute_cost_function(
    std::vector< masala::base::Size > const & candidate_solution
) const {
    return protected_weight() * static_cast< masala::base::Real >( protected_compute_cost_function_no_weight( candidate_solution ) );
}

/// @brief Given an old selection of choices at variable nodes and a new selection,
/// compute the cost function difference.
/// @details This version just computes the difference of the sums of the penalties of the
/// selected choices.  It isn't useful for much, and should probably not be called from other
/// code.
/// @note No mutex-locking is performed!
template< typename T >
masala::base::Real
ChoicePenaltySumBasedCostFunction<T>::compute_cost_function_difference(
    std::vector< masala::base::Size > const & candidate_solution_old,
    std::vector< masala::base::Size > const & candidate_solution_new
) const {
    using masala::base::Size;

    CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "compute_cost_function_difference", "The " + class_name()
        + " must be finalized before this function is called!"
    );
    Size const nentries_old( candidate_solution_old.size() );
    Size const nentries_new( candidate_solution_new.size() );
    CHECK_OR_THROW_FOR_CLASS( nentries_old == n_variable_positions_, "compute_cost_function", "Expected "
        "a vector of " + std::to_string( n_variable_positions_ ) + " choices for " + std::to_string( n_variable_positions_ )
        + " variable positions in the old candidate solution, but got " + std::to_string( nentries_old ) + "!" 
    );
    CHECK_OR_THROW_FOR_CLASS( nentries_new == n_variable_positions_, "compute_cost_function", "Expected "
        "a vector of " + std::to_string( n_variable_positions_ ) + " choices for " + std::to_string( n_variable_positions_ )
        + " variable positions in the new candidate solution, but got " + std::to_string( nentries_new ) + "!" 
    );

    T sum_new( 0 ), sum_old( 0 ); // We ignore the constant offset, since it won't appear in the difference.

    for( Size i(0); i<nentries_old; ++i ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( i < penalties_by_variable_node_and_choice_.size(),
            "compute_cost_function_difference", "Program error in accumulating choice penalties."
        );
        if( candidate_solution_new[i] != candidate_solution_old[i] ) {
            std::vector< T > const & vec( penalties_by_variable_node_and_choice_[i] );
            if( candidate_solution_old[i] < vec.size() ) {
                sum_old += vec[candidate_solution_old[i]];
            }
            if( candidate_solution_new[i] < vec.size() ) {
                sum_new += vec[candidate_solution_new[i]];
            }
        }
    }
    return protected_weight() * ( static_cast< masala::base::Real >( sum_new ) - static_cast< masala::base::Real >( sum_old ) );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given a selection of choices at variable nodes, compute the cost function.
/// @details This version just computes the sum of the penalties of the selected choices.
/// @note No mutex-locking is performed!  Also note that this version does not multiply the
/// result by the weight, since derived classes will likely do this after applying a nonlinear
/// function.
template< typename T >
T
ChoicePenaltySumBasedCostFunction<T>::protected_compute_cost_function_no_weight(
    std::vector< masala::base::Size > const & candidate_solution
) const {
    using masala::base::Size;

    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( protected_finalized(), "compute_cost_function", "The " + class_name()
        + " must be finalized before this function is called!"
    );
    Size const nentries( candidate_solution.size() );
    CHECK_OR_THROW_FOR_CLASS( nentries == n_variable_positions_, "compute_cost_function", "Expected "
        "a vector of " + std::to_string( n_variable_positions_ ) + " choices for " + std::to_string( n_variable_positions_ )
        + " variable positions, but got " + std::to_string( nentries ) + "!" 
    );
    T accumulator( constant_offset_ );
    for( Size i(0); i<nentries; ++i ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( i < penalties_by_variable_node_and_choice_.size(),
            "protected_compute_cost_function_no_weight", "Program error: penalties_by_variable_node_and_choice_ too small!"
        );
        std::vector< T > const & vec( penalties_by_variable_node_and_choice_[i] );
        if( candidate_solution[i] < vec.size() ) {
            accumulator += vec[candidate_solution[i]];
        }
    }
    return accumulator;
}

/// @brief Indicate that all data input is complete.  Performs no mutex-locking.
/// @param[in] variable_node_indices A list of all of the absolute node indices
/// for nodes that have more than one choice, indexed by variable node index.
/// @details The base class function simply marks this object as finalized.  Should
/// be overridden, and overrides should call parent class protected_finalize().
template< typename T >
void
ChoicePenaltySumBasedCostFunction<T>::protected_finalize(
    std::vector< masala::base::Size > const & variable_node_indices
) {
    using masala::base::Size;

    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( penalties_by_variable_node_and_choice_.empty(),
        "protected_finalize", "Program error: the penalties_by_variable_node_and_choice_ vector isn't empty!"
    );

    std::unordered_map< Size, Size > absolute_to_variable_index;
    for( Size i(0), imax(variable_node_indices.size()); i<imax; ++i ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
            absolute_to_variable_index.count( variable_node_indices[i] ) == 0, "protected_finalize", "The absolute index " + std::to_string( variable_node_indices[i] ) + " appears more than once in the list of absolute node indices."
        );
        absolute_to_variable_index[variable_node_indices[i]] = i;
    }

    n_variable_positions_ = variable_node_indices.size();
    penalties_by_variable_node_and_choice_.resize( n_variable_positions_ );

    for(
        typename std::unordered_map< std::pair< Size, Size >, T, base::size_pair_hash >::const_iterator it( penalties_by_absolute_node_and_choice_.cbegin() );
        it != penalties_by_absolute_node_and_choice_.cend();
        ++it
    ) {
        Size const absindex( it->first.first );
        Size const choiceindex( it->first.second );
        T const penalty( it->second );
        std::unordered_map< Size, Size >::const_iterator it2( absolute_to_variable_index.find( absindex ) );
        if( it2 != absolute_to_variable_index.end() ) {
            Size const varindex( it2->second );
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
                varindex < n_variable_positions_, "protected_finalize", "Program error: varindex out of range!"
            );
            std::vector< T > & vec( penalties_by_variable_node_and_choice_[varindex] );
            if( vec.size() <= choiceindex ) {
                vec.resize( choiceindex+1, T(0) );
            }
            vec[choiceindex] = penalty;
            //write_to_tracer( "<" + std::to_string( varindex ) + "," + std::to_string( choiceindex ) + ">=" + std::to_string(penalty) ); //DELETE ME
        } else {
#ifndef NDEBUG
            //Check that we have only one choice at this node.
            Size tempcounter(0);
            for(
                typename std::unordered_map< std::pair< Size, Size >, T, base::size_pair_hash >::const_iterator it3( penalties_by_absolute_node_and_choice_.cbegin() );
                it3 != penalties_by_absolute_node_and_choice_.cend();
                ++it3
            ) {
                if( it3->first.first == absindex ) {
                    ++tempcounter;
                }
            }
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( tempcounter == 1, "protected_finalize", "Expected exactly 1 choice "
                "for node " + std::to_string( absindex ) + ", but got " + std::to_string( tempcounter ) + "!"
            );
#endif
            constant_offset_ += penalty;
            write_to_tracer( "Adjusting constant offset for penalty of " + std::to_string( penalty )
                + " at constant node " + std::to_string( absindex ) + ".  Offset is now "
                + std::to_string( constant_offset_ ) + "."
            );
        }
    }
    penalties_by_absolute_node_and_choice_.clear(); // Save memory.

    CostFunction::protected_finalize( variable_node_indices );
}

/// @brief Override of assign_mutex_locked().  Calls parent function.
/// @details Throws if src is not a ChoicePenaltySumBasedCostFunction.
template< typename T >
void
ChoicePenaltySumBasedCostFunction<T>::assign_mutex_locked(
    CostFunction const & src
) {
    ChoicePenaltySumBasedCostFunction<T> const * const src_cast_ptr( dynamic_cast< ChoicePenaltySumBasedCostFunction<T> const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "assign_mutex_locked", "Cannot assign a ChoicePenaltySumBasedCostFunction given an input " + src.class_name() + " object!  Object types do not match." );

    penalties_by_absolute_node_and_choice_ = src_cast_ptr->penalties_by_absolute_node_and_choice_;
    penalties_by_variable_node_and_choice_ = src_cast_ptr->penalties_by_variable_node_and_choice_;
    // TODO OTHER ASSIGNMENT.

    CostFunction::assign_mutex_locked( src );
}

/// @brief Make this object fully independent.  Assumes mutex was already locked.
/// Should be called by overrides.
template< typename T >
void
ChoicePenaltySumBasedCostFunction<T>::make_independent_mutex_locked() {
    // GNDN
    CostFunction::make_independent_mutex_locked();
}

template class ChoicePenaltySumBasedCostFunction< masala::base::Real >;
template class ChoicePenaltySumBasedCostFunction< signed long int >;

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
