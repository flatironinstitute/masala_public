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

/// @file src/core_api/base_classes/selectors/Selector.hh
/// @brief Header for a pure virtual base class for Selectors.
/// @details Selectors select something (atoms, residues, etc.).
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_Selector_hh
#define Masala_src_core_api_base_classes_selectors_Selector_hh

// Forward declarations:
#include <core_api/base_classes/selectors/Selector.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Core headers:
#include <core/selection/Selection.fwd.hh>

// Core API headers:
#include <core_api/auto_generated_api/molecular_system/MolecularSystem_API.fwd.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {

/// @brief A pure virtual base class for Selectors.
/// @details Selectors select something (atoms, residues, etc.).
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Selector : public masala::base::managers::plugin_module::MasalaPlugin {

public:

	/// @brief Default constructor.
	Selector() = default;

	/// @brief Copy constructor.
	Selector( Selector const & ) = default;

	/// @brief Destructor.
	~Selector() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	// /// @brief Given the current molecular system, generate the selection.
	// /// @details Pure virtual function.  Must be implemented by sub-classes.
	// virtual
	// masala::core::selection::SelectionCSP
	// generate_selection(
	// 	masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API const & molecular_system
	// ) const = 0;

}; // class Selector

} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_Selector_hh