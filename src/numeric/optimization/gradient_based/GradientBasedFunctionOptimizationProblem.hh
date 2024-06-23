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

/// @file src/numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.hh
/// @brief Headers for a class for a GradientBasedFunctionOptimizationProblem.
/// @details A GradientBasedFunctionOptimizationProblem defines a numerical minimization function to be solved by
/// gradient-based methods for an arbitrary loss function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationProblem_hh
#define Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationProblem_hh

// Forward declarations:
#include <numeric/optimization/gradient_based/GradientBasedFunctionOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationProblem.hh>

// Numeric headers:

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <utility> //For std::pair.
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace gradient_based {

/// @brief A class for a GradientBasedFunctionOptimizationProblem.
/// @details A GradientBasedFunctionOptimizationProblem defines a numerical minimization function to be solved by
/// gradient-based methods for an arbitrary loss function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class GradientBasedFunctionOptimizationProblem : public masala::numeric::optimization::OptimizationProblem {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	GradientBasedFunctionOptimizationProblem() = default;

	/// @brief Copy constructor.
	GradientBasedFunctionOptimizationProblem( GradientBasedFunctionOptimizationProblem const & ) = default;

	// @brief Assignment operator.
	GradientBasedFunctionOptimizationProblem &
	operator=( GradientBasedFunctionOptimizationProblem const & ) = default;

	/// @brief Destructor.
	~GradientBasedFunctionOptimizationProblem() override = default;

	/// @brief Make a copy of this object, and return a shared pointer to the copy.
	/// @details Does NOT copy all the internal data, but retains pointers to existing data.
	masala::numeric::optimization::OptimizationProblemSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	GradientBasedFunctionOptimizationProblemSP
	deep_clone() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationProblem", "GradientBasedFunctionOptimizationProblem" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "gradient_based_optimization_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;
	
	/// @brief Get the category for this MasalaDataRepresentation.
	/// @returns { { "OptimizationProblem", "GradientBasedFunctionOptimizationProblem" } }.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
	/// is compatible.
	/// @returns An empty list.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this MasalaDataRepresentation.
	/// @returns { "optimization_problem", "gradient_based_optimization_problem" }.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

	/// @brief Get the name of this class.
	/// @returns "GradientBasedFunctionOptimizationProblem".
	std::string
	class_name() const override;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric::optimization::gradient_based".
	std::string
	class_namespace() const override;

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
//////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the GradientBasedFunctionOptimizationProblem class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Reset this object completely.  Mutex must be locked before calling.
	void protected_reset() override;

	/// @brief Make this object independent.
	/// @details Assumes mutex was already locked.
	/// @note Derived versions of this function should call the parent class version too.
	virtual void protected_make_independent();

	/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
	/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
	void protected_finalize() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

}; // class GradientBasedFunctionOptimizationProblem

} // namespace gradient_based
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_gradient_based_GradientBasedFunctionOptimizationProblem_hh