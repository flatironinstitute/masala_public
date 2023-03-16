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

/// @file tests/unit/core/molecular_system/MolecularSystemUnitTests.cc
/// @brief Unit tests for the MolecularSystem class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <core/molecular_system/MolecularSystem.hh>

namespace masala {
namespace tests {
namespace unit {
namespace core {
namespace molecular_system {

TEST_CASE( "Instantiate a molecular system", "[core::molecular_system::MolecularSystem][instantiation]" ) {
    REQUIRE_NOTHROW([&](){
        masala::core::molecular_system::MolecularSystemSP my_molecular_system( masala::make_shared< masala::core::molecular_system::MolecularSystem >() );
        my_molecular_system->write_to_tracer( "Instantiated a molecular system." );
    }() );
}

} // namespace molecular_system
} // namespace core
} // namespace unit
} // namespace tests
} // namespace masala
