/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/core_api/base_classes/selectors/atom_selector/AtomSelector.fwd.hh
/// @brief Forward declarations for a pure virtual base class for AtomSelectors.
/// @details AtomSelectors select something atoms in a pose based on some rule.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_atom_selector_AtomSelector_fwd_hh
#define Masala_src_core_api_base_classes_selectors_atom_selector_AtomSelector_fwd_hh

#include <memory> // For std::shared_ptr

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace atom_selectors {

	class AtomSelector;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a std::shared_ptr for objects of that class.
	using AtomSelectorSP = std::shared_ptr< AtomSelector >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a std::shared_ptr for const objects of that class.
	using AtomSelectorCSP = std::shared_ptr< AtomSelector const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a std::weak_ptr for objects of that class.
	using AtomSelectorWP = std::weak_ptr< AtomSelector >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a std::weak_ptr for const objects of that class.
	using AtomSelectorCWP = std::weak_ptr< AtomSelector const >;

} // namespace atom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namesapce masala

#endif // Masala_src_core_api_base_classes_selectors_atom_selector_AtomSelector_fwd_hh