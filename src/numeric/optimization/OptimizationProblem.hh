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

/// @file src/numeric/optimization/OptimizationProblem.hh
/// @brief Header for a base class for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_OptimizationProblem_hh
#define Masala_src_numeric_optimization_OptimizationProblem_hh

// Forward declarations:
#include <numeric/optimization/OptimizationProblem.fwd.hh>

// Parent header:
#include <base/managers/engine/MasalaDataRepresentation.hh>
#include <numeric/optimization/OptimizationSolutions.fwd.hh>

// STL headers:
#include <mutex>
#include <atomic>

namespace masala {
namespace numeric {
namespace optimization {

/// @brief A base class for OptimizationProblems.
/// @details OptimizationProblems define a numerical optimization problem to be solved
/// by a suitable Optimizer.  They do not contain any chemistry-specific concepts.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class OptimizationProblem : public masala::base::managers::engine::MasalaDataRepresentation {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND ASSIGNMENT
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	OptimizationProblem() = default;

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.
	OptimizationProblem( OptimizationProblem const & );

	/// @brief Assignment operator.
	OptimizationProblem &
	operator=(
		OptimizationProblem const &
	);

	/// @brief Destructor.
	~OptimizationProblem() override = default;

	/// @brief Make a copy of this object, and return a shared pointer to the copy.
	/// @details Does NOT copy all the internal data, but retains pointers to existing data.
	virtual
	OptimizationProblemSP
	clone() const;

	/// @brief Make a fully independent copy of this object.
	OptimizationProblemSP
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
	/// @returns { { "OptimizationProblem" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.  Default for all
	/// optimization problems; may be overridden by derived classes.
	/// @returns { "optimization_problem", "numeric" }
	std::vector< std::string >
	get_keywords() const override;

    /// @brief Get the categories that this data representation plugin falls into.
    /// @details Categories are hierarchical, with the hierarchy represented as a vector of
    /// strings.  One data representation category can be classified into multiple categories.
    /// @returns {{ "OptimizationProblem" }}
    std::vector< std::vector< std::string > >
    get_data_representation_categories() const override;

    /// @brief Get the MasalaEngines that with which this data representation plugin
    /// is DEFINITELY compatible.  (There may be other engines with which it is also
    /// compatible, so this is not necessarily an exhaustive list.)
    /// @note Must be implemented by derived classes.  The list is by full name (i.e.
    /// namespace + name), so for instance
    /// "specialized_masala_plugins::optimizers::SpecializedChargeOptimizer".
	/// @returns An empty list.
    std::vector< std::string >
    get_compatible_masala_engines() const override;

	/// @brief Get the class name.
	/// @returns "OptimizationProblem".
	std::string class_name() const override;

	/// @brief Get the class namespace.
	/// @returns "masala::numeric::optimization".
	std::string class_namespace() const override;

	/// @brief Reset all data in this object.
	void
	reset();

	/// @brief Finalize this problem: indicate that all problem setup is complete, and
	/// carry out any precomputation necessary for efficient solution.
	/// @details Derived classes should probably override this.
	void
	finalize();

	/// @brief Has this problem been finalized?
	/// @details Locks mutex for check.
	bool
	finalized() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the OptimizationProblem class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Create a solutions container for this type of optimization problem.
	/// @details Base class implementation creates a generic OptimizationSolutions container.  Derived
	/// classes may override this to create specialized solutions containers.
	virtual
	OptimizationSolutionsSP
	create_solutions_container() const;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Allow derived classes to access the mutex for this object.
	/// @note The mutex is mutable, and can be locked from a const function.
	std::mutex & problem_mutex() const;

	/// @brief Allow derived classes to access the API definition.
	/// @note Could be nullptr.
	masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition();

	/// @brief Allow derived classes to access whether this object is finalized.
	/// @note Assumes problem mutex was locked.
	inline bool protected_finalized() const { return finalized_.load(); }

	/// @brief Inner workings of finalize function.  Should be called with locked mutex.
	/// Base class protected_finalize() sets finalized_ to true.
	virtual void protected_finalize();

	/// @brief Reset all data in this object.
	/// @details Sets state to not finalized.  Mutex must be locked before calling this.
	virtual void protected_reset();

	/// @brief Make this object independent.
	/// @details Assumes mutex was already locked.
	/// @note Derived versions of this function should call the parent class version too.
	virtual void protected_make_independent();


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this object.
	mutable std::mutex problem_mutex_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief Has the problem setup been finalized?
	std::atomic_bool finalized_ = false;

}; // class OptimizationProblem

} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_OptimizationProblem_hh