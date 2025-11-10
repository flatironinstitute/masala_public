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
		0, 8, 9, 1, 2, 3, 11, 10 
	};
	std::vector< Size > actual_array(256);
	REQUIRE_NOTHROW([&](){
		HilbertIndexedMatrix< Size > mat( 16, 16 );
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
	}() );
}

} // namespace utility
} // namespace base_classes
} // namespace numeric
} // namespace unit
} // namespace tests
} // namespace masala
