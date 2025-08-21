/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizer.cc
/// @brief Implementation for a pure virtual base class for PluginCostFunctionNetworkOptimizers.
/// @details PluginCostFunctionNetworkOptimizers solve a numerical cost function network optimization
/// problem.  They have no chemical knowledge.  Cost function network problems include the packing
/// or side-chain optimization problem.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/cost_function_network/PluginCostFunctionNetworkOptimizer.hh>

// Numeric API headers:
#include <numeric_api/auto_generated_api/optimization/OptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblems_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem_API.hh>
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationSolutions_API.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.hh>

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
// PUBLIC CONSTRUCTORS, DESTRUCTORS, ETC.
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.  Explicit due to mutex.
PluginCostFunctionNetworkOptimizer::PluginCostFunctionNetworkOptimizer(
	PluginCostFunctionNetworkOptimizer const & src
) :
	Parent( src )
{
	std::lock( cfn_solver_mutex_, src.cfn_solver_mutex_ );
	std::lock_guard< std::mutex > lockthis( cfn_solver_mutex_, std::adopt_lock );
	std::lock_guard< std::mutex > lockthat( src.cfn_solver_mutex_, std::adopt_lock );
	protected_assign( src );
}

/// @brief Assignment operator.  Explicit due to mutex.
PluginCostFunctionNetworkOptimizer &
PluginCostFunctionNetworkOptimizer::operator=(
	PluginCostFunctionNetworkOptimizer const & src
) {
	std::lock( cfn_solver_mutex_, src.cfn_solver_mutex_ );
	std::lock_guard< std::mutex > lockthis( cfn_solver_mutex_, std::adopt_lock );
	std::lock_guard< std::mutex > lockthat( src.cfn_solver_mutex_, std::adopt_lock );
	protected_assign( src );
	return *this;
}

