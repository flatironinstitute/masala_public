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

/// @file src/core_api/base_classes/selectors/atom_selectors/AtomSelector.hh
/// @brief Header for a pure virtual base class for AtomSelectors.
/// @details AtomSelectors select atoms in a molecular system based on some rule.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_hh
#define Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_hh

// Parent class:
#include <core_api/base_classes/selectors/Selector.hh>

// Forward declarations:
#include <core_api/base_classes/selectors/atom_selectors/AtomSelector.fwd.hh>

// Core headers:
#include <core/selection/atom_selection/AtomSelection.fwd.hh>

// Core API headers:
#include <core_api/auto_generated_api/molecular_system/MolecularSystem_API.fwd.hh>
#include <core_api/auto_generated_api/selection/atom_selection/AtomSelection_API.fwd.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace atom_selectors {

/// @brief A pure virtual base class for AtomSelectors.
/// @details AtomSelectors select atoms in a molecular system based on some rule.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomSelector : public masala::core_api::base_classes::selectors::Selector {

public:

	/// @brief Default constructor.
	AtomSelector() = default;

	/// @brief Copy constructor.
	AtomSelector( AtomSelector const & ) = default;

	/// @brief Destructor.
	~AtomSelector() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	// /// @brief Given the current molecular system, generate the selection.
	// /// @details Calls generate_atom_selection(), which must be implemented
	// /// by derived classes.
	// masala::core_api::auto_generated_api::selection::Selection_APICSP
	// generate_selection(
	// 	masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API const & molecular_system
	// ) const override;

	/// @brief Given the current molecular system, generate the atom selection.
	/// @details Pure virtual function.
	virtual
	masala::core_api::auto_generated_api::selection::atom_selection::AtomSelection_APICSP
	generate_atom_selection(
		masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API const & molecular_system
	) const = 0;

}; // class AtomSelector

} // namespace atom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_hh