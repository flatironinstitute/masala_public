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

/// @file src/core_api/base_classes/selectors/Selector.fwd.hh
/// @brief Forward declarations for a pure virtual base class for Selectors.
/// @details Selectors select something (atoms, residues, etc.).
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_Selector_fwd_hh
#define Masala_src_core_api_base_classes_selectors_Selector_fwd_hh

#include <memory> // For std::shared_ptr

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {

	class Selector;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	using SelectorSP = std::shared_ptr< Selector >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	using SelectorCSP = std::shared_ptr< Selector const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	using SelectorWP = std::weak_ptr< Selector >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	using SelectorCWP = std::weak_ptr< Selector const >;

} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namesapce masala

#endif //Masala_src_core_api_base_classes_selectors_Selector_fwd_hh