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

/// @file tests/unit/core/molecular_system/RealValuedLocalOptimizationContainerTests.cc
/// @brief Unit tests for containers that store real-valued local optimization problems and solutions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <numeric_api/auto_generated_api/registration/register_numeric.hh>
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem_API.hh>
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolution_API.hh>
#include <numeric_api/auto_generated_api/optimization/real_valued_local/RealValuedFunctionLocalOptimizationSolutions_API.hh>

// Eigen headers:
#include <external/eigen/Eigen/Core>

// Base headers:
#include <base/types.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace tests {
namespace unit {
namespace numeric {
namespace optimization {
namespace real_valued_local {

masala::base::Real
testfxn(
    Eigen::VectorXd const & x,
    bool const additional_term
) {
    CHECK_OR_THROW( x.size() == 3, "masala::tests::unit::numeric::optimization::real_valued_local", "testfxn", "Expected a 3-vector as input." );
    masala::base::Real const X( x[0] );
    masala::base::Real const Y( x[1] );
    masala::base::Real const Z( x[2] );
    return 3*X*X + 4*X*Y*Z*Z*Z - 2*X*X*Z + Y*Y + ( additional_term ? Z*Y : 0 );
}

masala::base::Real
grad_testfxn(
    Eigen::VectorXd const & x,
    Eigen::VectorXd & df_dx,
    bool const additional_term
) {
    CHECK_OR_THROW( x.size() == 3, "masala::tests::unit::numeric::optimization::real_valued_local", "grad_testfxn", "Expected a 3-vector as input." );
    df_dx.resize(3);

    masala::base::Real const X( x[0] );
    masala::base::Real const Y( x[1] );
    masala::base::Real const Z( x[2] );

    df_dx[0] = 6*X + 4*Y*Z*Z*Z - 4*X*Z;
    df_dx[1] = 4*X*Z*Z*Z + 2*Y + ( additional_term ? Z : 0 );
    df_dx[2] = 12*X*Y*Z*Z - 2*X*X + ( additional_term ? Y : 0 );

    return testfxn( x, additional_term );
}

TEST_CASE(
    "Set up a few local optimization problems, and put them in a problems container.",
    "[numeric::optimization::real_valued_local::RealValuedFunctionLocalOptimizationProblem]"
    "[numeric::optimization::real_valued_local::RealValuedFunctionLocalOptimizationProblems]"
    "[numeric::optimization::real_valued_local::RealValuedFunctionLocalOptimizationSolution]"
    "[numeric::optimization::real_valued_local::RealValuedFunctionLocalOptimizationSolutions]"
    "[numeric_api::auto_generated_api::optimization::real_valued_local::RealValuedFunctionLocalOptimizationProblem_API]"
    "[numeric_api::auto_generated_api::optimization::real_valued_local::RealValuedFunctionLocalOptimizationProblems_API]"
    "[numeric_api::auto_generated_api::optimization::real_valued_local::RealValuedFunctionLocalOptimizationSolution_API]"
    "[numeric_api::auto_generated_api::optimization::real_valued_local::RealValuedFunctionLocalOptimizationSolutions_API]"
    "[instantiation]"
) {
    using namespace masala::numeric_api::auto_generated_api::optimization::real_valued_local;

    numeric_api::auto_generated_api::registration::register_numeric();

    RealValuedFunctionLocalOptimizationProblems_APISP problems( masala::make_shared< RealValuedFunctionLocalOptimizationProblems_API >() );

    RealValuedFunctionLocalOptimizationProblem_APISP prob1( masala::make_shared< RealValuedFunctionLocalOptimizationProblem_API >() );
    prob1->set_objective_function( std::bind( &testfxn, std::placeholders::_1, false ) );
    prob1->set_objective_function_gradient( std::bind( &grad_testfxn, std::placeholders::_1, std::placeholders::_2, false ) );
    Eigen::VectorXd startpt1(3);
    startpt1 << 4, 7, 1;
    prob1->add_starting_point( startpt1 );
    CHECK( !prob1->finalized() );
    prob1->finalize();
    CHECK( prob1->finalized() );
    CHECK( prob1->starting_points().size() == 1 );
    CHECK( std::abs( prob1->starting_points()[0][0] - 4.0 ) < 1.0e-7 );
    CHECK( std::abs( prob1->starting_points()[0][1] - 7.0 ) < 1.0e-7 );
    CHECK( std::abs( prob1->starting_points()[0][2] - 1.0 ) < 1.0e-7 );
    problems->add_optimization_problem(prob1);
    RealValuedFunctionLocalOptimizationProblem_APISP prob2( masala::make_shared< RealValuedFunctionLocalOptimizationProblem_API >() );
    prob2->set_objective_function( std::bind( &testfxn, std::placeholders::_1, true ) );
    prob2->set_objective_function_gradient( std::bind( &grad_testfxn, std::placeholders::_1, std::placeholders::_2, true ) );
    Eigen::VectorXd startpt2(3), startpt3(3);
    startpt2 << 2, 4, 1;
    startpt3 << 2, 4, 2;
    prob2->add_starting_point( startpt2 );
    prob2->add_starting_point( startpt3 );
    CHECK( !prob2->finalized() );
    prob2->finalize();
    CHECK( prob2->finalized() );
    CHECK( prob2->starting_points().size() == 2 );
    CHECK( std::abs( prob2->starting_points()[0][0] - 2.0 ) < 1.0e-7 );
    CHECK( std::abs( prob2->starting_points()[0][1] - 4.0 ) < 1.0e-7 );
    CHECK( std::abs( prob2->starting_points()[0][2] - 1.0 ) < 1.0e-7 );
    CHECK( std::abs( prob2->starting_points()[1][0] - 2.0 ) < 1.0e-7 );
    CHECK( std::abs( prob2->starting_points()[1][1] - 4.0 ) < 1.0e-7 );
    CHECK( std::abs( prob2->starting_points()[1][2] - 2.0 ) < 1.0e-7 );
    problems->add_optimization_problem(prob2);

    CHECK( problems->n_problems() == 2 );

    RealValuedFunctionLocalOptimizationSolutions_APISP solutions( masala::make_shared< RealValuedFunctionLocalOptimizationSolutions_API >() );
    RealValuedFunctionLocalOptimizationSolution_APISP sol1( masala::make_shared< RealValuedFunctionLocalOptimizationSolution_API >() );
    sol1->set_problem( problems->problem(0) );
    Eigen::VectorXd sp1(3);
    sp1 << 1, 3, 4;
    sol1->set_solution_point( sp1 );
    sol1->set_solution_score( 2.51 );
    sol1->set_solution_score_data_representation_approximation( 2.50 );
    sol1->set_solution_score_solver_approximation( 2.49 );
    sol1->set_iterations(105);
    sol1->set_n_times_solution_was_produced(1);
    sol1->set_starting_point_and_index( prob1->starting_points()[0], 0 );
    CHECK( std::abs(sol1->solution_point()[0] - 1.0) < 1.0e-7 );
    CHECK( std::abs(sol1->solution_point()[1] - 3.0) < 1.0e-7 );
    CHECK( std::abs(sol1->solution_point()[2] - 4.0) < 1.0e-7 );
    CHECK( std::abs(sol1->solution_score() - 2.51) < 1.0e-7 );
    CHECK( std::abs(sol1->solution_score_data_representation_approximation() - 2.50) < 1.0e-7 );
    CHECK( std::abs(sol1->solution_score_solver_approximation() - 2.49) < 1.0e-7 );
    CHECK( sol1->iterations() == 105 );
    CHECK( sol1->n_times_solution_was_produced() == 1 );
    CHECK( std::abs( sol1->starting_point()[0] - 4.0 ) < 1.0e-7 );
    CHECK( std::abs( sol1->starting_point()[1] - 7.0 ) < 1.0e-7 );
    CHECK( std::abs( sol1->starting_point()[2] - 1.0 ) < 1.0e-7 );
    solutions->add_optimization_solution( sol1 );

    RealValuedFunctionLocalOptimizationSolution_APISP sol2( masala::make_shared< RealValuedFunctionLocalOptimizationSolution_API >() );
    sol2->set_problem( problems->problem(1) );
    Eigen::VectorXd sp2(3);
    sp2 << 5, -2.5, 4.5;
    sol2->set_solution_point( sp2 );
    sol2->set_solution_score( 3.51 );
    sol2->set_solution_score_data_representation_approximation( 3.50 );
    sol2->set_solution_score_solver_approximation( 3.49 );
    sol2->set_iterations(551);
    sol2->set_n_times_solution_was_produced(4);
    sol2->set_starting_point_and_index( prob2->starting_points()[1], 1 );
    CHECK( std::abs(sol2->solution_point()[0] - 5.0) < 1.0e-7 );
    CHECK( std::abs(sol2->solution_point()[1] + 2.5) < 1.0e-7 );
    CHECK( std::abs(sol2->solution_point()[2] - 4.5) < 1.0e-7 );
    CHECK( std::abs(sol2->solution_score() - 3.51) < 1.0e-7 );
    CHECK( std::abs(sol2->solution_score_data_representation_approximation() - 3.50) < 1.0e-7 );
    CHECK( std::abs(sol2->solution_score_solver_approximation() - 3.49) < 1.0e-7 );
    CHECK( sol2->iterations() == 551 );
    CHECK( sol2->n_times_solution_was_produced() == 4 );
    CHECK( std::abs( sol2->starting_point()[0] - 2.0 ) < 1.0e-7 );
    CHECK( std::abs( sol2->starting_point()[1] - 4.0 ) < 1.0e-7 );
    CHECK( std::abs( sol2->starting_point()[2] - 2.0 ) < 1.0e-7 );
    solutions->add_optimization_solution( sol2 );

    CHECK( solutions->n_solutions() == 2 );

    numeric_api::auto_generated_api::registration::unregister_numeric();
}

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace unit
} // namespace tests
} // namespace masala
