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

/// @file src/core_api/base_classes/selectors/degree_of_freedom_selectors//DegreeOfFreedomSelector.cc
/// @brief Function implementations for a pure virtual base class for DegreeOfFreedomSelectors.
/// @details DegreeOfFreedomSelectors select degrees of freedom in a molecular system.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <core_api/base_classes/selectors/degree_of_freedom_selectors/DegreeOfFreedomSelector.hh>

// Core-API headers:
#include <core_api/base_classes/selectors/degree_of_freedom_selectors/DegreeOfFreedomSelection.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace degree_of_freedom_selectors {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// /// @brief Given the current molecular system, generate the selection.
// /// @details Calls generate_degree_of_freedom_selection(), which must be implemented
// /// by derived classes.
// core::selection::SelectionCSP
// DegreeOfFreedomSelector::generate_selection(
// 	core_api::auto_generated_api::molecular_system::MolecularSystem_API const & molecular_system
// ) const {
// 	return generate_degree_of_freedom_selection( molecular_system );
// }

} // namespace degree_of_freedom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala