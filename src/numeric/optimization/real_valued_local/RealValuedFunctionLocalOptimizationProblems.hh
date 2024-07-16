/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblems.hh
/// @brief Headers for a container for RealValuedFunctionLocalOptimizationProblems.
/// @details Each RealValuedFunctionLocalOptimizationProblem defines a numerical gradient-descent
/// minimization problem for an arbitrary loss function.  They do not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationProblems_hh
#define Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationProblems_hh

// Forward declarations:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblems.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationProblems.hh>

// Numeric headers:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.fwd.hh>

// STL headers:
#include <mutex>
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {

/// @brief A container for RealValuedFunctionLocalOptimizationProblems.
/// @details Each RealValuedFunctionLocalOptimizationProblem defines a numerical gradient-descent
/// minimization problem for an arbitrary loss function.  They do not contain any chemistry-specific
/// concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class RealValuedFunctionLocalOptimizationProblems : public masala::numeric::optimization::OptimizationProblems {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	RealValuedFunctionLocalOptimizationProblems() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.  Copies the pointers to, but does not deep-clone,
	/// the optimization problems.
	RealValuedFunctionLocalOptimizationProblems( RealValuedFunctionLocalOptimizationProblems const & ) = default;

	/// @brief Assignment operator.
	/// @details Copies the pointers to, but does not deep-clone,
	/// the optimization problems.
	RealValuedFunctionLocalOptimizationProblems &
	operator=(
		RealValuedFunctionLocalOptimizationProblems const &
	) = default;

	/// @brief Destructor.
	~RealValuedFunctionLocalOptimizationProblems() override = default;

	/// @brief Make a fully independent copy of this object.
	RealValuedFunctionLocalOptimizationProblemsSP
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
	/// @returns { { "OptimizationProblems", "RealValuedFunctionLocalOptimizationProblems" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "real_valued_local_optimization_problems", "optimization_problems", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the class name.
	/// @returns "RealValuedFunctionLocalOptimizationProblems".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization::real_valued_local".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationProblems class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object, clearing its problem list.
	void
	reset() override;

	/// @brief Add an optimization problem to the list of optimization problems
	/// stored in this container.
	/// @details Throws if the added problem is not a RealValuedFunctionLocalOptimizationProblem.
	void
	add_optimization_problem(
		OptimizationProblemSP problem_in
	) override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////


}; // class RealValuedFunctionLocalOptimizationProblems

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationProblems_hh