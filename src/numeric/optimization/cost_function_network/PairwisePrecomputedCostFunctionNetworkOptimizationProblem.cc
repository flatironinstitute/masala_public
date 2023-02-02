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

/// @file src/numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem.cc
/// @brief Implementation for a pure virtual base class for PairwisePrecomputedCostFunctionNetworkOptimizationProblems.
/// @details PairwisePrecomputedCostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>
#include <set>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a fully independent copy of this object.
PairwisePrecomputedCostFunctionNetworkOptimizationProblemSP
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::deep_clone() const {
    PairwisePrecomputedCostFunctionNetworkOptimizationProblemSP new_problem( masala::make_shared< PairwisePrecomputedCostFunctionNetworkOptimizationProblem >( *this ) );
    new_problem->make_independent();
    return new_problem;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::make_independent() {
    masala::numeric::optimization::OptimizationProblem::make_independent();
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "PairwisePrecomputedCostFunctionNetworkOptimizationProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
std::vector< std::string >
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function_network_optimization_problem",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "PairwisePrecomputedCostFunctionNetworkOptimizationProblem".
std::string
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::class_name() const {
    return "PairwisePrecomputedCostFunctionNetworkOptimizationProblem";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the fixed background constant offset.
masala::numeric::Real
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::background_constant_offset() const {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    return background_constant_offset_;
}

/// @brief Get the constant offset for nodes.
/// @details This is the sum of onebody energies for nodes that have exactly
/// one choice, plus the twobdy energies between those nodes.
masala::numeric::Real
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::one_choice_node_constant_offset() const {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    CHECK_OR_THROW_FOR_CLASS( finalized(), "one_choice_node_constant_offset", "The problem setup must be finalized with a call "
        "to finalize() before this function can be called."
    );
    return one_choice_node_constant_offset_;
}

/// @brief Get the total constant offset.
/// @details This is the sum of background_constant_offset() and one_choice_node_constant_offset().
masala::numeric::Real
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::total_constant_offset() const {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    CHECK_OR_THROW_FOR_CLASS( finalized(), "total_constant_offset", "The problem setup must be finalized with a call "
        "to finalize() before this function can be called."
    );
    return one_choice_node_constant_offset_ + background_constant_offset_;
}

// ALSO TODO:
// - ADD FINALIZATION STEP IN WHICH WE COMPUTE THE TWOBODY INTERACTIONS OF ALL VARIABLE NODE CHOICES WITH
// SINGLE-CHOICE NODES, TRANSFER THOSE TO THE ONEBODY ENERGIES OF THOSE VARIABLE NODE CHOICES, AND DELETE
// THE CORRESPONDING TWOBODY ENERGIES.
// - CHECK WHETHER THIS OBJECT IS FINALIZED IN SETTERS.

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset all data in this object.
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::reset() {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    PairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_reset();
}

/// @brief Indicates that problem setup is complete, locking the one- and two-node penalties
/// and making the object read-only.
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::finalize() {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    PairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_finalize();
}

/// @brief Add onebody penalty for a choice at a node.
/// @details If the node has not yet been listed, it's added to the n_choices_by_node_index_ map.
/// If the number of choices at the node is currently less than the node index, the number of
/// choices is increased.
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::set_onebody_penalty(
    masala::base::Size const node_index,
    masala::base::Size const choice_index,
    masala::numeric::Real const penalty
) {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    std::map< masala::base::Size, masala::base::Size >::iterator it( n_choices_by_node_index().find(node_index) );
    if( it == n_choices_by_node_index().end() ) {
        // Update the number of choices per node:
        n_choices_by_node_index()[node_index] = choice_index + 1;
        // Set the one-body penalty:
        single_node_penalties_[node_index] = std::map< masala::base::Size, masala::numeric::Real >{ { choice_index, penalty} };
    } else {
        // Update the number of choices per node:
        if( it->second <= choice_index ) {
            it->second = choice_index + 1;
        }
        // Set the one-body penalty:
        single_node_penalties_[node_index][choice_index] = penalty;
    }
}

/// @brief Set the two-node penalty for a particular pair of choice indices corresponding to a particular
/// pair of node indices.
/// @param[in] node_indices A pair of node indices.  The lower index should be first.  (This function will
/// throw if it is not, since it makes the choice indices ambiguous).
/// @param[in] choice_indices The corresponding pair of choice indices.  The first entry should be the choice
/// index for the lower-numbered node, and the second should be the choice index for the higher-numbered node.
/// @param[in] penalty The value of the two-node penalty (or, if negative, bonus).
/// @details If a node has not yet been listed, it's added to the n_choices_by_node_index_ map.
/// If the number of choices at the node is currently less than the node index, the number of
/// choices is increased.
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::set_twobody_penalty(
    std::pair< masala::base::Size, masala::base::Size > const & node_indices,
    std::pair< masala::base::Size, masala::base::Size > const & choice_indices,
    masala::numeric::Real penalty
) {
    std::lock_guard< std::mutex > lock( problem_mutex() );

    // Sanity check:
    CHECK_OR_THROW_FOR_CLASS(
        node_indices.second > node_indices.first,
        "set_twobody_penalty",
        "This function requires that the second node index be higher than the first.  Got node_index1="
        + std::to_string( node_indices.first ) + ", node_index2=" + std::to_string( node_indices.second ) + "."
    );

    // Update the number of choices per node:
    set_minimum_number_of_choices_at_node_mutex_locked( node_indices.first, choice_indices.first + 1 );
    set_minimum_number_of_choices_at_node_mutex_locked( node_indices.second, choice_indices.second + 1 );

    // Update the penalties:
    std::map< std::pair< base::Size, base::Size >, std::map< std::pair< base::Size, base::Size >, numeric::Real > >::iterator it(
        pairwise_node_penalties_.find( node_indices )
    );
    if( it == pairwise_node_penalties_.end() ) {
        pairwise_node_penalties_[node_indices] = std::map< std::pair< base::Size, base::Size >, numeric::Real >{ { choice_indices, penalty } };
    } else {
        it->second[choice_indices] = penalty;
    }
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the PairwisePrecomputedCostFunctionNetworkOptimizationProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::get_api_definition() {
    using namespace masala::base::api;
    
    std::lock_guard< std::mutex > lock( problem_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The PairwisePrecomputedCostFunctionNetworkOptimizationProblem class defines a numerical cost function "
                "optimization problem.  This is the problem reduced to numbers, with no chemical classes "
                "or concepts included.",
                false, false
            )
        );

        // Constructors:

        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < PairwisePrecomputedCostFunctionNetworkOptimizationProblem > > (
                class_name(),
                "Creates an empty PairwisePrecomputedCostFunctionNetworkOptimizationProblem."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < PairwisePrecomputedCostFunctionNetworkOptimizationProblem, PairwisePrecomputedCostFunctionNetworkOptimizationProblem const & > > (
                class_name(),
                "Copy constructor: copies an input PairwisePrecomputedCostFunctionNetworkOptimizationProblem.",
                "src", "The input PairwisePrecomputedCostFunctionNetworkOptimizationProblem to copy.  Unaltered by this operation."
            )
        );

        // Work functions:

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< numeric::Real > >(
                "background_constant_offset", "Get the fixed background constant offset.",
                "background_contant_offset", "A fixed, constant value added to all energies for all solutions.  Useful for parts "
                "of the problem that are not variable.", false, false,
                std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblem::background_constant_offset, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< numeric::Real > >(
                "one_choice_node_constant_offset", "Get the constant offset for nodes.  This is the sum of onebody energies "
                "for nodes that have exactly one choice, plus the twobdy energies between those nodes.  Note that this could "
                "be rather slow.",
                "one_choice_node_constant_offset", "A fixed, constant value from all nodes with exactly one choice.", false, false,
                std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblem::one_choice_node_constant_offset, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< numeric::Real > >(
                "total_constant_offset", "Get the total (background + node) constant offset.",
                "total_constant_offset", "This is the sum of background_constant_offset() and one_choice_node_constant_offset().",
                false, false,
                std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblem::total_constant_offset, this )
            )
        );

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Completely reset the problem description, deleting all one-node and two-node penalties and "
                "all choices for each node.", false, true,
                std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblem::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "finalize", "Indicates that problem setup is complete, locking the one- and two-node penalties and making the object read-only.",
                false, true,
                std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblem::finalize, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ThreeInput< base::Size, base::Size, numeric::Real > >(
                "set_onebody_penalty", "Set the one-node penalty for a particular choice index selected at a particular node index.",
                "node_index", "The index of the node for which we're setting a penalty.",
                "choice_index", "The index of the choice at this node for which we're setting a penalty.",
                "penalty", "The value of the penalty (or, if negative, bonus).", false, false,
                std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblem::set_onebody_penalty, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ThreeInput< std::pair< base::Size, base::Size >, std::pair< base::Size, base::Size >, numeric::Real > >(
                "set_twobody_penalty", "Set the two-node penalty for a pair of choices at a pair of nodes.",

                "node_indices", "A pair of node indices.  The lower index should be first.  (This function will "
                "throw if it is not, since it makes the choice indices ambiguous).",

                "choice_indices", "The corresponding pair of choice indices.  The first entry should be the choice "
                "index for the lower-numbered node, and the second should be the choice index for the higher-numbered "
                "node.",

                "penalty", "The value of the penalty (or, if negative, bonus).",

                false, false,

                std::bind( &PairwisePrecomputedCostFunctionNetworkOptimizationProblem::set_twobody_penalty, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 )
            )
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object.  Assumes mutex has been locked.
/// @details Calls parent protected_reset().
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_reset() {
    single_node_penalties_.clear();
    pairwise_node_penalties_.clear();
    background_constant_offset_ = 0.0;
    CostFunctionNetworkOptimizationProblem::protected_reset();
}

/// @brief Indicates that problem setup is complete, locking the one- and two-node penalties
/// and making the object read-only.  Must be called from a mutex-locked context.
/// @details Calls parent protected_finalize().
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::protected_finalize() {
    move_twobody_energies_involving_one_choice_nodes_to_onebody_for_variable_nodes();
    one_choice_node_constant_offset_ = compute_one_choice_node_constant_offset();
    CostFunctionNetworkOptimizationProblem::protected_finalize();
    write_to_tracer( "Finalized problem description." );
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Calculate the constant offset for nodes.
/// @details This is the sum of onebody energies for nodes that have exactly
/// one choice, plus the twobdy energies between those nodes.
/// @note This function should be called from a mutex-locked context.
masala::numeric::Real
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::compute_one_choice_node_constant_offset() {
    using masala::numeric::Real;
    using masala::base::Size;

    Real accumulator1( 0.0 ), accumulator2( 0.0 );
    std::set< Size > one_choice_nodes;

    for( std::map< Size, Size >::const_iterator it( n_choices_by_node_index().begin() );
        it != n_choices_by_node_index().end();
        ++it
    ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( one_choice_nodes.count( it->first ) == 0, "compute_one_choice_node_constant_offset", "Node " + std::to_string( it->first ) + " is already in the set of one-choice nodes!" );
        if( it->second == 1 ) {
            one_choice_nodes.insert(it->first);
        }
    }

    for( std::map< Size, std::map< Size, Real > >::const_iterator it( single_node_penalties_.begin() );
        it != single_node_penalties_.end();
        ++it
    ) {
        if( one_choice_nodes.count( it->first ) != 0 ) {
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( it->second.size() == 1, "one_choice_node_constant_offset", "Program error: multiple choice assignments found in single-node energies!" );
            accumulator1 += it->second.begin()->second; // Add onebody energies of nodes with only one choice.
        }
    }

    write_to_tracer( "Sum of one-body energies of nodes with only one choice: " + std::to_string( accumulator1 ) );

    for( std::map< std::pair< Size, Size >, std::map< std::pair< Size, Size >, Real > >::const_iterator it( pairwise_node_penalties_.begin() );
        it != pairwise_node_penalties_.end();
        ++it
    ) {
        if( single_node_penalties_.count( it->first.first ) != 0 && single_node_penalties_.count( it->first.first ) != 0 ) {
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( it->second.size() == 1, "one_choice_node_constant_offset", "Program error: multiple choice assignments found in pairwise node energies!" );
            accumulator2 += it->second.begin()->second; // Add twobody energies of pairs of nodes with only one choice.
        }
    }

    write_to_tracer( "Sum of two-body energies between nodes with only one choice: " + std::to_string( accumulator2 ) );

    Real total_accumulator( accumulator1 + accumulator2 );
    write_to_tracer( "Total node background: " + std::to_string( total_accumulator ) );

    return total_accumulator;
}


/// @brief Find all twobody energies involving one node with one choice and another node with more than
/// one choice.  Transfer all of these to the onebody energies of the variable node, deleting the corresponding
/// twobody energy.
/// @note This function should be called from a mutex-locked context.  It is called from protected_finalized().
void
PairwisePrecomputedCostFunctionNetworkOptimizationProblem::move_twobody_energies_involving_one_choice_nodes_to_onebody_for_variable_nodes() {
    using masala::numeric::Real;
    using masala::base::Size;

    std::set< Size > one_choice_nodes;
    for( std::map< Size, Size >::const_iterator it( n_choices_by_node_index().begin() );
        it != n_choices_by_node_index().end();
        ++it
    ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( one_choice_nodes.count( it->first ) == 0, "move_twobody_energies_involving_one_choice_nodes_to_onebody_for_variable_nodes", "Node " + std::to_string( it->first ) + " is already in the set of one-choice nodes!" );
        if( it->second == 1 ) {
            one_choice_nodes.insert(it->first);
        }
    }

    for( std::map< std::pair< Size, Size >, std::map< std::pair< Size, Size >, Real > >::iterator it( pairwise_node_penalties_.begin() );
        it!= pairwise_node_penalties_.end();
        // no increment here
    ) {
        std::pair< Size, Size > const & node_indices( it->first );
        Size other_node;
        bool other_node_is_first;
        if( one_choice_nodes.count( node_indices.first ) != 0 && one_choice_nodes.count( node_indices.second ) == 0 ) {
            other_node = node_indices.second;
            other_node_is_first = false;
        } else if ( one_choice_nodes.count( node_indices.second ) != 0 && one_choice_nodes.count( node_indices.first ) == 0 ) {
            other_node = node_indices.first;
            other_node_is_first = true;
        } else {
            ++it; //Increment here.
            continue; // Neither has one choice, or both have one choice.
        }

        // Ensure that there are onebody energies for the other node.
        std::map< Size, std::map< Size, Real > >::iterator it_onebodynode( single_node_penalties_.find( other_node ) );
        if( it_onebodynode == single_node_penalties_.end() ) {
            single_node_penalties_[ other_node ] = std::map< Size, Real >{};
            it_onebodynode = single_node_penalties_.find( other_node );
        }
        std::map< Size, Real > & onebody_choice_penalties_for_other( it_onebodynode->second );

        // Update the onebody energies for the multi-choice node's choices:
        for( std::map< std::pair< Size, Size >, Real >::iterator it_twobodychoices( it->second.begin() );
            it_twobodychoices != it->second.end();
            ++it_twobodychoices
        ) {
            //Sanity check:
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( (other_node_is_first ? it_twobodychoices->first.second : it_twobodychoices->first.first ) == 0,
                "move_twobody_energies_involving_one_choice_nodes_to_onebody_for_variable_nodes",
                "Program error: got additional choice for a single-choice node when iterating."
            );

            Size const choiceindex( other_node_is_first ? it_twobodychoices->first.first : it_twobodychoices->first.second );

            std::map< Size, Real >::iterator it_onebodychoice( onebody_choice_penalties_for_other.find( choiceindex ) );
            if( it_onebodychoice == onebody_choice_penalties_for_other.end() ) {
                onebody_choice_penalties_for_other[ choiceindex ] = it_twobodychoices->second;
            } else {
                it_onebodychoice->second += it_twobodychoices->second;
            }
        }

        // Delete the twobody energy and update the iterator.
        it = pairwise_node_penalties_.erase(it);
    }
}



} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
