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

/// @file tests/unit/base/masla/plugin_module/MasalaPluginModuleManagerTests.cc
/// @brief Unit tests for string manipulation utility functions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/utility/string/string_manipulation.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <string>

namespace masala {
namespace tests {
namespace unit {
namespace base {
namespace utility {
namespace string {


TEST_CASE( "Trim strings", "[base::utility::string][utility][string][string_manipulation]" ) {

    using namespace masala::base::utility::string;

    std::string output1, output2, output3, output4, output5, output6, output7, output8, output9;

    REQUIRE_NOTHROW([&](){
        output1 = rtrim("  test one \t");
        output2 = ltrim("  test two \t");
        output3 = trim(" \n\t test\n three \n\n");
        output4 = rtrim( "  \t\n" );
        output5 = ltrim( "  \t\n" );
        output6 = trim( "  \t\n" );
        output7 = rtrim( "nothing to\ttrim\nhere" );
        output8 = rtrim( "nothing to\ttrim\nhere" );
        output9 = rtrim( "nothing to\ttrim\nhere" );
    }() );

    CHECK( output1 == "  test one" );
    CHECK( output2 == "test two \t" );
    CHECK( output3 == "test\n three" );
    CHECK( output4 == "" );
    CHECK( output5 == "" );
    CHECK( output6 == "" );
    CHECK( output7 == "nothing to\ttrim\nhere" );
    CHECK( output8 == "nothing to\ttrim\nhere" );
    CHECK( output9 == "nothing to\ttrim\nhere" );
}


} // namespace string
} // namespace utility
} // namespace base
} // namespace unit
} // namespace tests
} // namespace masala
