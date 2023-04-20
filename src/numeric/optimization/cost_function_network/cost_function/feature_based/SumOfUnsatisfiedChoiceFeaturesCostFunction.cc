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

/// @file src/numeric/optimization/cost_function_network/cost_function/feature_based/SumOfUnsatisfiedChoiceFeaturesCostFunction.cc
/// @brief Implementation for a pure virtual base class for SumOfUnsatisfiedChoiceFeaturesCostFunctions.
/// @details SumOfUnsatisfiedChoiceFeaturesCostFunctions define a penalty function which is based on the following:
/// - One or more features are defined for each choice at each node.  (A feature could be a hydrogen bond
/// donor or acceptor, for instance, in a packing problem)
/// - Each feature has an expected minimum and maximum number of connections that can be set.
/// - For each pair of choices, the features that are connected can be set.
/// - At calculation time, the number of unsatisfied features (total features minus features
/// satisfied by connections) is returned.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/SumOfUnsatisfiedChoiceFeaturesCostFunction.hh>

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/error/ErrorHandling.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {
namespace feature_based {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.
template< typename T >
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::SumOfUnsatisfiedChoiceFeaturesCostFunction(
    SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const & src
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
SumOfUnsatisfiedChoiceFeaturesCostFunction<T> &
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::operator=(
    SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const & src
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
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::get_categories() const {
	return CostFunction::get_categories();
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric", "unsatisfied_choice_feature_sum_based" }
template< typename T >
std::vector< std::string >
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::get_keywords() const {
	std::vector< std::string > outvec( CostFunction::get_keywords() );
    outvec.push_back( "unsatisfied_choice_feature_sum_based" );
    return outvec;
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add a choice feature for a set of nodes, indexed by absolute node index.
/// @details This can only be called prior to object finalization.
///
/// @param[in] absolute_node_index The index of this node (absolute).
/// @param[in] choice_index The index of this choice.
/// @param[in] min_connections_to_satisfy_feature The minimum number of connections that
/// this feature must make in order to be satisfied.
/// @param[in] max_connections_to_satisfy_feature The maximum number of connections that
/// this feature must make in order to be satisfied.
/// @param[in] feature_connection_offset The number of connections that this feature always
/// makes (e.g. to background, or to itself).
///
/// @returns The index of the newly-added choice feature in the vector of choice features for
/// this position.
template< typename T >
masala::base::Size
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::add_choice_feature_by_absolute_node_index(
    masala::base::Size const absolute_node_index,
    masala::base::Size const choice_index,
    masala::base::Size const min_connections_to_satisfy_feature,
    masala::base::Size const max_connections_to_satisfy_feature,
    masala::base::Size const feature_connection_offset
) {
    using masala::base::Size;
    std::lock_guard< std::mutex > lock( mutex() );
    CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "add_choice_feature_by_absolute_node_index",
        "Choice features cannot be added after this object has already been finalized!"
    );
    std::pair< Size, Size > key( absolute_node_index, choice_index );
    std::unordered_map<
	    std::pair< masala::base::Size, masala::base::Size >,
		std::vector< ChoiceFeatureCSP >,
		masala::base::size_pair_hash
	>::iterator it(
        choice_features_by_absolute_node_and_choice_.find( key )
    );
    if( it == choice_features_by_absolute_node_and_choice_.end() ) {
        choice_features_by_absolute_node_and_choice_[key] = std::vector< ChoiceFeature >{
            masala::make_shared< ChoiceFeature >(
                min_connections_to_satisfy_feature,
                max_connections_to_satisfy_feature,
                feature_connection_offset
            )
        };
        return 0;
    } else {
        it->second.push_back(
            masala::make_shared< ChoiceFeature >(
                min_connections_to_satisfy_feature,
                max_connections_to_satisfy_feature,
                feature_connection_offset
            )
        );
        return it->second.size() - 1;
    }
    return 0; // Keep older compilers happy, though we never reach here.
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given a selection of choices at variable nodes, compute the cost function.
/// @note No mutex-locking is performed!  Also note that this version does not multiply the
/// result by the weight, since derived classes will likely do this after applying a nonlinear
/// function.
template< typename T >
masala::base::Real
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::compute_cost_function(
    std::vector< masala::base::Size > const & candidate_solution
) const {
    TODO TODO TODO
    - Outer iteration over all selected ChoiceFeatures at variable positions, and all fixed Choice Features at non-variable.
    - Inner iteration over same (to lower indices).
    - For each choice feature, accumulate number of connections.
    - After loops, count number of features that are satisfied.
    - Return count.
}

/// @brief Given an old selection of choices at variable nodes and a new selection,
/// compute the cost function difference.
/// @note No mutex-locking is performed!  Also note that this version does not multiply the
/// result by the weight, since derived classes will likely do this after applying a nonlinear
/// function.
template< typename T >
masala::base::Real
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::compute_cost_function_difference(
    std::vector< masala::base::Size > const & candidate_solution_old,
    std::vector< masala::base::Size > const & candidate_solution_new
) const {
    TODO TODO TODO
}

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
template< typename T >
void
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::protected_finalize(
    std::vector< masala::base::Size > const & variable_node_indices
) {
    TODO TODO TODO
    - Copy data from choice_features_by_absolute_node_and_choice_ to choice_features_by_variable_node_and_choice_.
    - Identify ChoiceFeatures that are now part of fixed background, and store these in a list.

    CostFunction::protected_finalize( variable_node_indices );
}

/// @brief Override of assign_mutex_locked().  Calls parent function.
/// @details Throws if src is not a SumOfUnsatisfiedChoiceFeaturesCostFunction.
template< typename T >
void
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::assign_mutex_locked(
    CostFunction const & src
) {
    SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const * const src_cast_ptr( dynamic_cast< SumOfUnsatisfiedChoiceFeaturesCostFunction<T> const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "assign_mutex_locked", "Cannot assign a SumOfUnsatisfiedChoiceFeaturesCostFunction given an input " + src.class_name() + " object!  Object types do not match." );

    TODO TODO TODO

    CostFunction::assign_mutex_locked( src );
}

/// @brief Make this object fully independent.  Assumes mutex was already locked.
/// Should be called by overrides.
template< typename T >
void
SumOfUnsatisfiedChoiceFeaturesCostFunction<T>::make_independent_mutex_locked() {
    // GNDN
    CostFunction::make_independent_mutex_locked();
}

template class SumOfUnsatisfiedChoiceFeaturesCostFunction< masala::base::Real >;
template class SumOfUnsatisfiedChoiceFeaturesCostFunction< signed long int >;

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
