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

/// @file src/core_api/base_classes/selectors/degree_of_freedom_selectors/DegreeOfFreedomSelector.hh
/// @brief Header for a pure virtual base class for DegreeOfFreedomSelectors.
/// @details DegreeOfFreedomSelectors select degrees of freedom in a pose.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_degree_of_freedom_selectors_DegreeOfFreedomSelector_hh
#define Masala_src_core_api_base_classes_selectors_degree_of_freedom_selectors_DegreeOfFreedomSelector_hh

// Parent class:
#include <core_api/base_classes/selectors/Selector.hh>

// Forward declarations:
#include <core_api/base_classes/selectors/degree_of_freedom_selectors/DegreeOfFreedomSelector.fwd.hh>

// Core headers:
#include <core/selection/Selection.fwd.hh>

// Core API headers:
#include <core_api/base_classes/selectors/degree_of_freedom_selectors/DegreeOfFreedomSelection.fwd.hh>
#include <core_api/auto_generated_api/pose/MolecularSystem_API.fwd.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace degree_of_freedom_selectors {

/// @brief A pure virtual base class for DegreeOfFreedomSelectors.
/// @details DegreeOfFreedomSelectors select atoms in a pose based on annotated regions.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class DegreeOfFreedomSelector : public masala::core_api::base_classes::selectors::Selector {

public:

	/// @brief Default constructor.
	DegreeOfFreedomSelector() = default;

	/// @brief Copy constructor.
	DegreeOfFreedomSelector( DegreeOfFreedomSelector const & ) = default;

	/// @brief Destructor.
	~DegreeOfFreedomSelector() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	// /// @brief Given the current pose, generate the selection.
	// /// @details Calls generate_degree_of_freedom_selection(), which must be implemented
	// /// by derived classes.
	// core::selection::SelectionCSP
	// generate_selection(
	// 	core_api::auto_generated_api::pose::MolecularSystem_API const & pose
	// ) const override;

	/// @brief Given the current pose, generate the annotated region selection.
	/// @details Pure virtual function.
	virtual
	DegreeOfFreedomSelectionCSP
	generate_degree_of_freedom_selection(
		core_api::auto_generated_api::pose::MolecularSystem_API const & pose
	) const = 0;

}; // class DegreeOfFreedomSelector

} // namespace degree_of_freedom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_degree_of_freedom_selectors_DegreeOfFreedomSelector_hh