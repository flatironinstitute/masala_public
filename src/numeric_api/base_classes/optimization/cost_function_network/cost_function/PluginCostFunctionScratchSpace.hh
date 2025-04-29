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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunctionScratchSpace.hh
/// @brief Header for a non-instantiable base class for PluginCostFunctionScratchSpaces.
/// @details PluginCostFunctionScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunction to another.  They are intended to be used with one particular cost function instance for
/// one particular problem.  The PluginCostFunctionScratchSpace class derives from CostFunctionScratchSpace,
/// and permits cost function scratch spaces to be defined in plug-in libraries.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_cost_function_PluginCostFunctionScratchSpace_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_cost_function_PluginCostFunctionScratchSpace_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/cost_function_network/cost_function/PluginCostFunctionScratchSpace.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/cost_function/CostFunctionScratchSpace.hh>

// Numeric headers:

// Base headers:
#include <base/types.hh>

// STL headers:
#include <mutex>
#include <atomic>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {
namespace cost_function {

/// @brief A non-instantiable base class for PluginCostFunctionScratchSpaces.
/// @details PluginCostFunctionScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunction to another.  They are intended to be used with one particular cost function instance for
/// one particular problem.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginCostFunctionScratchSpace : public masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpace {

	typedef masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpace Parent;
	typedef masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpaceSP ParentSP;
	typedef masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpaceCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginCostFunctionScratchSpace() = default;

	/// @brief Copy constructor.
	PluginCostFunctionScratchSpace( PluginCostFunctionScratchSpace const & /*src*/ ) = default;

	// @brief Assignment operator.
	PluginCostFunctionScratchSpace &
	operator=( PluginCostFunctionScratchSpace const & /*src*/ ) = default;

	/// @brief Destructor.
	~PluginCostFunctionScratchSpace() override = default;

	/// @brief Make a copy of this object.  Must be implemented by derived classes.
	masala::numeric::optimization::cost_function_network::cost_function::CostFunctionScratchSpaceSP
	clone() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Ensure that this class is a pure virtual class.
	std::string class_name() const override = 0;

	/// @brief Ensure that this class is a pure virtual class.
	std::string class_namespace() const override = 0;

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

}; // class PluginCostFunctionScratchSpace

} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_cost_function_network_cost_function_PluginCostFunctionScratchSpace_hh