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

/// @file src/core_api/base_classes/selectors/degree_of_freedom_selectors/DegreeOfFreedomSelection.fwd.hh
/// @brief Header for a pure virtual base class for DegreeOfFreedomSelections.
/// @details DegreeOfFreedomSelections are generated by DegreeOfFreedomSelectors, and provide a list of a
/// degrees of freedom in a molecular system.  They are dependent on the current MolecularSystem.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_degree_of_freedom_selectors_DegreeOfFreedomSelection_hh
#define Masala_src_core_api_base_classes_selectors_degree_of_freedom_selectors_DegreeOfFreedomSelection_hh

// Parent class:
#include <core/selection/Selection.hh>

// Forward declarations:
#include <core_api/base_classes/selectors/degree_of_freedom_selectors/DegreeOfFreedomSelection.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace degree_of_freedom_selectors {

/// @brief A pure virtual base class for DegreeOfFreedomSelections.
/// @details DegreeOfFreedomSelections are generated by DegreeOfFreedomSelectors, and provide a list of a
/// subset of atoms to select based on annotated regions.  They are dependent on the current MolecularSystem.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class DegreeOfFreedomSelection : public masala::core::selection::Selection {

public:

	/// @brief Default constructor.
	DegreeOfFreedomSelection() = default;

	/// @brief Copy constructor.
	DegreeOfFreedomSelection( DegreeOfFreedomSelection const & ) = default;

	/// @brief Destructor.
	~DegreeOfFreedomSelection() override = default;

}; // class DegreeOfFreedomSelection

} // namespace degree_of_freedom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_DegreeOfFreedomSelection_hh