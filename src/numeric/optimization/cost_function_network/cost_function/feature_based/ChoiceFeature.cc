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
/// @note This class is a lightweight class that offers thread safety for setup only.
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

/// @brief Default constructor.
ChoiceFeature::ChoiceFeature() :
    masala::base::managers::plugin_manager::MasalaPlugin(),
    finalized_(false)
{}


/// @brief Copy constructor.
ChoiceFeature::ChoiceFeature(
    ChoiceFeature const & src
) {
    std::lock( src.mutex_, mutex_ );
    std::lock_guard< std::mutex > lock_this( mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lock_that( src.mutex_, std::adopt_lock );
    protected_assign( src );
}

// @brief Assignment operator.
ChoiceFeature &
ChoiceFeature::operator=( ChoiceFeature const & src ) {
    std::lock( src.mutex_, mutex_ );
    std::lock_guard< std::mutex > lock_this( mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lock_that( src.mutex_, std::adopt_lock );
    protected_assign( src );
    return *this;
}

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

/// @brief Finalize this object.
/*virtual*/
void
ChoiceFeature::finalize() {
    std::lock< std::mutex > lock(mutex_);
    protected_finalize();
}

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get an object describing the API for this object.
/// @details Default implementation returns nullptr.  May be overridden by
/// derived objects.
/// @note This is a weak pointer rather than a shared pointer since the
/// original object is expected to hold on to its API definition (which includes
/// function pointers to the functions of the instance).  Querying whether the
/// weak pointer can be converted to a shared pointer serves on a check as to
/// whether it is safe to use the function pointers.  Not ideal, but better than
/// nothing.
masala::base::api::MasalaObjectAPIDefinitionCWP
ChoiceFeature::get_api_definition() {
    using namespace masala::base::api;
    std::lock< std::mutex > lock( mutex_ );

    if( api_definition_ == nullptr ) {
        MasalaObjectAPIDefinitionSP apidef(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "An object that stores one feature on a node choice in a
                cost function optimization problem.  Features can make connections
                to other node choices, and can be satisfied by having a number
                of connections between a minimum and a maximum value.",
                true, false
            )
        )

        api_definition_ = apidef; //Nonconst to const.
    }
    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign this object based on src.  Assumes that both locks have been set.
/*virtual*/
void
ChoiceFeature::protected_assign(
    ChoiceFeature const & src
) {
    finalized_ = src.finalized_.load();
}

/// @brief Finalize this object.  Assumes mutex has been locked.
/*virtual*/
void
protected_finalize() {
    CHECK_OR_THROW_FOR_CLASS( finalized_.load() == false, "protected_finalize", "This object has already been finalized!" );
    finalized_ = true;
}

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
