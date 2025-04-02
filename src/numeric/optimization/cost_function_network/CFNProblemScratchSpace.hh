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

/// @file src/numeric/optimization/cost_function_network/CFNProblemScratchSpace.hh
/// @brief Header for a non-instantiable base class for CFNProblemScratchSpaces.
/// @details CFNProblemScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunctionNetworkOptimizationProblem to another.  They store the scratch spaces for the
/// individual cost functions.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_CFNProblemScratchSpace_hh
#define Masala_src_numeric_optimization_cost_function_network_CFNProblemScratchSpace_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/CFNProblemScratchSpace.fwd.hh>

// Parent header:
#include <base/MasalaNoAPIObject.hh>

// Numeric headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunctionScratchSpace.fwd.hh>
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <vector>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {

/// @brief A non-instantiable base class for CFNProblemScratchSpaces.
/// @details CFNProblemScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunctionNetworkOptimizationProblem to another.  They store the scratch spaces for the
/// individual cost functions.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CFNProblemScratchSpace : public masala::base::MasalaNoAPIObject {

	typedef masala::base::MasalaNoAPIObject Parent;
	typedef masala::base::MasalaNoAPIObjectSP ParentSP;
	typedef masala::base::MasalaNoAPIObjectCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CFNProblemScratchSpace() = default;

	/// @brief CostFunction vector constructor.
	/// @details Initializes the cost_function_scratch_spaces_ vector.
	CFNProblemScratchSpace(
		std::vector< cost_function::CostFunctionCSP > const & cost_functions
	);

	/// @brief Copy constructor.
	CFNProblemScratchSpace( CFNProblemScratchSpace const & /*src*/ ) = default;

	// @brief Assignment operator.
	CFNProblemScratchSpace &
	operator=( CFNProblemScratchSpace const & /*src*/ ) = default;

	/// @brief Destructor.
	~CFNProblemScratchSpace() override = default;
	
public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the name of this class ("CFNProblemScratchSpace").
	static
	std::string
	class_name_static();

	/// @brief Get the name of this class ("masala::numeric::optimization::cost_function_network").
	static
	std::string
	class_namespace_static();

	/// @brief Get the namespace and name of this class ("masala::numeric::optimization::cost_function_network::CFNProblemScratchSpace").
	static
	std::string
	class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the scratch space for the ith cost function.
	/// @param cost_function_index The index of the cost function.
	/// @returns A pointer to the scratch space, or nullptr if the cost function doesn't use a scratch space.
	/// In debug mode, this throws if the index is out of range.
	masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpace *
	cost_function_scratch_space_raw_ptr(
		masala::base::Size const cost_function_index
	) const;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a finalized cost function, grab its scratch space and add it to the
	/// vector of scratch spaces.  Adds nullptr if the cost function does not define its
	/// own scratch space type.
	void
	add_cost_function_scratch_space(
		masala::numeric::optimization::cost_function_network::cost_function::CostFunction const & cost_fxn
	);

	/// @brief Indicate that the last update of the calculation should be "accepted" -- whatever that means.
	/// @details The scratch space can choose its own strategy for making recomputation efficient.  Acceptance
	/// of a move implies that many subsequent moves will have the last state as their starting point, so
	/// any information from the last evaluation that can be more permanently cached should be at this point.
	/// @note Calls accept_last_move for each cached CostFunctionScratchSpace.  Also calls protected_accept_last_move(),
	/// which should be implemented by derived classes.
	void accept_last_move();

	/// @brief Mark this object as finalized (i.e. no more scratch spaces can be added).
	void
	finalize();

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Should be implemented by derived classes.  Base class does nothing.  Derived classes
	/// should call parent class function.
	virtual
	void
	protected_accept_last_move();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief Has this object been finalized?
	/// @details After finalization, scratch spaces are mutable, but no new cost function scratch spaces can be added.
	bool finalized_ = false;

	/// @brief A vector of scratch spaces for cost functions in a problem (or nullptr if a cost function doesn't use a scratch space).
	std::vector< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpaceSP > cost_function_scratch_spaces_;


}; // class CFNProblemScratchSpace

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_CFNProblemScratchSpace_hh