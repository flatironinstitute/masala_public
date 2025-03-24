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

/// @file src/numeric/optimization/cost_function_network/cost_function/CostFunctionScratchSpace.hh
/// @brief Header for a non-instantiable base class for CostFunctionScratchSpaces.
/// @details CostFunctionScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunction to another.  They are intended to be used with one particular cost function instance for
/// one particular problem.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunctionScratchSpace_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunctionScratchSpace_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/CostFunctionScratchSpace.fwd.hh>

// Parent header:
#include <base/MasalaObject.hh>

// Base headers:
#include <base/types.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

/// @brief A non-instantiable base class for CostFunctionScratchSpaces.
/// @details CostFunctionScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunction to another.  They are intended to be used with one particular cost function instance for
/// one particular problem.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CostFunctionScratchSpace : public masala::base::MasalaObject {

	typedef masala::base::MasalaObject Parent;
	typedef masala::base::MasalaObjectSP ParentSP;
	typedef masala::base::MasalaObjectCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	CostFunctionScratchSpace() = default;

	/// @brief Copy constructor.
	CostFunctionScratchSpace( CostFunctionScratchSpace const & /*src*/ ) = default;

	// @brief Assignment operator.
	CostFunctionScratchSpace &
	operator=( CostFunctionScratchSpace const & /*src*/ ) = default;

	/// @brief Destructor.
	~CostFunctionScratchSpace() override = default;
	
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

}; // class CostFunctionScratchSpace

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_CostFunctionScratchSpace_hh