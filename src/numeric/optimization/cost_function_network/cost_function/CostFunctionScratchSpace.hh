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
#include <base/MasalaNoAPIObject.hh>

// Base headers:
#include <base/types.hh>
#include <string>

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
class CostFunctionScratchSpace : public masala::base::MasalaNoAPIObject {

	typedef masala::base::MasalaNoAPIObject Parent;
	typedef masala::base::MasalaNoAPIObjectSP ParentSP;
	typedef masala::base::MasalaNoAPIObjectCSP ParentCSP;

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

	/// @brief Get the name of this class ("CostFunctionScratchSpace").
	static
	std::string
	class_name_static();

	/// @brief Get the name of this class ("masala::numeric::optimization::cost_function_network::cost_function").
	static
	std::string
	class_namespace_static();

	/// @brief Get the namespace and name of this class ("masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpace").
	static
	std::string
	class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Indicate that the last update of the calculation should be "accepted" -- whatever that means.
	/// @details The scratch space can choose its own strategy for making recomputation efficient.  Acceptance
	/// of a move implies that many subsequent moves will have the last state as their starting point, so
	/// any information from the last evaluation that can be more permanently cached should be at this point.
	/// @note Calls protected_accept_last_move(), which should be implemented by derived classes.
	void accept_last_move();

public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Should be implemented by derived classes.  Base class version does nothing.  Derived classes
	/// should call parent class function.
	virtual
	void
	protected_accept_last_move();

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