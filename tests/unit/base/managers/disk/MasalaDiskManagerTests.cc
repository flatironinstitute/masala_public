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

/// @file tests/unit/base/managers/disk/MasalaDiskManagerTests.cc
/// @brief Unit tests for the Masala disk manager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/managers/disk/MasalaDiskManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/utility/container/container_util.tmpl.hh>

// STL headers:
#include <vector>

namespace masala {
namespace tests {
namespace unit {
namespace base {
namespace managers {
namespace disk {

std::string const testname( "masala::tests::unit::base::managers::disk::MasalaDiskManagerTests" );

TEST_CASE( "Test datestamps on files", "[base::managers::disk::MasalaDiskManager][disk][output][datestamp]" ) {
	using namespace masala::base::managers::disk;
	using namespace masala::base::managers::tracer;

	MasalaTracerManagerHandle tm( MasalaTracerManager::get_instance() );

	std::string outstring;

	REQUIRE_NOTHROW([&](){
		outstring = MasalaDiskManager::datestamped_filename( "myfile", ".txt", true, true, true );
	}() );

	std::string const expected_output( "myfile_thread_0_date_YYYYMMDD_time_HHMMSS.txt" );
	std::string outstring2( outstring );
	outstring2[21] = 'Y';
	outstring2[22] = 'Y';
	outstring2[23] = 'Y';
	outstring2[24] = 'Y';
	outstring2[25] = 'M';
	outstring2[26] = 'M';
	outstring2[27] = 'D';
	outstring2[28] = 'D';
	outstring2[35] = 'H';
	outstring2[36] = 'H';
	outstring2[37] = 'M';
	outstring2[38] = 'M';
	outstring2[39] = 'S';
	outstring2[40] = 'S';

	tm->write_to_tracer( testname, "EXPECTED:\t" + expected_output );
	tm->write_to_tracer( testname, "  ACTUAL:\t" + outstring );
	tm->write_to_tracer( testname, " ACTUAL2:\t" + outstring2 );

	CHECK( outstring2 == expected_output );
}


} // namespace disk
} // namespace managers
} // namespace base
} // namespace unit
} // namespace tests
} // namespace masala
