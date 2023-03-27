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

/// @file src/numeric/api/generate_api_classes.cc
/// @brief Utility functions to generate all of the classes in numeric that define
/// an API.  Used for auto-generating the numeric api.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header
#include <numeric/api/generate_api_classes.hh>

// Numeric headers
#include <numeric/optimization/OptimizationProblem.hh>
#include <numeric/optimization/OptimizationProblems.hh>
#include <numeric/optimization/OptimizationSolution.hh>
#include <numeric/optimization/OptimizationSolutions.hh>
#include <numeric/optimization/annealing/AnnealingScheduleBase.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblems.hh>
#include <numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblem.hh>
#include <numeric/optimization/cost_function_network/PairwisePrecomputedCostFunctionNetworkOptimizationProblems.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolution.hh>
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions.hh>
#include <numeric/optimization/cost_function_network/cost_function/SquareOfChoicePenaltySumCostFunction.hh>

namespace masala {
namespace numeric {
namespace api {

    /// @brief Generate an instance of each of the classes in core that have a defined API, and
    /// return a vector of owning pointers to these instances.
    /// @details Used for auto-generating the core API description (as a JSON file).
    std::vector< masala::base::MasalaObjectSP >
    generate_api_classes() {
        std::vector< masala::base::MasalaObjectSP > outvec;

        // Add to this vector whenever a class is added with a defined API:
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::OptimizationProblem >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::OptimizationProblems >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::OptimizationSolution >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::OptimizationSolutions >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::annealing::AnnealingScheduleBase >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblems >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::cost_function_network::PairwisePrecomputedCostFunctionNetworkOptimizationProblem >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::cost_function_network::PairwisePrecomputedCostFunctionNetworkOptimizationProblems >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationSolution >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationSolutions >() );
        outvec.emplace_back( masala::make_shared< masala::numeric::optimization::cost_function_network::cost_function::SquareOfChoicePenaltySumCostFunction >() );
        // ADD MORE ENTRIES HERE

        return outvec;
    }

} // namespace api
} // namespace numeric
} // namespace masala
