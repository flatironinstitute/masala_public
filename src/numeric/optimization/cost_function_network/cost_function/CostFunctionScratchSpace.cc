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

/// @file src/numeric/optimization/cost_function_network/cost_function/CostFunctionScratchSpace.cc
/// @brief Implementations for a non-instantiable base class for CostFunctionScratchSpaces.
/// @details CostFunctionScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunction to another.  They are intended to be used with one particular cost function instance for
/// one particular problem.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <numeric/optimization/cost_function_network/cost_function/CostFunctionScratchSpace.hh>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this class ("CostFunctionScratchSpace").
/*static*/
std::string
CostFunctionScratchSpace::class_name_static() {
	return "CostFunctionScratchSpace";
}

/// @brief Get the namespace of this class ("masala::numeric::optimization::cost_function_network::cost_function").
/*static*/
std::string
CostFunctionScratchSpace::class_namespace_static() {
	return "masala::numeric::optimization::cost_function_network::cost_function";
}

/// @brief Get the namespace and name of this class ("masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpace").
/*static*/
std::string
CostFunctionScratchSpace::class_namespace_and_name_static() {
	return class_namespace_static() + "::" + class_name_static();
}

/// @brief Naming function.
/// @returns "CostFunctionScratchSpace".
std::string
CostFunctionScratchSpace::class_name() const {
	return "CostFunctionScratchSpace";
}

/// @brief Namespace function.
/// @returns "masala::numeric::optimization::cost_function_network".
std::string
CostFunctionScratchSpace::class_namespace() const {
	return "masala::numeric::optimization::cost_function_network::cost_function";
}

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Indicate that the last update of the calculation should be "accepted" -- whatever that means.
/// @details The scratch space can choose its own strategy for making recomputation efficient.  Acceptance
/// of a move implies that many subsequent moves will have the last state as their starting point, so
/// any information from the last evaluation that can be more permanently cached should be at this point.
/// @note Calls protected_accept_last_move(), which should be implemented by derived classes.
void
CostFunctionScratchSpace::accept_last_move() {
    protected_accept_last_move();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Should be implemented by derived classes.  Base class version does nothing.  Derived classes
/// should call parent class function.
void
CostFunctionScratchSpace::protected_accept_last_move() {
    // GNDN
}


} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala
