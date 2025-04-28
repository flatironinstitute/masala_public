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

/// @file src/numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCFNProblemScratchSpace.hh
/// @brief Header for a non-instantiable base class for PluginPairwisePrecomputedCFNProblemScratchSpaces.
/// @details PluginPairwisePrecomputedCFNProblemScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunctionNetworkOptimizationProblem to another.  They store the scratch spaces for the individual cost functions.  These
/// are subclassed in other Masala libraries.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCFNProblemScratchSpace_hh
#define Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCFNProblemScratchSpace_hh

// Forward declarations:
#include <numeric_api/base_classes/optimization/cost_function_network/PluginPairwisePrecomputedCFNProblemScratchSpace.fwd.hh>

// Parent header:
#include <numeric/optimization/cost_function_network/CFNProblemScratchSpace.hh>

// Numeric headers
#include <numeric/optimization/cost_function_network/cost_function/CostFunction.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <vector>

namespace masala {
namespace numeric_api {
namespace base_classes {
namespace optimization {
namespace cost_function_network {

/// @brief A non-instantiable base class for PluginPairwisePrecomputedCFNProblemScratchSpaces.
/// @details PluginPairwisePrecomputedCFNProblemScratchSpaces allow data to be cached and reused from one evaluation of a
/// CostFunctionNetworkOptimizationProblem to another.  They store the scratch spaces for the individual cost functions.  These
/// are subclassed in other Masala libraries.
/// @note These objects are intended to be used by a single thread, and are not threadsafe.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginPairwisePrecomputedCFNProblemScratchSpace : public masala::numeric::optimization::cost_function_network::CFNProblemScratchSpace {

	typedef masala::numeric::optimization::cost_function_network::CFNProblemScratchSpace Parent;
	typedef masala::numeric::optimization::cost_function_network::CFNProblemScratchSpaceSP ParentSP;
	typedef masala::numeric::optimization::cost_function_network::CFNProblemScratchSpaceCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginPairwisePrecomputedCFNProblemScratchSpace() = default;

	/// @brief Cost function vector constructor.
	PluginPairwisePrecomputedCFNProblemScratchSpace(
		std::vector< masala::numeric::optimization::cost_function_network::cost_function::CostFunctionCSP > const & cost_functions
	);

	/// @brief Copy constructor.
	PluginPairwisePrecomputedCFNProblemScratchSpace( PluginPairwisePrecomputedCFNProblemScratchSpace const & /*src*/ ) = default;

	// @brief Assignment operator.
	PluginPairwisePrecomputedCFNProblemScratchSpace &
	operator=( PluginPairwisePrecomputedCFNProblemScratchSpace const & /*src*/ ) = default;

	/// @brief Destructor.
	~PluginPairwisePrecomputedCFNProblemScratchSpace() override = default;
	
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

}; // class PluginPairwisePrecomputedCFNProblemScratchSpace

} // namespace cost_function_network
} // namespace optimization
} // namespace base_classes
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_base_classes_optimization_cost_function_network_PluginPairwisePrecomputedCFNProblemScratchSpace_hh