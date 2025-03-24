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
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
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
    masala::base::managers::engine::MasalaDataRepresentation(),
    finalized_(false)
{}

/// @brief Copy constructor (protected in API).
CostFunction::CostFunction(
    CostFunction const & src
) :
    masala::base::managers::engine::MasalaDataRepresentation( src )
{
    std::lock( src.data_representation_mutex(), data_representation_mutex() );
    std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock );
    finalized_.store(false);
    protected_assign( src );
}

// @brief Assignment operator.
CostFunction &
CostFunction::operator=(
    CostFunction const & src
) {
    std::lock( src.data_representation_mutex(), data_representation_mutex() );
    std::lock_guard< std::mutex > lockthat( src.data_representation_mutex(), std::adopt_lock );
    std::lock_guard< std::mutex > lockthis( data_representation_mutex(), std::adopt_lock );
    protected_assign( src );
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

/// @brief Get the category for this MasalaDataRepresentation.
/// @returns { { "CostFunction" } }.
std::vector< std::vector< std::string > >
CostFunction::get_data_representation_categories() const {
    return std::vector< std::vector< std::string > >{ { "CostFunction" } };
}

/// @brief Get the keywords that this data representation plugin has.
/// @details Categories are hierarchical, with the hierarchy represented as a vector of
/// strings.  One data representation category can be classified into multiple categories.
/// @returns { "optimization_problem", "cost_function", "numeric" }
std::vector< std::string >
CostFunction::get_data_representation_keywords() const {
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
CostFunction::get_compatible_masala_engines() const {
    return std::vector< std::string >{};
}

/// @brief Get the properties of this MasalaDataRepresentation.
/// @returns { "cost_function" }.
std::vector< std::string >
CostFunction::get_present_data_representation_properties() const {
    return std::vector< std::string >{ "cost_function" };
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
    std::lock_guard< std::mutex > lock( data_representation_mutex() );
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
    std::lock_guard< std::mutex > lock( data_representation_mutex() );
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
    std::lock_guard< std::mutex > lock( data_representation_mutex() );
    protected_finalize( variable_node_indices );
}

/// @brief Does this class use a cost function scratch space?
/// @details Returns false by default.  May be overridden by derived classes to return true.  If this returns true,
/// then it is expected that (a) generate_cost_function_scratch_space() returns a non-null pointer to a suitable object
/// derived from CostFunctionScratchSpace, and (b) compute_cost_function() and compute_cost_function_difference() accept
/// an object of that type and use it.
/*virtual*/
bool
CostFunction::uses_cost_function_scratch_space() const {
    return false;
}

/// @brief Generate a suitable object of type CostFunctionScratchSpace (by owning pointer).
/// @details Base class generates nullptr.  May be overridden by derived classes, which should
/// return a suitable class derived from CostFunctionScratchSpace which can be accepted by compute_cost_function()
/// and compute_cost_function_difference() function overrides.
/*virtual*/
CostFunctionScratchSpaceOP
CostFunction::generate_cost_function_scratch_space() const {
    return nullptr;
}

/// @brief Given a selection of choices at variable nodes, compute the cost function.
/// @details This version returns 0; must be overridden by derived classes.
/// @param[in] candidate_solution The current solution, expressed as a vector of variable node indices.
/// @param[in] scratch_space A pointer to a CostFunctionScratchSpace object.  Thie could be nullptr.  If non-null,
/// then the derived class must check that this is an appropriate CostFunctionScratchSpace type and use it appropriately.
/// This is to help to make calculations more efficient on re-evaluation by caching relevant information from past evaluations.
masala::base::Real
CostFunction::compute_cost_function(
    std::vector< masala::base::Size > const & /*candidate_solution*/,
    CostFunctionScratchSpace * /*scratch_space*/
) const {
    return 0.0;
}

/// @brief Given an old selection of choices at variable nodes and a new selection,
/// compute the cost function difference.
/// @details This version returns 0; must be overridden by derived classes.
/// @param[in] candidate_solution_old The previous solution, expressed as a vector of variable node indices.
/// @param[in] candidate_solution_new The new solution, expressed as a vector of variable node indices.
/// @param[in] scratch_space A pointer to a CostFunctionScratchSpace object.  Thie could be nullptr.  If non-null,
/// then the derived class must check that this is an appropriate CostFunctionScratchSpace type and use it appropriately.
/// This is to help to make calculations more efficient on re-evaluation by caching relevant information from past evaluations.
masala::base::Real
CostFunction::compute_cost_function_difference(
    std::vector< masala::base::Size > const & /*candidate_solution_old*/,
    std::vector< masala::base::Size > const & /*candidate_solution_new*/,
    CostFunctionScratchSpace * /*scratch_space*/
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
    using masala::base::Size;
    using masala::base::Real;

    std::lock_guard< std::mutex > lock( data_representation_mutex() );
    if( api_definition_ == nullptr ) {
        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this, "A cost function, used in cost function network optimization algorithms.",
                false, true
            )
        );

        ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( CostFunction, api_def );

        {
            work_function::MasalaObjectAPIWorkFunctionDefinitionSP compute_cost_function_def(
                masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< Real, std::vector< Size > const & > >(
                    "compute_cost_function", "Given a selection of choices at variable nodes, compute the cost function.  Note that no mutex-locking is performed.",
                    true, false, true, false,
                    "candidate_solution", "The indices of the selected node choices, indexed by variable node index.",
                    "cost_function", "The square of the total number of features that are unsatisfied, multiplied by the weight of this cost function.",
                    std::bind( &CostFunction::compute_cost_function, this, std::placeholders::_1 )               
                )
            );
            compute_cost_function_def->set_triggers_no_mutex_lock();
            api_def->add_work_function( compute_cost_function_def );
        }
        {
            work_function::MasalaObjectAPIWorkFunctionDefinitionSP compute_cost_function_difference_def(
                masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< Real, std::vector< Size > const &, std::vector< Size > const & > >(
                    "compute_cost_function_difference", "Given an old selection of choices at variable nodes and a new selection, "
                    "compute the cost function difference.  Note that no mutex-locking is performed.",
                    true, false, true, false,
                    "candidate_solution_old", "The indices of the selected node choices for the OLD selection, indexed by variable node index.",
                    "candidate_solution_new", "The indices of the selected node choices for the NEW selection, indexed by variable node index.",
                    "cost_function", "The difference of the squares of the total number of features that are unsatisfied, multiplied by the weight of this cost function.",
                    std::bind( &CostFunction::compute_cost_function_difference,
                        this, std::placeholders::_1, std::placeholders::_2
                    )               
                )
            );
            compute_cost_function_difference_def->set_triggers_no_mutex_lock();
            api_def->add_work_function( compute_cost_function_difference_def );
        }


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

/// @brief Is this data representation empty?
/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
/// @returns True if no data have been loaded into this data representation, false otherwise.
/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
bool
CostFunction::protected_empty() const {
    return true;
}

/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
void
CostFunction::protected_clear() {
    //GNDN
}

/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
void
CostFunction::protected_reset() {
    weight_ = 1.0;
}

/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
/// by derived classses.  Performs no mutex-locking.
void
CostFunction::protected_make_independent() {
    // GNDN
}

/// @brief Assignment operator, assuming that we've already locked the write mutex.
void
CostFunction::protected_assign(
    masala::base::managers::engine::MasalaDataRepresentation const & src
) {
    CostFunction const * src_ptr_cast( dynamic_cast< CostFunction const * >( &src ) );
    CHECK_OR_THROW_FOR_CLASS( src_ptr_cast != nullptr, "protected_assign", "Cannot assign an object of type " + src.class_name() + " to a CostFunction object." );
    weight_ = src_ptr_cast->weight_;
    Parent::protected_assign(src);
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
} // namespace masala
