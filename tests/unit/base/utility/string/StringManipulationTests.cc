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

/// @file tests/unit/base/masla/utility/string/StringManipulationTests.cc
/// @brief Unit tests for string manipulation utility functions.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/utility/string/string_manipulation.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

// STL headers:
#include <string>

namespace masala {
namespace tests {
namespace unit {
namespace base {
namespace utility {
namespace string {

std::string const test_tracer( "masala::tests::unit::base::utility::string::string_manipulation_tests" );

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

TEST_CASE( "Convert camelcase to boxcar", "[base::utility::string][utility][string][string_manipulation]" ) {
	using namespace masala::base::utility::string;
	using namespace masala::base::managers::tracer;

	std::string const input1( "ThisIsTheTest" );
	std::string const input2( "THIsIsTheTEST" );
	std::string const input3( "T" );
	std::string const input4( "47IsTheTest32" );
	std::string const input5( "This_IsTheTest" );
	std::string const input6( "" );
	std::string output1, output2, output3, output4, output5, output6;
	
	REQUIRE_NOTHROW([&](){
		output1 = camelcase_to_boxcar( input1 );
		output2 = camelcase_to_boxcar( input2 );
		output3 = camelcase_to_boxcar( input3 );
		output4 = camelcase_to_boxcar( input4 );
		output5 = camelcase_to_boxcar( input5 );
		output6 = camelcase_to_boxcar( input6 );
	}() );

	MasalaTracerManagerHandle tm( MasalaTracerManager::get_instance() );
	tm->write_to_tracer( test_tracer, "\tINPUT\tOUTPUT" );
	tm->write_to_tracer( test_tracer, "\t\"" + input1 + "\"\t\"" + output1 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input2 + "\"\t\"" + output2 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input3 + "\"\t\"" + output3 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input4 + "\"\t\"" + output4 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input5 + "\"\t\"" + output5 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input6 + "\"\t\"" + output6 + "\"" );

	CHECK( output1 == "this_is_the_test" );
	CHECK( output2 == "this_is_the_test" );
	CHECK( output3 == "t" );
	CHECK( output4 == "47_is_the_test32" );
	CHECK( output5 == "this_is_the_test" );
	CHECK( output6 == "" );
}

TEST_CASE( "Convert boxcar to camelcase", "[base::utility::string][utility][string][string_manipulation]" ) {
	using namespace masala::base::utility::string;
	using namespace masala::base::managers::tracer;

	std::string const input1( "this_is_the_test" );
	std::string const input2( "this_is_a_test" );
	std::string const input3( "_this_is_a__tEsT" );
	std::string const input4( "47_iS_tHeTe_st3_2" );
	std::string const input5( "ThisIsTheTest" );
	std::string const input6( "" );
	std::string output1, output2, output3, output4, output5, output6;
	
	REQUIRE_NOTHROW([&](){
		output1 = boxcar_to_camelcase( input1 );
		output2 = boxcar_to_camelcase( input2 );
		output3 = boxcar_to_camelcase( input3 );
		output4 = boxcar_to_camelcase( input4 );
		output5 = boxcar_to_camelcase( input5 );
		output6 = boxcar_to_camelcase( input6 );
	}() );

	MasalaTracerManagerHandle tm( MasalaTracerManager::get_instance() );
	tm->write_to_tracer( test_tracer, "\tINPUT\tOUTPUT" );
	tm->write_to_tracer( test_tracer, "\t\"" + input1 + "\"\t\"" + output1 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input2 + "\"\t\"" + output2 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input3 + "\"\t\"" + output3 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input4 + "\"\t\"" + output4 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input5 + "\"\t\"" + output5 + "\"" );
	tm->write_to_tracer( test_tracer, "\t\"" + input6 + "\"\t\"" + output6 + "\"" );

	CHECK( output1 == "ThisIsTheTest" );
	CHECK( output2 == "ThisIsATest" );
	CHECK( output3 == "ThisIsATest" );
	CHECK( output4 == "47IsTheteSt32" );
	CHECK( output5 == "Thisisthetest" );
	CHECK( output6 == "" );
}


} // namespace string
} // namespace utility
} // namespace base
} // namespace unit
} // namespace tests
} // namespace masala
