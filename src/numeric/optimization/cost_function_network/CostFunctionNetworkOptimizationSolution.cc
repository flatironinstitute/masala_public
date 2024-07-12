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

/// @file src/numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkOptimizationSolutions.
/// @details A CostFunctionNetworkOptimizationSolution contains the solution to a particular
/// CostFunctionNetworkOptimizationProblem, after it is solved by a suitable CostFunctionNetworkOptimizer.
/// It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_FiveInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Constructor that initializes from the problem description.
/// @details The problem definition is stored directly, not copied.  The solution is represented
/// as a vector of choice indices, one per variable position (i.e. per position with more than one
/// choice) in order of indices of variable positions.
CostFunctionNetworkOptimizationSolution::CostFunctionNetworkOptimizationSolution(
    CostFunctionNetworkOptimizationProblemCSP const & problem_in,
    std::vector< masala::base::Size > const & solution_vector_in,
    masala::base::Real const solution_score,
    masala::base::Real const solution_score_data_representation_approximation,
    masala::base::Real const solution_score_solver_approximation
) :
    masala::numeric::optimization::OptimizationSolution()
{
    protected_problem() = problem_in;
    protected_set_solution_vector( solution_vector_in );
    protected_solution_score() = solution_score;
    protected_solution_score_data_representation_approximation() = solution_score_data_representation_approximation;
    protected_solution_score_solver_approximation() = solution_score_solver_approximation;
}

/// @brief Make a copy of this object.
masala::numeric::optimization::OptimizationSolutionSP
CostFunctionNetworkOptimizationSolution::clone() const {
    return masala::make_shared< CostFunctionNetworkOptimizationSolution >( *this );
}

