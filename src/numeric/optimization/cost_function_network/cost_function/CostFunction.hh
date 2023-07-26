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
/// @brief Header for a non-instantiable base class for CostFunctions.
/// @details CostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh>

// Parent header:
#include <base/managers/engine/MasalaDataRepresentation.hh>

// Numeric headers:

// Base headers:
#include <base/types.hh>

// STL headers:
#include <mutex>
#include <atomic>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

/// @brief A non-instantiable base class for CostFunctions.
/// @details CostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunction : public masala::base::managers::engine::MasalaDataRepresentation {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor (protected in API).
	CostFunction();

	/// @brief Copy constructor (protected in API).
	CostFunction( CostFunction const & src );

	// @brief Assignment operator.
	CostFunction &
	operator=( CostFunction const & src );

	/// @brief Destructor.
	~CostFunction() override = default;

	/// @brief Make a copy of this object.
	virtual
	CostFunctionSP
	clone() const;

	/// @brief Make a fully independent copy of this object.
	CostFunctionSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
	virtual
	void make_independent();

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

	/// @brief Get the class name ("CostFunction").
	static
	std::string class_name_static();

	/// @brief Get the class namespace ("masala::numeric::optimization::cost_function_network::cost_function").
	static
	std::string class_namespace_static();

	/// @brief Get the class namespace and name
	/// ("masala::numeric::optimization::cost_function_network::cost_function::CostFunction").
	static
	std::string class_namespace_and_name_static();

	/// @brief Get the class name.  Calls class_name_static().
	std::string class_name() const override;

	/// @brief Get the class namespace.  Calls class_namespace_static().
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Has this object been finalized?
	/// @details Locks write mutex for check.
	bool finalized() const;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the weight for this penalty function.
	/// @details Function must not have been finalized.
	void set_weight( masala::base::Real const weight_in );

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Indicate that all data input is complete.
	/// @param[in] variable_node_indices A list of all of the absolute node indices
	/// for nodes that have more than one choice, indexed by variable node index.
	void
	finalize(
		std::vector< masala::base::Size > const & variable_node_indices
	);

	/// @brief Given a selection of choices at variable nodes, compute the cost function.
	/// @details This version returns 0; must be overridden by derived classes.
	virtual
	masala::base::Real
	compute_cost_function(
		std::vector< masala::base::Size > const & candidate_solution
	) const;

	/// @brief Given an old selection of choices at variable nodes and a new selection,
	/// compute the cost function difference.
	/// @details This version returns 0; must be overridden by derived classes.
	virtual
	masala::base::Real
	compute_cost_function_difference(
		std::vector< masala::base::Size > const & candidate_solution_old,
		std::vector< masala::base::Size > const & candidate_solution_new
	) const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the API definition for this (non-instantiable) class.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Indicate that all data input is complete.  Performs no mutex-locking.
	/// @param[in] variable_node_indices A list of all of the absolute node indices
	/// for nodes that have more than one choice, indexed by variable node index.
	/// @details The base class function simply marks this object as finalized.  Should
	/// be overridden, and overrides should call parent class protected_finalize().
	virtual
	void
	protected_finalize(
		std::vector< masala::base::Size > const & variable_node_indices
	);

	/// @brief Assignment operator, assuming that we've already locked the write mutex.
	virtual void assign_mutex_locked( CostFunction const & src );

	/// @brief Allow derived classes to access the mutex.
	inline std::mutex & mutex() const { return mutex_; }

	/// @brief Has this object been finalized?
	/// @details Performs no locking of write mutex for check.
	bool protected_finalized() const;

	/// @brief Make this object fully independent.  Assumes mutex was already locked.
	/// Should be called by overrides.
	virtual
	void
	make_independent_mutex_locked();

	/// @brief Access the API definition.  Mutex must be locked by calling function.
	inline
	masala::base::api::MasalaObjectAPIDefinitionCSP &
	api_definition_mutex_locked() {
		return api_definition_;
	}

	/// @brief Access the weight.
	/// @details Should only be used in contexts in which the mutex is locked,
	/// or in which the object is finailized.
	masala::base::Real
	protected_weight() const {
		return weight_;
	}

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for data-loading.  Not used during access phase.
	mutable std::mutex mutex_;

	/// @brief An atomic bool for whether this object is finalized.
	std::atomic_bool finalized_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief A weighting factor by which the computed penalty function is multiplied.
	masala::base::Real weight_ = 1.0;

}; // class CostFunction

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunction_hh