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

/// @file src/numeric/optimization/OptimizationProblems.hh
/// @brief Header for a container for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_OptimizationProblems_hh
#define Masala_src_numeric_optimization_OptimizationProblems_hh

// Forward declarations:
#include <numeric/optimization/OptimizationProblems.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Numeric headers:
#include <base/types.hh>
#include <numeric/optimization/OptimizationProblem.fwd.hh>

// STL headers:
#include <mutex>
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {

/// @brief A container for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class OptimizationProblems : public masala::base::managers::plugin_module::MasalaPlugin {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	OptimizationProblems() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.  Copies the pointers to, but does not deep-clone,
	/// the optimization problems.
	OptimizationProblems( OptimizationProblems const & );

	/// @brief Assignment operator.
	/// @details Copies the pointers to, but does not deep-clone,
	/// the optimization problems.
	OptimizationProblems &
	operator=(
		OptimizationProblems const &
	);

	/// @brief Destructor.
	~OptimizationProblems() override = default;

	/// @brief Make a fully independent copy of this object.
	OptimizationProblemsSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared
	/// (i.e. everything is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationProblems" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problems", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the class name.
	/// @returns "OptimizationProblems".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the OptimizationProblems class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object, clearing its problem list.
	virtual
	void
	reset();

	/// @brief Add an optimization problem to the list of optimization problems
	/// stored in this container.
	/// @details Derived classes should override this to check the type of the
	/// optimization problem stored.
	virtual
	void
	add_optimization_problem(
		OptimizationProblemSP problem_in
	);

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the ith problem in this object, where the index is zero-based.
	/// @details Does bounds-checking.  Throws if out of range.  Use the
	/// n_problems() method to check number of problems.
	OptimizationProblemCSP
	problem(
		masala::base::Size const index
	) const;

	/// @brief Nonconst access to the ith problem in this object, where the index is zero-based.
	/// @details Does bounds-checking.  Throws if out of range.  Use the
	/// n_problems() method to check number of problems.
	OptimizationProblemSP
	problem_nonconst(
		masala::base::Size const index
	);

	/// @brief Get the number of problems stored in this object.
	masala::base::Size n_problems() const;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Allow derived classes to access the mutex for this object.
	/// @note The mutex is mutable, and can be locked from a const function.
	std::mutex & problems_mutex() const;

	/// @brief Allow derived classes to access the API definition.
	/// @note Could be nullptr.  This does NOT lock the mutex.
	masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition();

	/// @brief Allow derived classes to access the vector of optimization problems.
	/// @details This does NOT lock the problems_mutex_ mutex.  Calling functions must
	/// do this first.
	std::vector< OptimizationProblemSP > & optimization_problems();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this object.
	mutable std::mutex problems_mutex_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief The contained vector of OptimizationProblems
	std::vector< OptimizationProblemSP > optimization_problems_;

}; // class OptimizationProblems

} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_OptimizationProblems_hh