/// @brief Make a fully independent copy of this object.
CostFunctionNetworkOptimizationSolutionSP
CostFunctionNetworkOptimizationSolution::deep_clone() const {
    CostFunctionNetworkOptimizationSolutionSP new_solution( std::static_pointer_cast< CostFunctionNetworkOptimizationSolution >( this->clone() ) );
    new_solution->make_independent();
    return new_solution;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
CostFunctionNetworkOptimizationSolution::make_independent() {
    masala::numeric::optimization::OptimizationSolution::make_independent();
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "CostFunctionNetworkOptimizationSolution" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunctionNetworkOptimizationSolution::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunctionNetworkOptimizationSolution" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solution", "cost_function_network_optimization_solution", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizationSolution::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solution",
        "cost_function_network_optimization_solution",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "CostFunctionNetworkOptimizationSolution".
std::string
CostFunctionNetworkOptimizationSolution::class_name() const {
    return "CostFunctionNetworkOptimizationSolution";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionNetworkOptimizationSolution::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the CostFunctionNetworkOptimizationSolution class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunctionNetworkOptimizationSolution::get_api_definition() {
    using namespace masala::base::api;
    using base::Real;
    using base::Size;

    std::lock_guard< std::mutex > lock( solution_mutex() );

    if( api_definition() == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The CostFunctionNetworkOptimizationSolution class stores the solution to a numerical "
                "cost function optimization problem.  This is the problem reduced to numbers, with no "
                "chemical classes or concepts included.",
                false, false
            )
        );

        // Constructors:

        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < CostFunctionNetworkOptimizationSolution > > (
                class_name(),
                "Creates an empty CostFunctionNetworkOptimizationSolution."
            )
        );
        api_def->add_constructor(
            masala::make_shared<
                constructor::MasalaObjectAPIConstructorDefinition_FiveInput <
                    CostFunctionNetworkOptimizationSolution,
                    CostFunctionNetworkOptimizationProblemCSP,
                    std::vector< masala::base::Size > const &,
                    Real, Real, Real
                >
            > (
                class_name(),
                "Initialization constructor: initialize the solution from the problem definition.  (The problem definition "
                "stored directly -- i.e. not deep-cloned -- for future reference).",
                "problem_in", "The problem definition.  Unaltered by this operation.",
                "solution_vector_in", "The solution, expressed as a vector of node choice indices, with one entry for each node that has at least two choices.",
                "solution_score_in", "The solution score.  This is the actual, non-approximate solution score.",
                "solution_score_data_representation_approximation_in", "The solution score given the data representation.  Data representations may use exact solution scores, or may make approximations for speed.",
                "solution_score_solver_approximation_in", "The solution score returned by the solver.  This may be exact, or may be approximate both due to the data representation used and due to reduced precision of the solver."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < CostFunctionNetworkOptimizationSolution, CostFunctionNetworkOptimizationSolution const & > > (
                class_name(),
                "Copy constructor: copies an input CostFunctionNetworkOptimizationSolution.",
                "src", "The input CostFunctionNetworkOptimizationSolution to copy.  Unaltered by this operation."
            )
        );

        // Work functions:
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput <bool, std::vector< base::Size > const & > > (
                "operator==", "Compare this solution to the solution vector of another solution.  Return true if they match, false otherwise.",
                true, false, false, false,
                "other_solution_vector", "The solution vector to which we are comparing.  Unaltered by this operation.",
                "vectors_match", "True of the stored solution vector matches the other solution vector; false otherwise.",
                std::bind( &CostFunctionNetworkOptimizationSolution::operator==, this, std::placeholders::_1 )
            )
        );

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Real > >(
                "solution_score", "Get the score associated with this CFN solution.  This is the exact "
				"score, recomputed once the solution has been produced.",
                "solution_score", "The exact score associated with this CFN solution.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::solution_score, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Real > >(
                "solution_score_data_representation_approximation", "Get the approximate score associated "
				"with this CFN solution, given the CFN data representation.  Certain data representations may use "
				"reduced floating point precision or other approximations for greater efficiency.",
                "solution_score_data_representation_approximation", "The approximate score with this CFN solution, "
				"given the CFN data representation",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::solution_score_data_representation_approximation, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Real > >(
                "solution_score_solver_approximation", "Get the approximate score returned by the CFN solver that produced "
				"this CFN solution.  In addition to approximation from the data representation, a solver may accumulate "
				"numerical error, over a trajectory use lower-precision math, perform arithmetic that accumulates "
				"floating-point error, or use external analogue methods (e.g. quantum computation) that introduce "
				"their own error.",
                "solution_score_solver_approximation", "The approximate score associated with this CFN solution, returned "
				"by the solver.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::solution_score_solver_approximation, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< std::vector< Size > > >(
                "solution_at_variable_positions", "Get the solution "
                "vector for this problem for variable nodes only.  "
                "This returns the solution vector as one value per "
                "variable position, in order of variable positions.  Indices "
                "in the vector do NOT necessarily correspond to node indices, "
                "since nodes with zero or one choice are omitted.  Problem and "
                "solution vector must have been set.",
                "solution_at_variable_positions", "A vector of choices, one per variable node.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::solution_at_variable_positions, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< std::vector< Size > > >(
                "solution_at_all_positions", "Get the solution vector "
                "for this problem, for all nodes.  "
                "This returns the solution vector as one value per "
                "position, in order of positions.  Indices "
                "in the vector correspond to node indices.  Problem and "
                "solution vector must have been set.",
                "solution_at_all_positions", "A vector of choices, one per node.  Nodes "
                "with no choices will show a zero for the choice index.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::solution_at_all_positions, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< OptimizationProblemCSP > >(
                "problem", "Get the problem associated with this solution.",
                "problem", "The problem associated with this solution.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::problem, this )
            )
        );

        // Setters:
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
                "set_solution_score", "Set the score associated with this solution.  This is the "
                "exact score, recomputed once the solution has been produced.",
                "score_in", "The score to set.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::set_solution_score, this, std::placeholders::_1 )
            ) 
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
                "set_solution_score_data_representation_approximation", "Set an approximate score associated "
				"with this solution, given the data representation.  Certain data representations may use reduced "
				"floating point precision or other approximations for greater efficiency.",
                "dr_approx_score_in", "The approximate score (from the data representation) to set.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::set_solution_score_data_representation_approximation, this, std::placeholders::_1 )
            ) 
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
                "set_solution_score_solver_approximation", "Set an approximate score returned by the solver that "
				"produced this solution. In addition to approximation from the data representation, a solver may "
				"accumulate numerical error over a trajectory, use lower-precision math, perform arithmetic that accumulates "
				"floating-point error, or use external analogue methods (e.g. quantum computation) that introduce "
				"their own error.",
                "solver_approx_score_in", "The approximate score (from the solver) to set.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::set_solution_score_solver_approximation, this, std::placeholders::_1 )
            ) 
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationProblemCSP const & > >(
                "set_problem", "Set the problem that gave rise to this solution.",
                "problem_in", "Const shared pointer to the problem that gave rise to the solution.  This "
                "must be a cost function network optimizatoin problem, and this function will throw if it is "
                "not.  Stored directly (not cloned) on input.",
                false, true,
                std::bind( &CostFunctionNetworkOptimizationSolution::set_problem, this, std::placeholders::_1 )
            ) 
        );
        api_def->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< std::vector< masala::base::Size > const & > >(
                "set_solution_vector", "Set the solution vector for this problem.",
                "solution_vector_in", "The solution, expressed as a vector of choice indices where each entry corresponds "
                "to each successive node with at least two choices, and there's one entry for each multi-choice node.",
                false, false,
                std::bind( &CostFunctionNetworkOptimizationSolution::set_solution_vector, this, std::placeholders::_1 )
            ) 
        );

        api_definition() = api_def; //Make const.
    }

    return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the solution vector for this problem.
