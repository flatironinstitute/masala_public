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
    Parent()
{
    std::lock( src.data_representation_mutex(), data_representation_mutex() );
    std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock );
    protected_assign( src );
}

// @brief Assignment operator.
PluginCostFunction &
PluginCostFunction::operator=(
    PluginCostFunction const & src
) {
    std::lock( src.data_representation_mutex(), data_representation_mutex() );
    std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock );
    protected_assign( src );
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

/// @brief Get the keywords for this MasalaDataRepresentation.
/// @returns { "optimization_problem", "cost_function", "numeric" }
std::vector< std::string >
PluginCostFunction::get_data_representation_keywords() const {
    return std::vector< std::string > {
		"optimization_problem",
		"cost_function",
		"numeric"
	};
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
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
PluginCostFunction::protected_empty() const {
    return Parent::protected_empty();
}

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
PluginCostFunction::protected_clear() {
    Parent::protected_clear();
}

/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
void
PluginCostFunction::protected_reset() {
    Parent::protected_reset();
}

/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
/// by derived classses.  Performs no mutex-locking.
void
PluginCostFunction::protected_make_independent() {
    Parent::protected_make_independent();
}

/// @brief Assignment operator, assuming that we've already locked the write mutex.
void
PluginCostFunction::protected_assign(
    masala::base::managers::engine::MasalaDataRepresentation const & src
) {
    CHECK_OR_THROW_FOR_CLASS( dynamic_cast< PluginCostFunction const * >( &src ) != nullptr, "protected_assign",
        "Unable to assign an object of type " + src.class_name() + " to a PluginCostFunction."
    );
    Parent::protected_assign(src);
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
