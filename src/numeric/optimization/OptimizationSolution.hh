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
	/// entry in the outher vector), but must be in at least one.  The first one is used as
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

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this object.
	mutable std::mutex solution_mutex_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

}; // class OptimizationSolution

} // namespace optimization
} // namespace numeric
} // namesapce masala

#endif // Masala_src_numeric_optimization_OptimizationSolution_hh