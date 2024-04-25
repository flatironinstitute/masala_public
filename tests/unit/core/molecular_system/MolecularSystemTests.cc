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

/// @file tests/unit/core/molecular_system/MolecularSystemTests.cc
/// @brief Unit tests for the MolecularSystem class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <core/molecular_system/MolecularSystem.hh>
#include <core_api/auto_generated_api/molecular_system/MolecularSystem_API.hh>
#include <core_api/auto_generated_api/chemistry/atoms/AtomInstance_API.hh>
#include <core_api/auto_generated_api/registration/register_core.hh>
#include <numeric_api/auto_generated_api/registration/register_numeric.hh>

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

TEST_CASE( "Instantiate a molecular system by its API and add some atoms and bonds.", "[core::molecular_system::MolecularSystem][core_api::auto_generated_api::molecular_system::MolecularSystem_API][instantiation]" ) {
	using masala::core_api::auto_generated_api::molecular_system::MolecularSystem_APISP;
	using masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API;
	using masala::core_api::auto_generated_api::chemistry::atoms::AtomInstance_APISP;
	using masala::core_api::auto_generated_api::chemistry::atoms::AtomInstance_API;
	using masala::base::Real;

    masala::numeric_api::auto_generated_api::registration::register_numeric();
    masala::core_api::auto_generated_api::registration::register_core();

    REQUIRE_NOTHROW([&](){
       MolecularSystem_APISP my_molecular_system( masala::make_shared< MolecularSystem_API >() );
        my_molecular_system->write_to_tracer( "Instantiated a molecular system." );
		AtomInstance_APISP atom1( masala::make_shared< AtomInstance_API >( "H", "s", 0, 0 ) );
		AtomInstance_APISP atom2( masala::make_shared< AtomInstance_API >( "H", "s", 0, 0 ) );
		my_molecular_system->add_atom( atom1, std::array< Real, 3 >{ 0, 0, 0 } );
		my_molecular_system->add_atom( atom2, std::array< Real, 3 >{ 0.74, 0, 0 } );
    }() );

    masala::core_api::auto_generated_api::registration::unregister_core();
    masala::numeric_api::auto_generated_api::registration::unregister_numeric();
}

} // namespace molecular_system
} // namespace core
} // namespace unit
} // namespace tests
} // namespace masala
