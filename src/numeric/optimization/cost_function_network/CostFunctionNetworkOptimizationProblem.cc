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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkOptimizationProblems.
/// @details CostFunctionNetworkOptimizationProblems define a numerical cost function network optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/error/ErrorHandling.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a fully independent copy of this object.
CostFunctionNetworkOptimizationProblemSP
CostFunctionNetworkOptimizationProblem::deep_clone() const {
    CostFunctionNetworkOptimizationProblemSP new_problem( masala::make_shared< CostFunctionNetworkOptimizationProblem >( *this ) );
    new_problem->make_independent();
    return new_problem;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
CostFunctionNetworkOptimizationProblem::make_independent() {
    masala::numeric::optimization::OptimizationProblem::make_independent();
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "CostFunctionNetworkOptimizationProblem" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outher vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunctionNetworkOptimizationProblem::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunctionNetworkOptimizationProblem" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function_network_optimization_problem", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizationProblem::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function_network_optimization_problem",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "CostFunctionNetworkOptimizationProblem".
std::string
CostFunctionNetworkOptimizationProblem::class_name() const {
    return "CostFunctionNetworkOptimizationProblem";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationProblem::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

/// @brief Reset all data in this object.
void
CostFunctionNetworkOptimizationProblem::reset() {
    n_choices_by_node_index_.clear();
    single_node_penalties_.clear();
    pairwise_node_penalties_.clear();
}

/// @brief Add onebody penalty for a choice at a node.
/// @details If the node has not yet been listed, it's added to the n_choices_by_node_index_ map.
/// If the number of choices at the node is currently less than the node index, the number of
/// choices is increased.
void
CostFunctionNetworkOptimizationProblem::set_onebody_penalty(
    masala::numeric::Size const node_index,
    masala::numeric::Size const choice_index,
    masala::numeric::Real const penalty
) {
    std::map< masala::numeric::Size, masala::numeric::Size >::iterator it( n_choices_by_node_index_.find(node_index) );
    if( it == n_choices_by_node_index_.end() ) {
        // Update the number of choices per node:
        n_choices_by_node_index_[node_index] = choice_index + 1;
        // Set the one-body penalty:
        single_node_penalties_[node_index] = std::map< masala::numeric::Size, masala::numeric::Real >{ { choice_index, penalty} };
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
CostFunctionNetworkOptimizationProblem::set_twobody_penalty(
    std::pair< masala::numeric::Size, masala::numeric::Size > const & node_indices,
    std::pair< masala::numeric::Size, masala::numeric::Size > const & choice_indices,
    masala::numeric::Real penalty
) {
    // Sanity check:
    CHECK_OR_THROW_FOR_CLASS(
        node_indices.second > node_indices.first,
        "set_twobody_penalty",
        "This function requires that the second node index be higher than the first.  Got node_index1="
        + std::to_string( node_indices.first ) + ", node_index2=" + std::to_string( node_indices.second ) + "."
    );

    // Update the number of choices per node:
    masala::numeric::Size node_index( node_indices.first );
    masala::numeric::Size choice_index( choice_indices.first );
    for( unsigned short i(0); i<2; ++i ) {
        std::map< masala::numeric::Size, masala::numeric::Size >::iterator it( n_choices_by_node_index_.find(node_index) );
        if( it == n_choices_by_node_index_.end() ) {
            n_choices_by_node_index_[node_index] = choice_index + 1;
        } else {
            if( it->second <= choice_index ) {
                it->second = choice_index + 1;
            }
        }
        node_index = node_indices.second;
        choice_index = choice_indices.second;
    }

    // Update the penalties:
    std::map< std::pair< numeric::Size, numeric::Size >, std::map< std::pair< numeric::Size, numeric::Size >, numeric::Real > >::iterator it(
        pairwise_node_penalties_.find( node_indices )
    );
    if( it == pairwise_node_penalties_.end() ) {
        pairwise_node_penalties_[node_indices] = std::map< std::pair< numeric::Size, numeric::Size >, numeric::Real >{ { choice_indices, penalty } };
    } else {
        it->second[choice_indices] = penalty;
    }
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationProblem::get_api_definition() {
    using namespace masala::base::api;

    if( api_definition() == nullptr ) {
        std::lock_guard< std::mutex > lock( problem_mutex() );

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The CostFunctionNetworkOptimizationProblem class defines a numerical cost function "
                "optimization problem.  This is the problem reduced to numbers, with no chemical classes "
                "or concepts included.",
                false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < CostFunctionNetworkOptimizationProblem > > (
                class_name(),
                "Creates an empty CostFunctionNetworkOptimizationProblem."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationProblem, CostFunctionNetworkOptimizationProblem const & > > (
                class_name(),
                "Copy constructor: copies an input CostFunctionNetworkOptimizationProblem.",
                "src", "The input CostFunctionNetworkOptimizationProblem to copy.  Unaltered by this operation."
            )
        );

        // Work functions:

        // Getters:

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Completely reset the problem description, deleting all one-node and two-node penalties and "
                "all choices for each node.", std::bind( &CostFunctionNetworkOptimizationProblem::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ThreeInput< numeric::Size, numeric::Size, numeric::Real > >(
                "set_onebody_penalty", "Set the one-node penalty for a particular choice index selected at a particular node index.",
                "node_index", "The index of the node for which we're setting a penalty.",
                "choice_index", "The index of the choice at this node for which we're setting a penalty.",
                "penalty", "The value of the penalty (or, if negative, bonus).",
                std::bind( &CostFunctionNetworkOptimizationProblem::set_onebody_penalty, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ThreeInput< std::pair< numeric::Size, numeric::Size >, std::pair< numeric::Size, numeric::Size >, numeric::Real > >(
                "set_twobody_penalty", "Set the two-node penalty for a pair of choices at a pair of nodes.",

                "node_indices", "A pair of node indices.  The lower index should be first.  (This function will "
                "throw if it is not, since it makes the choice indices ambiguous).",

                "choice_indices", "The corresponding pair of choice indices.  The first entry should be the choice "
                "index for the lower-numbered node, and the second should be the choice index for the higher-numbered "
                "node.",

                "penalty", "The value of the penalty (or, if negative, bonus).",

                std::bind( &CostFunctionNetworkOptimizationProblem::set_twobody_penalty, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 )
            )
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
