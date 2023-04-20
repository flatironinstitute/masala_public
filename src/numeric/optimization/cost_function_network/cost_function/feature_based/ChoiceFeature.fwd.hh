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

/// @file src/numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.fwd.hh
/// @brief Forward declarations for a class for ChoiceFeatures.
/// @details ChoiceFeatures are objects attached to node choices, which can form connections across
/// choices at different nodes.  Each feature has a minimum and maximum number of connections that
/// it must make to be satisfied.
/// @note This class is a lightweight class that offers thread safety for the API definition only.  There
/// are no setters, so everything is set in the constructor, and it's read-only after that.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_ChoiceFeature_fwd_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_ChoiceFeature_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {
namespace feature_based {

	class ChoiceFeature;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using ChoiceFeatureSP = MASALA_SHARED_POINTER< ChoiceFeature >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using ChoiceFeatureCSP = MASALA_SHARED_POINTER< ChoiceFeature const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using ChoiceFeatureWP = MASALA_WEAK_POINTER< ChoiceFeature >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using ChoiceFeatureCWP = MASALA_WEAK_POINTER< ChoiceFeature const >;

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_ChoiceFeature_fwd_hh