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
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
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
/// entry in the outer vector), but must be in at least one.  The first one is used as
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

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the total number of nodes in this problem.
/// @details This is the index of the highest-numbered node that has been
/// referred to plus one (since nodes are zero-indexed), NOT the number of
/// nodes with multiple choices.
masala::numeric::Size
CostFunctionNetworkOptimizationProblem::total_nodes() const {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    if( n_choices_by_node_index_.empty() ) { return 0; }
    return n_choices_by_node_index_.rbegin()->first + 1; //Maps are sorted; last element is the biggest.
}

/// @brief Get the total number of nodes in this problem that have at least
/// two choices associated with them.
masala::numeric::Size
CostFunctionNetworkOptimizationProblem::total_variable_nodes() const {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    if( n_choices_by_node_index_.empty() ) { return 0; }
    numeric::Size accumulator(0);
    for(
        std::map< numeric::Size, numeric::Size >::const_iterator it( n_choices_by_node_index_.begin() );
        it != n_choices_by_node_index_.end();
        ++it
    ) {
        if( it->second > 1 ) {
            ++accumulator;
        }
    }
    return accumulator;
}

/// @brief Get a vector of pairs with one entry for each variable node, where the first entry in the pair indicates
/// the variable node's index, and the second indicates the number of choices at that node.
/// @note Indices in this vector are NOT node indices, since nodes with fewer than two choices are omitted.
/// The length of the vector is total_variable_nodes(), not total_nodes().  This vector is guaranteed to be sorted
/// in order of node index, though.
std::vector< std::pair< masala::numeric::Size, masala::numeric::Size > >
CostFunctionNetworkOptimizationProblem::n_choices_at_variable_nodes() const {
    using masala::numeric::Size;
    std::vector< std::pair< Size, Size > > outvec;
    outvec.reserve( n_choices_by_node_index_.size() );
    {   // Scope for mutex lock.
        std::lock_guard< std::mutex > lock( problem_mutex() );
        for( std::map< Size, Size >::const_iterator it( n_choices_by_node_index_.begin() ); it != n_choices_by_node_index_.end(); ++it ) {
            if( it->second > 1 ) {
                outvec.push_back( std::make_pair( it->first, it->second ) );
            }
        }
    }   // Unlock mutex.
    outvec.shrink_to_fit();
    std::sort(
        outvec.begin(), outvec.end(),
        [](
            std::pair< Size, Size > const & first, std::pair< Size, Size > const & second
        ){
            return first.first < second.first;
        }
    );

    return outvec;
}

/// @brief Get the product of the number of choices at each node (the total number
/// of combinatorial solutions to this cost function network problem).
/// @note Due to integer overruns, this is a floating-point number, not an integer.
masala::numeric::Real
CostFunctionNetworkOptimizationProblem::total_combinatorial_solutions() const {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    if( n_choices_by_node_index_.empty() ) { return 1.0; }
    numeric::Real product(1.0);
    for(
        std::map< numeric::Size, numeric::Size >::const_iterator it( n_choices_by_node_index_.begin() );
        it != n_choices_by_node_index_.end();
        ++it
    ) {
        if( it->second > 1 ) {
            product *= static_cast< numeric::Real >( it->second );
        }
    }
    return product;
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset all data in this object.
void
CostFunctionNetworkOptimizationProblem::reset() {
    n_choices_by_node_index_.clear();
}

/// @brief Set the (minimum) number of choices at a node.
/// @details If the number of choices has already been set to greater than the
/// specified number, this does nothing.
void
CostFunctionNetworkOptimizationProblem::set_minimum_number_of_choices_at_node(
    masala::numeric::Size const node_index,
    masala::numeric::Size const min_choice_count
) {
    std::lock_guard< std::mutex > lock( problem_mutex() );
    set_minimum_number_of_choices_at_node_mutex_locked( node_index, min_choice_count );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationProblem class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationProblem::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( problem_mutex() );

    if( api_definition() == nullptr ) {

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

        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< numeric::Size > >(
                "total_nodes", "Get the total number of nodes in this problem.  This is the index of the "
                "highest-numbered node that has been referred to plus one (since nodes are zero-indexed), "
                "NOT the number of nodes with multiple choices.",

                "total_nodes", "The total number of nodes in this problem (whether or not they have choices).",

                false, false,

                std::bind( &CostFunctionNetworkOptimizationProblem::total_nodes, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< numeric::Size > >(
                "total_variable_nodes", "Get the total number of nodes in this problem that have at least "
	            "two choices associated with them.",

                "total_variable_nodes", "The total number of nodes in this problem for which choices exist.",

                false, false,

                std::bind( &CostFunctionNetworkOptimizationProblem::total_variable_nodes, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput<
                std::vector< std::pair< numeric::Size, numeric::Size > > >
            >(
                "n_choices_at_variable_nodes", "Get a vector of pairs with one entry for each variable node, "
                "where the first entry in the pair indicates the variable node's index, and the second "
                "indicates the number of choices at that node.",
                "n_choices_at_variable_nodes", "A vector of pairs of ( node index, number of choices ) for all "
                "variable node indices (i.e. nodes with more than one choice).  Indices in this vector are NOT "
                "node indices, since nodes with fewer than two choices are omitted.  The length of the vector "
                "is total_variable_nodes(), not total_nodes().  This vector is guaranteed to be sorte in order "
                "of node index, though.", false, false,
                std::bind( &CostFunctionNetworkOptimizationProblem::n_choices_at_variable_nodes, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< numeric::Real > >(
                "total_combinatorial_solutions", "Get the product of the number of choices at each node "
                "(the total number of combinatorial solutions to this cost function network problem).  "
                "Note that due to possible integer overruns, the return value is a floating-point number, "
                "not an integer.",

                "total_combinatorial_solutions", "The total number of combinatorial solutions to this problem.",

                false, false,

                std::bind( &CostFunctionNetworkOptimizationProblem::total_combinatorial_solutions, this )
            )
        );

        // Setters:

        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Completely reset the problem description, deleting all choices for each node.",
                true, false,
                std::bind( &CostFunctionNetworkOptimizationProblem::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< numeric::Size, numeric::Size > >(
                "set_minimum_number_of_choices_at_node", "Set the (minimum) number of choices at a node.  "
                "If the number of choices has already been set to greater than the specified number, this does nothing.",

                "node_index", "The index of the node for which we're setting the minimum number of choices.",

                "min_choice_count", "The minimum number of choices at this node.  If the number of choices has already "
                "been set for this node to a value greater than this, then this does nothing.",

                false, false,

                std::bind( &CostFunctionNetworkOptimizationProblem::set_minimum_number_of_choices_at_node, this, std::placeholders::_1, std::placeholders::_2 )            )
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the (minimum) number of choices at a node.
/// @details If the number of choices has already been set to greater than the
/// specified number, this does nothing.
/// @note This version assumes that the problem mutex has already been set.
void
CostFunctionNetworkOptimizationProblem::set_minimum_number_of_choices_at_node_mutex_locked(
    masala::numeric::Size const node_index,
    masala::numeric::Size const min_choice_count
) {
    std::map< masala::numeric::Size, masala::numeric::Size >::iterator it( n_choices_by_node_index_.find(node_index) );
    if( it == n_choices_by_node_index_.end() ) {
        n_choices_by_node_index_[node_index] = min_choice_count;
    } else {
        if( it->second < min_choice_count ) {
            it->second = min_choice_count;
        }
    }
}


} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
