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

/// @file src/numeric/optimization/cost_function_network/cost_function/feature_based/SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction.cc
/// @brief Implementation for a pure virtual base class for SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunctions.
/// @details SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunctions define a penalty function which is based on the following:
/// - One or more features are defined for each choice at each node.  (A feature could be a hydrogen bond
/// donor or acceptor, for instance, in a packing problem)
/// - Each feature has an expected minimum and maximum number of connections that can be set.
/// - For each pair of choices, the features that are connected can be set.
/// - At calculation time, the number of unsatisfied features (total features minus features
/// satisfied by connections) is returned.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction.hh>

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/utility/container/container_util.tmpl.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_FiveInput.tmpl.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {
namespace feature_based {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction(
    SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction const & src
) :
    SumOfUnsatisfiedChoiceFeaturesCostFunction()
{
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    assign_mutex_locked( src );
}

// @brief Assignment operator.
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction &
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::operator=(
    SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction const & src
) {
    std::lock( src.mutex(), mutex() );
    std::lock_guard< std::mutex > lockthis( mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex(), std::adopt_lock );
    assign_mutex_locked( src );
    return *this;
}

/// @brief Return a shared pointer to a copy of this object.
CostFunctionSP
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::clone() const {
    return masala::make_shared< SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction >( *this );
}

/// @brief Deep-clone all data stored in this class.
void
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::make_independent() {
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
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::get_categories() const {
	return SumOfUnsatisfiedChoiceFeaturesCostFunction::get_categories();
}

/// @brief Get the keywords for this plugin class.  Default for all
/// optimization problems; may be overridden by derived classes.
/// @returns { "optimization_problem", "cost_function", "numeric", "unsatisfied_choice_feature_sum_based" }
std::vector< std::string >
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::get_keywords() const {
    return SumOfUnsatisfiedChoiceFeaturesCostFunction::get_keywords();
}

/// @brief Return the name of this class ("SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction").
std::string
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::class_name() const {
    return "SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction";
}

/// @brief Return the namespace of this class ("masala::numeric::optimization::cost_function_network::cost_function::feature_based");
std::string
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::class_namespace() const {
    return "masala::numeric::optimization::cost_function_network::cost_function::feature_based";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get an object describing the API for this object.
/// @details Default implementation returns nullptr.  May be overridden by
/// derived objects.
/// @note This is a weak pointer rather than a shared pointer since the
/// original object is expected to hold on to its API definition (which includes
/// funciton pointers to the functions of the instance).  Querying whether the
/// weak pointer can be converted to a shared pointer serves on a check as to
/// whether it is safe to use the function pointers.  Not ideal, but better than
/// nothing.
masala::base::api::MasalaObjectAPIDefinitionCWP
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::get_api_definition() {
    using namespace masala::base::api;
    using masala::base::Size;
    using masala::base::Real;
    std::lock_guard< std::mutex > lock( mutex() );

    if( api_definition_mutex_locked() == nullptr ) {
        MasalaObjectAPIDefinitionSP apidef(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "A cost function based on the square of the number of unsatisfied features in "
                "the selected node choices.  During configuration, features can indicate which "
                "other node choices will form a connection to them, and the number of connections "
                "needed to be satisfied (i.e. not under- or over-satisfied).",
                false, false
            )
        );

        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction, apidef );

        // Setters:
        apidef->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Real > >(
                "set_weight", "Set the weight for this penalty function.  The object must not have been finalized already.",
                "weight_in", "The weight for this penalty function.",
                false, false,
                std::bind( &SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::set_weight, this, std::placeholders::_1 )
            )
        );
        apidef->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_FiveInput< Size, Size, Size, Size, Size > >(
                "add_choice_feature_by_absolute_node_index", "Add a choice feature for a set of nodes, indexed by "
                "absolute node index.  This can only be done prior to finalizing this object.",
                "absolute_node_index", "The index of this node (absolute).",
                "choice_index", "The index of this choice.",
                "min_connections_to_satisfy_feature", "The minimum number of connections that this feature "
                "must make in order to be satisfied.",
                "max_connections_to_satisfy_feature", "The maximum number of connections that this feature "
                "must make in order to be satisfied.",
                "feature_connection_offset", "The number of connections that this feature always "
                "makes (e.g. to background, or to itself).",
                false, false,
                std::bind( &SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::add_choice_feature_by_absolute_node_index,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3,
                    std::placeholders::_4,
                    std::placeholders::_5
                )
            )
        );
        apidef->add_setter(
            masala::make_shared< setter::MasalaObjectAPISetterDefinition_TwoInput< Size, std::vector< std::vector< Size > > const & > >(
                "increment_offsets_at_node", "For all choices at a given node, increment the offsets.  This can only be "
                "called prior to object finalization.  Locks mutex (i.e. threadsafe).  If node or choices have not yet "
                "been declared, they are added.",
                "absolute_node_index", "The index of the node for which we are updating choices.",
                "offset_increments", "The amount by which we are incrementing the choices, provided as "
                "a vector indexed by choice index of vectors indexed by choice feature index.  Any choices "
                "or features not yet declared are added and initialized to the value provided.",
                false, false,
                std::bind( &SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::increment_offsets_at_node, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );

        // Getters:
        apidef->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< bool > >(
                "finalized", "Has this object been finalized?  Performs a mutex lock for the check.",
                "finalized", "True if the object has been finalized, false otherwise.",
                false, false, std::bind( &SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::finalized, this )
            )
        );

        // Work functions:
        apidef->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< void, std::vector< Size > const & > >(
                "finalize", "Indicate that all setup is complete for this object, and "
                "prepare it for use in high-efficiency calculations.",
                false, false, false, false,
                "variable_node_indices", "A list of all of the absolute node indices for "
                "nodes that have more than one choice, indexed by variable node index.",
                "void", "This function returns nothing.",
                std::bind( &SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::finalize, this, std::placeholders::_1 )               
            )
        );
        {
            work_function::MasalaObjectAPIWorkFunctionDefinitionSP compute_cost_function_def(
                masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< Real, std::vector< Size > const & > >(
                    "compute_cost_function", "Given a selection of choices at variable nodes, compute the cost function.  Note that no mutex-locking is performed.",
                    true, false, false, true,
                    "candidate_solution", "The indices of the selected node choices, indexed by variable node index.",
                    "cost_function", "The square of the total number of features that are unsatisfied, multiplied by the weight of this cost function.",
                    std::bind( &SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::compute_cost_function, this, std::placeholders::_1 )               
                )
            );
            compute_cost_function_def->set_triggers_no_mutex_lock();
            apidef->add_work_function( compute_cost_function_def );
        }
        {
            work_function::MasalaObjectAPIWorkFunctionDefinitionSP compute_cost_function_difference_def(
                masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< Real, std::vector< Size > const &, std::vector< Size > const & > >(
                    "compute_cost_function_difference", "Given an old selection of choices at variable nodes and a new selection, "
                    "compute the cost function difference.  Note that no mutex-locking is performed.",
                    true, false, false, true,
                    "candidate_solution_old", "The indices of the selected node choices for the OLD selection, indexed by variable node index.",
                    "candidate_solution_new", "The indices of the selected node choices for the NEW selection, indexed by variable node index.",
                    "cost_function", "The difference of the squares of the total number of features that are unsatisfied, multiplied by the weight of this cost function.",
                    std::bind( &SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::compute_cost_function_difference,
                        this, std::placeholders::_1, std::placeholders::_2
                    )               
                )
            );
            compute_cost_function_difference_def->set_triggers_no_mutex_lock();
            apidef->add_work_function( compute_cost_function_difference_def );
        }


        api_definition_mutex_locked() = apidef; // Nonconst to const;
    }

    return api_definition_mutex_locked();
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

/// @brief Given a selection of choices at variable nodes, compute the cost function.
/// @note No mutex-locking is performed!
masala::base::Real
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::compute_cost_function(
    std::vector< masala::base::Size > const & candidate_solution
) const {
    using masala::base::Real;
    using masala::base::Size;
    Size const count( protected_compute_cost_function_no_weight( candidate_solution ) );
    return protected_weight() * static_cast< Real >( count*count );
}

/// @brief Given an old selection of choices at variable nodes and a new selection,
/// compute the cost function difference.
/// @note No mutex-locking is performed!
masala::base::Real
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::compute_cost_function_difference(
    std::vector< masala::base::Size > const & candidate_solution_old,
    std::vector< masala::base::Size > const & candidate_solution_new
) const {
    using masala::base::Real;
    using masala::base::Size;
    Size const countnew( protected_compute_cost_function_no_weight( candidate_solution_new ) );
    Size const countold( protected_compute_cost_function_no_weight( candidate_solution_old ) );
    return protected_weight() * ( static_cast< Real >( countnew*countnew - countold*countold ) );
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
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::protected_finalize(
    std::vector< masala::base::Size > const & variable_node_indices
) {
    SumOfUnsatisfiedChoiceFeaturesCostFunction::protected_finalize( variable_node_indices );
}

/// @brief Override of assign_mutex_locked().  Calls parent function.
/// @details Throws if src is not a SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction.
void
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::assign_mutex_locked(
    CostFunction const & src
) {
    SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction const * const src_cast_ptr( dynamic_cast< SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_cast_ptr != nullptr, "assign_mutex_locked", "Cannot assign a SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction given an input " + src.class_name() + " object!  Object types do not match." );
    SumOfUnsatisfiedChoiceFeaturesCostFunction::assign_mutex_locked( src );
}

/// @brief Make this object fully independent.  Assumes mutex was already locked.
/// Should be called by overrides.
void
SquareOfSumOfUnsatisfiedChoiceFeaturesCostFunction::make_independent_mutex_locked() {
    SumOfUnsatisfiedChoiceFeaturesCostFunction::make_independent_mutex_locked();
}

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
