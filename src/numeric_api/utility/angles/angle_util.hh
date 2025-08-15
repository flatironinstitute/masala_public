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

/// @file src/numeric_api/utility/angles/angle_util.hh
/// @brief Inlined functions for manipulating angles.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_utility_angles_angle_util_hh
#define Masala_src_numeric_api_utility_angles_angle_util_hh

#include <cmath>

namespace masala {
namespace numeric_api {
namespace utility {
namespace angles {

    /// @brief Convert an angle, in degrees, to the equivalent angle, in degrees, in the range [0, 360).
    /// @tparam T The type of the angle (e.g. float, double, masala::base::Real).
    /// @param angle_in The input angle, in degrees.
    /// @return An angle, in degrees, in the range [0, 360).
    template < typename T >
    inline
    T
    positive_angle_degrees(
        T angle_in
    ) {
        T const fmod_result( std::fmod( angle_in, T(360) ) );
        return (fmod_result < 0 ? fmod_result + T(360) : fmod_result);
    }

    /// @brief Convert an angle, in degrees, to the equivalent angle, in degrees, in the range [-180, 180).
    /// @tparam T The type of the angle (e.g. float, double, masala::base::Real).
    /// @param angle_in The input angle, in degrees.
    /// @return An angle, in degrees, in the range [-180, 180).
    template < typename T >
    inline
    T
    zero_centred_angle_degrees(
        T angle_in
    ) {
        return ( positive_angle_degrees( angle_in + T(180) ) - T(180) );
    }

} // namespace angles
} // namespace utility
} // namespace numeric_api
} // namespace masala

#endif // Masala_src_numeric_api_utility_angles_angle_util_hh