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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunction.hh
/// @brief Header for a non-instantiable base class for PluginCostFunctions.
/// @details PluginCostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)  The PluginCostFunction class derives from CostFunction,
/// and permits cost functions to be defined in plug-in libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_cost_function_PluginCostFunction_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_cost_function_PluginCostFunction_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunction.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Numeric_api headers:
#include <numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunctionScratchSpace.fwd.hh>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

/// @brief A non-instantiable base class for PluginCostFunctions.
/// @details PluginCostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)  The PluginCostFunction class derives from CostFunction,
/// and permits cost functions to be defined in plug-in libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginCostFunction : public masala::numeric::optimization::cost_function_network::cost_function::CostFunction {

	typedef masala::numeric::optimization::cost_function_network::cost_function::CostFunction Parent;
	typedef masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP ParentSP;
	typedef masala::numeric::optimization::cost_function_network::cost_function::CostFunctionCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor (protected in API).
	PluginCostFunction() = default;

	/// @brief Copy constructor (protected in API).
	PluginCostFunction( PluginCostFunction const & src );

	// @brief Assignment operator.
	PluginCostFunction &
	operator=( PluginCostFunction const & src );

	/// @brief Destructor.
	~PluginCostFunction() override = default;

	/// @brief Make a copy of this object.
	ParentSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	PluginCostFunctionSP
	deep_clone() const;

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

	/// @brief Get the category for this MasalaDataRepresentation.
	/// @returns { { "CostFunction" } }.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the keywords for this MasalaDataRepresentation.
	/// @returns { "optimization_problem", "cost_function", "numeric" }
	std::vector< std::string >
	get_data_representation_keywords() const override;

	/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
	/// is compatible.
	/// @returns An empty list.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this MasalaDataRepresentation.
	/// @returns { "cost_function" }.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

	/// @brief Get the class name ("PluginCostFunction").
	static
	std::string class_name_static();

	/// @brief Get the class namespace ("masala::numeric_api::base_classes::optimization::cost_function_network::cost_function").
	static
	std::string class_namespace_static();

	/// @brief Get the class name.  Calls class_name_static().
	std::string class_name() const override;

	/// @brief Get the class namespace.  Calls class_namespace_static().
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Does this class use a cost function scratch space?
	/// @details Returns false by default.  May be overridden by derived classes to return true.  If this returns true,
	/// then it is expected that (a) generate_cost_function_scratch_space() returns a non-null pointer to a suitable object
	/// derived from CostFunctionScratchSpace, and (b) compute_cost_function() and compute_cost_function_difference() accept
	/// an object of that type and use it.
	virtual
	bool
	uses_cost_function_scratch_space() const;

	/// @brief Generate a suitable object of type CostFunctionScratchSpace (by shared pointer).
	/// @details Base class generates nullptr.  May be overridden by derived classes, which should
	/// return a suitable class derived from CostFunctionScratchSpace which can be accepted by compute_cost_function()
	/// and compute_cost_function_difference() function overrides.
	virtual
	PluginCostFunctionScratchSpaceSP
	generate_cost_function_scratch_space() const;

	/// @brief Given a selection of choices at variable nodes, compute the cost function.
	/// @details Must be implemented by derived classes.
	/// @param[in] candidate_solution The current solution, expressed as a vector of variable node indices.
	/// @param[in] scratch_space A pointer to a PluginCostFunctionScratchSpace object.  Thie could be nullptr.  If non-null,
	/// then the derived class must check that this is an appropriate PluginCostFunctionScratchSpace type and use it appropriately.
	/// This is to help to make calculations more efficient on re-evaluation by caching relevant information from past evaluations.
	virtual
	masala::base::Real
	compute_cost_function(
		std::vector< masala::base::Size > const & candidate_solution,
		PluginCostFunctionScratchSpace * scratch_space
	) const = 0;

	/// @brief Given an old selection of choices at variable nodes and a new selection,
	/// compute the cost function difference.
	/// @details Must be implemented by derived classes.
	/// @param[in] candidate_solution_old The previous solution, expressed as a vector of variable node indices.
	/// @param[in] candidate_solution_new The new solution, expressed as a vector of variable node indices.
	/// @param[in] scratch_space A pointer to a PluginCostFunctionScratchSpace object.  Thie could be nullptr.  If non-null,
	/// then the derived class must check that this is an appropriate PluginCostFunctionScratchSpace type and use it appropriately.
	/// This is to help to make calculations more efficient on re-evaluation by caching relevant information from past evaluations.
	virtual
	masala::base::Real
	compute_cost_function_difference(
		std::vector< masala::base::Size > const & candidate_solution_old,
		std::vector< masala::base::Size > const & candidate_solution_new,
		PluginCostFunctionScratchSpace * scratch_space
	) const = 0;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is this data representation empty?
	/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
	/// @returns True if no data have been loaded into this data representation, false otherwise.
	/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
	bool
	protected_empty() const override;

	/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
	/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
	void
	protected_clear() override;

	/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
	/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
	void
	protected_reset() override;

	/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
	/// by derived classses.  Performs no mutex-locking.
	void
	protected_make_independent() override;

	/// @brief Assignment operator, assuming that we've already locked the write mutex.
	void protected_assign( masala::base::managers::engine::MasalaDataRepresentation const & src ) override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////


}; // class PluginCostFunction

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_cost_function_network_cost_function_PluginCostFunction_hh