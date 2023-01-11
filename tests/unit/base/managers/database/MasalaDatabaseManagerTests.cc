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

/// @file tests/unit/base/managers/database/MasalaDatabaseManagerTests.cc
/// @brief Unit tests for the Masala database manager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/managers/database/MasalaDatabaseManager.hh>
#include <base/managers/database/elements/MasalaElementDatabase.hh>
#include <base/managers/database/elements/ElementType.hh>

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
namespace database {

TEST_CASE( "Load the element database", "[base::managers::database::MasalaDatabaseManager][database][elements]" ) {

    masala::base::managers::database::MasalaDatabaseManagerHandle dm(  masala::base::managers::database::MasalaDatabaseManager::get_instance() );
    REQUIRE_NOTHROW([&](){
        dm->element_database(); // Triggers load of element database.
    }() );

    masala::base::managers::database::elements::ElementTypeCSP calcium, magnesium, sulfur;
    REQUIRE_NOTHROW([&](){
        calcium = dm->element_database().element_type_from_abbreviation("Ca");
        magnesium = dm->element_database().element_type_from_ucase_abbreviation("MG");
        sulfur = dm->element_database().element_type_from_abbreviation("S");
    }() );
    
    CHECK( calcium->atomic_number() == 20 );
    CHECK( std::abs( calcium->average_atomic_mass() - 40.078  ) < 2.0e-3 );
    CHECK( magnesium->atomic_number() == 12 );
    CHECK( std::abs( magnesium->average_atomic_mass() - 24.305  ) < 2.0e-3 );
    CHECK( sulfur->atomic_number() == 16 );
    CHECK( std::abs( sulfur->average_atomic_mass() - 32.06 ) < 2.0e-3 );

}


} // namespace database
} // namespace managers
} // namespace base
} // namespace unit
} // namespace tests
} // namespace masala