/// @brief Make this object fully independent.
/// @details Calls protected_make_independent().
void
PluginCostFunctionNetworkOptimizer::make_independent() {
	std::lock_guard< std::mutex > lock( cfn_solver_mutex_ );
	protected_make_independent();
}

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
PluginCostFunctionNetworkOptimizer::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "Optimizer", "CostFunctionNetworkOptimizer" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all optimizers; may be overridden
/// by derived classes.
/// @returns { "optimizer", "cost_function_network", "numeric" }
std::vector< std::string >
PluginCostFunctionNetworkOptimizer::get_keywords() const {
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
PluginCostFunctionNetworkOptimizer::get_engine_categories() const {
	return std::vector< std::vector < std::string > >{ { "Optimizer", "CostFunctionNetworkOptimizer" } };
}

/// @brief Keywords for engines.
/// @returns { "optimizer", "cost_function_network", "numeric" }
std::vector < std::string >
PluginCostFunctionNetworkOptimizer::get_engine_keywords() const {
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
PluginCostFunctionNetworkOptimizer::run_optimizer(
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
PluginCostFunctionNetworkOptimizer::set_template_preferred_cfn_data_representation(
    masala::base::managers::engine::MasalaDataRepresentationAPICSP const & representation_in
) {
	CHECK_OR_THROW_FOR_CLASS( representation_in->inner_object_empty(), "set_template_preferred_cfn_data_representation",
		"The " + representation_in->inner_class_name() + " object passed to this function was not empty!  The template preferred "
		"cost function network optimization problem data representation must not be loaded with data."
	);
	CHECK_OR_THROW_FOR_CLASS(
		std::dynamic_pointer_cast< masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblem const >( representation_in->get_inner_data_representation_object_const() ) != nullptr,
		"set_template_preferred_cfn_data_representation",
		"The " + representation_in->inner_class_name() + " object passed to this functionw was not a sub-class of CostFunctionNetworkOptimizationProblem."
	);
	std::lock_guard< std::mutex > lock( cfn_solver_mutex_ );
	protected_set_template_preferred_cfn_data_representation( representation_in );
}

/// @brief Get a template cost function network optimization problem data representation, configured by the user but with no data entered.
/// @details If set_template_preferred_cfn_data_representation() has not been called, this returns the output of protected_get_default_template_preferred_cfn_data_representation().
/// This is nullptr by default, but can be overridden by derived classes.  Returns a deep clone of the object otherwise.
masala::base::managers::engine::MasalaDataRepresentationAPISP
PluginCostFunctionNetworkOptimizer::get_template_preferred_cfn_data_representation_copy() const {
	using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
	using namespace masala::base::managers::engine;

	std::lock_guard< std::mutex > lock( cfn_solver_mutex_ );
	if( template_preferred_cfn_data_representation_ == nullptr ) {
		MasalaDataRepresentationAPISP data_rep_out( protected_get_default_template_preferred_cfn_data_representation() );
		if( data_rep_out != nullptr ) {
			CHECK_OR_THROW_FOR_CLASS( data_rep_out->inner_object_empty(), "get_template_preferred_cfn_data_representation_copy",
				"The " + data_rep_out->inner_class_name() + " object returned by this function was not empty!  It is expected that "
				"this function should return a Masala data representation that has not yet been loaded with any data.  If it "
				"does not, that implies that the protected_make_indpendent() function of the " + data_rep_out->inner_class_name()
				+ " class is not properly deep-cloning all contained objects, or that a contained object has not properly "
				"implemented its own deep-clone functionality.  Please consult a developer and provide them with this information."
			);
		}
		return data_rep_out;
	}

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

	MasalaDataRepresentationAPISP data_rep_copy_out( rep_cast->deep_clone() );
	CHECK_OR_THROW_FOR_CLASS( data_rep_copy_out != nullptr, "get_template_preferred_cfn_data_representation_copy",
		"Deep-cloning of the " + template_preferred_cfn_data_representation_->inner_class_name() + " class failed, returning nullptr.  "
		"This is a program error.  Please consult a developer."
	);
	CHECK_OR_THROW_FOR_CLASS( data_rep_copy_out->inner_object_empty(), "get_template_preferred_cfn_data_representation_copy",
		"The " + data_rep_copy_out->inner_class_name() + " object returned by this function was not empty!  It is expected that "
		"this function should return a Masala data representation that has not yet been loaded with any data.  If it "
		"does not, that implies that the protected_make_indpendent() function of the " + data_rep_copy_out->inner_class_name()
		+ " class is not properly deep-cloning all contained objects, or that a contained object has not properly "
		"implemented its own deep-clone functionality.  Please consult a developer and provide them with this information."
	);
	return data_rep_copy_out;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign src to this object.  Must be implemented by derived classes.  Performs no mutex-locking.  Derived classes should call their parent's protected_assign().
/*virtual*/
void
PluginCostFunctionNetworkOptimizer::protected_assign(
	PluginCostFunctionNetworkOptimizer const & src
) {
	using namespace masala::numeric_api::auto_generated_api::optimization::cost_function_network;
	if( src.template_preferred_cfn_data_representation_ == nullptr ) {
		template_preferred_cfn_data_representation_ = nullptr;
	} else {
		CostFunctionNetworkOptimizationProblem_APICSP rep_cast(
			std::dynamic_pointer_cast< CostFunctionNetworkOptimizationProblem_API const >(
				src.template_preferred_cfn_data_representation_
			)
		);
		CHECK_OR_THROW_FOR_CLASS(
			rep_cast != nullptr,
			"get_template_preferred_cfn_data_representation_copy",
			"An object of type \"" + template_preferred_cfn_data_representation_->inner_class_name() + "\" was stored as the template preferred CFN data "
			"representation in the source object, but it could not be interpreted as a CostFunctionNetworkOptimizationProblem object type."
		);
		template_preferred_cfn_data_representation_ = rep_cast->deep_clone();
	}
	//Parent::protected_assign(src);
}

/// @brief Make this object fully independent.  Must be implemented by derived classes.  Performs no
/// mutex-locking.  Derived classes should call their parent's protected_make_independent().
void
PluginCostFunctionNetworkOptimizer::protected_make_independent() {
	// GNDN
}

/// @brief Set a template cost function network optimization problem data representation, configured by the user but with no data entered.
/// @details This can optionally be passed in, in which case the get_template_preferred_cfn_data_representation() function can be
/// used to retrieve a deep clone.  This allows the solver to cache its preferred data representation with its setup.
/// @note This version performs no mutex-locking, and is called by set_template_preferred_cfn_data_representation(), which does lock the mutex.
/// This version is virtual to allow derived classes to override it, to add checks of their own.  If overridden, the override should call the
/// base class to set the variable internally.
/*virtual*/
void
PluginCostFunctionNetworkOptimizer::protected_set_template_preferred_cfn_data_representation(
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

/// @brief If the template preferred CFN data representation has not been set, return a default CFN data representation.
/// @details The base class implementation returns nullptr.  Derived classes may override this to return something else.  Performs no mutex-locking.
/*virtual*/
// masala::base::managers::engine::MasalaDataRepresentationAPISP
// PluginCostFunctionNetworkOptimizer::protected_get_default_template_preferred_cfn_data_representation() const {
// 	return nullptr;
// }

} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
