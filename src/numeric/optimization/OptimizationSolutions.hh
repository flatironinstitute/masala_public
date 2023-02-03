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

/// @file src/numeric/optimization/OptimizationSolutions.hh
/// @brief Header for a base class for OptimizationSolutions continer.
/// @details The OptimizationSolutions container holds a collection of OptimizationSolution objects.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_OptimizationSolutions_hh
#define Masala_src_numeric_optimization_OptimizationSolutions_hh

// Forward declarations:
#include <numeric/optimization/OptimizationSolutions.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Numeric headers:
#include <numeric/optimization/OptimizationSolution.fwd.hh>
#include <base/types.hh>

// STL headers:
#include <mutex>
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {

/// @brief A base class for OptimizationSolutions continer.
/// @details The OptimizationSolutions container holds a collection of OptimizationSolution objects.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class OptimizationSolutions : public masala::base::managers::plugin_module::MasalaPlugin {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	OptimizationSolutions() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.  Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	OptimizationSolutions( OptimizationSolutions const & );

	/// @brief Assignment operator.
	/// @details Copies the pointers to, but does not deep-clone,
	/// the optimization solutions.
	OptimizationSolutions &
	operator=(
		OptimizationSolutions const &
	);

	/// @brief Destructor.
	~OptimizationSolutions() override = default;

	/// @brief Make a fully independent copy of this object.
	OptimizationSolutionsSP
	deep_clone() const;

	/// @brief Ensure that all data are unique and not shared
	/// (i.e. everytihng is deep-cloned.)
	void make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { { "OptimizationSolutions" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization solutions; may be overridden by derived classes.
	/// @returns { "optimization_solutions", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the class name.
	/// @returns "OptimizationSolutions".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the OptimizationSolutions class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object, clearing its solution list.
	virtual
	void
	reset();

	/// @brief Add an optimization solution to the list of optimization solutions
	/// stored in this container.
	/// @details Derived classes should override this to check the type of the
	/// optimization solution stored.
	virtual
	void
	add_optimization_solution(
		OptimizationSolutionSP solution_in
	);

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the ith solution in this object, where the index is zero-based.
	/// @details Does bounds-checking.  Throws if out of range.  Use the
	/// n_solutions() method to check number of solutions.
	OptimizationSolutionCSP
	solution(
		masala::base::Size const index
	) const;

	/// @brief Get the number of solutions stored in this object.
	masala::base::Size n_solutions() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Sort all of the solutions stored in this object by score.
	void sort_by_score();
	
protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Allow derived classes to access the mutex for this object.
	/// @note The mutex is mutable, and can be locked from a const function.
	std::mutex & solutions_mutex() const;

	/// @brief Allow derived classes to access the API definition.
	/// @note Could be nullptr.  This does NOT lock the mutex.
	masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition();

	/// @brief Allow derived classes to access the vector of optimization solutions.
	/// @details This does NOT lock the solutions_mutex_ mutex.  Calling functions must
	/// do this first.
	std::vector< OptimizationSolutionSP > & optimization_solutions();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this object.
	mutable std::mutex solutions_mutex_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief The contained vector of OptimizationSolutions
	std::vector< OptimizationSolutionSP > optimization_solutions_;

}; // class OptimizationSolutions

} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_OptimizationSolutions_hh