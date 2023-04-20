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
/// @note This class is a lightweight class.  It offers thread safety during setup only.  After finalization,
/// it is read-only.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.hh>

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {
namespace feature_based {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Constructor with min and max connections for satisfaction, and
/// the offset (number of connections from internal satisfaction or background).
ChoiceFeature::ChoiceFeature(
    masala::base::Size min_connections,
    masala::base::Size max_connections,
    masala::base::Size offset /*=0*/
) :
    masala::base::managers::plugin_module::MasalaPlugin(),
    finalized_(false),
    min_connections_(min_connections),
    max_connections_(max_connections),
    offset_(offset)
{
    CHECK_OR_THROW( min_connections_ <= max_connections_,
        class_namespace_static() + "::" + class_name_static(),
        "ChoiceFeature", "The minimum number of connections "
        "must be less than or equal to the maximum."
    );
}


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

/// @brief Finalize this object.
void
ChoiceFeature::finalize() {
    std::lock_guard< std::mutex > lock( mutex_ );
    protected_finalize();
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

/// @brief This returns the class name ("ChoiceFeature").  Static version.
/*static*/
std::string
ChoiceFeature::class_name_static() {
    return "ChoiceFeature";
}

/// @brief This returns the class namespace ("masala::numeric::optimization::cost_function_network::cost_function::feature_based").
/// Static version.
/*static*/
std::string
ChoiceFeature::class_namespace_static() {
    return "masala::numeric::optimization::cost_function_network::cost_function::feature_based";
}

/// @brief This returns the class name ("ChoiceFeature").
std::string
ChoiceFeature::class_name() const {
    return class_name_static();
}

/// @brief This returns the class namespace ("masala::numeric::optimization::cost_function_network::cost_function::feature_based").
std::string
ChoiceFeature::class_namespace() const {
    return class_namespace_static();
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the minimum number of connections that this feature must have to be satisfied.
masala::base::Size
ChoiceFeature::min_connections() const {
    return min_connections_;
}

/// @brief Get the maximum number of connections that this feature must have to be satisfied.
masala::base::Size
ChoiceFeature::max_connections() const {
    return max_connections_;
}

/// @brief Get the offset in the number of connections (the number of connections that are
/// always satisfied).
masala::base::Size
ChoiceFeature::offset() const {
    return offset_;
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

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
    std::lock_guard< std::mutex > lock( mutex_ );

    if( api_definition_ == nullptr ) {
        MasalaObjectAPIDefinitionSP apidef(
            masala::make_shared< MasalaObjectAPIDefinition >(
                this,
                "An object that stores one feature on a node choice in a "
                "cost function optimization problem.  Features can make connections "
                "to other node choices, and can be satisfied by having a number "
                "of connections between a minimum and a maximum value.",
                true, false
            )
        );

        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( ChoiceFeature, apidef );

        apidef->add_getter(
            std::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::base::Size > >(
                "min_connections", "Get the minimum number of connections that this feature must have to be satisfied.  Not threadsafe.",
                "min_connections", "The minimum number of connections that this feature must have to be satisfied.",
                false, false, std::bind( &ChoiceFeature::min_connections, this )
            )
        );
        apidef->add_getter(
            std::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::base::Size > >(
                "max_connections", "Get the maximum number of connections that this feature must have to be satisfied.  Not threadsafe.",
                "max_connections", "The maximum number of connections that this feature must have to be satisfied.",
                false, false, std::bind( &ChoiceFeature::max_connections, this )
            )
        );
        apidef->add_getter(
            std::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::base::Size > >(
                "offset", "Get the offset in the number of connections.  Not threadsafe.",
                "offset", "The offset in the number of connections (i.e. the number of connections that "
                "are always satisfied).",
                false, false, std::bind( &ChoiceFeature::offset, this )
            )
        );


        apidef->add_setter(
            std::make_shared< setter::MasalaObjectAPISetterDefinition_ZeroInput >(
                "finalize", "Indicate that data entry is complete, and that this object is now read-only.  Threadsafe.",
                false, false, std::bind( &ChoiceFeature::finalize, this )
            )
        );

        api_definition_ = apidef; //Nonconst to const.
    }
    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Assign this object based on src.  Assumes that both mutexes have been locked.
/*virtual*/
void
ChoiceFeature::protected_assign(
    ChoiceFeature const & src
) {
    finalized_.store( src.finalized_.load() );
    min_connections_ = src.min_connections_;
    max_connections_ = src.max_connections_;
    offset_ = src.offset_;
}

/// @brief Finalize this object.  Assumes that mutex has been locked.
/*virtual*/
void
ChoiceFeature::protected_finalize() {
    CHECK_OR_THROW_FOR_CLASS( finalized_.load() == false, "protected_finalize",
        "This ChoiceFeature has already been finalized!"
    );
    finalized_.store(true);
}

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
