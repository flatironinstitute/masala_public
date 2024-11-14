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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/CostFunctionNetworkOptimizer.cc
/// @brief Implementation for a pure virtual base class for CostFunctionNetworkOptimizers.
/// @details CostFunctionNetworkOptimizers solve a numerical cost function network optimization
/// problem.  They have no chemical knowledge.  Cost function network problems include the packing
/// or side-chain optimization problem.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/cost_function_network/CostFunctionNetworkOptimizer.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/OptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions_API.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all optimizers;
/// may be overridden by derived classes.
/// @returns { { "Optimizer", "CostFunctionNetworkOptimizer" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunctionNetworkOptimizer::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "Optimizer", "CostFunctionNetworkOptimizer" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
/// by derived classes.
/// @returns { "optimizer", "cost_function_network", "numeric" }
std::vector< std::string >
CostFunctionNetworkOptimizer::get_keywords() const {
	return std::vector< std::string > {
		"optimizer",
        "cost_function_network",
		"numeric"
	};
}

/// @brief Categories for engines.
/// @details Like plugin categories, engine categories are hierarchical.  The hieraruchy
/// is important for deciding what engines are equvalent. For instance, if I had
/// "Solver"->"KinematicSolver"->"AnalyticKinematicSolver", I could request only the analytic
/// kinematic solvers, all kinematic solvers, or all solvers in general.
/// @note An engine may exist in more than one hierarchical category.  The outer vector is
/// a list of hierarchical categories, and the inner vector is the particular hierarchical
/// category, from most general to most specific.  Also note that this function is pure
/// virtual, and must be defined for instantiable MasalaEngine subclasses.
/// @returns { {"Optimizer", "CostFunctionNetworkOptimizer"} }
std::vector< std::vector < std::string > >
CostFunctionNetworkOptimizer::get_engine_categories() const {
    return std::vector< std::vector < std::string > >{ { "Optimizer", "CostFunctionNetworkOptimizer" } };
}

/// @brief Keywords for engines.
/// @returns { "optimizer", "cost_function_network", "numeric" }
std::vector < std::string >
CostFunctionNetworkOptimizer::get_engine_keywords() const {
    return std::vector< std::string > {
		"optimizer",
        "cost_function_network",
		"numeric"
	};
}

/// @brief Run the optimizer on a set of optimization problems, and produce a set of solutions.
/// @details Must be implemented by derived classes.   Each solutions set in the vector of solutions corresponds to
/// the problem with the same index.
std::vector< masala::numeric_api::auto_generated_api::optimization::OptimizationSolutions_APICSP >
CostFunctionNetworkOptimizer::run_optimizer(
    masala::numeric_api::auto_generated_api::optimization::OptimizationProblems_API const & problems
) const {
    using namespace masala::numeric_api::auto_generated_api::optimization;
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
    CostFunctionNetworkOptimizationProblems_API const * problems_cast( dynamic_cast< CostFunctionNetworkOptimizationProblems_API const * >( &problems ) );
    CHECK_OR_THROW_FOR_CLASS(
        problems_cast != nullptr,
        "run_optimizer",
        "A set of optimization problems was passed to the run_optimizer function, but it was not "
        "a set of cost function network optimization problems."
    );

    std::vector< CostFunctionNetworkOptimizationSolutions_APICSP > const outvec1( run_cost_function_network_optimizer( *problems_cast ) );

    // Conversion to base class pointers requires another step, irritatingly:
    std::vector< OptimizationSolutions_APICSP > outvec2( outvec1.size() );
    for( base::Size i(0), imax(outvec1.size()); i<imax; ++i ) {
        outvec2[i] = outvec1[i];
    }

    return outvec2;
}

/// @brief Set a template cost function network optimization problem data representation, configured by the user but with no data entered.
/// @details This can optionally be passed in, in which case the get_template_preferred_cfn_data_representation() function can be
/// used to retrieve a deep clone.  This allows the solver to cache its preferred data representation with its setup.
void
CostFunctionNetworkOptimizer::set_template_preferred_cfn_data_representation(
    masala::base::managers::engine::MasalaDataRepresentationAPICSP const & representation_in
) {
    std::lock_guard< std::mutex > lock( cfn_solver_mutex_ );
    protected_set_template_preferred_cfn_data_representation( representation_in );
}

/// @brief Get a template cost function network optimization problem data representation, configured by the user but with no data entered.
/// @details If set_template_preferred_cfn_data_representation() has not been called, this returns nullptr.  Returns a deep clone of the object otherwise.
masala::base::managers::engine::MasalaDataRepresentationAPISP
CostFunctionNetworkOptimizer::get_template_preferred_cfn_data_representation_copy() const {
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
    std::lock_guard< std::mutex > lock( cfn_solver_mutex_ );
    if( template_preferred_cfn_data_representation_ == nullptr ) { return nullptr; }

    CostFunctionNetworkOptimizationProblem_APICSP rep_cast(
        std::dynamic_pointer_cast< CostFunctionNetworkOptimizationProblem_API const >(
            template_preferred_cfn_data_representation_
        )
    );
    CHECK_OR_THROW_FOR_CLASS(
        rep_cast != nullptr,
        "get_template_preferred_cfn_data_representation_copy",
        "An object of type \"" + template_preferred_cfn_data_representation_->inner_class_name() + "\" was stored as the template preferred CFN data "
        "representation, but it could not be interpreted as a CostFunctionNetworkOptimizationProblem object type."
    );

    return rep_cast->deep_clone();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set a template cost function network optimization problem data representation, configured by the user but with no data entered.
/// @details This can optionally be passed in, in which case the get_template_preferred_cfn_data_representation() function can be
/// used to retrieve a deep clone.  This allows the solver to cache its preferred data representation with its setup.
/// @note This version performs no mutex-locking, and is called by set_template_preferred_cfn_data_representation(), which does lock the mutex.
/// This version is virtual to allow derived classes to override it, to add checks of their own.  If overridden, the override should call the
/// base class to set the variable internally.
/*virtual*/
void
CostFunctionNetworkOptimizer::protected_set_template_preferred_cfn_data_representation(
    masala::base::managers::engine::MasalaDataRepresentationAPICSP const & representation_in
) {
    using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
    if( representation_in != nullptr ) {
        CHECK_OR_THROW_FOR_CLASS(
            std::dynamic_pointer_cast< CostFunctionNetworkOptimizationProblem_API const >( representation_in ) != nullptr,
            "protected_set_template_preferred_cfn_data_representation",
            "An object of type \"" + representation_in->inner_class_name() + "\" was passed to this function, but it could not be interpreted as a "
            "CostFunctionNetworkOptimizationProblem object type."
        );
    }
    template_preferred_cfn_data_representation_ = representation_in;
}

} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
