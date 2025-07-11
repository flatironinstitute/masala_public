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
#include <base/enums/ChemicalBondTypeEnum.fwd.hh>
#include <base/enums/AtomHybridizationStateEnum.fwd.hh>
#include <base/managers/database/elements/ElementType.fwd.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition.hh>

// STL headers
#include <array>

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

TEST_CASE( "Test deprecated functions in molecular system.", "[core::molecular_system::MolecularSystem][core_api::auto_generated_api::molecular_system::MolecularSystem_API][deprecation]" ) {
	using masala::core_api::auto_generated_api::molecular_system::MolecularSystem_APISP;
	using masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API;
	using namespace masala::base::api;

	masala::numeric_api::auto_generated_api::registration::register_numeric();
	masala::core_api::auto_generated_api::registration::register_core();

	MolecularSystem_APISP my_molecular_system( masala::make_shared< MolecularSystem_API >() );
	MasalaObjectAPIDefinitionCSP api_def( my_molecular_system->get_api_definition_for_inner_class().lock() );
	CHECK( api_def != nullptr );
	setter::MasalaObjectAPISetterDefinition_OneInputCSP<masala::base::Size> dep_setter( api_def->get_oneinput_setter_function< masala::base::Size >( "deprecated_api_setter" ).lock() );
	getter::MasalaObjectAPIGetterDefinition_OneInputCSP<bool, masala::base::Size> dep_getter( api_def->get_oneinput_getter_function< bool, masala::base::Size >( "deprecated_api_getter" ).lock() );
	work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInputCSP< masala::base::Size, masala::base::Real const, bool const > dep_work_fxn( api_def->get_twoinput_work_function< masala::base::Size, masala::base::Real const, bool const  >( "deprecated_api_work_function" ).lock() );
	CHECK( dep_setter != nullptr );
	CHECK( dep_getter != nullptr );
	CHECK( dep_work_fxn != nullptr );
	my_molecular_system->write_to_tracer( "The next step is expected to throw an error indicating that a setter function is deprecated." );
	REQUIRE_THROWS([&](){
		dep_setter->function( 5 );
	}() );
	my_molecular_system->write_to_tracer( "The next step is expected to throw an error indicating that a getter function is deprecated." );
	REQUIRE_THROWS([&](){
		dep_getter->function( 5 );
	}() );
	my_molecular_system->write_to_tracer( "The next step is expected to throw an error indicating that a work function is deprecated." );
	REQUIRE_THROWS([&](){
		dep_work_fxn->function( 5.0, true );
	}() );

	CHECK( api_def->n_constructors() > api_def->n_constructors_non_deprecated() );
	CHECK( api_def->n_setters() > api_def->n_setters_non_deprecated() );
	CHECK( api_def->n_getters() > api_def->n_getters_non_deprecated() );
	CHECK( api_def->n_work_functions() > api_def->n_work_functions_non_deprecated() );

	bool dep_setter_found(false), dep_setter_found_in_nondep(false);
	bool dep_getter_found(false), dep_getter_found_in_nondep(false);
	bool dep_workfxn_found(false), dep_workfxn_found_in_nondep(false);
	for( std::vector<masala::base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator it( api_def->setters_begin() ); it != api_def->setters_end(); ++it ) {
		if( (*it)->setter_function_name() == "deprecated_api_setter" ) { dep_setter_found = true; }
	}
	for( std::vector<masala::base::api::setter::MasalaObjectAPISetterDefinitionCSP>::const_iterator it( api_def->setters_non_deprecated_begin() ); it != api_def->setters_non_deprecated_end(); ++it ) {
		if( (*it)->setter_function_name() == "deprecated_api_setter" ) { dep_setter_found_in_nondep = true; }
	}
	for( std::vector<masala::base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator it( api_def->getters_begin() ); it != api_def->getters_end(); ++it ) {
		if( (*it)->getter_function_name() == "deprecated_api_getter" ) { dep_getter_found = true; }
	}
	for( std::vector<masala::base::api::getter::MasalaObjectAPIGetterDefinitionCSP>::const_iterator it( api_def->getters_non_deprecated_begin() ); it != api_def->getters_non_deprecated_end(); ++it ) {
		if( (*it)->getter_function_name() == "deprecated_api_getter" ) { dep_getter_found_in_nondep = true; }
	}
	for( std::vector<masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator it( api_def->work_functions_begin() ); it != api_def->work_functions_end(); ++it ) {
		if( (*it)->work_function_name() == "deprecated_api_work_function" ) { dep_workfxn_found = true; }
	}
	for( std::vector<masala::base::api::work_function::MasalaObjectAPIWorkFunctionDefinitionCSP>::const_iterator it( api_def->work_functions_non_deprecated_begin() ); it != api_def->work_functions_non_deprecated_end(); ++it ) {
		if( (*it)->work_function_name() == "deprecated_api_work_function" ) { dep_workfxn_found_in_nondep = true; }
	}
	CHECK( dep_setter_found == true );
	CHECK( dep_getter_found == true );
	CHECK( dep_workfxn_found == true );
	CHECK( dep_setter_found_in_nondep == false );
	CHECK( dep_getter_found_in_nondep == false );
	CHECK( dep_workfxn_found_in_nondep == false );

	masala::core_api::auto_generated_api::registration::unregister_core();
	masala::numeric_api::auto_generated_api::registration::unregister_numeric();
}

