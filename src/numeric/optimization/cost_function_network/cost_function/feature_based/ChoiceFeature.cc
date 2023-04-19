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

/// @file src/numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.cc
/// @brief Implementation for a class for ChoiceFeatures.
/// @details ChoiceFeatures are objects attached to node choices, which can form connections across
/// choices at different nodes.  Each feature has a minimum and maximum number of connections that
/// it must make to be satisfied.
/// @note This class is a lightweight class that offers no thread safety.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.hh>

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
namespace feature_based {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy this object and return a shared pointer to the copy.
ChoiceFeatureSP
ChoiceFeature::clone() const {
    return masala::make_shared< ChoiceFeature >( *this );
}

/// @brief Ensure that this object is fully independent.
void
ChoiceFeature::make_independent() {
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the category or categories for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { { "ChoiceFeature" } }
/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
/// in more than one hierarchical category (in which case there would be more than one
/// entry in the outer vector), but must be in at least one.  The first one is used as
/// the primary key.
std::vector< std::vector< std::string > >
ChoiceFeature::get_categories() const {
	return std::vector< std::vector< std::string > >{ { "ChoiceFeature" } };
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric", "choice_feature" }
std::vector< std::string >
ChoiceFeature::get_keywords() const {
    return std::vector< std::string >{ "optimization_problem", "cost_function", "numeric", "choice_feature" };
}

/// @brief This returns the class name ("ChoiceFeature").
std::string
ChoiceFeature::class_name() const {
    return "ChoiceFeature";
}

/// @brief This returns the class namespace ("masala::numeric::optimization::cost_function_network::cost_function::feature_based").
std::string
ChoiceFeature::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network::cost_function::feature_based";
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
