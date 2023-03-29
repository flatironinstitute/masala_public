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

/// @file src/numeric/optimization/cost_function_network/cost_function/CostFunction.cc
/// @brief Implementation for a non-instantiable base class for CostFunctions.
/// @details CostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Numeric headers:

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor (protected in API).
CostFunction::CostFunction() :
    masala::base::managers::plugin_module::MasalaPlugin(),
    finalized_(false)
{}

/// @brief Copy constructor (protected in API).
CostFunction::CostFunction(
    CostFunction const & src
) :
    masala::base::managers::plugin_module::MasalaPlugin( src )
{
    std::lock( src.mutex_, mutex_ );
    std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
    assign_mutex_locked( src );
}

// @brief Assignment operator.
CostFunction &
CostFunction::operator=(
    CostFunction const & src
) {
    std::lock( src.mutex_, mutex_ );
    std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
    assign_mutex_locked( src );
    return *this;
}

/// @brief Make a copy of this object.
CostFunctionSP
CostFunction::clone() const {
    return masala::make_shared< CostFunction >(*this);
}

/// @brief Make a fully independent copy of this object.
CostFunctionSP
CostFunction::deep_clone() const {
    CostFunctionSP new_object( clone() );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
void
CostFunction::make_independent() {
    std::lock_guard< std::mutex > lock( mutex_ );
    make_independent_mutex_locked();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "CostFunction" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
CostFunction::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunction" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric" }
std::vector< std::string >
CostFunction::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function",
		"numeric"
	};
}

/// @brief Get the class name ("CostFunction").
/*static*/
std::string
CostFunction::class_name_static() {
    return "CostFunction";
}

/// @brief Get the class namespace ("masala::numeric::optimization::cost_function_network::cost_function").
/*static*/
std::string
CostFunction::class_namespace_static() {
    return "masala::numeric::optimization::cost_function_network::cost_function";
}

/// @brief Get the class namespace and name
/// ("masala::numeric::optimization::cost_function_network::cost_function::CostFunction").
/*static*/
std::string
CostFunction::class_namespace_and_name_static() {
    return class_namespace_static() + "::" + class_name_static();
}

/// @brief Get the class name.  Calls class_name_static().
std::string
CostFunction::class_name() const {
    return class_name_static();
}

/// @brief Get the class namespace.  Calls class_namespace_static().
std::string
CostFunction::class_namespace() const {
    return class_namespace_static();
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Has this object been finalized?
/// @details Locks write mutex for check.
bool
CostFunction::finalized() const {
    std::lock_guard< std::mutex > lock( mutex_ );
    return protected_finalized();
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the weight for this penalty function.
/// @details Function must not have been finalized.
void
CostFunction::set_weight(
    masala::base::Real const weight_in
) {
    std::lock_guard< std::mutex > lock( mutex_ );
    CHECK_OR_THROW_FOR_CLASS( !protected_finalized(), "set_weight", "The weight for a " + class_name()
        + " cost function cannot be set after the object is finalized."
    );
    write_to_tracer( "Set weight for " + class_name() + " cost function to " + std::to_string(weight_in) + "." );
    weight_ = weight_in;
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Indicate that all data input is complete.
/// @param[in] variable_node_indices A list of all of the absolute node indices
/// for nodes that have more than one choice, indexed by variable node index.
void
CostFunction::finalize(
    std::vector< masala::base::Size > const & variable_node_indices
) {
    std::lock_guard< std::mutex > lock( mutex_ );
    protected_finalize( variable_node_indices );
}

/// @brief Given a selection of choices at variable nodes, compute the cost function.
/// @details This version returns 0; must be overridden by derived classes.
masala::base::Real
CostFunction::compute_cost_function(
    std::vector< masala::base::Size > const & /*candidate_solution*/
) const {
    return 0.0;
}

/// @brief Given an old selection of choices at variable nodes and a new selection,
/// compute the cost function difference.
/// @details This version returns 0; must be overridden by derived classes.
masala::base::Real
CostFunction::compute_cost_function_difference(
    std::vector< masala::base::Size > const & /*candidate_solution_old*/,
    std::vector< masala::base::Size > const & /*candidate_solution_new*/
) const {
    return 0.0;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the API definition for this (non-instantiable) class.
masala::base::api::MasalaObjectAPIDefinitionCWP
CostFunction::get_api_definition() {
    using namespace masala::base::api;

    std::lock_guard< std::mutex > lock( mutex_ );
    if( api_definition_ == nullptr ) {
        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this, "A cost function, used in cost function network optimization algorithms.",
                false, true
            )
        );

        ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( CostFunction, api_def );

        api_definition_ = api_def;
    }
    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Indicate that all data input is complete.  Performs no mutex-locking.
/// @param[in] variable_node_indices A list of all of the absolute node indices
/// for nodes that have more than one choice, indexed by variable node index.
/// @details The base class function simply marks this object as finalized.  Should
/// be overridden, and overrides should call parent class protected_finalize().
void
CostFunction::protected_finalize(
    std::vector< masala::base::Size > const & //variable_node_indices
) {
    CHECK_OR_THROW_FOR_CLASS( finalized_ == false, "protected_finalize", "This " + class_name() + " object has already been finalized!" );
    finalized_ = true;
}

/// @brief Assignment operator, assuming that we've already locked the write mutex.
void
CostFunction::assign_mutex_locked(
    CostFunction const & src
) {
    finalized_ = src.finalized_.load();
    api_definition_ = nullptr; // Deliberately not assigned.
    weight_ = src.weight_;
}

/// @brief Has this object been finalized?
/// @details Performs no locking of write mutex for check.
bool
CostFunction::protected_finalized() const {
    return finalized_.load();
}

/// @brief Make this object fully independent.  Assumes mutex was already locked.
/// Should be called by overrides.
void
CostFunction::make_independent_mutex_locked() {
    //GNDN.
}

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
