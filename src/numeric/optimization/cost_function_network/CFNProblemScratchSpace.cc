/*
	Masala
	Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/numeric/optimization/cost_function_network/CFNProblemScratchSpace.cc
/// @brief Implementations for a non-instantiable base class for CFNProblemScratchSpaces.
/// @details CFNProblemScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunctionNetworkOptimizationProblem to another.  They store the scratch spaces for the
/// individual cost functions.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <numeric/optimization/cost_function_network/CFNProblemScratchSpace.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunctionScratchSpace.hh>
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief CostFunction vector constructor.
/// @details Initializes the cost_function_scratch_spaces_ vector.
CFNProblemScratchSpace::CFNProblemScratchSpace(
	std::vector< cost_function::CostFunctionCSP > const & cost_functions
) :
	Parent()
{
	for( auto const & cost_function : cost_functions ) {
		cost_function_scratch_spaces_.push_back( cost_function->generate_cost_function_scratch_space() );
	}
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this class ("CFNProblemScratchSpace").
/*static*/
std::string
CFNProblemScratchSpace::class_name_static() {
	return "CFNProblemScratchSpace";
}

/// @brief Get the name of this class ("masala::numeric::optimization::cost_function_network").
/*static*/
std::string
CFNProblemScratchSpace::class_namespace_static() {
	return "masala::numeric::optimization::cost_function_network";
}

/// @brief Get the namespace and name of this class ("masala::numeric::optimization::cost_function_network::CFNProblemScratchSpace").
/*static*/
std::string
CFNProblemScratchSpace::class_namespace_and_name_static() {
	return class_namespace_static() + "::" + class_name_static();
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the scratch space for the ith cost function.
/// @param cost_function_index The index of the cost function.
/// @returns A pointer to the scratch space, or nullptr if the cost function doesn't use a scratch space.
/// In debug mode, this throws if the index is out of range.
masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpace *
CFNProblemScratchSpace::cost_function_scratch_space_raw_ptr(
	masala::base::Size const cost_function_index
) const {
	CHECK_OR_THROW_FOR_CLASS( finalized_, "cost_function_scratch_space_raw_ptr", "This object must be finalized before the "
		"cost_function_scratch_space_raw_ptr() function can be called."
	);
	DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( cost_function_index < cost_function_scratch_spaces_.size(), "cost_function_scratch_space_raw_ptr",
		"A cost function scratch space with index " + std::to_string( cost_function_index ) + " was requested, but we have only "
		+ std::to_string( cost_function_scratch_spaces_.size() ) + " cost function scratch spaces."
	);
	if( cost_function_scratch_spaces_[cost_function_index] == nullptr ) { return nullptr; }
	return cost_function_scratch_spaces_[cost_function_index].get();
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given a finalized cost function, grab its scratch space and add it to the
/// vector of scratch spaces.  Adds nullptr if the cost function does not define its
/// own scratch space type.
void
CFNProblemScratchSpace:: add_cost_function_scratch_space(
	masala::numeric::optimization::cost_function_network::cost_function::CostFunction const & cost_fxn
) {
	CHECK_OR_THROW_FOR_CLASS( !finalized_, "add_cost_function_scratch_space", "This object has already been finalized.  Cost function scratch spaces "
		"cannot be added after finalization."
	);
	CHECK_OR_THROW_FOR_CLASS( cost_fxn.finalized(), "add_cost_function_scratch_space", "A " + cost_fxn.class_name() + " object was passed to "
		"this function that had not yet been finalized."
	);
	if( cost_fxn.uses_cost_function_scratch_space() ) {
		cost_function_scratch_spaces_.push_back( cost_fxn.generate_cost_function_scratch_space() );
	} else {
		cost_function_scratch_spaces_.push_back( nullptr );
	}
}

/// @brief Mark this object as finalized (i.e. no more scratch spaces can be added).
void
CFNProblemScratchSpace::finalize() {
	CHECK_OR_THROW_FOR_CLASS( !finalized_, "finalize", "This object has already been finalized." );
	finalized_ = true;
}


} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
