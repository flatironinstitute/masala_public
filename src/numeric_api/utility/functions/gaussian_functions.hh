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

/// @file src/numeric_api/utility/functions/gaussian_functions.hh
/// @brief Utility functions for computing Gaussian functions and their derivatives.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_utility_functions_gaussian_functions_hh
#define Masala_src_numeric_api_utility_functions_gaussian_functions_hh

#include <base/types.hh>
#include <numeric_api/utility/constants/constants.hh>
#include <cmath>

namespace masala {
namespace numeric_api {
namespace utility {
namespace functions {

/// @brief Compute a 1D Gaussian, normalized.
/// @param x The position in 1 dimension.
/// @param x0 The centre of the Gaussian in 1 dimension.
/// @param sigma The standard deviation of the Gaussian.
inline
masala::base::Real
compute_1d_gaussian(
    masala::base::Real const x,
    masala::base::Real const x0,
    masala::base::Real const sigma
) {
    masala::base::Real const xdiff( x-x0 );
    return 1.0/(sigma * MASALA_SQRT_2PI ) * std::exp( - xdiff*xdiff / (2*sigma*sigma) );
}

/// @brief Compute the first derivative of a 1D Gaussian (dG(x)/dx), normalized.
/// @param x The position in 1 dimension.
/// @param x0 The centre of the Gaussian in 1 dimension.
/// @param sigma The standard deviation of the Gaussian.
inline
masala::base::Real
compute_1d_gaussian_deriv(
    masala::base::Real const x,
    masala::base::Real const x0,
    masala::base::Real const sigma
) {
    masala::base::Real const xdiff( x-x0 );
    masala::base::Real const sigma_squared( sigma*sigma );
    return - xdiff /(sigma_squared*sigma * MASALA_SQRT_2PI ) * std::exp( - xdiff*xdiff / (2*sigma_squared) );
}

} // namespace functions
} // namespace utility
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_utility_functions_gaussian_functions_hh