TEST_CASE( "Instantiate a molecular system by its API and add some atoms and bonds.", "[core::molecular_system::MolecularSystem][core_api::auto_generated_api::molecular_system::MolecularSystem_API][instantiation]" ) {
	using masala::core_api::auto_generated_api::molecular_system::MolecularSystem_APISP;
	using masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API;
	using masala::core_api::auto_generated_api::chemistry::atoms::AtomInstance_APISP;
	using masala::core_api::auto_generated_api::chemistry::atoms::AtomInstance_API;
	using masala::base::Real;
	using masala::base::managers::database::elements::ElementTypeEnum;
	using masala::base::enums::AtomHybridizationState;
	using masala::base::enums::ChemicalBondType;

	masala::numeric_api::auto_generated_api::registration::register_numeric();
	masala::core_api::auto_generated_api::registration::register_core();

	REQUIRE_NOTHROW([&](){
		MolecularSystem_APISP my_molecular_system( masala::make_shared< MolecularSystem_API >() );
		my_molecular_system->write_to_tracer( "Instantiated a molecular system." );
		// Build carbon dioxide:
		AtomInstance_APISP atom1( masala::make_shared< AtomInstance_API >( "C", "sp2", 0, 0 ) ); // Less efficient -- requires string parsing.
		AtomInstance_APISP atom2( masala::make_shared< AtomInstance_API >( ElementTypeEnum::O, AtomHybridizationState::sp2, 0, 0 ) ); // More efficient -- enum-based.
		AtomInstance_APISP atom3( masala::make_shared< AtomInstance_API >( ElementTypeEnum::O, AtomHybridizationState::sp2, 0, 0 ) ); // More efficient -- enum-based.
		my_molecular_system->add_atom( atom1, std::array< Real, 3 >{ 0, 0, 0 } );
		my_molecular_system->add_atom( atom2, std::array< Real, 3 >{ 1.16, 0, 0 } );
		my_molecular_system->add_atom( atom3, std::array< Real, 3 >{ -1.16, 0, 0 } );
		my_molecular_system->add_bond( atom1, atom2, ChemicalBondType::DOUBLE_BOND ); // Enum is more efficient than parsing strings.
		my_molecular_system->add_bond( atom1, atom3, "double_bond" ); // Strings are less efficient.
		my_molecular_system->write_to_tracer( "Built carbon dioxide (O=C=O)." );
	}() );

	masala::core_api::auto_generated_api::registration::unregister_core();
	masala::numeric_api::auto_generated_api::registration::unregister_numeric();
}

} // namespace molecular_system
} // namespace core
} // namespace unit
} // namespace tests
} // namespace masala
