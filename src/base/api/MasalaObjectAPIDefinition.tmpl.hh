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

/// @file src/base/api/MasalaObjectAPIDefinition.tmpl.hh
/// @brief Implementations of template functions for a class that stores
/// the definition for the API for an object.  Used to auto-generate the
/// public C++ headers, plus the bindings for Python or XML (or other
/// scripting languages).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaObjectAPIDefinition_tmpl_hh
#define Masala_src_base_api_MasalaObjectAPIDefinition_tmpl_hh

// Forward declarations.
#include <base/api/MasalaObjectAPIDefinition.hh>

// Base headers.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_TwoInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ThreeInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_FourInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_FiveInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ThreeInput.tmpl.hh>

namespace masala {
namespace base {
namespace api {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC TEMPLATE MEMBER FUNCTIONS FOR ACCESSING SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a one-parameter setter definition.
/// @returns Nullptr if the function doesn't exist; a const weak pointer
/// to the function otherwise.
template< typename P1 >
masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
MasalaObjectAPIDefinition::get_oneinput_setter_function(
	std::string const & function_name
) const {
	using namespace setter;

	for( auto const & setter: setters_ ) {
		if( setter->num_input_parameters() == 1 && setter->setter_function_name() == function_name ) {
			MasalaObjectAPISetterDefinition_OneInputCSP< P1 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_OneInput< P1 > const >( setter ) );
			if( setter_cast != nullptr ) {
				return setter;
			}
		}
	}
	return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
}

/// @brief Get a two-parameter setter definition.
/// @returns Nullptr if the function doesn't exist; a const weak pointer
/// to the function otherwise.
template< typename P1, typename P2 >
masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
MasalaObjectAPIDefinition::get_twoinput_setter_function(
	std::string const & function_name
) const {
	using namespace setter;

	for( auto const & setter: setters_ ) {
		if( setter->num_input_parameters() == 1 && setter->setter_function_name() == function_name ) {
			MasalaObjectAPISetterDefinition_TwoInputCSP< P1, P2 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_TwoInput< P1, P2 > const >( setter ) );
			if( setter_cast != nullptr ) {
				return setter;
			}
		}
	}
	return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
}

/// @brief Get a three-parameter setter definition.
/// @returns Nullptr if the function doesn't exist; a const weak pointer
/// to the function otherwise.
template< typename P1, typename P2, typename P3 >
masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
MasalaObjectAPIDefinition::get_threeinput_setter_function(
	std::string const & function_name
) const {
	using namespace setter;

	for( auto const & setter: setters_ ) {
		if( setter->num_input_parameters() == 1 && setter->setter_function_name() == function_name ) {
			MasalaObjectAPISetterDefinition_ThreeInputCSP< P1, P2, P3 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_ThreeInput< P1, P2, P3 > const >( setter ) );
			if( setter_cast != nullptr ) {
				return setter;
			}
		}
	}
	return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
}

/// @brief Get a four-parameter setter definition.
/// @returns Nullptr if the function doesn't exist; a const weak pointer
/// to the function otherwise.
template< typename P1, typename P2, typename P3, typename P4 >
masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
MasalaObjectAPIDefinition::get_fourinput_setter_function(
	std::string const & function_name
) const {
	using namespace setter;

	for( auto const & setter: setters_ ) {
		if( setter->num_input_parameters() == 1 && setter->setter_function_name() == function_name ) {
			MasalaObjectAPISetterDefinition_FourInputCSP< P1, P2, P3, P4 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_FourInput< P1, P2, P3, P4 > const >( setter ) );
			if( setter_cast != nullptr ) {
				return setter;
			}
		}
	}
	return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
}

/// @brief Get a five-parameter setter definition.
/// @returns Nullptr if the function doesn't exist; a const weak pointer
/// to the function otherwise.
template< typename P1, typename P2, typename P3, typename P4, typename P5 >
masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP
MasalaObjectAPIDefinition::get_fiveinput_setter_function(
	std::string const & function_name
) const {
	using namespace setter;

	for( auto const & setter: setters_ ) {
		if( setter->num_input_parameters() == 1 && setter->setter_function_name() == function_name ) {
			MasalaObjectAPISetterDefinition_FiveInputCSP< P1, P2, P3, P4, P5 > setter_cast( std::dynamic_pointer_cast< MasalaObjectAPISetterDefinition_FiveInput< P1, P2, P3, P4, P5 > const >( setter ) );
			if( setter_cast != nullptr ) {
				return setter;
			}
		}
	}
	return masala::base::api::setter::MasalaObjectAPISetterDefinitionCWP();
}

} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_MasalaObjectAPIDefinition_tmpl_hh