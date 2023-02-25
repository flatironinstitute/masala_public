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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.cc
/// @brief Implementation for CostFunctionNetworkOptimizationSolutions container class.
/// @details CostFunctionNetworkOptimizationSolutionss define a numerical optimization solution produced
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ThreeInput.tmpl.hh>
#include <base/utility/container/container_util.tmpl.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// STL headers:
#include <vector>
#include <string>
#include <tuple>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a copy of this object and return an owning pointer.
OptimizationSolutionsSP
CostFunctionNetworkOptimizationSolutions::clone() const {
	return masala::make_shared< CostFunctionNetworkOptimizationSolutions >( *this );
}

/// @brief Make a fully independent copy of this object.
CostFunctionNetworkOptimizationSolutionsSP
CostFunctionNetworkOptimizationSolutions::deep_clone() const {
    CostFunctionNetworkOptimizationSolutionsSP new_object( std::static_pointer_cast< CostFunctionNetworkOptimizationSolutions >( this->clone() ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
CostFunctionNetworkOptimizationSolutions::make_independent() {
    masala::numeric::optimization::OptimizationSolutions::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { { "CostFunctionNetworkOptimizationSolutions" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunctionNetworkOptimizationSolutions::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunctionNetworkOptimizationSolutions" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "cost_function_network_optimization_solutions", "optimization_solutions", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizationSolutions::get_keywords() const {
	std::vector< std::string > outvec( masala::numeric::optimization::OptimizationSolutions::get_keywords() );
    outvec.push_back( "cost_function_network_optimization_solutions" );
    return outvec;
}

/// @brief Get the class name.
/// @returns "CostFunctionNetworkOptimizationSolutions".
std::string
CostFunctionNetworkOptimizationSolutions::class_name() const {
    return "CostFunctionNetworkOptimizationSolutions";
}

/// @brief Get the class namespace.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationSolutions::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolutions class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationSolutions::get_api_definition() {
    using namespace masala::base::api;
    using masala::base::Size;
    using masala::base::Real;

    std::lock_guard< std::mutex > lock( solutions_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The CostFunctionNetworkOptimizationSolutions class defines a container for cost function network "
                "numerical optimization solutions.  These are the solutions reduced to numbers, with no chemical "
                "classes or concepts included.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < CostFunctionNetworkOptimizationSolutions > > (
                class_name(),
                "Creates an empty CostFunctionNetworkOptimizationSolutions container."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationSolutions, CostFunctionNetworkOptimizationSolutions const & > > (
                class_name(),
                "Copy constructor: copies an input CostFunctionNetworkOptimizationSolutions container.",
                "src", "The input CostFunctionNetworkOptimizationSolutions container object to copy.  Unaltered by this operation."
            )
        );

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "reset", "Resets the container, deleting all contained solutions.",
                false, true, std::bind( &CostFunctionNetworkOptimizationSolutions::reset, this )
            )
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationSolutionSP > >(
                "add_optimization_solution",
                "Add a cost function network optimization solution to the list of optimization solutions that this container contains.",
                "solution_in", "The cost function network optimization solution that we are adding to the container.  Throws if this is "
                "not a cost function network optimization solution.",
                false, true, std::bind( &CostFunctionNetworkOptimizationSolutions::add_optimization_solution, this, std::placeholders::_1 )
            )
        );
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< masala::base::Size > >(
				"remove_optimization_solution", "Remove an optimization solution, by solution index.",
				"solution_index", "The index of the solution to remove.  Must be in range; throws otherwise.",
				false, false,
				std::bind( &OptimizationSolutions::remove_optimization_solution, this, std::placeholders::_1 )
			)
		);

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_OneInput< masala::base::Real, masala::base::Size > >(
                "solution_score", "Get the score of the nth solution.",
                "solution_index", "The index of the solution whose score we are retrieving.  This "
	            " will throw if this index is not in range.",
                "solution_score", "The score associated with this solution.",
                false, false, std::bind( &CostFunctionNetworkOptimizationSolutions::solution_score, this, std::placeholders::_1 )
            )
        );

        // Work functions:
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< bool, masala::base::Size, std::vector< masala::base::Size > const & > >(
                "solution_matches", "Does a given solution's solution vector match a solution vector "
                "to which we are comparing?",
                true, false, false, false,
                "solution_index", "The index of the solution to remove.  Must be in range; throws otherwise.",
                "comparison_solution_vector", "The vector of solutions to which we are comparing.  This "
                "is one choice index per variable node.  (There should not be entries for fixed nodes.)",
                "solutions_match", "True if the solutions match; false otherwise.",
                std::bind( &CostFunctionNetworkOptimizationSolutions::solution_matches, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_ThreeInput< void, std::vector< std::tuple< std::vector< Size >, Real, Size > > const &, Size, CostFunctionNetworkOptimizationProblemCSP > (
                "merge_in_lowest_scoring_solutions", "Given another collection of solutions, merge-sort the solutions "
	            "and keep up to the lowest-scoring N.  Note: if both sets contain the same solution, the number of times "
                "that solution was produced will be incremented in this set by the number of times it was produced "
                "in the other set.",
                false, false, false, false,
                "other_solutions", "The other solutions, represented as a vector of "
				"tuples of (solution vector for variable positions only, solution score, "
				"solution count).  Unchanged by this operation.",
                "max_solutions_to_store_total", "The maximum number of solutions that we "
                "want to be storing at the end of this operation.  The lowest-scoring solutions "
                "from the union of both sets are stored, and any solutions past the lowest N are "
                "discarded.",
				"problem", "The problem for all of these solutions.",
                "void", "Returns nothing.",
                std::bind( &CostFunctionNetworkOptimizationSolutions::merge_in_lowest_scoring_solutions, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 )
            )
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Reset this object, clearing its solution list.
void
CostFunctionNetworkOptimizationSolutions::reset() {
    masala::numeric::optimization::OptimizationSolutions::reset();
}

/// @brief Add an optimization solution to the list of optimization solutions
/// stored in this container.
/// @details Derived classes should override this to check the type of the
/// optimization solution stored.
void
CostFunctionNetworkOptimizationSolutions::add_optimization_solution(
    OptimizationSolutionSP solution_in
) {
    CHECK_OR_THROW_FOR_CLASS(
        std::dynamic_pointer_cast< CostFunctionNetworkOptimizationSolution >( solution_in ) != nullptr,
        "add_optimization_solution", "Only a CostFunctionNetworkOptimizationSolution can be added "
        "to a CostFunctionNetworkOptimizationSolutions container."
    );
    masala::numeric::optimization::OptimizationSolutions::add_optimization_solution( solution_in );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the score of the nth solution.
/// @param solution_index The index of the solution whose score we are retrieving.  This
/// will throw if this index is not in range.
masala::base::Real
CostFunctionNetworkOptimizationSolutions::solution_score(
    masala::base::Size const solution_index
) const {
    std::lock_guard< std::mutex > lock( solutions_mutex() );
    CHECK_OR_THROW_FOR_CLASS( solution_index < optimization_solutions().size(), "solution_score",
        "Solution index out of range!  There are " + std::to_string( optimization_solutions().size() ) +
        " solutions stored in this object, yet I was asked to access solution " +
        std::to_string(solution_index) + "."
    );
    return optimization_solutions()[solution_index]->solution_score();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Does a given solution's solution vector match a solution vector to which we
/// are comparing?
/// @param solution_index The index of the solution.  Must be within range, or this will throw.
/// @param comparison_solution_vector The vector of solutions to which we are comparing.  This
/// is one choice index per variable node.  (There should not be entries for fixed nodes.)
/// @return True if the solution vector matches, false otherwise.
bool
CostFunctionNetworkOptimizationSolutions::solution_matches(
    masala::base::Size const solution_index,
    std::vector< masala::base::Size > const & comparison_solution_vector
) const {
    std::lock_guard< std::mutex > lock( solutions_mutex() );
    CHECK_OR_THROW_FOR_CLASS( solution_index < optimization_solutions().size(), "solution_matches",
        "Solution index out of range!  There are " + std::to_string( optimization_solutions().size() ) +
        " solutions stored in this object, yet I was asked to access solution " +
        std::to_string(solution_index) + "."
    );
    return std::static_pointer_cast< CostFunctionNetworkOptimizationSolution const >( optimization_solutions()[solution_index] )->operator==( comparison_solution_vector );
}

/// @brief Given another collection of solutions, merge-sort the solutions
/// and keep up to the lowest-scoring N.
/// @param[in] other_solutions The other solutions, represented as a vector of
/// tuples of (solution vector for variable positions only, solution score,
/// solution count).
/// @param[in] max_solutions_to_store_total The maximum number of solutions that we
/// want to be storing at the end of this operation.  The lowest-scoring solutions
/// from the union of both sets are stored, and any solutions past the lowest N are
/// discarded.
/// @param[in] problem The problem for all of these solutions.
/// @note If both sets contain the same solution, the number of times that solution
/// was produced will be incremented in this set by the number of times it was produced
/// in the other set.
void
CostFunctionNetworkOptimizationSolutions::merge_in_lowest_scoring_solutions(
    std::vector< std::tuple< std::vector< masala::base::Size >, masala::base::Real, masala::base::Size > > const & other_solutions,
    masala::base::Size const max_solutions_to_store_total,
    CostFunctionNetworkOptimizationProblemCSP problem
) {
    using masala::base::Size;
    using masala::base::Real;
    std::lock_guard< std::mutex > lock( solutions_mutex() );
    
    std::vector< std::tuple< Size, bool, Real > > solution_summaries; //Store solution index, whether it is in this (true) or other (false), and the score.

    solution_summaries.reserve( optimization_solutions().size() + other_solutions.size() );
    for( Size i(0), imax(optimization_solutions().size()); i<imax; ++i ) {
        // Add solutions from THIS container.
        solution_summaries.push_back( std::make_tuple( i, true, optimization_solutions()[i]->solution_score() ) );
    }
    for( Size i(0), imax(other_solutions.size()); i<imax; ++i ) {
        // Add solutions from THAT container.  Skip any that are already in this container, though.
        std::tuple< std::vector< Size >, Real, Size > const & other_solution( other_solutions[i] );
        std::vector< Size > const & other_solution_vec( std::get<0>( other_solution ) );
        bool found(false);
        for( Size j(0), jmax(optimization_solutions().size()); j<jmax; ++j ) {
            CostFunctionNetworkOptimizationSolutionSP this_solution( std::static_pointer_cast< CostFunctionNetworkOptimizationSolution >( optimization_solutions()[j] ) );
            if( this_solution->operator==( other_solution_vec ) ) {
                // If the solution is already in this container, increment the number times it was produced.
                this_solution->increment_n_times_solution_was_produced( std::get<2>( other_solution ) );
                found = true;
                break;
            }
        }
        if( !found ) {
            solution_summaries.push_back( std::make_tuple( i, false, std::get<1>( other_solution ) ) );
        }
    }
    
    // Sort the vector of summaries by score:
    std::sort(
        solution_summaries.begin(), solution_summaries.end(),
        [](
            std::tuple< Size, bool, Real > const & a,
            std::tuple< Size, bool, Real > const & b
        ){
            return std::get<2>(a) < std::get<2>(b);
        }
    );

    // Take the first N solutions and make them the new solution vector:
    std::vector< masala::numeric::optimization::OptimizationSolutionSP > new_solutions;
    Size const nsol( std::min( solution_summaries.size(), max_solutions_to_store_total ) );
    new_solutions.reserve( nsol );
    for( Size i(0); i<nsol; ++i ) {
        if( std::get<1>(solution_summaries[i]) ) {
            // In THIS object.
            new_solutions.push_back( optimization_solutions()[ std::get<0>( solution_summaries[i] ) ] );
        } else {
            // In THAT object.
            std::tuple< std::vector< Size >, Real, Size > const & other_solution( other_solutions[ std::get<0>( solution_summaries[i] ) ] );
            std::vector< Size > const & other_solution_vec( std::get<0>( other_solution ) );
            Real const other_solution_score( std::get<1>(other_solution) );
            CostFunctionNetworkOptimizationSolutionSP new_solution( masala::make_shared< CostFunctionNetworkOptimizationSolution >( problem, other_solution_vec, other_solution_score ) );
            new_solution->set_n_times_solution_was_produced( std::get<2>(other_solution) );
            new_solutions.push_back( new_solution );
        }
    }
    optimization_solutions() = new_solutions;
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
