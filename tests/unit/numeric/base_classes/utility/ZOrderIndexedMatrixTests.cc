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

/// @file tests/unit/numeric/base_classes/utility/ZOrderIndexedMatrixTests.cc
/// @brief Unit tests for the ZOrder curve indexed matrix template class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <numeric_api/base_classes/utility/ZOrderIndexedMatrix.tmpl.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

// STL headers:
#include <sstream>
#include <iomanip>

namespace masala {
namespace tests {
namespace unit {
namespace numeric {
namespace base_classes {
namespace utility {

std::string const testname( "masala::tests::unit::numeric::base_classes::utility" );

TEST_CASE(
	"Test the ZOrderIndexedMatrix::shift_for_interleave() function.",
	"[numeric_api::base_classes::utility::ZOrderIndexedMatrix]"
) {
	using masala::base::Size;
	using namespace masala::numeric_api::base_classes::utility;
	using namespace masala::base::utility::container;
	using namespace masala::base::managers::tracer;

	MasalaTracerManagerHandle tm(MasalaTracerManager::get_instance() );

	REQUIRE_NOTHROW([&](){
		ZOrderIndexedMatrixTester< Size > tester;

		{
			std::vector< Size > const inputs1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			std::vector< Size > const expected_outputs1{ 0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85, 256 };
			std::vector< Size > outputs1( inputs1.size(), 0 );
			std::ostringstream ss;
			ss << "Input1\tExpected1\tActual1\n";
			for( Size i(0); i<inputs1.size(); ++i ) {
				outputs1[i] = inputs1[i];
				tester.shift_for_interleave( outputs1[i], 16 );
				ss << inputs1[i] << "\t" << expected_outputs1[i] << "\t" << outputs1[i] << "\n";
			}
			tm->write_to_tracer( testname, ss.str() );
			CHECK( expected_outputs1 == outputs1 );
		}

		{
			std::vector< Size > const inputs2{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			std::vector< Size > const expected_outputs2{ 0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85, 256 };
			std::vector< Size > outputs2( inputs2.size(), 0 );
			std::ostringstream ss;
			ss << "Input2\tExpected2\tActual2\n";
			for( Size i(0); i<inputs2.size(); ++i ) {
				outputs2[i] = inputs2[i];
				tester.shift_for_interleave( outputs2[i], 31 );
				ss << inputs2[i] << "\t" << expected_outputs2[i] << "\t" << outputs2[i] << "\n";
			}
			tm->write_to_tracer( testname, ss.str() );
			CHECK( expected_outputs2 == outputs2 );
		}

		{
			std::vector< Size > const inputs3{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			std::vector< Size > const expected_outputs3{ 0, 1, 4, 5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85, 128 };
			std::vector< Size > outputs3( inputs3.size(), 0 );
			std::ostringstream ss;
			ss << "Input3\tExpected3\tActual3\n";
			for( Size i(0); i<inputs3.size(); ++i ) {
				outputs3[i] = inputs3[i];
				tester.shift_for_interleave( outputs3[i], 4 );
				ss << inputs3[i] << "\t" << expected_outputs3[i] << "\t" << outputs3[i] << "\n";
			}
			tm->write_to_tracer( testname, ss.str() );
			CHECK( expected_outputs3 == outputs3 );
		}

		{
			std::vector< Size > const inputs4{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			std::vector< Size > const expected_outputs4{ 0, 1, 4, 5, 16, 17, 20, 21, 32, 33, 36, 37, 48, 49, 52, 53, 64 };
			std::vector< Size > outputs4( inputs4.size(), 0 );
			std::ostringstream ss;
			ss << "Input4\tExpected4\tActual4\n";
			for( Size i(0); i<inputs4.size(); ++i ) {
				outputs4[i] = inputs4[i];
				tester.shift_for_interleave( outputs4[i], 3 );
				ss << inputs4[i] << "\t" << expected_outputs4[i] << "\t" << outputs4[i] << "\n";
			}
			tm->write_to_tracer( testname, ss.str() );
			CHECK( expected_outputs4 == outputs4 );
		}
	}() );
}

TEST_CASE(
	"Test the ZOrderIndexedMatrix class with unsigned integer values.",
	"[numeric_api::base_classes::utility::ZOrderIndexedMatrix]"
	"[instantiation]"
	"[storage]"
) {
	using masala::base::Size;
	using namespace masala::numeric_api::base_classes::utility;
	using namespace masala::base::utility::container;
	using namespace masala::base::managers::tracer;

	MasalaTracerManagerHandle tm(MasalaTracerManager::get_instance() );

	std::vector< Size > const expected_array{
		0, 1, 16, 17, 2, 3, 18, 19, 32, 33, 48, 49, 34, 35, 50, 51, 4, 5, 20, 21,
		6, 7, 22, 23, 36, 37, 52, 53, 38, 39, 54, 55, 64, 65, 80, 81, 66, 67, 82, 83,
		96, 97, 112, 113, 98, 99, 114, 115, 68, 69, 84, 85, 70, 71, 86, 87, 100, 101,
		116, 117, 102, 103, 118, 119, 8, 9, 24, 25, 10, 11, 26, 27, 40, 41, 56, 57,
		42, 43, 58, 59, 12, 13, 28, 29, 14, 15, 30, 31, 44, 45, 60, 61, 46, 47, 62,
		63, 72, 73, 88, 89, 74, 75, 90, 91, 104, 105, 120, 121, 106, 107, 122, 123,
		76, 77, 92, 93, 78, 79, 94, 95, 108, 109, 124, 125, 110, 111, 126, 127, 128,
		129, 144, 145, 130, 131, 146, 147, 160, 161, 176, 177, 162, 163, 178, 179,
		132, 133, 148, 149, 134, 135, 150, 151, 164, 165, 180, 181, 166, 167, 182,
		183, 192, 193, 208, 209, 194, 195, 210, 211, 224, 225, 240, 241, 226, 227,
		242, 243, 196, 197, 212, 213, 198, 199, 214, 215, 228, 229, 244, 245, 230,
		231, 246, 247, 136, 137, 152, 153, 138, 139, 154, 155, 168, 169, 184, 185,
		170, 171, 186, 187, 140, 141, 156, 157, 142, 143, 158, 159, 172, 173, 188,
		189, 174, 175, 190, 191, 200, 201, 216, 217, 202, 203, 218, 219, 232, 233,
		248, 249, 234, 235, 250, 251, 204, 205, 220, 221, 206, 207, 222, 223, 236,
		237, 252, 253, 238, 239, 254, 255
	};
	std::vector< Size > actual_array(256);

	std::vector< std::vector< Size > > expected_final_matrix{
		std::vector< Size >{  0,  1,  4,  5, 16, 17, 20, 21, 64, 65, 68, 69, 80, 81, 84, 85},
		std::vector< Size >{  2,  3,  6,  7, 18, 19, 22, 23, 66, 67, 70, 71, 82, 83, 86, 87},
		std::vector< Size >{  8,  9, 12, 13, 24, 25, 28, 29, 72, 73, 76, 77, 88, 89, 92, 93},
		std::vector< Size >{ 10, 11, 14, 15, 26, 27, 30, 31, 74, 75, 78, 79, 90, 91, 94, 95},
		std::vector< Size >{ 32, 33, 36, 37, 48, 49, 52, 53, 96, 97,100,101,112,113,116,117},
		std::vector< Size >{ 34, 35, 38, 39, 50, 51, 54, 55, 98, 99,102,103,114,115,118,119},
		std::vector< Size >{ 40, 41, 44, 45, 56, 57, 60, 61,104,105,108,109,120,121,124,125},
		std::vector< Size >{ 42, 43, 46, 47, 58, 59, 62, 63,106,107,110,111,122,123,126,127},
		std::vector< Size >{128,129,132,133,144,145,148,149,192,193,196,197,208,209,212,213},
		std::vector< Size >{130,131,134,135,146,147,150,151,194,195,198,199,210,211,214,215},
		std::vector< Size >{136,137,140,141,152,153,156,157,200,201,204,205,216,217,220,221},
		std::vector< Size >{138,139,142,143,154,155,158,159,202,203,206,207,218,219,222,223},
		std::vector< Size >{160,161,164,165,176,177,180,181,224,225,228,229,240,241,244,245},
		std::vector< Size >{162,163,166,167,178,179,182,183,226,227,230,231,242,243,246,247},
		std::vector< Size >{168,169,172,173,184,185,188,189,232,233,236,237,248,249,252,253},
		std::vector< Size >{170,171,174,175,186,187,190,191,234,235,238,239,250,251,254,255}
	};

	REQUIRE_NOTHROW([&](){
		ZOrderIndexedMatrix< Size > mat( 16, 16 );
		CHECK( mat.allocated_array_size() == 256 );
		Size counter( 0 );
		for( Size row(0); row < 16; ++row ) {
			for( Size col(0); col < 16; ++col ) {
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
		CHECK( mat( 0,15 ) == 15 );
		CHECK( mat( 1,0 ) == 16 );
		CHECK( mat( 15,0 ) == 240 );

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
	"Test resizing the ZOrderIndexedMatrix class with unsigned integer values.",
	"[numeric_api::base_classes::utility::ZOrderIndexedMatrix]"
	"[instantiation]"
	"[resizing]"
) {
	using masala::base::Size;
	using namespace masala::numeric_api::base_classes::utility;
	using namespace masala::base::utility::container;
	using namespace masala::base::managers::tracer;

	MasalaTracerManagerHandle tm(MasalaTracerManager::get_instance() );

	REQUIRE_NOTHROW([&](){
		ZOrderIndexedMatrix< Size > mat( 15, 15 );
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
					ss << std::setfill(' ') << std::setw(3) << mat(row, col);
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
					ss << std::setfill(' ') << std::setw(3) << mat(row, col);
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
		tm->write_to_tracer( testname, "Row-expanded matrix 2:");
		{
			std::ostringstream ss;
			for( Size row(0); row<16; ++row ) {
				if(row > 0) { ss << "\n"; }
				for( Size col(0); col<16; ++col ) {
					if(col > 0) { ss << " "; }
					ss << std::setfill(' ') << std::setw(3) << mat(row, col);
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

		// Further increase the size.  Should trigger reallocation.
		mat.conservativeResize( 20, 20 );
		for( Size icol(0); icol < 20; ++icol ) {
			for( Size irow(0); irow < 20; ++irow ) {
				if( icol > 14 || irow > 14 ) {
					mat(icol, irow) = 0;
				}
			}
		}
		counter = 0;
		tm->write_to_tracer( testname, "Row- and column-expanded matrix 3:");
		{
			std::ostringstream ss;
			for( Size row(0); row<20; ++row ) {
				if(row > 0) { ss << "\n"; }
				for( Size col(0); col<20; ++col ) {
					if(col > 0) { ss << " "; }
					ss << std::setfill(' ') << std::setw(3) << mat(row, col);
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

		// Contract the size.  Should not trigger reallocation.
		mat.conservativeResize( 20, 8 );
		counter = 0;
		tm->write_to_tracer( testname, "Row-expanded, column-contracted matrix 4:");
		{
			std::ostringstream ss;
			for( Size row(0); row<20; ++row ) {
				if(row > 0) {
					ss << "\n";
					counter += 7;
				}
				for( Size col(0); col<8; ++col ) {
					if(col > 0) { ss << " "; }
					ss << std::setfill(' ') << std::setw(3) << mat(row, col);
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

		// Contract the size.  Should trigger reallocation.
		mat.conservativeResize( 8, 8 );
		counter = 0;
		tm->write_to_tracer( testname, "Row-expanded, column-contracted matrix 5:");
		{
			std::ostringstream ss;
			for( Size row(0); row<8; ++row ) {
				if(row > 0) {
					ss << "\n";
					counter += 7;
				}
				for( Size col(0); col<8; ++col ) {
					if(col > 0) { ss << " "; }
					ss << std::setfill(' ') << std::setw(3) << mat(row, col);
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
