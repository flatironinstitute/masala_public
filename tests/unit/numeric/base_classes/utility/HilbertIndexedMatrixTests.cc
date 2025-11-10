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

/// @file tests/unit/numeric/base_classes/utility/HilbertIndexedMatrixTests.cc
/// @brief Unit tests for the Hilbert curve indexed matrix template class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <numeric_api/base_classes/utility/HilbertIndexedMatrix.tmpl.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

namespace masala {
namespace tests {
namespace unit {
namespace numeric {
namespace base_classes {
namespace utility {

std::string const testname( "masala::tests::unit::numeric::base_classes::utility" );

TEST_CASE(
	"Test the HilbertIndexedMatrix class with unsigned integer values.",
	"[numeric_api::base_classes::utility::HilbertIndexedMatrix]"
	"[instantiation]"
) {
	using masala::base::Size;
	using namespace masala::numeric_api::base_classes::utility;
	using namespace masala::base::utility::container;
	using namespace masala::base::managers::tracer;

	MasalaTracerManagerHandle tm(MasalaTracerManager::get_instance() );

	std::vector< Size > expected_array{
		0,16,17,1,2,3,19,18,34,35,51,50,49,33,32,48,
		64,65,81,80,96,112,113,97,98,114,115,99,83,82,66,67,
		68,69,85,84,100,116,117,101,102,118,119,103,87,86,70,71,
		55,39,38,54,53,52,36,37,21,20,4,5,6,22,23,7,
		8,9,25,24,40,56,57,41,42,58,59,43,27,26,10,11,
		12,28,29,13,14,15,31,30,46,47,63,62,61,45,44,60,
		76,92,93,77,78,79,95,94,110,111,127,126,125,109,108,124,
		123,122,106,107,91,75,74,90,89,73,72,88,104,105,121,120,
		136,137,153,152,168,184,185,169,170,186,187,171,155,154,138,139,
		140,156,157,141,142,143,159,158,174,175,191,190,189,173,172,188,
		204,220,221,205,206,207,223,222,238,239,255,254,253,237,236,252,
		251,250,234,235,219,203,202,218,217,201,200,216,232,233,249,248,
		247,231,230,246,245,244,228,229,213,212,196,197,198,214,215,199,
		183,182,166,167,151,135,134,150,149,133,132,148,164,165,181,180,
		179,178,162,163,147,131,130,146,145,129,128,144,160,161,177,176,
		192,208,209,193,194,195,211,210,226,227,243,242,241,225,224,240
	};

	std::vector< Size > actual_array(256);
	REQUIRE_NOTHROW([&](){
		HilbertIndexedMatrix< Size > mat( 16, 16 );
		CHECK( mat.allocated_array_size() == 256 );
		Size counter( 0 );
		for( Size col(0); col < 16; ++col ) {
			for( Size row(0); row < 16; ++row ) {
				mat( row, col ) = counter;
				++counter;
			}
		}
	
		Size * data( mat.data_nonconst() );
		for( Size i(0); i<256; ++i ) {
			actual_array[i] = data[i];
		}
		tm->write_to_tracer( testname, "Actual array:\t[" + container_to_string( actual_array, "," ) + "]" );
		tm->write_to_tracer( testname, "Expected array:\t[" + container_to_string( expected_array, "," ) + "]");
		CHECK( actual_array == expected_array );
	}() );
}

} // namespace utility
} // namespace base_classes
} // namespace numeric
} // namespace unit
} // namespace tests
} // namespace masala
