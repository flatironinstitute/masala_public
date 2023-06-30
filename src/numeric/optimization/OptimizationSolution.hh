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

/// @file src/numeric/optimization/OptimizationSolution.hh
/// @brief Header for a pure virtual base class for OptimizationSolutions.
/// @details An OptimizationSolution contains the solution to a particular OptimizationProblem,
/// after it is solved by a suitable Optimizer.  It does not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_OptimizationSolution_hh
#define Masala_src_numeric_optimization_OptimizationSolution_hh

// Forward declarations:
#include <numeric/optimization/OptimizationSolution.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Numeric headers:
#include <numeric/optimization/OptimizationProblem.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace numeric {
namespace optimization {

/// @brief A pure virtual base class for OptimizationSolutions.
/// @details An OptimizationSolution contains the solution to a particular OptimizationProblem,
/// after it is solved by a suitable Optimizer.  It does not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class OptimizationSolution : public masala::base::managers::plugin_module::MasalaPlugin {

public:

	/// @brief Default constructor.
	OptimizationSolution() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.
	OptimizationSolution( OptimizationSolution const & );

	/// @brief Assignment operator.
	OptimizationSolution &
	operator=(
		OptimizationSolution const &
	);

	/// @brief Destructor.
	~OptimizationSolution() override = default;

	/// @brief Make a copy of this object.
	/// @details Must be implemented for derived classes.
	virtual
	OptimizationSolutionSP
	clone() const;

	/// @brief Make a fully independent copy of this object.
	OptimizationSolutionSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared
	/// (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationSolution" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "optimization_solution", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the class name.
	/// @returns "OptimizationSolution".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the score for this solution.
	void set_solution_score( masala::base::Real const score_in );

	/// @brief Set the problem that gave rise to this solution.
	/// @details Cloned on input.  Can be overridden by derived classes
	/// to add checks that the problem type is correct.
	virtual void set_problem( OptimizationProblemCSP const & problem );

	/// @brief Increment the number of times that the solution was produced by 1.
	///	@details An optimizer might produce the same solution many times.  This is
	/// the count of the number of times this solution was produced during optimization.
	void increment_n_times_solution_was_produced();

	/// @brief Increment the number of times that the solution was produced by additional_times_produced.
	///	@details An optimizer might produce the same solution many times.  This is
	/// the count of the number of times this solution was produced during optimization.
	void increment_n_times_solution_was_produced( masala::base::Size const additional_times_produced );

	/// @brief Set the number of times that the solution was produced.
	///	@details An optimizer might produce the same solution many times.  This is
	/// the count of the number of times this solution was produced during optimization.
	void set_n_times_solution_was_produced( masala::base::Size const n_times_produced );

	/// @brief Set the solution vector for this problem.
	/// @details If the problem has been set, this solution vector must be of compatible size.
	/// @note Overloaded to allow different data type inputs in derived classes.
	virtual void
	set_solution_vector(
		std::vector< masala::base::Size > const & solution_vector_in
	);

	/// @brief Set the solution vector for this problem.
	/// @details If the problem has been set, this solution vector must be of compatible size.
	/// @note Overloaded to allow different data type inputs in derived classes.
	virtual void
	set_solution_vector(
		std::vector< bool > const & solution_vector_in
	);

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the score for this solution.
	masala::base::Real solution_score() const;

	/// @brief Access the problem.
	OptimizationProblemCSP problem() const;

	/// @brief Get the number of times that the solution was produced.
	///	@details An optimizer might produce the same solution many times.  This is
	/// the count of the number of times this solution was produced during optimization.
	masala::base::Size n_times_solution_was_produced() const;

	/// @brief Get the solution vector for this problem.
	/// @details This returns the solution vector as one value per
	/// variable position, in order of variable positions.  Indices
	/// in the vector do NOT necessarily correspond to node indices,
	/// since nodes with zero or one choice are omitted.
	/// @note Problem and solution vector must have been set.
	virtual 
	std::vector< masala::base::Size >
	solution_at_variable_positions() const;

	/// @brief Get the solution vector for this problem.
	/// @details This returns the solution vector as one value per
	/// position, in order of all positions.  Indices in the vector
	/// correspond to node indices.
	/// @note Problem and solution vector must have been set.
	virtual 
	std::vector< masala::base::Size >
	solution_at_all_positions() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Recompute the score of this solution.  This is useful, for instance, after
	/// an optimizer that uses approximate methods or low floating-point precision completes
	/// its work, to allow scores to be stored with full floating-point precision and accuracy.
	/// @details The problem_ pointer must be set.
	/// @note The base class recompute_score() function throws.  Derived classes
	/// must override this and provide their own implementations.
	virtual void recompute_score();

	/// @brief Determine whether this solution is the same as another.
	/// @details Compares the stored solution vector to a provided solution vector.
	/// @note Overloaded to allow different data type inputs in derived classes.
	virtual bool operator==( std::vector< masala::base::Size > const & other_solution_vector ) const;

	/// @brief Determine whether this solution is the same as another.
	/// @details Compares the stored solution vector to a provided solution vector.
	/// @note Overloaded to allow different data type inputs in derived classes.
	virtual bool operator==( std::vector< bool > const & other_solution_vector ) const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the OptimizationSolution class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Allow derived classes to access the mutex for this object.
	/// @note The mutex is mutable, and can be locked from a const function.
	std::mutex & solution_mutex() const;

	/// @brief Allow derived classes to access the API definition.
	/// @note Could be nullptr.
	masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition();

	/// @brief Access the solution score from derived classes.
	/// @details Performs no mutex locking.  Should be called from a mutex-locked
	/// context only.
	masala::base::Real & protected_solution_score();

	/// @brief Const access to the solution score from derived classes.
	/// @details Performs no mutex locking.  Should be called from a mutex-locked
	/// context only.
	masala::base::Real const & protected_solution_score() const;

	/// @brief Access the problem.
	/// @details Performs no mutex locking.  Should be called from a mutex-locked
	/// context only.  May return nullptr.
	OptimizationProblemCSP & protected_problem();

	/// @brief Access the problem.  Const version.
	/// @details Performs no mutex locking.  Should be called from a mutex-locked
	/// context only.  May return nullptr.
	OptimizationProblemCSP const & protected_problem() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this object.
	mutable std::mutex solution_mutex_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief A score associated with this solution.
	masala::base::Real solution_score_ = 0.0;

	/// @brief The problem that gave rise to this solution.
	OptimizationProblemCSP problem_;

	/// @brief An optimizer might produce the same solution many times.  This is
	/// the count of the number of times this solution was produced during optimization.
	masala::base::Size n_times_solution_was_produced_ = 1;

}; // class OptimizationSolution

} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_OptimizationSolution_hh