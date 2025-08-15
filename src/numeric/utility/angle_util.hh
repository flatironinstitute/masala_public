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

/// @file src/numeric/utility/angle_util.hh
/// @brief Inlined functions for manipulating angles.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_utility_angle_util_hh
#define Masala_src_numeric_utility_angle_util_hh

#include <numeric>

namespace masala {
namespace numeric {
namespace utility {

    /// @brief Convert an angle, in degrees, to the equivalent angle, in degrees, in the range [0, 360).
    /// @tparam T The type of the angle (e.g. float, double, masala::base::Real).
    /// @param angle_in The input angle, in degrees.
    /// @return An angle, in degrees, in the range [0, 360).
    template < typename T >
    T
    inline
    positive_angle_degrees(
        T const angle_in
    ) {
        return angle_in % T(360);
    }

    /// @brief Convert an angle, in degrees, to the equivalent angle, in degrees, in the range (-180, 180].
    /// @tparam T The type of the angle (e.g. float, double, masala::base::Real).
    /// @param angle_in The input angle, in degrees.
    /// @return An angle, in degrees, in the range (-180, 180].
    template < typename T >
    T
    inline
    zero_centred_angle_degrees(
        T const angle_in
    ) {
        return ( (angle_in + T(180)) % T(360) ) - T(180);
    }

} // namespace utility
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_utility_angle_util_hh