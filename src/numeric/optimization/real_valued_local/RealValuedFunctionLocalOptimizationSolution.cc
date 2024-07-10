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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.cc
/// @brief Implementations for a pure virtual base class for a RealValuedFunctionLocalOptimizationSolution.
/// @details A RealValuedFunctionLocalOptimizationSolution contains the solution to a particular
/// RealValuedFunctionLocalOptimizationProblem, after it is solved by a suitable
/// GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution.hh>

// Numeric headers:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.hh>

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
namespace real_valued_local {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Make a copy of this object.
masala::numeric::optimization::OptimizationSolutionSP
RealValuedFunctionLocalOptimizationSolution::clone() const {
	return masala::make_shared< RealValuedFunctionLocalOptimizationSolution >( *this );
}

/// @brief Make a fully independent copy of this object.
RealValuedFunctionLocalOptimizationSolutionSP
RealValuedFunctionLocalOptimizationSolution::deep_clone() const {
	RealValuedFunctionLocalOptimizationSolutionSP new_solution( std::static_pointer_cast< RealValuedFunctionLocalOptimizationSolution >( this->clone() ) );
	new_solution->make_independent();
	return new_solution;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
RealValuedFunctionLocalOptimizationSolution::make_independent() {
	masala::numeric::optimization::OptimizationSolution::make_independent();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "OptimizationSolution", "RealValuedFunctionLocalOptimizationSolution" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
RealValuedFunctionLocalOptimizationSolution::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "OptimizationSolution", "RealValuedFunctionLocalOptimizationSolution" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization solutions; may be overridden by derived classes.
/// @returns { "optimization_solution", "local", "real_valued", "numeric" }
std::vector< std::string >
RealValuedFunctionLocalOptimizationSolution::get_keywords() const {
	return std::vector< std::string > {
		"optimization_solution",
		"local",
		"real_valued",
		"numeric"
	};
}

/// @brief Get the name of this class.
/// @returns "RealValuedFunctionLocalOptimizationSolution".
std::string
RealValuedFunctionLocalOptimizationSolution::class_name() const {
	return "RealValuedFunctionLocalOptimizationSolution";
}

/// @brief Get the namespace for this class.
/// @returns "masala::numeric::optimization::real_valued_local".
std::string
RealValuedFunctionLocalOptimizationSolution::class_namespace() const {
	return "masala::numeric::optimization::real_valued_local";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationSolution class.
masala::base::api::MasalaObjectAPIDefinitionCWP
RealValuedFunctionLocalOptimizationSolution::get_api_definition() {
	using namespace masala::base::api;
	using base::Real;
	using base::Size;

	std::lock_guard< std::mutex > lock( solution_mutex() );

	if( api_definition() == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"A RealValuedFunctionLocalOptimizationSolution contains the solution to a particular "
				"RealValuedFunctionLocalOptimizationProblem, after it is solved by a suitable "
				"GradientBasedFunctionOptimizer.  It does not contain any chemistry-specific concepts.",
				false, false
			)
		);

		// Constructors:
		api_def->add_constructor(
			masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < RealValuedFunctionLocalOptimizationSolution > > (
				class_name(),
				"Creates an empty RealValuedFunctionLocalOptimizationSolution."
			)
		);
		api_def->add_constructor(
			masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < RealValuedFunctionLocalOptimizationSolution, RealValuedFunctionLocalOptimizationSolution const & > > (
				class_name(),
				"Copy constructor: copies an input RealValuedFunctionLocalOptimizationSolution.",
				"src", "The input RealValuedFunctionLocalOptimizationSolution to copy.  Unaltered by this operation."
			)
		);

		// Work functions:

		// Getters:
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Eigen::Vector< Real, Eigen::Dynamic > const & > >(
				"starting_point", "Get the starting point that gave rise to this local minimum.",
				"starting_point", "The starting point that gave rise to this local minimum.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::starting_point, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Size > >(
				"starting_point_index", "Get the index (in the problem) of the starting point that gave rise to this local minimum.",
				"starting_point_index", "The starting point index.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::starting_point_index, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & > >(
				"solution_point", "Get the local minimum point found by the optimizer.",
				"solution_point", "The point found that is a local minimum.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::solution_point, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput<bool> >(
				"is_converged", "Did the optimizer report convergence?",
				"converged", "True if the optimizer reported convergence; false otherwise.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::is_converged, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Size > >(
				"iterations", "How many iterations did the optimizer report taking?",
				"iterations", "The number of iterations that the optimizer took to find the minimum.  Note "
				"that some optimizers may use non-iterative approaches, in which case this value will be zero.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::iterations, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Real > >(
				"solution_score", "Get the score associated with this local optimization solution.  This is the exact "
				"score, recomputed once the solution has been produced.",
				"solution_score", "The exact score associated with this local optimization solution.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::solution_score, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Real > >(
				"solution_score_data_representation_approximation", "Get the approximate score associated "
				"with this local optimization solution, given the local optimization data representation.  Certain data representations may use "
				"reduced floating point precision or other approximations for greater efficiency.",
				"solution_score_data_representation_approximation", "The approximate score with this local optimization solution, "
				"given the local optimization data representation",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::solution_score_data_representation_approximation, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< Real > >(
				"solution_score_solver_approximation", "Get the approximate score returned by the local optimization solver that produced "
				"this local optimization solution.  In addition to approximation from the data representation, a solver may accumulate "
				"numerical error, over a trajectory use lower-precision math, perform arithmetic that accumulates "
				"floating-point error, or use external analogue methods (e.g. quantum computation) that introduce "
				"their own error.",
				"solution_score_solver_approximation", "The approximate score associated with this local optimization solution, returned "
				"by the solver.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::solution_score_solver_approximation, this )
			)
		);
		api_def->add_getter(
			masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< OptimizationProblemCSP > >(
				"problem", "Get the local optimization problem associated with this local optimization solution.",
				"problem", "The problem associated with this solution.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::problem, this )
			)
		);

		// Setters:
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
				"set_solution_score", "Set the score associated with this solution.  This is the "
				"exact score, recomputed once the solution has been produced.",
				"score_in", "The score to set.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::set_solution_score, this, std::placeholders::_1 )
			) 
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
				"set_solution_score_data_representation_approximation", "Set an approximate score associated "
				"with this solution, given the data representation.  Certain data representations may use reduced "
				"floating point precision or other approximations for greater efficiency.",
				"dr_approx_score_in", "The approximate score (from the data representation) to set.",
				false, false,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::set_solution_score_data_representation_approximation, this, std::placeholders::_1 )
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
				std::bind( &RealValuedFunctionLocalOptimizationSolution::set_solution_score_solver_approximation, this, std::placeholders::_1 )
			) 
		);
		api_def->add_setter(
			masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< OptimizationProblemCSP > >(
				"set_problem", "Set the problem that gave rise to this solution.",
				"problem_in", "Const shared pointer to the problem that gave rise to the solution.  This "
				"must be a cost function network optimizatoin problem, and this function will throw if it is "
				"not.  Stored directly (not cloned) on input.",
				false, true,
				std::bind( &RealValuedFunctionLocalOptimizationSolution::set_problem, this, std::placeholders::_1 )
			) 
		);

		api_definition() = api_def; //Make const.
	}

	return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief The starting point that gave rise to this local minimum.
Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &
RealValuedFunctionLocalOptimizationSolution::starting_point() const {
	std::lock_guard< std::mutex > lock( solution_mutex() );
	return starting_point_;
}

