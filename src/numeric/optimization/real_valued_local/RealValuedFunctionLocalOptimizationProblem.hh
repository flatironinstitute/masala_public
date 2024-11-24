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

/// @file src/numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.hh
/// @brief Headers for a class for a RealValuedFunctionLocalOptimizationProblem.
/// @details A RealValuedFunctionLocalOptimizationProblem defines a numerical minimization function to be solved by
/// gradient-based methods or other local optimization methods for an arbitrary loss function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationProblem_hh
#define Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationProblem_hh

// Forward declarations:
#include <numeric/optimization/real_valued_local/RealValuedFunctionLocalOptimizationProblem.fwd.hh>

// Parent header:
#include <numeric/optimization/OptimizationProblem.hh>

// Base headers:
#include <base/types.hh>

// External headers:
#include <external/eigen/Eigen/Core>

// STL headers:
#include <functional>
#include <vector>
#include <utility>

namespace masala {
namespace numeric {
namespace optimization {
namespace real_valued_local {

/// @brief A class for a RealValuedFunctionLocalOptimizationProblem.
/// @details A RealValuedFunctionLocalOptimizationProblem defines a numerical minimization function to be solved by
/// gradient-based methods for an arbitrary loss function.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class RealValuedFunctionLocalOptimizationProblem : public masala::numeric::optimization::OptimizationProblem {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	RealValuedFunctionLocalOptimizationProblem() = default;

	/// @brief Copy constructor.
	RealValuedFunctionLocalOptimizationProblem( RealValuedFunctionLocalOptimizationProblem const & src );

	// @brief Assignment operator.
	RealValuedFunctionLocalOptimizationProblem &
	operator=( RealValuedFunctionLocalOptimizationProblem const & src );

	/// @brief Destructor.
	~RealValuedFunctionLocalOptimizationProblem() override;

	/// @brief Make a copy of this object, and return a shared pointer to the copy.
	/// @details Does NOT copy all the internal data, but retains pointers to existing data.
	masala::numeric::optimization::OptimizationProblemSP
	clone() const override;

	/// @brief Make a fully independent copy of this object.
	RealValuedFunctionLocalOptimizationProblemSP
	deep_clone() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { { "OptimizationProblem", "RealValuedFunctionLocalOptimizationProblem" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "local", "real_valued", "numeric" }
	std::vector< std::string >
	get_keywords() const override;
	
	/// @brief Get the category for this MasalaDataRepresentation.
	/// @returns { { "OptimizationProblem", "RealValuedFunctionLocalOptimizationProblem" } }.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the keywords that this data representation plugin has.
	/// @details Categories are hierarchical, with the hierarchy represented as a vector of
	/// strings.  One data representation category can be classified into multiple categories.
	/// @returns { "optimization_problem", "local", "real_valued", "numeric" }
	std::vector< std::string >
	get_data_representation_keywords() const override;

	/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
	/// is compatible.
	/// @returns An empty list.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this MasalaDataRepresentation.
	/// @returns { "optimization_problem", "real_valued_local_optimization_problem" }.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

	/// @brief Get the name of this class.
	/// @returns "RealValuedFunctionLocalOptimizationProblem".
	std::string
	class_name() const override;

	/// @brief Get the namespace for this class.
	/// @returns "masala::numeric::optimization::real_valued_local".
	std::string
	class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Has an objective function been provided for this problem?
	bool has_objective_function() const;

	/// @brief Has a gradient for the objective function been provided for this problem?
	bool has_objective_function_gradient() const;

	/// @brief Has at least one starting point been provided for this problem?
	bool has_at_least_one_starting_point() const;

	/// @brief Get the objective function.
	/// @details Throws if objective function isn't set.
	std::function< masala::base::Real( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) > const &
	objective_function() const;

	/// @brief Get the objective function gradient.
	/// @details Throws if objective function gradient isn't set.
	std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) > const &
	objective_function_gradient() const;

	/// @brief Access the vector of starting points.
	std::vector< Eigen::Vector< masala::base::Real, Eigen::Dynamic > > const &
	starting_points() const;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the objective function.
	/// @details The function object is copied.
	void
	set_objective_function(
		std::function< masala::base::Real( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) > const & objective_fxn_in
	);

	/// @brief Clear the objective function.
	void
	clear_objective_function();

	/// @brief Set the objective function derivative.
	/// @details The derivative function object is copied.
	void
	set_objective_function_gradient(
		std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &, Eigen::Vector< masala::base::Real, Eigen::Dynamic > & ) > const & objective_fxn_gradient_in
	);

	/// @brief Clear the objective function gradient.
	void
	clear_objective_function_gradient();

	/// @brief Add a bunch of starting points to the set of starting points for local minimum search.
	void
	add_starting_points(
		std::vector< Eigen::Vector< masala::base::Real, Eigen::Dynamic > > const & starting_points_in
	);

	/// @brief Add a single point to the set of starting points for local minimum search.
	void
	add_starting_point(
		Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & starting_point_in
	);

	/// @brief Clear the starting points.
	void
	clear_starting_points();

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
//////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a description of the API for the RealValuedFunctionLocalOptimizationProblem class.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

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

	/// @brief Reset this object completely.  Mutex must be locked before calling.
	void protected_reset() override;

	/// @brief Make this object independent.
	/// @details Assumes mutex was already locked.
	/// @note Derived versions of this function should call the parent class version too.
	void protected_make_independent() override;

	/// @brief Inner workings of finalize function.  Should be called with locked mutex.	
	/// @details Base class protected_finalize() sets finalized_ to true, so this calls that.
	void protected_finalize() override;

	/// @brief Inner workings of assignment operator.  Should be called with locked mutex.
	/// Should be implemented by derived classes, which shoudl call base class function.
	void protected_assign( masala::base::managers::engine::MasalaDataRepresentation const & src ) override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

/// @brief The objective function for which we're trying to find a local minimum, evaluated
/// at some point in R^N.
/// @details Stored by raw pointer; could be nullptr.  The owner of the function object is
/// the RealValuedFunctionLocalOptimizationProblem, which cleans it up on destruction.
std::function< masala::base::Real ( Eigen::Vector< masala::base::Real, Eigen::Dynamic > const & ) > const * objective_function_ = nullptr;

/// @brief A function that returns the objective function value, and also computes and sets
/// the objective function gradient at a particular point in R^N.
/// @details Stored by raw pointer; could be nullptr.  The owner of the function object is
/// the RealValuedFunctionLocalOptimizationProblem, which cleans it up on destruction.
std::function<
	masala::base::Real (
		Eigen::Vector< masala::base::Real, Eigen::Dynamic > const &,
		Eigen::Vector< masala::base::Real, Eigen::Dynamic > &
	)
> const * objective_function_gradient_ = nullptr;

/// @brief Starting points for the local minimum search.
std::vector< Eigen::Vector< masala::base::Real, Eigen::Dynamic > > starting_points_;

}; // class RealValuedFunctionLocalOptimizationProblem

} // namespace real_valued_local
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_real_valued_local_RealValuedFunctionLocalOptimizationProblem_hh