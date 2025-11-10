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

// STL headers:
#include <sstream>

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
	"[storage]"
) {
	using masala::base::Size;
	using namespace masala::numeric_api::base_classes::utility;
	using namespace masala::base::utility::container;
	using namespace masala::base::managers::tracer;

	MasalaTracerManagerHandle tm(MasalaTracerManager::get_instance() );

	std::vector< Size > const expected_array{
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

	std::vector< std::vector< Size > > expected_final_matrix{
		std::vector< Size >{0,1,14,15,16,19,20,21,234,235,236,239,240,241,254,255},
		std::vector< Size >{3,2,13,12,17,18,23,22,233,232,237,238,243,242,253,252},
		std::vector< Size >{4,7,8,11,30,29,24,25,230,231,226,225,244,247,248,251},
		std::vector< Size >{5,6,9,10,31,28,27,26,229,228,227,224,245,246,249,250},
		std::vector< Size >{58,57,54,53,32,35,36,37,218,219,220,223,202,201,198,197},
		std::vector< Size >{59,56,55,52,33,34,39,38,217,216,221,222,203,200,199,196},
		std::vector< Size >{60,61,50,51,46,45,40,41,214,215,210,209,204,205,194,195},
		std::vector< Size >{63,62,49,48,47,44,43,42,213,212,211,208,207,206,193,192},
		std::vector< Size >{64,67,68,69,122,123,124,127,128,131,132,133,186,187,188,191},
		std::vector< Size >{65,66,71,70,121,120,125,126,129,130,135,134,185,184,189,190},
		std::vector< Size >{78,77,72,73,118,119,114,113,142,141,136,137,182,183,178,177},
		std::vector< Size >{79,76,75,74,117,116,115,112,143,140,139,138,181,180,179,176},
		std::vector< Size >{80,81,94,95,96,97,110,111,144,145,158,159,160,161,174,175},
		std::vector< Size >{83,82,93,92,99,98,109,108,147,146,157,156,163,162,173,172},
		std::vector< Size >{84,87,88,91,100,103,104,107,148,151,152,155,164,167,168,171},
		std::vector< Size >{85,86,89,90,101,102,105,106,149,150,153,154,165,166,169,170}
	};

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

		CHECK( mat( 15,15 ) == 255 );
		CHECK( mat( 0,0 ) == 0 );
		CHECK( mat( 15,0 ) == 15 );
		CHECK( mat( 0,1 ) == 16 );
		CHECK( mat( 0,15 ) == 240 );

		for( Size i(0); i<256; ++i ) {
			data[i] = i;
		}

		std::ostringstream ss;
		tm->write_to_tracer( testname, "Matrix after overwriting data array:");
		for( Size row(0); row<16; ++row ) {
			if(row > 0) { ss << "\n"; }
			for( Size col(0); col<16; ++col ) {
				if(col > 0) { ss << " "; }
				ss << mat(row, col);
				CHECK( mat(row, col) == expected_final_matrix[row][col] );
			}
		}
		tm->write_to_tracer( testname, ss.str() );
	}() );
}

TEST_CASE(
	"Test resizing the HilbertIndexedMatrix class with unsigned integer values.",
	"[numeric_api::base_classes::utility::HilbertIndexedMatrix]"
	"[instantiation]"
	"[resizing]"
) {
	using masala::base::Size;
	using namespace masala::numeric_api::base_classes::utility;
	using namespace masala::base::utility::container;
	using namespace masala::base::managers::tracer;

	MasalaTracerManagerHandle tm(MasalaTracerManager::get_instance() );

	REQUIRE_NOTHROW([&](){
		HilbertIndexedMatrix< Size > mat( 15, 15 );
		Size counter(0);
		for( Size irow(0); irow < 15; ++irow ) {
			for( Size icol(0); icol < 15; ++icol ) {
				mat( irow, icol ) = counter;
				++counter;
			}
		}
		{
			std::ostringstream ss;
			tm->write_to_tracer( testname, "Initial matrix:");
			for( Size row(0); row<15; ++row ) {
				if(row > 0) { ss << "\n"; }
				for( Size col(0); col<15; ++col ) {
					if(col > 0) { ss << " "; }
					ss << mat(row, col);
				}
			}
			tm->write_to_tracer( testname, ss.str() );
		}

		// Add a column.  Should not trigger reallocation.
		mat.conservativeResize( mat.rows(), 16 );
		for( Size irow(0); irow < 15; ++irow ) {
			mat( irow, 15 ) = 0; 
		}
		counter = 0;
		tm->write_to_tracer( testname, "Column-expanded matrix 1:");
		{
			std::ostringstream ss;
			for( Size row(0); row<15; ++row ) {
				if(row > 0) { ss << "\n"; }
				for( Size col(0); col<16; ++col ) {
					if(col > 0) { ss << " "; }
					ss << mat(row, col);
					if( col < 15 ) {
						CHECK( mat(row, col) == counter );
						++counter;
					} else {
						CHECK( mat(row, col) == 0 );
					}
				}
			}
			tm->write_to_tracer( testname, ss.str() );
		}

		// Add a row.  Should not trigger reallocation.
		mat.conservativeResize( 16, mat.cols() );
		for( Size icol(0); icol < 16; ++icol ) {
			mat( 15, icol ) = 0; 
		}
		counter = 0;
		tm->write_to_tracer( testname, "Row-expanded matrix 1:");
		{
			std::ostringstream ss;
			for( Size row(0); row<16; ++row ) {
				if(row > 0) { ss << "\n"; }
				for( Size col(0); col<16; ++col ) {
					if(col > 0) { ss << " "; }
					ss << mat(row, col);
					if( col < 15 && row < 15 ) {
						CHECK( mat(row, col) == counter );
						++counter;
					} else {
						CHECK( mat(row, col) == 0 );
					}
				}
			}
			tm->write_to_tracer( testname, ss.str() );
		}

	}() );
}

} // namespace utility
} // namespace base_classes
} // namespace numeric
} // namespace unit
} // namespace tests
} // namespace masala
