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

/// @file src/core_api/base_classes/selectors/atom_selectors/AtomSelector.fwd.hh
/// @brief Forward declarations for a pure virtual base class for AtomSelectors.
/// @details AtomSelectors select atoms in a molecular system based on some rule.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_fwd_hh
#define Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace atom_selectors {

	class AtomSelector;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using AtomSelectorSP = MASALA_SHARED_POINTER< AtomSelector >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using AtomSelectorCSP = MASALA_SHARED_POINTER< AtomSelector const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using AtomSelectorWP = MASALA_WEAK_POINTER< AtomSelector >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using AtomSelectorCWP = MASALA_WEAK_POINTER< AtomSelector const >;

} // namespace atom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_fwd_hh