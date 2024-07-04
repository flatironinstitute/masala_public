/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/numeric_api/utility/optimization/cost_function_network/util.hh
/// @brief Prototypes for utility functions for cost function network optimization problems.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_utility_constants_constants_hh
#define Masala_src_numeric_api_utility_constants_constants_hh

// Forward declarations:
#include <numeric_api/auto_generated_api/optimization/cost_function_network/CostFunctionNetworkOptimizationProblem_API.fwd.hh>

#define MASALA_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#define MASALA_GOLDEN_RATIO_LONG_DOUBLE constexpr( ( 1.0L + std::sqrtl( 5.0L ) ) / 2.0L )
#define MASALA_GOLDEN_RATIO_DOUBLE constexpr( ( 1.0 + std::sqrt( 5.0 ) ) / 2.0 )
#define MASALA_GOLDEN_RATIO_FLOAT constexpr( ( 1.0f + std::sqrtf( 5.0f ) ) / 2.0f )

#endif // Masala_src_numeric_api_utility_constants_constants_hh