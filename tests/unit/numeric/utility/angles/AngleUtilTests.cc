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

/// @file tests/unit/numeric/utility/angles/AngleUtilTests.cc
/// @brief Unit tests for angle utility functions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <numeric_api/utility/angles/angle_util.hh>

// Base headers:
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/types.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace tests {
namespace unit {
namespace numeric {
namespace utility {
namespace angles {

TEST_CASE(
	"Test the conversion of an angle in degrees to the 0 to 360 range.",
	"[numeric_api::utility::angles]"
	"[numeric_api::utility::angles::positive_angle_degrees]"
) {
	using namespace masala::numeric_api::utility::angles;
	using masala::base::Real;
	using masala::base::Size;
	std::vector< Real > const testcases{ -781.8, -720.0, -492.3, -360.0, -72.3, 0.0, 33.5, 189.4, 360.0, 360.1, 718.0, 720.0, 750.1 };
	std::vector< Real > const expected_results{ 298.2, 0.0, 227.7, 0.0, -287.7, 0.0, 33.5, 189.4, 0.0, 0.1, 358.0, 720.0, 30.1 };
	std::vector< Real > actual_results( testcases.size() );
	REQUIRE_NOTHROW([&](){
		for( Size i(0); i<testcases.size(); ++i ) {
			actual_results[i] = positive_angle_degrees( testcases[i] );
		}
	}() );

	masala::base::managers::tracer::MasalaTracerManagerHandle tm( masala::base::managers::tracer::MasalaTracerManager::get_instance() );
	std::stringstream ss;
	ss << "Case\tInput\tExpected\tActual";
	for( Size i(0); i<testcases.size(); ++i ){
		ss << "\n" << i
			<< "\t" << testcases[i]
			<< "\t" << expected_results[i]
			<< "\t" << actual_results[i];
		CHECK( std::abs( expected_results[i] - actual_results[i] ) < 1.0e-6 );
	}
	tm->write_to_tracer( ss.str() );
}

} // namespace angles
} // namespace utility
} // namespace numeric
} // namespace unit
} // namespace tests
} // namespace masala
