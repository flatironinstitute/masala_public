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

/// @file tests/unit/core/pose/PoseUnitTests.cc
/// @brief Unit tests for the Pose class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <core/pose/Pose.hh>

namespace masala {
namespace tests {
namespace unit {
namespace core {
namespace pose {

TEST_CASE( "Instantiate a pose", "[core::pose::Pose][instantiation]" ) {
    REQUIRE_NOTHROW([&](){
        masala::core::pose::PoseSP mypose( masala::make_shared< masala::core::pose::Pose >() );
        mypose->write_to_tracer( "Instantiated a pose." );
    }() );
}

} // namespace pose
} // namespace core
} // namespace unit
} // namespace tests
} // namespace masala
