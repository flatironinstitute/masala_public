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

/// @file src/core_api/base_classes/selectors/atom_selectors/annotated_region_selectors/AnnotatedRegionSelector.hh
/// @brief Header for a pure virtual base class for AnnotatedRegionSelectors.
/// @details AnnotatedRegionSelectors select atoms in a molecular system based on annotated regions.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_atom_selectors_annotated_region_selectors_AnnotatedRegionSelector_hh
#define Masala_src_core_api_base_classes_selectors_atom_selectors_annotated_region_selectors_AnnotatedRegionSelector_hh

// Parent class:
#include <core_api/base_classes/selectors/atom_selectors/AtomSelector.hh>

// Forward declarations:
#include <core_api/base_classes/selectors/atom_selectors/annotated_region_selectors/AnnotatedRegionSelector.fwd.hh>

// Core headers:
#include <core/selection/Selection.fwd.hh>

// Core API headers:
#include <core_api/base_classes/selectors/atom_selectors/annotated_region_selectors/AnnotatedRegionSelection.fwd.hh>
#include <core_api/auto_generated_api/molecular_system/MolecularSystem_API.fwd.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace atom_selectors {
namespace annotated_region_selectors {

/// @brief A pure virtual base class for AnnotatedRegionSelectors.
/// @details AnnotatedRegionSelectors select atoms in a molecular system based on annotated regions.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AnnotatedRegionSelector : public masala::core_api::base_classes::selectors::atom_selectors::AtomSelector {

public:

	/// @brief Default constructor.
	AnnotatedRegionSelector() = default;

	/// @brief Copy constructor.
	AnnotatedRegionSelector( AnnotatedRegionSelector const & ) = default;

	/// @brief Destructor.
	~AnnotatedRegionSelector() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	// /// @brief Given the current molecular system, generate the selection.
	// /// @details Calls generate_annotated_region_selection(), which must be implemented
	// /// by derived classes.
	// masala::core::selection::SelectionCSP
	// generate_selection(
	// 	masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API const & molecular_system
	// ) const override;

	/// @brief Given the current molecular system, generate the annotated region selection.
	/// @details Pure virtual function.
	virtual
	AnnotatedRegionSelectionCSP
	generate_annotated_region_selection(
		masala::core_api::auto_generated_api::molecular_system::MolecularSystem_API const & molecular_system
	) const = 0;

}; // class AnnotatedRegionSelector

} // namespace annotated_region_selectors
} // namespace atom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_atom_selectors_annotated_region_selectors_AnnotatedRegionSelector_hh