/// @brief The starting point index in the problem.
masala::base::Size
RealValuedFunctionLocalOptimizationSolution::starting_point_index() const {
	std::lock_guard< std::mutex > lock( solution_mutex() );
	return starting_point_index_;
}

/// @brief The point found that is a local minimum.
Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &
RealValuedFunctionLocalOptimizationSolution::solution_point() const {
	std::lock_guard< std::mutex > lock( solution_mutex() );
	return solution_point_;
}

/// @brief Did the optimizer report convergence?
bool
RealValuedFunctionLocalOptimizationSolution::is_converged() {
	std::lock_guard< std::mutex > lock( solution_mutex() );
	return is_converged_;
}

/// @brief How many iterations did the optimizer report taking?
/// @details Some optimizers may use non-iterative approaches, in which case this value will be zero.
masala::base::Size
RealValuedFunctionLocalOptimizationSolution::iterations() {
	std::lock_guard< std::mutex > lock( solution_mutex() );
	return iterations_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the problem that gave rise to this solution.
/// @details Stored directly (not cloned) on input.  This override checks that the problem
/// is a CostFunctionNetworkOptimizationProblem.  If the solution vector has been
/// set, the problem must match it.
void
RealValuedFunctionLocalOptimizationSolution::set_problem(
	OptimizationProblemCSP const & problem
) {
	using masala::base::Size;

	RealValuedFunctionLocalOptimizationProblemCSP problem_cast( std::dynamic_pointer_cast< RealValuedFunctionLocalOptimizationProblem const >( problem ) );
	CHECK_OR_THROW_FOR_CLASS(
		problem_cast != nullptr,
		"set_problem", "A problem was passed to this function that was not a real-valued function local optimization problem.  Problem type was "
		+ problem->class_name() + "."
	);

	std::lock_guard< std::mutex > lock( solution_mutex() );

	if( solution_point_.size() > 0 ) {
		Size const n_starting_pts( problem_cast->starting_points().size() );
		for( Size i(0); i<n_starting_pts; ++i ) {
			CHECK_OR_THROW_FOR_CLASS( solution_point_.size() == problem_cast->starting_points()[i].size(),
				"set_problem", "The solution vector be of the same length as the starting points in the problem.  The problem "
				"specifies " + std::to_string( problem_cast->starting_points()[i].size() ) + "-dimensional starting coordinates, "
				"but the solution is " + std::to_string( solution_point_.size() ) + "-dimensional."
			);
		}
	}

	if( starting_point_.size() > 0 ) {
		CHECK_OR_THROW_FOR_CLASS(
			starting_point_index_ < problem_cast->starting_points().size(), "set_problem",
			"The starting point index was set to " + std::to_string( starting_point_index_ ) + ", but there are only "
			+ std::to_string( problem_cast->starting_points().size() ) + " starting points in the problem."
		)
		CHECK_OR_THROW_FOR_CLASS(
			starting_point_ == problem_cast->starting_points()[starting_point_index_], "set_problem",
			"The starting point does not match the corresponding starting point in the problem."
		)
	}

	protected_problem() = problem;
}

/// @brief Set the starting point that gave rise to this local minimum, and the corresponding
/// starting point index in the problem.
/// @details If the problem has already been set, this must match it.  If a solution vector has
/// been set, the starting point's length must match it.
void
RealValuedFunctionLocalOptimizationSolution::set_starting_point_and_index(
	Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & starting_point_in,
	masala::base::Size const starting_point_index
) {
	using masala::base::Size;
	std::lock_guard< std::mutex > lock( solution_mutex() );

	if( solution_point_.size() > 0 ) {
		CHECK_OR_THROW_FOR_CLASS( starting_point_in.size() == solution_point_.size(), "set_starting_point_and_index",
			"Starting point and solution vector dimensionality do not match."
		);
	}
	if( protected_problem() != nullptr ) {
		RealValuedFunctionLocalOptimizationProblem const * prob( dynamic_cast< RealValuedFunctionLocalOptimizationProblem const * >( protected_problem().get() ) );
		CHECK_OR_THROW_FOR_CLASS( prob != nullptr, "set_starting_point_and_index", "Problem is not a RealValuedFunctionLocalOptimizationProblem!" );
		CHECK_OR_THROW_FOR_CLASS( starting_point_index < prob->starting_points().size(), "set_starting_point_and_index", "The starting point index is out of range." );
		CHECK_OR_THROW_FOR_CLASS( starting_point_in == prob->starting_points()[starting_point_index], "set_starting_point_and_index",
			"The starting point does not match the corresponding starting point in the problem."
		);
	}
		
	starting_point_ = starting_point_in;
	starting_point_index_ = starting_point_index;
}

/// @brief Set the point found that is a local minimum.
/// @details If the problem has already been set, this must match it.  If a starting point has
/// been set, the solution vector's length must match it.
void
RealValuedFunctionLocalOptimizationSolution::set_solution_point(
	Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & solution_point_in
) {
	using masala::base::Size;
	std::lock_guard< std::mutex > lock( solution_mutex() );

	CHECK_OR_THROW_FOR_CLASS( solution_point_in.size() > 0, "set_solution_point", "Solutions must have nonzero length." );
	if( starting_point_.size() > 0 ) {
		CHECK_OR_THROW_FOR_CLASS( solution_point_in.size() == starting_point_.size(), "set_solution_point",
			"Solutions must have the same dimensionality as the starting point."
		);
	}
	if( protected_problem() != nullptr ) {
		RealValuedFunctionLocalOptimizationProblem const * prob( dynamic_cast< RealValuedFunctionLocalOptimizationProblem const * >( protected_problem().get() ) );
		CHECK_OR_THROW_FOR_CLASS( prob != nullptr, "set_solution_point", "Problem is not a RealValuedFunctionLocalOptimizationProblem!" );
		Size const nstarts( static_cast< Size >( prob->starting_points().size() ) );
		for( Size i(0); i<nstarts; ++i ) {
			CHECK_OR_THROW_FOR_CLASS( solution_point_in.size() == prob->starting_points()[i].size(), "set_solution_point",
				"The solution vector dimensionality does not match a problem starting point vector's dimensionality."
			);
		}
	}

	solution_point_ = solution_point_in;
}

/// @brief Set whether the optimizer reported convergence.
void
RealValuedFunctionLocalOptimizationSolution::set_converged(
	bool const converged_in
) {
	std::lock_guard< std::mutex > lock( solution_mutex() );
	is_converged_ = converged_in;
}

/// @brief Set the number of iterations that the optimizer reported taking.
/// @details Some optimizers may use non-iterative approaches, in which case this value will be zero.
void
RealValuedFunctionLocalOptimizationSolution::set_iterations(
	masala::base::Size const iterations_in
) {
	std::lock_guard< std::mutex > lock( solution_mutex() );
	iterations_ = iterations_in;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala
