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

/// @file src/core_api/base_classes/selectors/atom_selectors/AtomSelector.cc
/// @brief Function implementations for a pure virtual base class for AtomSelectors.
/// @details AtomSelectors select atoms in a molecular system based on some rule.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <core_api/base_classes/selectors/atom_selectors/AtomSelector.hh>

// Core headers:
#include <core/selection/atom_selection/AtomSelection.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace atom_selectors {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// /// @brief Given the current molecular system, generate the selection.
// /// @details Calls generate_atom_selection(), which must be implemented
// /// by derived classes.
// masala::core::selection::SelectionCSP
// AtomSelector::generate_selection(
// 	masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API const & molecular_system
// ) const {
// 	return generate_atom_selection( molecular_system );
// }

} // namespace atom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala