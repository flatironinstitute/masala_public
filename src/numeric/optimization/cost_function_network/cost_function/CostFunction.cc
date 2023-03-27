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
/// @brief Implementation for a pure virtual base class for CostFunctions.
/// @details CostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Numeric headers:

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor.
CostFunction::CostFunction() :
    masala::base::managers::plugin_module::MasalaPlugin(),
    finalized_(false)
{}

/// @brief Copy constructor.
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

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////


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
    std::vector< masala::base::Size > const & variable_node_indices
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
}

/// @brief Has this object been finalized?
/// @details Performs no locking of write mutex for check.
bool
CostFunction::protected_finalized() const {
    return finalized_.load();
}

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namesapce masala
