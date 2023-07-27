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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunction.cc
/// @brief Implementation for a non-instantiable base class for PluginCostFunctions.
/// @details PluginCostFunctions define a penalty function for a given solution to a cost
/// function network optimization problem.  (That is, given a selection of one choice
/// per node, produce a numerical value.)  The PluginCostFunction class derives from CostFunction,
/// and permits cost functions to be defined in plug-in libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunction.hh>

// Numeric headers:

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor (protected in API).
PluginCostFunction::PluginCostFunction(
    PluginCostFunction const & src
) :
    masala::numeric::optimization::cost_function_network::cost_function::CostFunction( src )
{
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    assign_mutex_locked( src );
}

// @brief Assignment operator.
PluginCostFunction &
PluginCostFunction::operator=(
    PluginCostFunction const & src
) {
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    assign_mutex_locked( src );
    return *this;
}

/// @brief Make a copy of this object.
masala::numeric::optimization::cost_function_network::cost_function::CostFunctionSP
PluginCostFunction::clone() const {
    return masala::make_shared< PluginCostFunction >(*this);
}

/// @brief Make a fully independent copy of this object.
PluginCostFunctionSP
PluginCostFunction::deep_clone() const {
    PluginCostFunctionSP new_object( std::static_pointer_cast< PluginCostFunction >( clone() ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everything is deep-cloned.)
void
PluginCostFunction::make_independent() {
    std::lock_guard< std::mutex > lock( mutex() );
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
PluginCostFunction::get_categories() const {
	return std::vector< std::vector< std::string > > {
		{ "CostFunction" }
	};
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric" }
std::vector< std::string >
PluginCostFunction::get_keywords() const {
	return std::vector< std::string > {
		"optimization_problem",
		"cost_function",
		"numeric"
	};
}

/// @brief Get the category for this MasalaDataRepresentation.
/// @returns { { "CostFunction" } }.
std::vector< std::vector< std::string > >
PluginCostFunction::get_data_representation_categories() const {
    return std::vector< std::vector< std::string > >{ { "CostFunction" } };
}

/// @brief Get the non-exhaustive list of engines with which this MasalaDataRepresentation
/// is compatible.
/// @returns An empty list.
std::vector< std::string >
PluginCostFunction::get_compatible_masala_engines() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation.
/// @returns { "cost_function" }.
std::vector< std::string >
PluginCostFunction::get_present_data_representation_properties() const {
    return std::vector< std::string >{ "cost_function" };
}

/// @brief Get the class name ("PluginCostFunction").
/*static*/
std::string
PluginCostFunction::class_name_static() {
    return "PluginCostFunction";
}

/// @brief Get the class namespace ("masala::numeric_api::base_classes::optimization::cost_function_network::cost_function").
/*static*/
std::string
PluginCostFunction::class_namespace_static() {
    return "masala::numeric_api::base_classes::optimization::cost_function_network::cost_function";
}

/// @brief Get the class name.  Calls class_name_static().
std::string
PluginCostFunction::class_name() const {
    return class_name_static();
}

/// @brief Get the class namespace.  Calls class_namespace_static().
std::string
PluginCostFunction::class_namespace() const {
    return class_namespace_static();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala
