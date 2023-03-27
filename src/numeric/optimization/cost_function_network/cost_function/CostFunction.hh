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

/// @file src/numeric/optimization/cost_function_network/cost_function/CostFunction.hh
/// @brief Header for a pure virtual base class for CostFunctions.
/// @details CostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.  This class
/// is deliberately NOT THREADSAFE for writes (though simultaneous read-access is safe).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <utility> //For std::pair.

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

/// @brief A pure virtual base class for CostFunctions.
/// @details CostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.  This class
/// is deliberately NOT THREADSAFE for writes (though simultaneous read-access is safe).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunction : public masala::base::managers::plugin_module::MasalaPlugin {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunction() = default;

	/// @brief Copy constructor.
	CostFunction( CostFunction const & ) = default;

	// @brief Assignment operator.
	CostFunction &
	operator=( CostFunction const & ) = default;

	/// @brief Destructor.
	~CostFunction() override = default;

	/// @brief Make a copy of this object.
	virtual
	CostFunctionSP
	clone() const = 0;

	/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
	virtual
	void make_independent() = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// cost functions; may be overridden by derived classes.
	/// @returns { { "CostFunction" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "cost_function", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Attach a problem with which this cost function is associated.
	/// @details The problem is stored by weak pointer.  Should be called before
	/// CostFunctionNetworkOptimizationProblem::add_cost_function().
	void
	attach_problem(
		masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblemCSP const & problem
	);

	/// @brief Given a selection of choices at variable nodes, compute the cost function.
	virtual
	masala::base::Real
	compute_cost_function(
		std::vector< masala::base::Size > const & candidate_solution
	) const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Access the problem, by shared pointer.
	/// @details Returns nullptr if no problem is attached or if the problem has been destroyed.
	/// @note Inefficient in a multi-threaded context: incremenets reference count of shared pointer.
	masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblemCSP problem() const;


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The cost function network optimization problem to which this cost function is attached.
	masala::numeric::optimization::cost_function_network::CostFunctionNetworkOptimizationProblemCWP problem_;


}; // class CostFunction

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_hh