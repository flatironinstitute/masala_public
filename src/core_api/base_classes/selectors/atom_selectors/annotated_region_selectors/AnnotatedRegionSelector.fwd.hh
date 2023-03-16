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

/// @file src/core_api/base_classes/selectors/atom_selectors/annotated_region_selectors/AnnotatedRegionSelector.fwd.hh
/// @brief Forward declarations for a pure virtual base class for AnnotatedRegionSelectors.
/// @details AnnotatedRegionSelectors select atoms in a molecular system based on annotated regions.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_atom_selectors_annotated_region_selectors_AnnotatedRegionSelector_fwd_hh
#define Masala_src_core_api_base_classes_selectors_atom_selectors_annotated_region_selectors_AnnotatedRegionSelector_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace atom_selectors {
namespace annotated_region_selectors {

	class AnnotatedRegionSelector;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using AnnotatedRegionSelectorSP = MASALA_SHARED_POINTER< AnnotatedRegionSelector >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using AnnotatedRegionSelectorCSP = MASALA_SHARED_POINTER< AnnotatedRegionSelector const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using AnnotatedRegionSelectorWP = MASALA_WEAK_POINTER< AnnotatedRegionSelector >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using AnnotatedRegionSelectorCWP = MASALA_WEAK_POINTER< AnnotatedRegionSelector const >;

} // namespace annotated_region_selectors
} // namespace atom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_atom_selectors_annotated_region_selectors_AnnotatedRegionSelector_fwd_hh