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
#include <base/MasalaObject.hh>

// Base headers:
#include <base/types.hh>

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
class CFNProblemScratchSpace : public masala::base::MasalaObject {

	typedef masala::base::MasalaObject Parent;
	typedef masala::base::MasalaObjectSP ParentSP;
	typedef masala::base::MasalaObjectCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CFNProblemScratchSpace() = default;

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

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

}; // class CFNProblemScratchSpace

} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_CFNProblemScratchSpace_hh