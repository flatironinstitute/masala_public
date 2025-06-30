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

/// @file tests/unit/base/masla/plugin_module/MasalaPluginModuleManagerTests.cc
/// @brief Unit tests for string comparison utility functions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/utility/string/string_comparison.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <string>
#include <vector>

namespace masala {
namespace tests {
namespace unit {
namespace base {
namespace utility {
namespace string {


TEST_CASE( "Check string starts and endings", "[base::utility::string][utility][string][string_comparison]" ) {

    using namespace masala::base::utility::string;
    using masala::base::Size;

    std::vector< std::string > inputs { "Henry VII", "Henry VIII", "Elizabeth I" };
    std::vector< std::string > endings{ "VII", "VIII", "I", "X", "Henry VIII" };
    std::vector< std::string > starts{ "Henry VII", "Elizabeth", "Richard", "Elizabeth I" };
    std::vector< bool > end_results( inputs.size() * endings.size() );
    std::vector< bool > const expected_end_results{
        true, false, true, false, false,
        false, true, true, false, true,
        false, false, true, false, false
    };
    std::vector< bool > start_results( inputs.size() * starts.size() );
    std::vector< bool > const expected_start_results{
        true, false, false, false,
        true, false, false, false,
        false, true, false, true
    };

    REQUIRE_NOTHROW([&](){
        Size counter(0);
        for( Size i(0); i<inputs.size(); ++i ) {
            for( Size j(0); j<endings.size(); ++j ) {
                end_results[counter] = string_ends_with( inputs[i], endings[j] );
                ++counter;
            }
        }
        counter = 0;
        for( Size i(0); i<inputs.size(); ++i ) {
            for( Size j(0); j<starts.size(); ++j ) {
                start_results[counter] = string_starts_with( inputs[i], starts[j] );
                ++counter;
            }
        }
    }() );

    CHECK( end_results == expected_end_results );
    CHECK( start_results == expected_start_results );
}


} // namespace string
} // namespace utility
} // namespace base
} // namespace unit
} // namespace tests
} // namespace masala