/// @details This returns the solution vector as one value per
/// variable position, in order of variable positions.  Indices
/// in the vector do NOT necessarily correspond to node indices,
/// since nodes with zero or one choice are omitted.
/// @note Problem and solution vector must have been set.
std::vector< masala::base::Size >
CostFunctionNetworkOptimizationSolution::solution_at_variable_positions() const {
    std::lock_guard< std::mutex > lock( solution_mutex() );
    CHECK_OR_THROW_FOR_CLASS( protected_problem() != nullptr, "solution_at_variable_positions",
        "The problem must be set before calling this function!"
    );
    CHECK_OR_THROW_FOR_CLASS( !solution_vector_.empty(), "solution_at_variable_positions",
        "An empty solution vector was found!  Was the solution vector set before calling this function?"
    );
    return solution_vector_;
}

/// @brief Get the solution vector for this problem.
/// @details This returns the solution vector as one value per
/// position, in order of all positions.  Indices in the vector
/// correspond to node indices.
/// @note Problem and solution vector must have been set.
std::vector< masala::base::Size >
CostFunctionNetworkOptimizationSolution::solution_at_all_positions() const {
    std::lock_guard< std::mutex > lock( solution_mutex() );
    CHECK_OR_THROW_FOR_CLASS( protected_problem() != nullptr, "solution_at_all_positions",
        "The problem must be set before calling this function!"
    );
    CHECK_OR_THROW_FOR_CLASS( !solution_vector_.empty(), "solution_at_all_positions",
        "An empty solution vector was found!  Was the solution vector set before calling this function?"
    );
    CostFunctionNetworkOptimizationProblemCSP problem( std::static_pointer_cast< CostFunctionNetworkOptimizationProblem const >( protected_problem() ) );
    std::vector< std::pair< base::Size, base::Size > > const varnodes( problem->n_choices_at_variable_nodes() );
    std::vector< base::Size > solution( problem->total_nodes(), 0 );
    for( base::Size i(0), imax(solution_vector_.size()); i<imax; ++i ) {
        solution[varnodes[i].first] = solution_vector_[i];
    }
    return solution;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the problem that gave rise to this solution.
/// @details Stored directly (not cloned) on input.  This override checks that the problem
/// is a CostFunctionNetworkOptimizationProblem.  If the solution vector has been
/// set, the problem must match it.
void
CostFunctionNetworkOptimizationSolution::set_problem(
    OptimizationProblemCSP const & problem
) {
    CostFunctionNetworkOptimizationProblemCSP problem_cast( std::dynamic_pointer_cast< CostFunctionNetworkOptimizationProblem const >( problem ) );
    CHECK_OR_THROW_FOR_CLASS(
        problem_cast != nullptr,
        "set_problem", "A problem was passed to this function that was not a cost function network optimization problem."
    );
    std::lock_guard< std::mutex > lock( solution_mutex() );
    if( !solution_vector_.empty() ) {
        CHECK_OR_THROW_FOR_CLASS( solution_vector_.size() == problem_cast->total_variable_nodes(),
            "set_problem", "The solution vector must have one choice for each variable node.  The problem "
            "defines " + std::to_string( problem_cast->total_variable_nodes() ) + " nodes, but the solution vector has "
            + std::to_string( solution_vector_.size() ) + " entries."
        );
    }
    protected_problem() = problem;
}

/// @brief Set the solution vector for this problem.
/// @details If the problem has been set, this solution vector must be of compatible size.
void
CostFunctionNetworkOptimizationSolution::set_solution_vector(
    std::vector< masala::base::Size > const & solution_vector_in
) {
    std::lock_guard< std::mutex > lock( solution_mutex() );
    protected_set_solution_vector( solution_vector_in );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Determine whether this solution is the same as another.
/// @details Compares the stored solution vector to a provided solution vector.
bool
CostFunctionNetworkOptimizationSolution::operator==(
    std::vector< masala::base::Size > const & other_solution_vector
) const {
    std::lock_guard< std::mutex > lock( solution_mutex() );
    return solution_vector_ == other_solution_vector;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the solution vector for this problem.  This function assumes that the mutex has been locked.
/// @details If the problem has been set, this solution vector must be of compatible size.
void
CostFunctionNetworkOptimizationSolution::protected_set_solution_vector(
    std::vector< masala::base::Size > const & solution_vector_in
) {
    if( protected_problem() != nullptr ) {
        CostFunctionNetworkOptimizationProblemCSP problem_cast( std::static_pointer_cast< CostFunctionNetworkOptimizationProblem const >( protected_problem() ) );
        CHECK_OR_THROW_FOR_CLASS( solution_vector_in.size() == 0 || solution_vector_in.size() == problem_cast->total_variable_nodes(),
            "protected_set_solution_vector", "The solution vector must have one choice for each variable node.  The problem "
            "defines " + std::to_string( problem_cast->total_variable_nodes() ) + " nodes, but the solution vector has "
            + std::to_string( solution_vector_in.size() ) + " entries."
        );

        if( solution_vector_in.size() == 0 && problem_cast->total_variable_nodes() > 0 ) {
            protected_solution_is_valid() = false;
        }
    }
    solution_vector_ = solution_vector_in;
}

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
